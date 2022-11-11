#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct _polinom;
typedef struct _polinom* pozicija;
typedef struct  _polinom
{
	int eksponent;
	int koeficijent;
	pozicija next;
}polinom;

pozicija inicijalizacija(pozicija);
int procitajIzDatoteke(pozicija, pozicija, char*);
int DodajSortiraniEksponent(pozicija , int , int);
int ispis(pozicija);
int zbrojiPolinome(pozicija, pozicija, pozicija);
int PomnoziPolinome(pozicija , pozicija , pozicija );

int main()
{
	char imeDat[40] = { 0 };
	pozicija head1 = NULL, head2 = NULL, headZbr = NULL, headUmn = NULL; 

	head1 = inicijalizacija(head1);
	head2 = inicijalizacija(head2);
	headZbr = inicijalizacija(headZbr);
	headUmn = inicijalizacija(headUmn);

	printf("Unesi ime datoteke iz koje ces citati polinome: ");
	scanf(" %s", imeDat);

	procitajIzDatoteke(head1, head2, imeDat);
	ispis(head1);
	ispis(head2);
	zbrojiPolinome(head1, head2, headZbr);
	ispis(headZbr);
	PomnoziPolinome(head1, head2, headUmn);
	ispis(headUmn);
	return 0;
}

pozicija inicijalizacija(pozicija p)
{
	p = (pozicija)malloc(sizeof(polinom));

	if (!p)
	{
		printf("Greska u inicijalizaciji!\n");
		return NULL;
	}

	p->eksponent = 0;
	p->koeficijent = 0;
	p->next = NULL;

	return p;
}

int procitajIzDatoteke(pozicija p1, pozicija p2, char* imeDat)
{
	
	char buffer[1024] = { 0 };
	char* pok = buffer;
	int n = 0, koef = 0, eksp = 0;

	FILE* fp = NULL;
	fp = fopen(imeDat, "r");

	if (!fp)
	{
		printf("Greska u ucitavanju datoteke!\n");
		return -1;
	}

		fgets(buffer, 1024, fp);
		pok=&buffer[0];

		while (strlen(pok) > 0)
		{
			sscanf(pok, "%d %d %n", &koef, &eksp, &n);
			DodajSortiraniEksponent(p1, koef, eksp);
			pok += n;
		}
		


		fgets(buffer, 1024, fp);
		pok = &buffer[0];
		while (strlen(pok) > 0)
		{
			sscanf(pok, "%d %d %n", &koef, &eksp, &n);
			DodajSortiraniEksponent(p2, koef, eksp);
			pok += n;
		}

	fclose(fp);

	return 0;
}
int DodajSortiraniEksponent(pozicija Head, int koef, int eksp)
{
	
	pozicija temp = Head;
	pozicija noviEksp = NULL;
		noviEksp = (pozicija)malloc(sizeof(polinom));
	if (koef == 0)
	{
		return EXIT_SUCCESS;
	}
	noviEksp->koeficijent = koef;
	noviEksp->eksponent = eksp;
	noviEksp->next = NULL;
	while (temp)
	{
		if (temp->next == NULL)
		{
			temp->next = noviEksp;
			return EXIT_SUCCESS;
		}
		if (temp->next->eksponent < eksp)
		{
			noviEksp->next = temp->next;
			temp->next = noviEksp;
			return EXIT_SUCCESS;
		}
		if (temp->next->eksponent == eksp)
		{
			
			if (temp->next->koeficijent == -koef)
			{
				pozicija pom = NULL;
				pom = temp->next->next;
				free(temp->next);
				temp->next = pom;
				return EXIT_SUCCESS;
			}
			else
			{
				
				temp->next->koeficijent += koef;
				return EXIT_SUCCESS;
			}
		}
		temp = temp->next;
	}
}
int ispis(pozicija head)
{
	
	pozicija temp = head->next;
	while (temp)
	{
		if (temp->koeficijent > 0)
		{
			printf("+");
		}
		printf("%dx^(%d)", temp->koeficijent, temp->eksponent);
		temp = temp->next;
	}
	printf("\n");
}
int zbrojiPolinome(pozicija p1, pozicija p2, pozicija pz)
{
	pozicija temp1 = p1->next;
	pozicija temp2 = p2->next;
	pozicija tempz = pz;
	while (temp1 && temp2)
	{
		if (temp1->eksponent == temp2->eksponent)
		{
			DodajSortiraniEksponent(pz, (temp1->koeficijent + temp2->koeficijent), temp1->eksponent);
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else if (temp1->eksponent > temp2->eksponent || temp2 == NULL)
		{
			DodajSortiraniEksponent(pz, temp1->koeficijent, temp1->eksponent);
			temp1 = temp1->next;
		}
		else
		{
			DodajSortiraniEksponent(pz, temp2->koeficijent, temp2->eksponent);
			temp2 = temp2->next;
		}
	}
	if (temp2 == NULL)
	{
		while (temp1)
		{
			DodajSortiraniEksponent(pz, temp1->koeficijent, temp1->eksponent);
			temp1 = temp1->next;
		}
	}
	else
	{
		while (temp2)
		{
			DodajSortiraniEksponent(pz, temp2->koeficijent, temp2->eksponent);
			temp2 = temp2->next;
		}
	}

}
int PomnoziPolinome(pozicija p1, pozicija p2, pozicija pz)
{
	pozicija temp1 = p1->next;
	pozicija temp2 = p2->next;
	pozicija tempz = pz;
	while (temp1)
	{
		while (temp2)
		{
			DodajSortiraniEksponent(pz, temp1->koeficijent * temp2->koeficijent, temp1->eksponent + temp2->eksponent);
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
	}
} 

