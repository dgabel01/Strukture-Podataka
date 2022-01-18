#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef ERROR
#define ERROR 1
#endif

struct elem;
typedef struct elem* position;
typedef struct elem {
	int koef;
	int pot;
	position next;
}element;

int OtvoriDatoteku(position P);
int SortiraniUnos(int koef, int pot, position P);
int Ispis(position P);
int Zbrajanje(position prvi, position drugi, position suma);
int Mnozenje(position prvi, position drugi, position umn);


int main()
{
	element poli1, poli2, poliumn, polizbr;

	poli1.next = NULL;
	poli2.next = NULL;
	poliumn.next = NULL;
	polizbr.next = NULL;
	

	printf("Unesite ime datoteke u kojem se nalazi prvi polinom (sa .txt nastavkom)\n");

	if (OtvoriDatoteku(&poli1) == ERROR)
	{
		perror("error reading poli1\n");
		return ERROR;
	}

	printf("Unesite ime datoteke u kojem se nalazi drugi polinom (sa .txt nastavkom)\n");

	if (OtvoriDatoteku(&poli2) == ERROR)
	{
		perror("error reading poli2\n");
		return ERROR;
	}

	
	printf("Prvi polinom\n");
	if (Ispis(&poli1) == ERROR)
		return ERROR;

	printf("Drugi polinom\n");
		if (Ispis(&poli2) == ERROR)
			return ERROR;

	
	if (Zbrajanje(poli1.next, poli2.next, &polizbr) == ERROR)
	{
			perror("error with f Zbrajanje\n");
			return ERROR;
	}

	printf("Zbroj polinoma\n");
	if (Ispis(&polizbr) == ERROR)
		return ERROR;

	
	
	if (Mnozenje(poli1.next, poli2.next, &poliumn) == ERROR)
	{
		perror("error with f Mnozenje\n");
		return ERROR;
	}

	printf("Umnozak polinoma\n");
	if (Ispis(&poliumn) == ERROR)
		return ERROR;



		return SUCCESS;

}
int OtvoriDatoteku(position P)
{
	FILE* f;
	char* filename;
	int koef = 0, pot = 0;

	filename = (char*)malloc(30 * sizeof(char));
	scanf("%s", filename);

	f = fopen(filename, "r");

	while (!feof(f))
	{
		fscanf(f,"%d %d", &koef, &pot);
		if (SortiraniUnos(koef, pot, P) == ERROR)
		{
			perror("Greska sortiranog unosa!\n");
			return ERROR;
		}

	}

	return SUCCESS;

}
int SortiraniUnos(int koef, int pot, position P)
{
	position NewNode = NULL;

	NewNode = (position)malloc(sizeof(element));

	NewNode->koef = koef;
	NewNode->pot = pot;
	NewNode->next = NULL;

	while ((P->next != NULL) && (P->next->pot > pot))
	{
		P = P->next;
	}

	if ((P->next != NULL) && (P->next->pot == pot))
	{
		P->next->koef = P->next->koef + koef;

		return SUCCESS;
	}

	NewNode->next = P->next;
	P->next = NewNode;

	return SUCCESS;


}
int Ispis(position P)
{	
	while (P->next != NULL)
	{
		printf("\t%d ^ %d\n", P->next->koef, P->next->pot);

		P = P->next;
	}

	return SUCCESS;

}
int Zbrajanje(position prvi, position drugi, position suma)
{
	int koef = 0, pot = 0;

	while (prvi != NULL)
	{
		koef = prvi->koef;
		pot = prvi->pot;
		if ((SortiraniUnos(koef, pot, suma) == ERROR))
			perror("Greska sortiranog unosa!");
		prvi = prvi->next;
	}

	while (drugi != NULL)
	{
		koef = drugi->koef;
		pot = drugi->pot;
		if ((SortiraniUnos(koef, pot, suma) == ERROR))
			perror("Greska sortiranog unosa!");
		drugi = drugi->next;
	}

	return SUCCESS;

}
int Mnozenje(position prvi, position drugi , position umn)
{
	position temp;
	int koef = 0, pot = 0;

	while (prvi != NULL)
	{
		temp = drugi;

		while (temp != NULL)
		{
			koef = prvi->koef * temp->koef;
			pot = prvi->pot + temp->pot;
			if ((SortiraniUnos(koef, pot, umn) == ERROR))
				perror("Greska sortiranog unosa!");
			
			temp = temp->next;
		}

		prvi = prvi->next;


	}

	return SUCCESS;



}

   

   
