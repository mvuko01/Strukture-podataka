#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_IME 50

typedef struct osoba* pozicija;

struct osoba {
	char ime[MAX_IME];
	char prezime[MAX_IME];
	int god_rodenja;
	pozicija next;


};

int UnosP(int x, char im[], char prez[], pozicija p)
{
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(struct osoba));
	if (q == NULL)
		return -1;

	q->god_rodenja = x;
	strcpy(q->ime, im);
	strcpy(q->prezime, prez);

	q->next = p->next;
	p->next = q;

	return 0;
}

int Ispisi(pozicija p)
{
	while (p != NULL) {
		printf("%s %s %d.\n", p->ime, p->prezime, p->god_rodenja);
		p = p->next;
	}

	return 0;
}

int UnosK(int x, char im[], char prez[], pozicija p)
{	
	pozicija q = NULL;

	q = (pozicija)malloc(sizeof(struct osoba));
	if (q == NULL)
		return -1;

	q->god_rodenja = x;
	strcpy(q->ime, im);
	strcpy(q->prezime, prez);

	while (p->next != NULL)
		p = p->next;

	q->next = p->next;
	p->next = q;

	return 0;


}

pozicija Pronadi(char prez[], pozicija p)
{
	while (p != NULL && (strcmp(p->prezime, prez)))
		p = p->next;
		

	return p;
}

int Obrisi(char prez[], pozicija p)
{
	pozicija q;
	q = Pronadi(prez, p->next);

	if (q == NULL)
		printf("Nema tog elementa!");
	else
	{
		while (p->next != q)
			p = p->next;

		p->next = q->next;

		free(q);
	}
	
	return 0;
}

int main()
{
	struct osoba Head;
	Head.next = NULL;
	pozicija q;

	UnosP(2000, "Ana", "Anic", &Head);
	UnosK(2002, "Ivo", "Ivic", &Head);
	UnosP(2100, "Hrvoje", "Horvat", &Head);
	UnosP(1312, "Luka", "Marin", &Head);
	UnosK(2100, "Ante", "Antic", &Head);
	
	// Pronadi("Ivvo", Head.next);
	//printf("%s %s %d.\n", q->ime, q->prezime, q->god_rodenja);
	Ispisi(Head.next);
	Obrisi("Marin", &Head);
	puts("\n\n");
	Ispisi(Head.next);
	puts("\n\n");
	UnosK(2100, "TTTT", "LLL", &Head);
	UnosP(2000, "lili", "vivi", &Head);
	Ispisi(Head.next);
	return 0;
}