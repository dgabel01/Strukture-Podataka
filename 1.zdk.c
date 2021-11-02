
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include<string.h>


typedef struct {
    char* ime;
    char* prez;
    int bod;

}_stud;

int BrojiRetke();
int UzmiIzDatoteke(int, _stud*);
int Ispis(int, _stud*);

int main()
{
    int br = 0;
    _stud* student = NULL;

    br = BrojiRetke();
    student = (_stud*)malloc(br * sizeof(_stud));

    UzmiIzDatoteke(br, student);
    Ispis(br, student);


    return 0;
}

int BrojiRetke()
{
    char c = 0;
    int br = 0;
    FILE* fp = NULL;

    fp = fopen("studenti.txt","r");

    if (fp = NULL)
        printf("Greška pri otvaranju datoteke!");

    do {
        c = getc(fp);
        if (c == '\n')
            br++;

    } while (feof(fp) == 0);

        fclose(fp);

    return br;

    
}

int UzmiIzDatoteke(int br, _stud* student)
{
    int i = 0;
    char temp1[30] = { 0 };
    char temp2[30] = { 0 };
    FILE* fp = NULL;

    fp = fopen("studenti.txt", "r");

    if (fp = NULL)
        printf("Greška pri otvaranju datoteke!");

    for (i = 0; i < br; i++)
    {
        fscanf(fp, "%d %s %s", &student[i].bod, temp1, temp2);

        student[i].ime = (char*)malloc(strlen(temp1) * sizeof(char));
        if (student[i].ime == NULL)
            printf("Greška sa imenom");
        student[i].prez = (char*)malloc(strlen(temp2) * sizeof(char));
        if (student[i].prez == NULL)
            printf("Greška sa prezimenom");

        strcpy(student[i].ime, temp1);
        strcpy(student[i].prez, temp2);
    }

    fclose(fp);
    return 0;
}

int Ispis(int br, _stud* student)
{
    int i = 0;
    FILE* fp = NULL;

    fp = fopen("studenti.txt", "r");

    if (fp == NULL)
        printf("Greška pri otvaranju datoteke");

    printf("\tIme     Prezime\ REL Bodovi\t\t\ APS Bodovi\n ");
    for (i = 0; i < br; i++)
        printf(" %10s %10s \t %.2f percent \t\t %d \n", student[i].ime, student[i].prez, (float)((student[i].bod / (float)50) * 100), student[i].bod);

    fclose(fp);

    return 0;

}
