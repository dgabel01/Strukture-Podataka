/*
Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
	- dinamièki dodaje novi element na pocetak liste,
	- ispisuje listu,
	- dinamicki dodaje novi element na kraj liste,
	- pronalazi element u listi (po prezimenu),
	- briše odreðeni element iz liste,

U zadatku se ne smiju koristiti globalne varijable.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct osoba;

typedef struct osoba * Position;

struct osoba
{
	char ime[10];
	char prezime[10];
	int g_r;
	Position Next;
};

void Insert(Position);
void Print(Position);
Position FindLast(Position);
Position Find(Position);
Position FindPrev(Position);
void Delete (Position);
void Sort(Position);



void main ()
{
	struct osoba head, *q;
	char izbor = 0;

	head.Next = NULL;
	while(izbor != 'K' && izbor != 'k')
	{
		printf("\nUnesi:");
		printf("\n\t0 - unos elementa na pocetak");
		printf("\n\t1 - ispis niza");
		printf("\n\t2 - unos elementa na kraj");
		printf("\n\t3 - trazenje elementa u listi po prezimenu");
		printf("\n\t4 - brisanje");

		printf("\n\tk - kraj\n\n\t");

		scanf(" %c", &izbor);

		switch (izbor)
		{
		case '0':
			Insert(&head);
			break;
		case '1':
			Print(head.Next);
			break;
		case '2':
			q = FindLast(&head);
			Insert(q);
			break;
		case '3':
			q = Find(head.Next);
			if( NULL == q)
				printf("\n Osoba ne postoji u listi!");
			else
				printf("\n\tOsoba je: %s %s, %d", q->ime, q->prezime, q->g_r);
			break;
		case '4':
			Delete(&head);
			break;

			break;
		case 'k':
		case 'K':
			printf("\nKraj programa!!!\n");
			break;
		default:
			printf("\nKrivi unos!!!\n");
		}
	}
}

void Insert(Position P)
{
	Position temp;

	temp = (Position)malloc(sizeof(struct osoba));
	printf("\nUnesite podatke o osobi: ");
	scanf( " %s %s %d", temp->ime, temp->prezime, &temp->g_r);

	temp->Next = P->Next;
	P->Next = temp;
}

void Print(Position P)
{
	if(NULL == P)
		printf("\nLista je prazna!!\n");
	else
	{
		printf("\nU listi se nalaze:");
		while(P!=NULL)
		{
			printf("\n\t %s %s %d", P->ime, P->prezime, P->g_r);
			P=P->Next;
		}
	}


}

Position FindLast(Position P)
{
	while(NULL != P->Next)
		P = P->Next;
	return P;
}


Position Find(Position P)
{
	char prez[10];


	printf("\nUnesi prezime osobe koju zelis pronaci: ");
	scanf(" %s", prez);

	while(P != NULL && strcmpi(P->prezime, prez)!= 0)
		P = P->Next;

	return P;
}

Position FindPrev(Position P)
{
	char prez[10];

	if(NULL == P->Next)
		P = NULL;
	else
	{
		printf("\nUnesi prezime osobe koju zelis pronaci: ");
		scanf(" %s", prez);


		while(strcmpi(P->Next->prezime, prez)!= 0 && P->Next->Next != NULL)
			P = P->Next;

		if(strcmpi(P->Next->prezime, prez)!= 0)
			P = NULL;
	}

	return P;
}

void Delete (Position P)
{
	Position prev;

	prev = FindPrev(P);

	if (NULL != prev)
	{
		P = prev->Next;
		prev->Next = P->Next;
		printf("\n Osoba %s %s %d je obrisana!", P->ime, P->prezime, P->g_r);
		free(P);
	}
	else
		printf("\n Osoba ne postoji u listi!");
}

void Sort(Position P)
{
	//Za sortiranje se koristi bubble sort
	Position i, j, prev_j, temp, end;

	end = NULL;

	i = P;

	while (i->Next != end)
	{
		prev_j = i;
		j = i->Next;
		while(j->Next!= end)
		{
			if(strcmp(j->prezime, j->Next->prezime)>0)
			{
				temp = j->Next;
				prev_j->Next = temp;
				j->Next = temp->Next;
				temp->Next = j;

				j= temp;
			}

			prev_j=j;
			j = j->Next;
		}
		end = j;
	}

}




