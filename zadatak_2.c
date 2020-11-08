#define _CRT_SECURE_NO_WARNINGS
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
int DodajIzad(char prez[],int x, char novoime[], char novoprezime[], pozicija p)
{
	pozicija q;

	p = Pronadi(prez, p->next);
	if (p == NULL) {
		printf("\nNema trazenog elementa!");
		return 0;
	}
	else {
		q = (pozicija)malloc(sizeof(struct osoba));
		q->god_rodenja = x;
		strcpy(q->ime, novoime);
		strcpy(q->prezime, novoprezime);
	
		q->next = p->next;
		p->next = q;
		return 0;
	}


}

int DodajIspred(char prez[], int x, char novoime[], char novoprezime[], pozicija p)
{
	pozicija q, f;

	q = Pronadi(prez, p->next);
	if (q == NULL) {
		printf("\nNema trazenog elementa!");
		return 0;
	}
	else
	{
		while (p->next != q)
			p = p->next;

		f = (pozicija)malloc(sizeof(struct osoba));
		f->god_rodenja = x;
		strcpy(f->ime, novoime);
		strcpy(f->prezime, novoprezime);

		f->next = p->next;
		p->next = f;
		return 0;
	}
}
int ObrisiSve(pozicija p)
{
	
	pozicija temp;

<<<<<<< HEAD
int DodajIzad(char prez[], int x, char novoime[], char novoprezime[], pozicija p)
{
	pozicija q;

	p = Pronadi(prez, p->next);
	if (p == NULL) {
		printf("\nNema trazenog elementa!");
		return 0;
	}
	else {
		q = (pozicija)malloc(sizeof(struct osoba));
		q->god_rodenja = x;
		strcpy(q->ime, novoime);
		strcpy(q->prezime, novoprezime);

		q->next = p->next;
		p->next = q;
		return 0;
	}


}

int DodajIspred(char prez[], int x, char novoime[], char novoprezime[], pozicija p)
{
	pozicija q, f;

	q = Pronadi(prez, p->next);
	if (q == NULL) {
		printf("\nNema trazenog elementa!");
		return 0;
	}
	else
	{
		while (p->next != q)
			p = p->next;

		f = (pozicija)malloc(sizeof(struct osoba));
		f->god_rodenja = x;
		strcpy(f->ime, novoime);
		strcpy(f->prezime, novoprezime);

		f->next = p->next;
		p->next = f;
		return 0;
	}
}

int ObrisiSve(pozicija p)
{
	
	pozicija temp;

=======
>>>>>>> 951f1444737bbd97897c642de75f188c0cf3cf28
	while (p->next != NULL)
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
		
	}
	return 0;
}

int UpisDatoteka(pozicija p, FILE* f)
{
	fputs("IME\tPREZIME\t    GODINA RODENJA\n", f);
	while (p->next != NULL)
	{
		p = p->next;
		fprintf(f, "%s\t%s\t\t%d.\n", p->ime, p->prezime, p->god_rodenja);

	}
	return 0;

}

int UcitajDatoteka(pozicija p, FILE* f)
{
	int br = 0, i;
	char str[50];
	char first[50], last[50];
	int year;

	while (!feof(f))
	{
		fgets(str, 50, f);
		br++;

	}
	rewind(f);

	for (i = 0; i < br; i++)
	{
		fscanf(f, "%s %s %d", first, last, &year);
		UnosK(year, first, last, p);
	}

	return 0;
}

int Sortiraj(pozicija p)
{
	pozicija end = NULL, j, prev_j, temp;

	while (p->next != end)
	{
		prev_j = p;
		j = p->next;
		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prev_j = j;
			j = j->next;

		}
		end = j;

	}
	return 0;


}
<<<<<<< HEAD

=======
>>>>>>> 951f1444737bbd97897c642de75f188c0cf3cf28
int main()
{
	struct osoba Head;
	Head.next = NULL;
	FILE* fo = NULL;
	FILE* fp = NULL;
	//pozicija q;

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
	Sortiraj(&Head);
	puts("\n\n");
	Ispisi(Head.next);

	fo = fopen("Popis.txt", "w");
	fp = fopen("citat.txt", "r");
	if (fo == NULL || fp == NULL)
	{
		printf("Datoteka nije otvorena!");
		return -1;
	}
	
	UpisDatoteka(&Head, fo);
	//puts("----------------");
	//ObrisiSve(&Head);
	//Ispisi(Head.next);
	
	fclose(fo);
	ObrisiSve(&Head);
	//UcitajDatoteka(&Head, fp);
	//Ispisi(Head.next);
	fclose(fp);

	return 0;
}
