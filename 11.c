#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CHAR 30
#define MAX_TABLE 11

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef ERROR
#define ERROR 1
#endif

struct Student;
typedef struct Student* position;
typedef struct Student {
	char Ime[MAX_CHAR];
	char Prezime[MAX_CHAR];
	int MB;
	position next;
}Stud;

int LoadFromFile(Stud []);
int CreateStud(Stud [],char[] ,char[] ,int );
int GenHash(char[]);
int PutInStud(position, position);
int Find(Stud[]);
position FindInHash(position, char[], char[]);
int Print(Stud[]);

int main() {
	Stud Hash_heads[MAX_TABLE];
	int i,choice = 1;

	for (i = 0; i < MAX_TABLE; i++)
		Hash_heads[i].next = NULL;

	while (choice)
	{
		printf("\n");
		printf("*****************************************\n");
		printf("*** 1 **    Ucitaj iz datoteke        ***\n");
		printf("*** 2 **    Ispisi podatke studenta   ***\n");
		printf("*** 3 **    Ispisi                    ***\n");
		printf("*** 0 **    Izlaz                     ***\n");
		printf("*****************************************\n");

		printf("Unesite zeljeniu akciju:\n");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
		{
			if (LoadFromFile(Hash_heads) == ERROR)
			{
				perror("Error with function LoadFromFile");
				return ERROR;
			}

			break;
		}
		case 2:
		{
			if (Find(Hash_heads) == ERROR)
			{
				perror("Error with function Find");
				return ERROR;
			}
			break;
		}
		case 3:
		{
			if (Print(Hash_heads) == ERROR)
			{
				perror("Error with function Print");
				return ERROR;
			}
			break;
		}
		case 0:
		{
			choice = 0;	
			break;
		}
		default:
				break;
		}


	}


	return SUCCESS;



}
int LoadFromFile(Stud Hash_heads[])
{
	char ime[MAX_CHAR];
	char prezime[MAX_CHAR];
	int MB;
	char filename[MAX_CHAR];
	FILE* f;


	printf("Unesite ime datoteke iz kojega uzimamo podatke studenata\n");
	scanf("%s", filename);

	f = fopen(filename, "r");

	if (f == NULL)
	{
		perror("Trazena datoteka nije pronadjena\n");
		return ERROR;
	}
	
	while (!feof(f))
	{
		fscanf(f, " %s %s %d", ime, prezime, &MB);
		if (CreateStud(Hash_heads, ime, prezime, MB) == ERROR)
		{
			perror("Error with function CreateStud");
			return ERROR;
		}
	}

	return SUCCESS;

}
int CreateStud(Stud Hash_heads[], char ime[], char prezime[], int MB)
{
	position Student;
	int HashValue = 0;

	Student = (position)malloc(sizeof(Stud));

	if (Student == NULL)
	{
		perror("Malloc failed\n");
		return ERROR;
	}

	strcpy(Student->Ime, ime);
	strcpy(Student->Prezime, prezime);
	Student->MB = MB;
	Student->next = NULL;

	HashValue = GenHash(prezime);

	if (PutInStud(&Hash_heads[HashValue],Student) == ERROR)
	{
		perror("Error with function PutInStud");
		return ERROR;
	}

	return SUCCESS;
}
int GenHash(char prezime[])
{
	int i = 0;
	int hash = 0;

	while (prezime[i] != '\0' && i < 5)
	{
		hash = hash + (int)prezime[i];
		i++;
	}

	return (hash % MAX_TABLE);
}
int PutInStud(position Head, position Student)
{
	if (Head == NULL || Student == NULL)
	{
		return ERROR;
	}

	while(Head->next != NULL && strcmp(Student->Prezime,Head->next->Prezime) > 0)
	{
		Head = Head->next;
	}

	if ((Head->next != NULL) && (strcmp(Student->Prezime, Head->next->Prezime) == 0))
	{
		while (Head->next != NULL && strcmp(Student->Ime, Head->next->Ime) > 0)
		{
			Head = Head->next;
		}
	}

	Student->next = Head->next;
	Head->next = Student;

	return SUCCESS;
}
int Find(Stud Hash_heads[])
{
	char ime[MAX_CHAR];
	char prezime[MAX_CHAR];
	position trazeni;

	printf("Unesite ime studenta: \n");
	scanf(" %s", ime);
	printf("Unesite prezime studenta: \n");
	scanf(" %s", prezime);

	trazeni = FindInHash(&Hash_heads[GenHash(prezime)], ime, prezime);

	if (trazeni == NULL)
	{
		printf("Nepostoji trazeni student \n");
		return SUCCESS;
	}
	else
	{
		printf("MB trazenog studenta je: %d \n",trazeni->MB);
		free(trazeni);
		return SUCCESS;
	}

}
position FindInHash(position Head, char ime[], char prezime[])
{
	Head = Head->next;
	
	while(Head != NULL && (strcmp(Head->Prezime, prezime) || strcmp(Head->Ime, ime)) )
	{
		Head = Head->next;
	}

	return Head;
}
int Print(Stud Hash_heads[])
{
	position Head;
	int i = 0;
	int j = 0;

	for (i = 0; i < MAX_TABLE; i++)
	{
		printf("**************\n");
		printf("** Kljuc %d **\n", i + 1);
		printf("**************\n");
		Head = Hash_heads[i].next;

		if (Head == NULL)
			printf("Ovaj kljuc je prazan");
		else
		{
			j = 0;
			while (Head != NULL)
			{
				printf("\t**********************************************\n");
				printf("\t        %d   ", j + 1);
				printf(" %s ", Head->Ime);
				printf(" %s   \n", Head->Prezime);
				printf("\t MB:    ||  %d  ||   \n", Head->MB);
				printf("\t**********************************************\n");
				printf("\n");
				Head = Head->next;
				j++;
			}
		}
	}

	return SUCCESS;
}