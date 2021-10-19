#include<stdio.h>
#include<stdlib.h>
#define MAX 80

typedef struct{
    char ime[MAX];
    char prezime[MAX];
    int bodovi[5];


}_student;
void ispis(_student *);
float apsolutniProsjek(_student *);
float relativniProsjek(_student *):


int main()
{
    int br=0, i, j;
    _student *stud;
    FILE *fp;

    fp = fopen("studenti.txt","r");
    if(fp==NULL){ 
        printf("Greška pri otvaranju datoteke!");
        exit(1);
    }

    while(!feof(fp)){
        if(fgetc(fp) == '\n') {
            br++; 

        }
    }
     stud = (_student *) malloc(br * sizeof(_student));
     rewind(fp);
     for(i=0;i<br;i++){
         fscanf(fp," %c %c %d", stud[i].ime, stud[i].prezime, &stud[i].bodovi[j])
         ispis(stud[i]);
         apsolutniProsjek(stud[i]);

     }   

    

    return 0;
}

void ispis(_student* s)
{

    printf("%c %c %s",s->ime, s->preizme, s->bodovi);

}
float apsolutniProsjek(_student *s)
{
    int i, zbroj = 0;
    for(i=0;i<brojac;i++){
        zbroj +=s->bod[i];
    }

    return (float)zbroj/5;
}

