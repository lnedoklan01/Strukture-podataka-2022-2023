#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (50)

struct _Osoba;
typedef struct _Osoba* Pozicija;
typedef struct _Osoba{
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int godina_rodenja;
	Pozicija Next;
}Osoba;

int UnosP(char* ime, char* prezime, int godina_rodenja, Pozicija P);
void UnosOsobe(char* ime, char* prezime, int* godina_rodenja);
void Ispis(Pozicija);
void IspisUDat(Pozicija);
void UpisIzDat(Pozicija);
int UnosK(char* ime, char* prezime, int godina_rodenja, Pozicija p);
int UnosNakon(char* ime, char* prezime, int godina_rodenja, Pozicija p);
int Sortiraj(Pozicija Head);
Pozicija Trazi(char*, Pozicija);
Pozicija TraziPret(char* ime, char* prezime, int godina_rodenja, Pozicija P);

int main()
{
	Osoba Head;
	Head.Next = NULL;
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int godina_rodenja;
	int provjera;
	char trazeno_prezime[MAX_SIZE];
	Pozicija rezultat;

	UpisIzDat(&Head);
	Ispis(Head.Next);
	UnosOsobe(ime, prezime, &godina_rodenja);
	provjera = UnosP(ime, prezime, godina_rodenja, &Head);
	UnosOsobe(ime, prezime, &godina_rodenja);
	provjera = UnosP(ime, prezime, godina_rodenja, &Head);
	UnosOsobe(ime, prezime, &godina_rodenja);
	provjera = UnosK(ime, prezime, godina_rodenja, &Head);
	Ispis(Head.Next);
	scanf("%s", trazeno_prezime);
	rezultat=Trazi(trazeno_prezime, &Head);
	printf("%s %s %d\n", rezultat->ime, rezultat->prezime, rezultat->godina_rodenja);
	provjera = Brisi(ime, prezime, godina_rodenja, &Head);
	Ispis(Head.Next);
	scanf("%s %s %d", ime, prezime, &godina_rodenja);
	provjera = UnosNakon(ime, prezime, godina_rodenja,trazeno_prezime,&Head);
	Ispis(Head.Next);
	scanf("%s", trazeno_prezime);
	scanf("%s %s %d", ime, prezime, &godina_rodenja);
	provjera = UnosPrije(ime, prezime, godina_rodenja, trazeno_prezime, &Head);
	Ispis(Head.Next);
	provjera = Sortiraj(&Head);
	IspisUDat(Head.Next);

}
int UnosP(char *ime,char *prezime, int godina_rodenja, Pozicija p)
{
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(Osoba));
	strcpy(q->ime, ime);
	strcpy(q->prezime,prezime);
	q->godina_rodenja = godina_rodenja;
	q->Next = p->Next;
	p->Next = q;
	return 0;
}
void UnosOsobe(char* ime, char* prezime, int* godina_rodenja)
{
	printf("Unesi ime: \n");
	scanf("%s", ime);
	printf("Unesi prezime: \n");
	scanf("%s", prezime);
	printf("Unesi godinu: \n");
	scanf("%d", godina_rodenja);
}
void Ispis(Pozicija p)
{
	while (p != NULL)
	{
		printf("%s %s %d\n", p->ime, p->prezime, p->godina_rodenja);
		p = p->Next;
	}
	return;
}
void IspisUDat(Pozicija p)
{
	FILE* izl=fopen("studenti.txt", "w");
	while (p != NULL)
	{
		fprintf(izl, "%s %s %d\n", p->ime, p->prezime, p->godina_rodenja);
		p = p->Next;
	}
	return;
}
void UpisIzDat(Pozicija Head)
{
	FILE* ulaz = fopen("studenti.txt", "r");
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int godina_rodenja;
	do {
		Pozicija p = (Pozicija)malloc(sizeof(Osoba));
		fscanf(ulaz, "%s %s %d\n", ime, prezime, &godina_rodenja);
		UnosK(ime, prezime, godina_rodenja, Head);
	} while (feof(ulaz) == 0);

	return;
}
int UnosK(char* ime, char* prezime, int godina_rodenja, Pozicija p)
{
	Pozicija q;
	while (p->Next != NULL)
	{
		p = p->Next;
	}
	q = (Pozicija)malloc(sizeof(Osoba));
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->godina_rodenja = godina_rodenja;
	p->Next=q;
	q->Next = NULL;
	return 0;
}
Pozicija Trazi(char* prezime, Pozicija P)
{
	while (P != NULL && strcmp(P->prezime, prezime))
	{
		P = P->Next;
	}
	return P;
}
Pozicija TraziPret( char* prezime, Pozicija P)
{
	Pozicija prev;
	prev = P;
	P = P->Next;
	while (P != 0 && strcmp(P->prezime, prezime))
	{
		prev = prev->Next;
		P = P->Next;
	}
	if(P=NULL)
	{
		return NULL;
	}
	else
	{
		return prev;
	}
}
int Brisi(char* ime, char* prezime, int godina_rodenja, Pozicija p)
{
	Pozicija prev, temp;
	prev = TraziPret(ime,prezime,godina_rodenja, p);
	if (NULL == prev)
	{
		printf("Nema ga");
		return -1;
	}
	else
	{
		temp = prev->Next;
		prev->Next = temp->Next;
		free(temp);
	}
}
int UnosNakon(char* ime, char* prezime, int godina_rodenja, char *prezime_prije,Pozicija Head)
{
	Pozicija q, p;
	q = (Pozicija)malloc(sizeof(Osoba));
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->godina_rodenja = godina_rodenja;
	p = Trazi(prezime_prije, Head);
	q->Next = p->Next;
	p->Next = q;
	return -1;
}
int UnosPrije(char* ime, char* prezime, int godina_rodenja, char* prezime_nakon, Pozicija Head)
{
	Pozicija q, p;
	q = (Pozicija)malloc(sizeof(Osoba));
	strcpy(q->ime, ime);
	strcpy(q->prezime, prezime);
	q->godina_rodenja = godina_rodenja;
	p = TraziPret(prezime_nakon, Head);
	q->Next = p->Next;
	p->Next = q;
	return -1;
}
int Sortiraj(Pozicija Head)
{
	int zamjena=0;
	Pozicija tren=Head->Next, prosli=Head, iduci=Head->Next->Next;
	do
	{
		zamjena = 0;
		tren = Head->Next;
		prosli = Head;
		iduci = Head->Next->Next;
		while (tren->Next != NULL) {
			if (strcmp(tren->prezime, iduci->prezime) > 0)
			{
				prosli->Next = iduci;
				tren->Next = iduci->Next;
				iduci->Next = tren;
				prosli = iduci;
				iduci = tren->Next;
				zamjena = 1;
			}
			else {
				prosli = tren;
				tren = tren->Next;
				iduci = tren->Next;
			}
		}
	} while (zamjena);
}

