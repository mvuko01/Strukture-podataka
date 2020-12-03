#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<time.h>

typedef struct cvor* Position;

struct cvor {
	int El;
	Position Next;
};

int Ispisi(Position p)
{
	while (p != NULL) {
		printf("%d ", p->El);
		p = p->Next;
	}
	return 0;
}

int push(Position p)
{
	Position q = NULL;
	int x;

	q = (Position)malloc(sizeof(struct cvor));
	if (q == NULL)
	{
		printf("Neuspjela alokacija memorije");
		return -1;
	}

	srand(time);
	x = 10 + rand() % 100;
	
	q->Next = p->Next;
	p->Next = q;

	return 0;
}

int pop(Position p)
{
	Position temp;

	temp = p->Next;
	p->Next = temp->Next;
	free(temp);

	return 0;
}

int StaviURed(Position p)
{
	Position q = NULL;
	int x;

	q = (Position)malloc(sizeof(struct cvor));
	if (q == NULL)
	{
		printf("Neuspjela alokacija memorije");
		return -1;
	}

	srand(time);
	x = 10 + rand() % 100;
	q->El = x;
	
	q->Next = p->Next;
	p->Next = q;

	return 0;

}

int MakniIzReda(Position p)
{
	Position temp;

	while (p->Next->Next != NULL)
	{
		p = p->Next;

	}

	temp = p->Next;
	p->Next = temp->Next;
	free(temp);

	return 0;
}

int main()
{
	

	struct cvor Head_stog;
	struct cvor Head_red;

	Head_stog.Next = NULL;
	Head_red.Next = NULL;

	push(&Head_stog);
	push(&Head_stog);
	push(&Head_stog);
	pop(&Head_stog);

	StaviURed(&Head_red);
	StaviURed(&Head_red);
	StaviURed(&Head_red);
	MakniIzReda(Head_red.Next);
	Ispisi(Head_red.Next);

}
