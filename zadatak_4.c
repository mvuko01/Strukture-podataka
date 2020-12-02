#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct polinom* Position;

struct polinom {
	int koef;
	int eks;
	Position next;

};

/*int UnesiIzDatoteke(FILE *f, Position p)
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
}*/

int UnesiIzDatoteke(FILE* f, Position p)
{
	Position q = NULL;
	Position start = p;

	while (!feof(f))
	{
		

		q = (Position)malloc(sizeof(struct polinom));
		if (q == NULL)
		{
			printf("Greska pri alokaciji memorije.");
			return -1;
		}

		fscanf(f, "%d %d", &(q->koef), &(q->eks));

		while (p->next != NULL && q->eks > p->next->eks)
		{
			p = p->next;
		}
		
		q->next = p->next;
		p->next = q;
		p = start;

	}
	return 0;
}

int ZbrojiPolinome(Position p, Position q, Position r) //p i q - polinomi koje zbrajamo, r - polinom dobiven zbrajanjem
{
	Position s = NULL;
	Position temp = NULL;
	
	while (p->next != NULL && q->next != NULL)
	{
		s = (Position)malloc(sizeof(struct polinom));
		if (s == NULL)
		{
			printf("Greska pri alokaciji memorije.");
			return -1;
		}
		s->next = NULL;

		if (p->next->eks < q->next->eks)
		{
			s->eks = p->next->eks;
			s->koef = p->next->koef;
			p = p->next;
		}
		else if (p->next->eks > q->next->eks)
		{
			s->eks = q->next->eks;
			s->koef = q->next->koef;
			q = q->next;
		}
		else
		{
			s->eks = q->next->eks;
			s->koef = q->next->koef + p->next->koef;
			p = p->next;
			q = q->next;
		}
		r->next = s;
		r = s;


	}
	if (p->next == NULL)
		temp = q->next;
	else
		temp = p->next;

	while (temp != NULL)
	{
		Position s = NULL;
		s = (Position)malloc(sizeof(struct polinom));
		if (s == NULL)
		{
			printf("Greska pri alokaciji memorije.");
			return -1;
		}
		s->next = NULL;

		s->eks = temp->eks;
		s->koef = temp->koef;
		r->next = s;
		r = s;

		temp = temp->next;

	}
		

	return 0;
}


/*int ZbrojiPolinome(Position p, Position q, Position r) //p i q - polinomi koje zbrajamo, r - polinom dobiven zbrajanjem
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
}*/


int Pomnozi(Position p, Position q, Position r)
{

	Position s = NULL;
	
	Position start_q;
	struct polinom P;

	p = p->next;
	q = q->next;
	
	start_q = q;
	
	s = (Position)malloc(sizeof(struct polinom));
	if (s == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return -1;
	}
	s->next = NULL;
	P.next = s;
	
	

	while (p != NULL)
	{
		while (q != NULL)
		{

			s->eks = p->eks + q->eks;
			s->koef = (p->koef) * (q->koef);
			

			
			ZbrojiPolinome(&P, r, r);
			q = q->next;
			
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
	struct polinom Umnozak;

	Umnozak.next = NULL;
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
	ZbrojiPolinome(&Head_1, &Head_2, &Zbroj);
	Pomnozi(&Head_1, &Head_2, &Umnozak);
	puts("\n\n\n");
	Ispisi(Zbroj.next);
	puts("\n\n\n");
	Ispisi(Umnozak.next);

	ObrisiSve(&Head_1);
	ObrisiSve(&Head_2);
	ObrisiSve(&Zbroj);
	
	
	return 0;
}