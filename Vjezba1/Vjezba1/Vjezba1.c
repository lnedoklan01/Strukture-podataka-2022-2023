#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
typedef struct
{
    char ime[50];
    char prezime[50];
    int bodovi;
    float relativni;
}_student;

int BrojStudenata(char*);

int main()
{
    FILE* ulz = NULL;
    int br = 0;
    int i;
    char buffer[MAX_LINE];
    int max;
    _student* studenti = NULL;
    int br_stud = BrojStudenata("studenti.txt");
    studenti = (_student*)malloc(br_stud * sizeof(_student));
    ulz = fopen("studenti.txt", "r");
    if (ulz == NULL)
    {
        printf("Datoteka se nije otvorila\n");
        return -1;
    }
    for (i = 0;i < br_stud;i++)
    {
        fscanf(ulz, " %s %s %d ", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
    }
    max = studenti[0].bodovi;
    for (i = 0;i < br_stud;i++)
    {
        if (studenti[i].bodovi > max)
        {
            max = studenti[i].bodovi;
        }
    }
    for (i = 0;i < br_stud;i++)
    {
        printf("%s %s %d %f\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, ((float)studenti[i].bodovi) / max * 100);
    }
}
int BrojStudenata(char* imeDatoteke)
{
    FILE* ulz = NULL;
    char buffer[MAX_LINE];
    int br = 0;
    ulz = fopen(imeDatoteke, "r");
    if (ulz == NULL)
    {
        printf("Datoteka se nije otvorila\n");
        return -1;
    }
    while (!feof(ulz))
    {
        fgets(buffer, MAX_LINE, ulz);
        br++;
    }
    fclose(ulz);
    return br;
}




