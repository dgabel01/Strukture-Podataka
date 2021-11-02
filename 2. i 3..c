#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifndef SUCSESS
#define SUCSESS 0
#endif

#ifndef ERROR
#define ERROR 1
#endif

struct student;
typedef struct student* pozicija;
typedef struct student {
	char* ime;
	char* prez;
	int god;
	pozicija next;
}stud;

int ReadFile(pozicija);
int Insert(pozicija, char*, char*, int);
int PrintWhole(pozicija);
int AddUpfront(pozicija);
int AddBack(pozicija);
int Delete(pozicija);
int Find(pozicija);
int AddUpfrontSomeone(pozicija);
int AddBackSomeone(pozicija);
int Sort(pozicija);
int PutInFile(pozicija);
int ReadNewFile(pozicija);

int main()
{
	stud head;
	head.next = NULL;
	int izbor = 0;


	if (ReadFile(&head) == ERROR)
		return ERROR;

	PrintWhole(head.next);

	fflush(stdin);

	printf("Upisite broj zeljene naredbe:\n");
	printf("1)Dodaj element na pocetak\n2)Ispisi listu\n3)Dodaj element na kraj liste\n4)Brisi element liste\n5)Nadji element iz liste\n6)Dodaj novi element ispred odre�enog elementa\n7)Dodaj novi element iza odre�enog elemnta\n8)Sortiraj listu po prezimenima\n9)Upisi listu u datoteku\n10)Ucitaj novu listu iz druge datoteke\n");
	printf("\n");
	scanf("%d", &izbor);
	printf("\n");
	switch (izbor)
	{
	case 1:

		if ((AddUpfront(&head) == SUCSESS))
		{
			printf("Vasa nova lista\n");
			PrintWhole(head.next);
		}
		else
		{
			perror("AddUpFront() ");
			return ERROR;
		}

		break;

	case 2:

		if ((PrintWhole(head.next) == SUCSESS))
		{
			printf("Ovo je vas registar\n");
		}
		else
		{
			perror("PrintWhole() ");
			return ERROR;
		}

		break;

	case 3:

		if ((AddBack(&head) == SUCSESS))
		{
			printf("Vasa nova lista\n");
			PrintWhole(head.next);
		}
		else
		{
			perror("AddBack() ");
			return ERROR;
		}
		break;

	case 4:

		if ((Delete(&head) == SUCSESS))
		{
			printf("Vasa nova lista\n");
			PrintWhole(head.next);
		}
		else
		{
			perror("Delete() ");
			return ERROR;
		}

		break;

	case 5:

		if ((Find(&head) == SUCSESS))
		{
			printf("Vasa nova lista\n");
			PrintWhole(head.next);
		}
		else
		{
			perror("AddBack() ");
			return ERROR;
		}

		break;

	case 6:

		if ((AddUpfrontSomeone(&head) == SUCSESS))
		{
			printf("Vasa nova lista\n");
			PrintWhole(head.next);
		}
		else
		{
			perror("AddUpfrontSomeone() ");
			return ERROR;
		}

		break;

	case 7:
		if ((AddBackSomeone(&head) == SUCSESS))
		{
			printf("Vasa nova lista\n");
			PrintWhole(head.next);
		}
		else
		{
			perror("AddBackSomeone() ");
			return ERROR;
		}
		break;
	case 8:
		if ((Sort(&head) == SUCSESS))
		{
			printf("Vasa nova lista\n");
			PrintWhole(head.next);
		}
		else
		{
			perror("Sort() ");
			return ERROR;
		}
		break;
	case 9:
		if ((PutInFile(&head) == SUCSESS))
		{
			printf("Vasa nova lista\n");
			PrintWhole(head.next);
		}
		else
		{
			perror("PutInFile() ");
			return ERROR;
		}
		break;
	case 10:
		if ((ReadNewFile(&head) == SUCSESS))
		{
			printf("Vasa nova lista\n");
			PrintWhole(head.next);
		}
		else
		{
			perror("ReadFile() ");
			return ERROR;
		}
		break;

	default:
		printf("Niste unjeli jedan od ponudenih brojeva,nista od odabira\n");
		break;
	}

	return SUCSESS;
}
int ReadFile(pozicija P)
{
	FILE* fp;
	char* buffime = NULL;
	char* buffprez = NULL;
	int buffgod = 0;
	char* filename = NULL;

	buffime = (char*)malloc(25 * sizeof(char));
	if (buffime == NULL)
		return ERROR;
	buffprez = (char*)malloc(25 * sizeof(char));
	if (buffprez == NULL)
		return ERROR;

	filename = (char*)malloc(25 * sizeof(char));
	if (filename == NULL)
		return ERROR;




	fp = fopen("studenti.txt", "r");

	if (fp == NULL)
		return ERROR;


	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d", buffime, buffprez, &buffgod);


		if ((Insert(P, buffime, buffprez, buffgod) == ERROR))
			return ERROR;

	}

	fclose(fp);

	return SUCSESS;

}
int Insert(pozicija P, char* name, char* surname, int yrs)
{
	pozicija NewNode = NULL;

	NewNode = (pozicija)malloc(sizeof(stud));
	if (NewNode == NULL)
		return ERROR;

	NewNode->ime = (char*)malloc(25 * sizeof(char));
	if (NewNode->ime == NULL)
		return ERROR;
	NewNode->prez = (char*)malloc(25 * sizeof(char));
	if (NewNode->prez == NULL)
		return ERROR;
	NewNode->next = NULL;

	strcpy(NewNode->ime, name);
	strcpy(NewNode->prez, surname);
	NewNode->god = yrs;

	while (P->next != NULL)
	{
		P = P->next;
	}


	NewNode->next = P->next;
	P->next = NewNode;

	return SUCSESS;
}
int PrintWhole(pozicija P)
{
	printf("\tIme\tPrezime\tGodiste \n");
	printf("\n");

	while (P != NULL) {

		printf("\t%s\t%s\t%d \n", P->ime, P->prez, P->god);

		P = P->next;

	}

	return SUCSESS;
}
int AddUpfront(pozicija P)
{
	pozicija NewNode = NULL;


	NewNode = (pozicija)malloc(sizeof(stud));
	if (NewNode == NULL)
		return ERROR;

	NewNode->ime = (char*)malloc(25 * sizeof(char));
	if (NewNode->ime == NULL)
		return ERROR;
	NewNode->prez = (char*)malloc(25 * sizeof(char));
	if (NewNode->prez == NULL)
		return ERROR;
	NewNode->next = NULL;

	printf("Unesite ime novog covjeka\n");
	scanf("%s", NewNode->ime);

	printf("Unesite prezime novog covjeka\n");
	scanf("%s", NewNode->prez);

	printf("Unesite godine novog covjeka\n");
	scanf("%d", &(NewNode->god));

	NewNode->next = P->next;
	P->next = NewNode;

	return SUCSESS;
}
int AddBack(pozicija P)
{
	pozicija NewNode = NULL;


	NewNode = (pozicija)malloc(sizeof(stud));
	if (NewNode == NULL)
		return ERROR;

	NewNode->ime = (char*)malloc(25 * sizeof(char));
	if (NewNode->ime == NULL)
		return ERROR;
	NewNode->prez = (char*)malloc(25 * sizeof(char));
	if (NewNode->prez == NULL)
		return ERROR;
	NewNode->next = NULL;

	printf("Unesite ime novog covjeka\n");
	scanf("%s", NewNode->ime);

	printf("Unesite prezime novog covjeka\n");
	scanf("%s", NewNode->prez);

	printf("Unesite godine novog covjeka\n");
	scanf("%d", &(NewNode->god));


	while (P->next != NULL)
	{
		P = P->next;
	}

	NewNode->next = P->next;
	P->next = NewNode;

	return SUCSESS;

}
int Delete(pozicija P)
{
	char* surname = NULL;
	pozicija temp = NULL;


	surname = (char*)malloc(sizeof(char) * 25);
	if (surname == NULL) return ERROR;

	printf("Unesi prezime covjeka kojeg zelis maknuti\n");
	scanf("%s", surname);

	while (P->next != NULL && strcmp(P->next->prez, surname) != 0)
	{
		P = P->next;
	}

	if (P->next != NULL)
	{
		temp = P->next;
		P->next = P->next->next;

		free(temp);
	}


	else
	{
		printf("Unjeli ste nepostojece prezime\n");
	}

	return SUCSESS;

}
int Find(pozicija P)
{
	char* surname;
	int br = 0;
	pozicija* FirstSame;


	surname = (char*)malloc(sizeof(char) * 20);
	if (surname == NULL) return ERROR;

	printf("Unesite prezime trazene osobe \n");
	scanf("%s", surname);

	P = P->next;

	while (P->next != NULL)
	{
		if (strcmp(P->prez, surname) == 0)
		{
			printf("%s %s %d\n", P->ime, P->prez, P->god);
			br++;
		}

		P = P->next;

	}

	if ((P->next == NULL) && br == 0)
	{
		printf("Nema unesenog prezimena koje ste trazili");
		return SUCSESS;
	}

	return SUCSESS;

}
int AddUpfrontSomeone(pozicija P)
{
	pozicija NewNode = NULL;
	char* covijek = NULL;


	NewNode = (pozicija)malloc(sizeof(stud));
	if (NewNode == NULL)
		return ERROR;

	NewNode->ime = (char*)malloc(25 * sizeof(char));
	if (NewNode->ime == NULL)
		return ERROR;
	NewNode->prez = (char*)malloc(25 * sizeof(char));
	if (NewNode->prez == NULL)
		return ERROR;
	NewNode->next = NULL;

	covijek = (char*)malloc(30 * sizeof(char));
	if (covijek == NULL)
		return ERROR;

	printf("Unesite ime novog covjeka\n");
	scanf("%s", NewNode->ime);

	printf("Unesite prezime novog covjeka\n");
	scanf("%s", NewNode->prez);

	printf("Unesite godine novog covjeka\n");
	scanf("%d", &(NewNode->god));

	printf("Unesite prezime covjeka ispred kojega zelite dodati novog covijeka\n");
	scanf("%s", covijek);

	while ((P->next) != NULL && (strcmp(covijek, P->next->prez) != 0))
	{
		P = P->next;
	}

	if (P->next == NULL)
		perror("AddUpfrontSomeone()");

	else
	{
		NewNode->next = P->next;
		P->next = NewNode;
	}

	return SUCSESS;

}
int AddBackSomeone(pozicija P)
{
	pozicija NewNode = NULL;
	char* covijek = NULL;


	NewNode = (pozicija)malloc(sizeof(stud));
	if (NewNode == NULL)
		return ERROR;

	NewNode->ime = (char*)malloc(25 * sizeof(char));
	if (NewNode->ime == NULL)
		return ERROR;
	NewNode->prez = (char*)malloc(25 * sizeof(char));
	if (NewNode->prez == NULL)
		return ERROR;
	NewNode->next = NULL;

	covijek = (char*)malloc(30 * sizeof(char));
	if (covijek == NULL)
		return ERROR;

	printf("Unesite ime novog covjeka\n");
	scanf("%s", NewNode->ime);

	printf("Unesite prezime novog covjeka\n");
	scanf("%s", NewNode->prez);

	printf("Unesite godine novog covjeka\n");
	scanf("%d", &(NewNode->god));

	printf("Unesite prezime covjeka iza kojega zelite dodati novog covijeka\n");
	scanf("%s", covijek);

	while ((P->next) != NULL && (strcmp(covijek, P->next->prez) != 0))
	{
		P = P->next;
	}

	if (P->next == NULL)
		perror("AddUpfrontSomeone()");

	else
	{
		NewNode->next = P->next->next;
		P->next->next = NewNode;
	}

	return SUCSESS;
}
int Sort(pozicija P)
{
	pozicija temp, now, bef, jeb;


	jeb = NULL;


	while (P->next != jeb)
	{
		bef = P;
		now = P->next;

		while (now->next != jeb)
		{
			if (strcmp(now->prez, now->next->prez) > 0)
			{
				temp = now->next;
				bef->next = temp;
				now->next = temp->next;
				temp->next = now;

				now = temp;

			}
			bef = now;
			now = now->next;

		}
		jeb = now;

	}

	return SUCSESS;

}
int PutInFile(pozicija P)
{
	FILE* fp;

	fp = fopen("izlaz.txt", "w");


	while (P->next != NULL)
	{
		fprintf(fp, "%s\t%s\t%d\n", P->next->ime, P->next->prez, P->next->god);

		P = P->next;
	}

	fclose(fp);


	return SUCSESS;

}
int ReadNewFile(pozicija P)
{
	FILE* fp;
	char* buffime = NULL;
	char* buffprez = NULL;
	int buffgod = 0;
	char* filename = NULL;
	pozicija temp = NULL;
	pozicija POC = NULL;

	POC = P;

	buffime = (char*)malloc(25 * sizeof(char));
	if (buffime == NULL)
		return ERROR;
	buffprez = (char*)malloc(25 * sizeof(char));
	if (buffprez == NULL)
		return ERROR;

	filename = (char*)malloc(25 * sizeof(char));
	if (filename == NULL)
		return ERROR;

	printf("Unesite ime nove datoteke sa .txt nastavkom\n");
	fflush(stdin);
	scanf("%s", filename);


	fp = fopen(filename, "r");

	if (fp == NULL)
		return ERROR;

	P = P->next;

	while (P->next != NULL)
	{
		temp = P;
		P = P->next;
		free(temp);


	}
	if (P->next == NULL)
	{
		temp = P;
		free(temp);
	}

	P = POC;

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d", buffime, buffprez, &buffgod);


		if ((Insert(P, buffime, buffprez, buffgod) == ERROR))
			return ERROR;

	}

	fclose(fp);

	return SUCSESS;


}