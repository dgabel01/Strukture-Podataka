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
    pgr next;

}grad;


struct drzava;
typedef struct drzava* pdr;

typedef struct drzava{
    char ime[MAX];
    pgr Grad;
    pdr l;
    pdr r;

}drzava;



pdr dodajDrzavu(pdr p, char* ime, char* datoteka);
int dodajGradove(pgr p, char* datoteka);
int ispisiDrzave(pdr p);
int ispisiGradove(pgr p);
int usporedbaGradova(pgr p, pgr q);
int Trazi(pdr p, char* ime, int stanovnici);
pdr traziDrzavu(pdr p, char* ime);




int main()
{
    pdr root = NULL;
    FILE* fp = NULL;
    char drzava[MAX];
    char datotekagrad[MAX];
    char kordrzava[MAX];
    int brojst = 0;

    fp= fopen("drzave.txt", "r");
    if(fp == NULL)
    {
        printf("Greška pri otvaranju datoteke!\n");
        return 0;
    }
      while(!feof(fp))
    {
        fscanf(fp, "%s %s", drzava, datotekagrad);
        root = dodajDrzavu(root, drzava, datotekagrad);
    }
    fclose(fp);
    ispisiDrzave(root);

    printf("Ime drzave :\n ");
    scanf("%s", kordrzava);
    printf("Broj stanovnika:\n");
    scanf("%d", &brojst);
    Trazi(root, drzava, brojst);

    return 0;
}

pdr dodajDrzavu(pdr p, char* ime, char* datoteka)    
{
    pdr q = NULL;
    pgr tmp = NULL;
    if(p == NULL)
    {
        q = (pdr)malloc(sizeof(drzava));
        if(q == NULL)
        {
            printf("Greška pri alokaciji memorije!\n");
            return NULL;
        }
        strcpy(q->ime, ime);

        tmp = (pgr)malloc(sizeof(grad));
        if(q == NULL)
        {
            printf("Greška pri alokaciji memorije!\n");
            return NULL;
        }
        strcpy(tmp->ime, "");
        tmp->brojstan= 0;
        tmp->next = NULL;
        q->Grad = tmp;

        dodajGradove(q->Grad, datoteka);
        q->l = NULL;
        q->r = NULL;

        return q;
    }
    else if(strcmp(p->ime, ime) > 0)
        p->l = dodajDrzavu(p->l, ime, datoteka);
    else if(strcmp(p->ime, ime) < 0)
        p->r = dodajDrzavu(p->r, ime, datoteka);
    return p;
}



int dodajGradove(pgr p, char* datoteka)
{
    pgr q = NULL;
    FILE* fp = NULL;
    char ime[MAX];
    int stan = 0;
    pgr prev = p;
    pgr poc = p;

    fp = fopen(datoteka, "r");
    if(fp == NULL)
    {
        printf("Greška pri otvaranju datoteke!\n");
        return -1;
    }

    while(!feof(fp))
    {
        prev = poc;
        p = poc;
        fscanf(fp, "%s %d", ime, &stan);
        q = (pgr)malloc(sizeof(grad));
        if(q == NULL)
        {
            printf("Greška pri alokaciji!\n");
            return -1;
        }
        strcpy(q->ime, ime);
        q->brojstan = stan;
        while(p != NULL)
        {
            if(p->next == NULL)
            {
                q->next = p->next;
                p->next = q;
                break;
            }
            if(usporedbaGradova(q, prev->next) == 1)
            {
                q->next = prev->next;
                prev->next = q;
                break;
            }
            prev = p;
            p = p->next;
        }
    }
    fclose(fp);
    return 0;
}

int ispisiDrzave(pdr p)
{
    if(p == NULL)
        return 0;
    ispisiDrzave(p->l);
    printf("%s\n", p->ime);
    ispisiGradove(p->Grad->next);
    ispisiDrzave(p->r);
    return 0;
}

int ispisiGradove(pgr p)
{ 
     while(p != NULL)
    {
        printf("%s %d\n", p->ime, p->brojstan);
        p = p->next;
    } 

    return 0;
}


int usporedbaGradova(pgr p, pgr q)
{
    if(p->brojstan > q->brojstan)
        return 1;
    else if(p->brojstan < q->brojstan)
        return -1;
    else
    {
        if(strcmp(p->ime, q->ime) > 0)
            return 1;
        else if(strcmp(p->ime, q->ime) < 0)
            return -1;
    }

    return 0;
}


pdr traziDrzavu(pdr p, char* ime)
{
    if(p == NULL)
        return NULL;
    else if(strcmp(ime, p->ime) == 0)
        return p;
    else if(strcmp(ime, p->ime) < 0)
        return traziDrzavu(p->l, ime);
    else if(strcmp(ime, p->ime) > 0)
        return traziDrzavu(p->r, ime);

    else return NULL;        
}


int trazi(pdr p, char* ime, int stanovnici)  // h = tmp
{
    pdr drzava = NULL;
    pgr tmp = NULL;
    int x = 0;

    drzava = traziDrzavu(p, ime);
    if(drzava == NULL)
    {
        printf("Drzava nije u datoteci!\n");
        return 0;
    }
    tmp = drzava->Grad;

    if(tmp == NULL)
    {
        printf("Nema nijedan grad u toj drzavi!\n");
        return 0;
    }
    tmp = tmp->next;
    while(tmp != NULL)
    {
        if(tmp->brojstan >= stanovnici)
        {
            printf("%s\n", tmp->ime);
            x = 1;
        }
        else
            break;
        tmp = tmp->next;
    }
    if(x == 0)
        printf("Nema nijedan takav grad!\n");
        
    return 0;
}
