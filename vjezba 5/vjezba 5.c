#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct element;
typedef struct element* pozicija;
typedef struct element
{
	double clan;
	pozicija next;
} Element;

void Provjera(char*, char*);
void Push(pozicija, int);
int Pop(pozicija);
void rjesenje(pozicija, char*, int);
int brisiSve(Pozicija);

int main(){
    
    int br;
    Element head;
    head.next= NULL;
    char ime_dat[256];
    char* buffer = NULL; 
    buffer = (char*)malloc(1000 * sizeof(char)); 
    
    printf("koju datoteku zelite otvoriti: ");
    scanf("%s", ime_dat);
    
    Provjera(&ime_dat, buffer);
    rjesenje(&head, buffer, br);
    int brisiSve(pozicija);

    return 0;
}

void Provjera(char* ime_dat, char* buffer)
{
    FILE* fp = NULL;
	fp = fopen(ime_dat, "r");
    if(!fp)
    {
        printf("neuspjesno otvoreno");
        return 1;
    }
    printf("postfix iz datoteke:");
    
   fgets(buffer,1000,fp); 


    fclose(fp);

}
void Push(pozicija p, int a) 
{ 
pozicija q = NULL; 
 
while (p->next != NULL) 
p = p->next; 
 
q = (pozicija)malloc(sizeof(Element)); 
q->clan = a; 
q->next = p->next; 
p->next = q; 
} 

int Pop(pozicija p) 
{ 
pozicija temp; 
int broj; 
temp = p; 
 
while (temp->next != NULL) 
{ 
p = temp; 
temp = temp->next; 
} 
broj = temp->clan; 
p->next = temp->next; 
free(temp); 
 
return broj; 
} 

void rjesenje(pozicija head, char* buffer, int b)
{
    int broj, rezultat=0, brojac=0;
    int i, j;
    char postfix;
    
    while (rezultat <= b) 
{ 
i = 0; 
j = 0; 
i=sscanf(buffer, "%d%n", &broj,&brojac); 
 
if (i == 1) 
{ 
printf(" %d",broj); 
Push(head, broj); 
} 
else 
{ 
j = sscanf(buffer, " %c%n", &postfix, &brojac); 
if (j == 1) 
{ 
printf(" %c", postfix); 
int clan_1 = Pop(head); 
int clan_2 = Pop(head); 
 
switch (postfix) 
{ 
case'+':
Push(head, clan_2 + clan_1);
break; 

case'-':
Push(head, clan_2 - clan_1);
break; 

case'*':
Push(head, clan_2 * clan_1);
break; 

case'/':
Push(head, clan_2 / clan_1); 
break; 

} 
} 
} 
buffer += brojac; 
rezultat += brojac; 
} 
printf("\nrjesenje je:%d\n", Pop(head)); 
} 
int brisiSve(pozicija p)
{
    	pozicija temp = NULL;
	
	while (p != NULL) 
	{
		temp = p;
		p = p->next;
		free(temp);
	}
}
    
    
   