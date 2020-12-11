#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 10

typedef struct Stog* Position;

struct Stog {
	int El;
	Position Next;
};

int postfixRezultat(Position p, FILE* f)
{
	char c[MAX];
	Position q = NULL, temp = NULL;;

	while (!feof(f))
	{
		fscanf(f, "%s", c);
		
		
		if (c[0] == '+' || c[0] == '-' || c[0] == '*')
		{
			switch (c[0]) {
			case '+':
				temp = p->Next;
				temp->Next->El = temp->Next->El + temp->El;
				p->Next = temp->Next;
				free(temp);
				break;

			case '-':
				temp = p->Next;
				temp->Next->El = temp->Next->El - temp->El;
				p->Next = temp->Next;
				free(temp);
				break;

			case '*':
				temp = p->Next;
				temp->Next->El = temp->Next->El * temp->El;
				p->Next = temp->Next;
				free(temp);
				break;

			}
		}	
		else 
		{

			q = (Position)malloc(sizeof(struct Stog));
			if (q == NULL)
			{
				printf("Neuspjesna alokacija memorije.");
				return -1;
			}

			(q->El) = atoi(c);
			q->Next = p->Next;
			p->Next = q;


		}



	}
	printf("Rezultat postfix izraza je: %d", p->Next->El);
	fclose(f);
	return 0;
	
}

int Ispisi(Position p)
{
	while (p != NULL)
	{
		printf("%d", p->El);
		p = p->Next;
	}
	return 0;
}

int ObrisiSve(Position p)
{
	Position temp;
	while (p->Next != NULL)
	{
		temp = p->Next;
		p->Next = temp->Next;
		free(temp);
	}
	return 0;
}

int main()
{
	FILE* f_read;
	

	struct Stog Head;
	Head.Next = NULL;

	f_read = fopen("postfix.txt", "r");
	if (f_read == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	
	postfixRezultat(&Head, f_read);
	ObrisiSve(&Head);
	
}