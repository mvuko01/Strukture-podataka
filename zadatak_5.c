#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct cvor* Pozicija;

struct cvor {
	int El;
	Pozicija next;
};

int UnosIzDatoteke(FILE *f, Pozicija p)
{
	Pozicija q = NULL;
	Pozicija start = p;
	do{	
		p = start;
		q = (Pozicija)malloc(sizeof(struct cvor));
		if (q == NULL)
			return -1;

		fscanf(f, "%d", &(q->El));

		while (p->next != NULL && q->El > p->next->El)
		{
			p = p->next;
		}
		q->next = p->next;
		p->next = q;

		
	} while (fgetc(f) != '\n');

	return 0;
}

int Unija(Pozicija p, Pozicija q, Pozicija r)
{
	p = p->next;
	q = q->next;
	Pozicija temp = NULL;

	while (p != NULL && q != NULL)
	{
		if (p->El < q->El)
		{
			temp = (Pozicija)malloc(sizeof(struct cvor));
			if (temp == NULL)
				return -1;
			temp->El = p->El;
			temp->next = r->next;
			r->next = temp;

			p = p->next;
			r = r->next;
		}
		else if (p->El > q->El)
		{
			temp = (Pozicija)malloc(sizeof(struct cvor));
			if (temp == NULL)
				return -1;
			temp->El = q->El;
			temp->next = r->next;
			r->next = temp;

			q = q->next;
			r = r->next;
		}
		else if (p->El == q->El)
		{
			temp = (Pozicija)malloc(sizeof(struct cvor));
			if (temp == NULL)
				return -1;
			temp->El = p->El;
			temp->next = r->next;
			r->next = temp;

			q = q->next;
			p = p->next;
			r = r->next;
		}


	}
	if (p == NULL )
	{
		while (q != NULL)
		{
			temp = (Pozicija)malloc(sizeof(struct cvor));
			if (temp == NULL)
				return -1;

			temp->El = q->El;
			temp->next = r->next;
			r->next = temp;

			r = r->next;
			q = q->next;
		}


	}
	if (q == NULL)
	{
		while (p != NULL)
		{
			temp = (Pozicija)malloc(sizeof(struct cvor));
			if (temp == NULL)
				return -1;

			temp->El = p->El;
			temp->next = r->next;
			r->next = temp;

			r = r->next;
			p = p->next;
		}


	}
	return 0;
}

int Presjek(Pozicija p, Pozicija q, Pozicija r)
{
	p = p->next;
	q = q->next;
	Pozicija temp;

	while (p != NULL && q != NULL)
	{
		if (p->El == q->El)
		{
			temp = (Pozicija)malloc(sizeof(struct cvor));
			if (temp == NULL)
				return -1;

			temp->El = p->El;
			temp->next = r->next;
			r->next = temp;

			p = p->next;
			q = q->next;
			r = r->next;
		}
		else if (p->El < q->El)
		{
			p = p->next;

		}
		else if (p->El > q->El)
		{
			q = q->next;
		}

	}
	return 0;
}

int Ispisi(Pozicija p)
{
	while (p != NULL) {
		printf("%d\n", p->El);
		p = p->next;
	}

	return 0;
}

int ObrisiSve(Pozicija p)
{
	Pozicija q;

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
	struct cvor Head_1;
	struct cvor Head_2;
	struct cvor Uni;
	struct cvor Presj;

	FILE *f1 ;
	FILE *f2 ;

	f1 = fopen("lista_1.txt", "r");
	f2 = fopen("lista_2.txt", "r");
	if (f1 == NULL || f2 == NULL)
	{
		puts("Greska pri otvaranju datoteka");
		return -1;
	}

	Head_1.next = NULL;
	Head_2.next = NULL;
	Uni.next = NULL;
	Presj.next = NULL;

	UnosIzDatoteke(f1, &Head_1);
	UnosIzDatoteke(f2, &Head_2);
	fclose(f1);
	fclose(f2);

	Ispisi(Head_1.next);
	puts("\n");
	Ispisi(Head_2.next);

	Unija(&Head_1, &Head_2, &Uni);
	puts("\n");
	Ispisi(Uni.next);

	Presjek(&Head_1, &Head_2, &Presj);
	puts("\n");
	Ispisi(Presj.next);
	
	ObrisiSve(&Head_1);
	ObrisiSve(&Head_2);
	ObrisiSve(&Uni);
	ObrisiSve(&Presj);
	
	return 0;
}
