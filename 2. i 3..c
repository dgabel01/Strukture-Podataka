#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>														
#include<string.h>															
#include<ctype.h>	// za toupper														
#define MAX 64

typedef struct Student * Pozicija;											

struct Student {															
	char ime[MAX];
	char prezime[MAX];
	int godRod;
	Pozicija next;
};

void Ispis(Pozicija P);														
void UnosP(char *FName, char *LName, int birthYear, Pozicija P);			
void UnosK(char *FName, char *LName, int birthYear, Pozicija P);			
Pozicija Trazi(char *LName, Pozicija P);									
Pozicija TraziP(char *LName, Pozicija P);								
void Brisi(char *LName, Pozicija P);										
void UnosIza(char *FName, char *LName, int birthYear, char *oldStudent, Pozicija P);		
void UnosIspred(char *FName, char *LName, int birthYear, char *oldStudent, Pozicija P);		
void UnosStudent(char *FName, char *LName, int birthYear, Pozicija q);		
void Sortiraj(Pozicija P);													
int Datoteka(Pozicija P);													
int RDatoteka(Pozicija P);													
int main() {
	char FName[MAX];
	char LName[MAX];
	char oldStudent[MAX];													
	int birthYear = 0;
	char izb;																
	struct Student Head;													

	Head.next = NULL;														

	while (1) {																

		printf("Izbornik:\nP - unos studenta na pocetak liste\nI - ispis liste\nK - unos studenta na kraj liste"
			"\nT - trazenje studenta (po prezimenu)\nB - brisanje odredenog studenta iz liste (po prezimenu)"
			"\nY - dodavanje novog studenta iza odredenog studenta\nX - dodavanje novog studenta ispred odredenog studenta"
			"\nS - sortiranje liste (po prezimenima)\nD - upisivanje liste u datoteku\nR - citanje liste iz datoteke\nQ - kraj programa\n\n");
		scanf(" %c", &izb);
		puts("");

		switch (toupper(izb)) {												
		case 'P':															
			puts("Vrsi se unos studenta na pocetak liste.");

			printf("\nUnesite ime studenta.\n");
			scanf(" %s", FName);
			printf("\nUnesite prezime studenta.\n");
			scanf(" %s", LName);
			printf("\nUnesite godinu rodenja studenta.\n");
			scanf("%d", &birthYear);

			UnosP(FName, LName, birthYear, &Head);

			printf("\nUspjesno ste dodali studenta na pocetak liste.\n\n");
			break;

		case 'I':															
			puts("Vrsi se ispis liste.");
			puts("");
			Ispis(Head.next);
			break;

		case 'K':															
			puts("Vrsi se unos studenta na kraj liste.");

			printf("\nUnesite ime studenta.\n");
			scanf(" %s", FName);
			printf("\nUnesite prezime studenta.\n");
			scanf(" %s", LName);
			printf("\nUnesite godinu rodenja studenta.\n");
			scanf("%d", &birthYear);

			UnosK(FName, LName, birthYear, &Head);

			printf("\nUspjesno ste dodali studenta na kraj liste.\n\n");
			break;

		case 'T':															
			puts("Vrsi se trazenje studenta (po prezimenu).");

			printf("\nUnesite prezime studenta kojeg zelite pronaci.\n");
			scanf(" %s", LName);

			Trazi(LName, Head.next);

			puts("");
			break;

		case 'B':															
			puts("Vrsi se brisanje studenta iz liste (po prezimenu).");

			printf("\nUnesite prezime studenta kojeg zelite izbrisati iz liste.\n");
			scanf(" %s", LName);

			Brisi(LName, &Head);

			puts("");
			break;

		case 'Y':
			puts("Vrsi se dodavanje novog studenta iza odredenog studenta.");

			printf("\nUnesite prezime studenta iza kojeg zelite dodati novog studenta.\n");
			scanf(" %s", oldStudent);

			if (Trazi(oldStudent, &Head) == NULL)							

			printf("\nVrsi se unos novog studenta.\n");

			printf("\nUnesite ime studenta.\n");
			scanf(" %s", FName);
			printf("\nUnesite prezime studenta.\n");
			scanf(" %s", LName);
			printf("\nUnesite godinu rodenja studenta.\n");
			scanf("%d", &birthYear);

			UnosIza(FName, LName, birthYear, oldStudent, &Head);

			printf("\nUspjesno ste dodali novog studenta iza studenta %s.\n\n", oldStudent);
			break;

		case 'X':
			puts("Vrsi se dodavanje novog studenta ispred odredenog studenta.");

			printf("\nUnesite prezime studenta ispred kojeg zelite dodati novog studenta.\n");
			scanf(" %s", oldStudent);

			if (TraziP(oldStudent, &Head) == NULL) {						
				break;														
				puts("");
				break;
			}

			printf("\nVrsi se unos novog studenta.\n");

			printf("\nUnesite ime studenta.\n");
			scanf(" %s", FName);
			printf("\nUnesite prezime studenta.\n");
			scanf(" %s", LName);
			printf("\nUnesite godinu rodenja studenta.\n");
			scanf("%d", &birthYear);

			UnosIspred(FName, LName, birthYear, oldStudent, &Head);

			printf("\nUspjesno ste dodali novog studenta ispred studenta %s.\n\n", oldStudent);
			break;

		case 'S':
			puts("Vrsi se sortiranje liste po prezimenima.");

			Sortiraj(&Head);

			printf("\nLista je uspjesno sortirana.\n\n");
			break;

		case 'D':
			puts("Vrsi se upis liste u datoteku.");

			Datoteka(Head.next);

			printf("\nLista je uspjesno upisana u datoteku.\n\n");
			break;
		case 'R':
			puts("Vrsi se citanje liste iz datoteke.");
			puts("");

			RDatoteka(&Head);

			printf("\nLista je uspjesno procitana iz datoteke.\n\n");
			break;

		case 'Q':															
			puts("Kraj programa!");
			return 1;
			break;

		default:															
			printf("Greska pri unosu! Pokusajte ponovno.\n\n");
			break;

		}
	}

	system("pause");

	return 0;
}


void Ispis(Pozicija P) {

	printf("Ime		 Prezime	Godina rodenja\n");
	while (P != NULL) {
		printf("%-8s\t %-8s\t %8d.\n", P->ime, P->prezime, P->godRod);
		P = P->next;
	}

	puts("");

}

void UnosP(char *FName, char *LName, int birthYear, Pozicija P) {

	Pozicija q;

	q = (Pozicija)malloc(sizeof(struct Student));						

	UnosStudent(FName, LName, birthYear, q);								
																			
	q->next = P->next;
	P->next = q;

}

void UnosK(char *FName, char *LName, int birthYear, Pozicija P) {

	Pozicija q;

	while (P->next != NULL)													
		P = P->next;


	q = (Pozicija)malloc(sizeof(struct Student));						

	UnosStudent(FName, LName, birthYear, q);

	q->next = P->next;
	P->next = q;

}

Pozicija Trazi(char *LName, Pozicija P) {

	int br = 1;																

	while (P != NULL && strcmp(P->prezime, LName)) {						
		P = P->next;														
		br++;
	}


	if (P == NULL) {														
		printf("\nStudent prezimena %s se ne nalazi unutar liste.\n", LName);
		return NULL;
	}
	else {
		printf("\nStudent %s %s (%d.) se nalazi na %d. mjestu u listi.\n", P->ime, P->prezime, P->godRod, br);
		return P;
	}

}

Pozicija TraziP(char *LName, Pozicija P) {

	Pozicija prev = P;
	P = P->next;

	while (P != NULL && strcmp(P->prezime, LName)) {						
		prev = P;
		P = P->next;
	}

	if (P == NULL) {
		printf("\nStudent prezimena %s se ne nalazi unutar liste.\n", LName);
		return NULL;
	}

	return prev;
}

void Brisi(char *LName, Pozicija P) {
	Pozicija prev;

	prev = TraziP(LName, P);

	printf("\nStudent %s %s (%d.) se izbrisao iz liste.\n", prev->next->ime, prev->next->prezime, prev->next->godRod);

	if (prev != NULL) {
		P = prev->next;														
		prev->next = P->next;
		free(P);															
	}

}

void UnosIza(char *FName, char *LName, int birthYear, char *oldStudent, Pozicija P) {

	Pozicija q;

	P = Trazi(oldStudent, P);

	q = (Pozicija)malloc(sizeof(struct Student));

	UnosStudent(FName, LName, birthYear, q);

	q->next = P->next;
	P->next = q;

}

void UnosIspred(char *FName, char *LName, int birthYear, char *oldStudent, Pozicija P) {

	Pozicija q;

	Pozicija prev = TraziP(oldStudent, P);

	q = (Pozicija)malloc(sizeof(struct Student));

	UnosStudent(FName, LName, birthYear, q);

	q->next = prev->next;
	prev->next = q;															

}

void UnosStudent(char *FName, char *LName, int birthYear, Pozicija q) {
	
	strcpy(q->ime, FName);
	strcpy(q->prezime, LName);
	q->godRod = birthYear;

}

void Sortiraj(Pozicija P) {													

	Pozicija j, prev_j, temp, end;

	end = NULL;

	while (P->next != end) {
		prev_j = P;
		j = P->next;
		
		while (j->next != end) {
			if (strcmp(j->prezime, j->next->prezime) > 0) {
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}

			prev_j = j;
			j = j->next;
		}

		end = j;
	}

}

int Datoteka(Pozicija P) {

	FILE *studenti;

	studenti = fopen("studenti.txt", "w");									

	if (studenti == NULL) {													
		puts("Greska pri otvaranju datoteke!");
		return -1;
	}

	fprintf(studenti, "Ime:\t\tPrezime:\t\tGodina rodenja:");
	while (P != NULL) {														

		fprintf(studenti, "\n");
		fprintf(studenti, "%s\t\t%s\t\t%d", P->ime, P->prezime, P->godRod);

		P = P->next;
	}

	fclose(studenti);														

	return 0;
}

int RDatoteka(Pozicija P) {

	Pozicija q;
	FILE *studenti;

	P->next = NULL;

	studenti = fopen("studenti.txt", "r");									

	if (studenti == NULL) {													
		puts("Datoteka je prazna.");
		return -1;
	}

	rewind(studenti);

	while (1)															
		if (fgetc(studenti) == '\n')
			break;

	while (!feof(studenti)) {
		q = (Pozicija)malloc(sizeof(struct Student));
		fscanf(studenti, "%s %s %d", q->ime, q->prezime, &q->godRod);

		q->next = P->next;
		P->next = q;
		P = q;
	}

	fclose(studenti);
	return 0;
}
