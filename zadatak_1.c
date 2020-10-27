#include<stdio.h>
#include<stdlib.h>
#define MAX_IME 50
#define MAX_BR_BODOVA 50

typedef struct{
	char ime[MAX_IME];
	char prezime[MAX_IME];
	int bodovi;

}Student;

int BrojRedaka(FILE* f)
{
	int br = 0;
	char str[50];
	while (!feof(f))
	{
		fgets(str, 50, f);
		br++;

	}
	printf("Broj redaka je %d.", br);
	rewind(f);
	return br;
}
int Ucitavanje(FILE* f, Student *s, int br)
{
	int i = 0;

	for (i = 0; i < br; i++) {
		fscanf(f,"%s %s %d", s[i].ime, s[i].prezime, &s[i].bodovi);
	}
	rewind(f);

	return 0;
}

int Ispisi(Student* s, int br)
{
	float rel = 0;
	int i = 0;

	for (i = 0; i < br; i++)
	{
		rel = 0;
		rel = (float)s[i].bodovi / MAX_BR_BODOVA * 100;
		printf("\nIme i prezime: %s %s \nBroj bodova: %d\nRelativan broj bodova: %f", s[i].ime, s[i].prezime, s[i].bodovi, rel);
		puts("\n");
	}

	return 0;

}

int main()
{
	FILE* fo;
	int br;
	Student* s = NULL;

	fo = fopen("datoteka.txt", "r");

	if (fo == NULL)
	{
		printf("Datoteka nije otvorena!");
		return -1;
	}

	br = BrojRedaka(fo);
	s = (Student*)malloc(br * sizeof(Student));

	if (s == NULL) {
		printf("Nije alocirana memorija");
		return -1;
	}
	Ucitavanje(fo, s, br);

	fclose(fo);
	Ispisi(s, br);
	free(s);

	return 0;
}