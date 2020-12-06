#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
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

int SlucajniBroj()
{
	

	int br_mog = 100 - 10 + 1;
	int nova_gr = RAND_MAX - (RAND_MAX % br_mog);
	int sl_br = rand();

	while (sl_br > nova_gr) //ako se broj nalazi u onom visku sta ti je u teci
		sl_br = rand();

	return sl_br % br_mog + 10;

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

	x = SlucajniBroj();
	q->El = x;
	
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

int pushR(Position p)
{
	Position q = NULL;
	int x;

	q = (Position)malloc(sizeof(struct cvor));
	if (q == NULL)
	{
		printf("Neuspjela alokacija memorije");
		return -1;
	}

	x = SlucajniBroj();
	q->El = x;
	
	q->Next = p->Next;
	p->Next = q;

	return 0;

}

int popR(Position p)
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
	
	srand((unsigned)time(NULL));
	struct cvor Head_stog;
	struct cvor Head_red;

	Head_stog.Next = NULL;
	Head_red.Next = NULL;

	push(&Head_stog);
	push(&Head_stog);
	push(&Head_stog);
	
	Ispisi(Head_stog.Next);
	pop(&Head_stog);
	printf("\n");
	Ispisi(Head_stog.Next);

	printf("\n\n");
	pushR(&Head_red);
	pushR(&Head_red);
	pushR(&Head_red);
	Ispisi(Head_red.Next);
	popR(Head_red.Next);
	printf("\n");
	Ispisi(Head_red.Next);

}
