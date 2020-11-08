#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct polinom* Position;

struct polinom {
	int koef;
	int eks;
	Position next;

};

int UnesiIzDatoteke(FILE *f, Position p)
{
	Position temp = NULL;
	Position start = p;

	do
	{
		p = start;
		temp = (Position)malloc(sizeof(struct polinom));
		if (temp == NULL)
			return -1;

		fscanf(f, "%d %d", &(temp->koef), &(temp->eks));

		
		while (p->next != NULL && temp->eks > p->next->eks)
		{
			p = p->next;
		}
		temp->next = p->next;
		p->next = temp;


	} while (fgetc(f) != '\n');


	return 0;
}
int ZbrojiPolinome(Position p, Position q, Position r) //p i q - polinomi koje zbrajamo, r - polinom dobiven zbrajanjem
{
	Position temp;
	
	while (p != NULL && q != NULL)
	{
		temp = (Position)malloc(sizeof(struct polinom));
		if (temp == NULL)
			return -1;

		if (p->eks < q->eks)
		{
			temp->eks = p->eks;
			temp->koef = p->koef;
			p = p->next;
			temp->next = r->next;
			r->next = temp;
			r = r->next;
		}
		else if (p->eks > q->eks)
		{
			temp->eks = q->eks;
			temp->koef = q->koef;
			q = q->next;
			temp->next = r->next;
			r->next = temp;
			r = r->next;
		}
		else
		{
			temp->eks = q->eks;
			temp->koef = p->koef + q->koef;
			q = q->next;
			p = p->next;
			temp->next = r->next;
			r->next = temp;
			r = r->next;

		}

	}
	if (q == NULL)
	{
		while (p != NULL)
		{
			temp = (Position)malloc(sizeof(struct polinom));
			if (temp == NULL)
				return -1;

			temp->eks = p->eks;
			temp->koef = p->koef;
			temp->next = r->next;
			r->next = temp;
			p = p->next;
			r = r->next;
		}


	}
	if (p == NULL)
	{
		while (q != NULL)
		{
			temp = (Position)malloc(sizeof(struct polinom));
			if (temp == NULL)
				return -1;

			temp->eks = q->eks;
			temp->koef = q->koef;
			temp->next = r->next;
			r->next = temp;
			q = q->next;
			r = r->next;
		}


	}

	return 0;
}

int Pomnozi(Position p, Position q, Position r)
{
	p = p->next;
	q = q->next;
	Position start_p = p;
	Position start_q = q;

	
	Position temp = NULL; 

	while (p != NULL)
	{
		while (q != NULL)
		{
			temp = (Position)malloc(sizeof(struct polinom));
			if (temp == NULL)
				return -1;

			temp->eks = p->eks + q->eks;
			temp->koef = (p->koef) * (q->koef);
			temp->next = NULL;

			q = q->next;
			ZbrojiPolinome(&temp, &r, &r);
		}
		q = start_q;
		p = p->next;



	}
	return 0;
}


int Ispisi(Position p)
{
	while (p != NULL) {
		printf("%d %d\n", p->koef, p->eks);
		p = p->next;
	}

	return 0;
}

int ObrisiSve(Position p)
{
	Position q;

	while (p->next != NULL)
	{
		q = p->next;
		p->next = p->next->next;
		free(q);
	}
	return 0;
}

int main()
{
	struct polinom Head_1;
	struct polinom Head_2;
	struct polinom Zbroj;

	Zbroj.next = NULL;
	Head_1.next = NULL;
	Head_2.next = NULL;

	FILE* f1, *f2;
	f1 = fopen("polinom1.txt", "r");
	f2 = fopen("polinom2.txt", "r");
	if (f1 == NULL || f2 == NULL)
	{
		printf("Greska pri otvaranju datoteke!");
		return -1;
	}

	UnesiIzDatoteke(f1, &Head_1);
	UnesiIzDatoteke(f2, &Head_2);
	fclose(f1);
	fclose(f2);

	Ispisi(Head_1.next);
	puts("\n\n\n");
	Ispisi(Head_2.next);
	//ZbrojiPolinome(Head_1.next, Head_2.next, &Zbroj);
	//Pomnozi(&Head_1, &Head_2, &Zbroj);
	puts("\n\n\n");
	Ispisi(Head_2.next);

	ObrisiSve(&Head_1);
	ObrisiSve(&Head_2);
	ObrisiSve(&Zbroj);
	
	
	return 0;
}