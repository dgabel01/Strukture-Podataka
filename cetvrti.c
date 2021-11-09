#define CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct polinom;
typedef struct polinom *pozicija;

typedef struct _pol
{
    int koef;
    int eksp;
    pozicija next;

}polinom;

int Unos1(pozicija);
int Unos2(pozicija);
int Ispis(pozicija);
int Zbroj(pozicija, pozicija, pozicija);
int Umnozak(pozicija, pozicija, pozicija);


int main()
{
    polinom prvi;
    polinom drugi;
    polinom zbroj;
    polinom umnozak;

    prvi.next = NULL;
    drugi.next = NULL;
    umnozak.next = NULL;
    zbroj.next = NULL;

    Unos1(&prvi);
    Unos2(&drugi);

    printf("Prvi polinom:");
    Ispis(prvi.next);
    printf("Drugi polinom:");
    Ispis(drugi.next);

    Zbroj(&prvi, &drugi, &zbroj);
    printf("Umnožak:");
    Ispis(zbroj.next);

    printf("Zbroj:");
    Umnozak(&prvi, &drugi, &umnozak);
    Ispis(umnozak.next);

    return 0;
}

int Ispis(pozicija p)
{
    while(p != NULL)
    {
        printf("Koeficijent polinoma: %d   Eksponent polinoma: %d", p->koef, p->eksp);
        p = p->next;
    }

    return 0;
}

int Unos1(pozicija p)
{
    FILE* fp = NULL;
    char* filename = NULL;

    filename = (char *)malloc(30* sizeof(char));
	
    printf("Unesite ime datoteke sa nastavkom .txt : ");
	scanf("%s", filename);

    fp = fopen(filename,"r");

    if(fp == NULL)
    {
        printf("Greška pri otvaranju datoteke!");
        return -1;
    }
    while(!feof(fp))
    {
        pozicija a = NULL;
        a = (pozcija)malloc(sizeof(polinom));
        if(a == NULL){
            printf("Greška pri alokaciji memorije");
            return -1;
        }

        pozicija prije, temp;
        temp = p->next;
        prije = p;
        fscanf(fp,"%d %d", &a->koef, &a->eksp);
        while(temp!= NULL && temp->eksp < a->eksp){
                prije = temp;
                temp = temp->next;

        }

        prije->next = a;
        if(temp!=NULL)
            a = a->next;
            else
            a->next = NULL;
    }

    return 0;
}

int Unos2(pozicija p)
{


    FILE* fp = NULL;
    char* filename = NULL;

    filename = (char *)malloc(30* sizeof(char));
	
    printf("Unesite ime datoteke sa nastavkom .txt : ");
	scanf("%s", filename);

    fp = fopen(filename,"r");

    if(fp == NULL)
    {
        printf("Greška pri otvaranju datoteke!");
        return -1;
    }
    while(!feof(fp))
    {
        pozicija a= NULL;
        a = (pozcija)malloc(sizeof(polinom));
        if(a == NULL){
            printf("Greška pri alokaciji memorije");
            return -1;
        }

        pozicija prije, temp;
        temp = p->next;
        prije = p;
        fscanf(fp,"%d %d", &a->koef, &a->eksp);
        while(temp!= NULL && temp->eksp < a->eksp){
                prije = temp;
                temp = temp->next;

        }

        prije->next = a;
        if(temp!=NULL)
            a = a->next;
            else
            a->next = NULL;
    }

    return 0;
}


int Zbroj(pozicija p, pozicija q, pozicija r)
{
    while (p->next != NULL && q->next != NULL)
	{
		pozicija a = NULL;
		a = (pozicija)malloc(sizeof(struct polinom));
		if (a == NULL)
		{
			printf("Greška pri alokaciji memeorije\n");
			return -1;
		}
		a->next = NULL;

		if (p->next->eksp < q->next->eksp)
		{
			a->eksp = p->next->eksp;
			a->koef = p->next->koef;
			p = p->next;
		}
		else if (p->next->eksp> q->next->eksp)
		{
			a->eksp = q->next->eksp;
			a->koef = q->next->koef;
			q = q->next;
		}
		else
		{
			a->eksp = p->next->eksp;
			a->koef =(p->next->koef + q->next->koef);
			p = p->next;
			q = q->next;
		}
		r->next = a;
		r = a;
	}
	pozicija temp;
	if (p->next == NULL)
		temp = q->next;
	else
		temp = p->next;
	while (temp != NULL)
	{
		pozicija a = NULL;
		a = (pozicija)malloc(sizeof(struct polinom));
		if (a== NULL)
		{
			printf("Greška pri alokaciji memorije\n");
			return -1;
		}
		a->next = NULL;
		a->eksp= temp->eksp;
		a->koef = temp->koef;
		r->next = a;
		r = a;
		temp = temp->next;
	}


    return 0;
}


int Umnozak(pozcija p, pozicija q, pozicija r)
{

    pozicija prvi = p->next;
	pozicija drugi = q->next;
    polinom P;
	pozicija a = NULL;
	a = (pozicija)malloc(sizeof(struct polinom));
	if (a == NULL)
	{
		printf("Greska pri alokaciji memorije!");
		return -1;
	}
	a->next = NULL;
	P.next = a;
	while (prvi != NULL)
	{
		drugi = q->next;
		while (drugi != NULL)
		{

			a->koeficijent = prvi->koeficijent * drugi->koeficijent;
			a->eksponent = prvi->eksponent + drugi->eksponent;

			Zbroj(&P, r, r);
			drugi = drugi->next;
		}
		prvi = prvi->next;
	}

    return 0;
}