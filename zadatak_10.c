#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct NodeTree* TreePointer;
typedef struct NodeStack* StackPointer;

struct NodeTree {
	char c[5];  //za viseznamenkaste brojeve
	TreePointer left;
	TreePointer right;

};

struct NodeStack {
	TreePointer TreePart;
	StackPointer next;
};

int OpenAndReadFile(FILE* f, char str[])
{
	f = fopen("postfix10zad.txt", "r");
	if (f == NULL){
		printf("Greska pri otvaranju datoteke!");
		return -1;
		
	}

	fgets(str, MAX, f);
	fclose(f);

	return 0;
}


int PushStack(TreePointer el, StackPointer Head_el) //vrh stoga je na pocetku
{
	StackPointer new_el = NULL;

	new_el = (StackPointer)malloc(sizeof(struct NodeStack));
	if (new_el == NULL)
	{
		printf("Neuspjesna alokacija memorije!");
		return -1;
	}

	new_el->TreePart = el;

	new_el->next = Head_el->next;
	Head_el->next = new_el;

	return 0;
}

TreePointer PopStack(StackPointer Head_el)
{
	TreePointer p;
	StackPointer temp;

	temp = Head_el->next;
	Head_el->next = temp->next;

	p = temp->TreePart;
	free(temp);

	return p;
}

TreePointer MakeTree(StackPointer Head_el, char str[])
{
	int i = 0, count = 0;
	char temp[10];
	char* d = str;
	int num_sym = NumberOfSymbols(str);
	TreePointer new_el;
	

	for (i = 0; i < num_sym ; i++)
	{
		d = d + count;
		sscanf(d, "%s", temp);
		count =  strlen(temp) + 1;

		switch (temp[0]) {
			case '+':
			case '-':
			case '*':
			case '/':
				new_el = (TreePointer)malloc(sizeof(struct NodeTree));
				strcpy(new_el->c, temp);
				new_el->right = PopStack(Head_el);
				new_el->left = PopStack(Head_el);
				PushStack(new_el, Head_el);
				break;
			default:
				new_el = (TreePointer)malloc(sizeof(struct NodeTree));
				strcpy(new_el->c, temp);
				new_el->left = NULL;
				new_el->right = NULL;
				PushStack(new_el, Head_el);
		}

	}
	return PopStack(Head_el);

}


TreePointer InOrderPrint(TreePointer current_pos, char str[])
{
	if (current_pos == NULL) {
		return NULL;
	}

	if (current_pos->c[0] == '+' || current_pos->c[0] == '-' || current_pos->c[0] == '*' || current_pos->c[0] == '/')
		strcat(str, "(");
	InOrderPrint(current_pos->left, str);
	strcat(str, current_pos->c);
	InOrderPrint(current_pos->right, str);
	if (current_pos->c[0] == '+' || current_pos->c[0] == '-' || current_pos->c[0] == '*' || current_pos->c[0] == '/')
		strcat(str, ")");

	

}

int OpenAndWriteInFile(FILE* f, char str[])
{
	f = fopen("Infix10zad.txt", "w");
	if (f == NULL)
	{
		printf("Neuspjesna alokacija memorije!");
		return -1;
	}

	fwrite(str, sizeof(str[0]), MAX , f);
	fclose(f);

	return 0;
}

int NumberOfSymbols(char str[]) 
{
	int i= 0, count=0;
	while (str[i] != '\0') 
	{
		if (str[i] == ' ')
			count++;		//broji razmake

		i++;
	}

	return count + 1;
}

int main(void)
{
	char in_str[MAX];
	char out_str[MAX] = {0};
	FILE* in_file = NULL;
	FILE* out_file = NULL;

	TreePointer root = NULL;

	struct NodeStack Head;
	Head.next = NULL;

	OpenAndReadFile(in_file, in_str);
	root = MakeTree(&Head, in_str);

	InOrderPrint(root, out_str);
	printf("%s", out_str);
	OpenAndWriteInFile(out_file, out_str);
	
	
	return 0;
}