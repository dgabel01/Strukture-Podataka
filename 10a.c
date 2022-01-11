#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 64

struct grad;
typedef struct grad* pgr;

typedef struct grad{
    char ime[MAX];
    int brojstan;
    pgr r;
    pgr l;

}grad;


struct drzava;
typedef struct drzava* pdr;

typedef struct drzava{
    char ime[MAX];
    pgr Grad;
    pdr next;

}drzava;

int dodajGrad(pgr p, char* datoteka);
pgr unosNovogGrada(pgr p, char* ime, int brstan);
int dodajDrzavu(pdr p, char* ime, char* datoteka);
int ispisiDrzave(pdr p);
int ispisiGradove(pgr p);
int nadiGrad(pgr p, int broj);
pdr nadiDrzavu(pdr p, char* ime);




int main()
{
    drzava head = {
        .ime = "",
        .Grad = NULL,
        .next = NULL
    };

    FILE* fp = NULL;
    char drzava[MAX];
    char datotekagrad[MAX];
    char kordrzava[MAX];
    pdr p = NULL;
    int brojst = 0;
    pgr tmp = NULL;

    fp = fopen("drzave.txt", "r");
    if(fp == NULL){
        printf("Greška pri otvaranju datoteke!\n");
        return 4;
    }
    while(!feof(fp)){
        fscanf(fp, "%s %s",drzava, datotekagrad);
        dodajDrzavu(&head, drzava, datotekagrad);
    }
    fclose(fp);
    ispisiDrzave(head.next);
    printf("Ime drzave:\n");
    scanf("%s", kordrzava);

    p = nadiDrzavu(head.next, kordrzava);
    if(p == NULL){
        printf("Unesena država nije u datoteci!\n");
        return 5;
    }
    printf("Unijeti broj stanovnika:\n");
    scanf("%d", &brojst);


    printf("Gradovi drzave %s sa vise od %d stanovnika :\n", p->ime, brojst);
    nadiGrad(p->Grad, brojst);
    
    return 0;
}


int dodajGrad(pgr p, char* datoteka)
{
    FILE* fp = NULL;
    char ime[MAX];
    int brstan = 0;


    fp = fopen(datoteka, "r");
    if(fp == NULL){
        printf("Greška pri otvaranju datoteke!\n");
        return 1;
    }

    while (!feof(fp))
    {
        fscanf(fp, "%s %d", ime, &brstan);
        p = unosNovogGrada(p, ime, brstan);
    }

    fclose(fp);
    return 0;
}


pgr unosNovogGrada(pgr p, char* ime, int brstan)
{
    pgr q = NULL;
    if(p == NULL)
    {
        q = (pgr)malloc(sizeof(grad));
        if(q == NULL)
        {
        printf("Greška pri alokaciji memorije!\n");
            return NULL;
        }
        strcpy(q->ime, ime);
        q->brojstan= brstan;
        q->r = NULL;
        q->l = NULL;
        return q;
    }
    if(brstan > p->brojstan)
        p->r = unosNovogGrada(p->r, ime, brstan);
    if(brstan < p->brojstan)
        p->l = unosNovogGrada(p->l, ime, brstan);
    if(brstan == p->brojstan)
    {
        if(strcmp(ime, p->ime) >= 0)
            p->r = unosNovogGrada(p->r, ime, brstan);
        else
            p->l = unosNovogGrada(p->l, ime, brstan);
    }

    return p;

}

int dodajDrzavu(pdr p, char* ime, char* datoteka)     
{

    pdr q = NULL;
    pdr prev = NULL;
    pgr tmp = NULL;
    q = (pdr)malloc(sizeof(drzava));
    if(q == NULL)
    {
        printf("Greška pri alokaciji memorije!\n");
        return 2;
    }
    strcpy(q->ime, ime);
    q->Grad = tmp;

    tmp = (pgr)malloc(sizeof(grad));
    if(tmp == NULL)
    {
        printf("Greška pri alokaciji memorije!\n");
        return 3;
    }
    strcpy(tmp->ime, "");
    tmp->brojstan= 0;
    tmp->r= NULL;
    tmp->l = NULL;
    q->Grad = tmp;
    dodajGrad(q->Grad, datoteka);

    prev = p;
    while(p != NULL)
    {
        if(p->next == NULL)
        {
            p->next = q;
            q->next = NULL;
            break;
        }
        if(strcmp(q->ime, prev->next->ime) < 0)
        {
            q->next = prev->next;
            prev->next = q;
            break;
        }
        p = p->next;
    }
    return 0;
}


int ispisiDrzave(pdr p)
{
    printf("Drzave:\n");
    while(p != NULL){
        printf("%s\n", p->ime);
        p = p->next;
    }

    return 0;
}

int ispisiGradove(pgr p)
{
    if(p == NULL){
        return 0;
    }
    ispisiGradove(p->l);
    printf("%s\n", p->ime);
    ispisiGradove(p->r);

    return 0;
}

int nadiGrad(pgr p, int broj)
{
    if(p == NULL){
        return 0;
    }
   nadiGrad(p->l, broj);
   if(p->brojstan >= broj){
        printf("%s %d\n", p->ime, p->brojstan);
        }
    nadiGrad(p->r, broj);
    return 0;
    
  
}


pdr nadiDrzavu(pdr p, char* ime)
{
    while(p != NULL)
    {
        if(strcmp(p->ime, ime) == 0){
            return p;
        }
        p = p->next;
    }
    return p;
}

