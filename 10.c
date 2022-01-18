#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128


struct _stablo;
typedef struct _stablo* pokstablo;
typedef struct _stablo{
    char grad[MAX];
    int populacija;
    pokstablo left;
    pokstablo right;
}stablo;

struct _lista;
typedef struct _lista* poklista;
typedef struct _lista{
    char drzava[MAX];
    pokstablo Stablo;
    poklista next;
}lista;



int drzavaizDatoteke(poklista head, pokstablo root, char* filename);
pokstablo gradizDatoteke(pokstablo root, char* filename);
poklista sortiraniUnos(poklista head, char* drzava);
int ispisListe(poklista head);
int inorderIspis(pokstablo root);
poklista stvorinoviLista(char* drzava);
int umetniIza(poklista pozicija, poklista el);
poklista nadiPrethodni(poklista head, poklista el);
pokstablo umetniuStablo(pokstablo root, char* grad, int pop);
pokstablo stvorielStablo(char* grad, int pop);
int pretraziListu(poklista head, pokstablo root, char* izbor);
int Trazi(pokstablo root, int pop);




int main()
{
    lista Lista = { .drzava = '\0', .next = NULL, .Stablo = NULL };
	poklista Head = NULL;
	Head = &Lista;
	pokstablo root = NULL;;
    char korfile[MAX];


    printf("Unijeti ime datoteke sa drzavama:\n");
    scanf("%s", korfile);
	drzavaizDatoteke(Head, root, korfile);

	char izbor[MAX];
	int pop;
	printf("Drzava sa .txt :\n");
	scanf("%s", izbor);

	pretraziListu(Head, root, izbor);



    return 0;
}


int drzavaizDatoteke(poklista head, pokstablo root, char* filename)
{
    char buffer[MAX];
    FILE* fp = NULL;
    fp = fopen(filename,"r");
    if(fp == NULL){
        exit(1);
    }
    poklista temp = NULL;

    while(!feof(fp)){

        fscanf(fp, "%s", buffer);
        temp = sortiraniUnos(head, buffer);
        temp->Stablo = root;
        root = NULL;
    }
    fclose(fp);

    ispisListe(head);

    return 0;
}



poklista sortiraniUnos(poklista head, char* drzava)
{
    poklista temp = NULL;
	temp = head->next;
	poklista novi = NULL;
	novi = stvorinoviLista(drzava); 

	poklista prethodni = NULL;
	if (!novi)
		return NULL;

	if (!temp)
	{
		umetniIza(head, novi);
		return head->next;
	}
	else
	{
		while (temp && strcmp(drzava, temp->drzava))
			temp = temp->next;

		prethodni = nadiPrethodni(head, temp);
		umetniIza(prethodni, novi);
	}

	return prethodni->next;


}

int ispisListe(poklista head)
{
    poklista temp = NULL;
    temp = head->next;  

    while (temp != NULL)
    {
        printf("%s\n", temp->drzava);
        inorderIspis(temp->Stablo);
        temp = temp->next;
    }
    
    return 0;
}

int inorderIspis(pokstablo root)
{
    pokstablo current = root;
	
	if (current != NULL)
	{
		inorderIspis(current->left);
		printf("%d  %s \n", current->populacija, current->grad);
		inorderIspis(current->right);
	}

    return 0;
}

poklista stvorinoviLista(char* drzava)
{
    poklista q = NULL;
	q= (poklista)malloc(sizeof(lista));
	if (!q)
	{
		printf("Greska pri alokaciji!\n");
		return NULL;
	}

	strcpy(q->drzava, drzava);
	q->next = NULL;
	q->Stablo = NULL;

	return q;
}

int umetniIza(poklista pozicija, poklista el)
{
	el->next = pozicija->next;
	pozicija->next = el;

    return 0;
}


poklista nadiPrethodni(poklista head, poklista el)
{
    poklista temp = head;

	while (temp->next != el)
		temp = temp->next;

	return temp;
}


pokstablo gradizDatoteke(pokstablo root, char* filename)
{
    char buffer[MAX];
	int pop;
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return NULL;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %d", buffer, &pop);
		root = umetniuStablo(root, buffer, pop);   

	}
	fclose(fp);

	return root;

}

pokstablo umetniuStablo(pokstablo root, char* grad, int pop)
{

	pokstablo current = NULL;
	current = root;

	pokstablo novi = NULL;


	if (current == NULL)
	{
		novi = stvorielStablo(grad, pop);
		return novi;
	}
	else if (pop < current->populacija)
		current->left = umetniuStablo(current->left, grad, pop);
	else if (pop > current->populacija)
		current->right = umetniuStablo(current->right, grad, pop);
	else if (pop == current->populacija && strcmp(current->grad, grad) < 0)
		current->right = umetniuStablo(current->right, grad, pop);
	else if (pop == current->populacija && strcmp(current->grad, grad) > 0)
		current->left = umetniuStablo(current->left, grad, pop);
	else
		free(novi);

	return current;

}

pokstablo stvorielStablo(char* grad, int pop)
{

    pokstablo novi = NULL;
	novi = (pokstablo)malloc(sizeof(stablo));
	if (novi == NULL)
	{
		perror("Greska pri alokaciji memorije!\n");
		return NULL;
	}

	strcpy(novi->grad, grad);
	novi->populacija = pop;
	novi->left = NULL;
	novi->right = NULL;

	return novi;
}

int pretraziListu(poklista head, pokstablo root, char* izbor)
{
    poklista temp = NULL;
	temp = head->next;
	int pop;

	while (temp->next)
	{

		if (strcmp(temp->drzava, izbor) == 0)
		{
			printf("Unijeti populaciju:\n ");
			scanf("%d", &pop);
			Trazi(temp->Stablo, pop);
			return 0;
		}


		temp = temp->next;

	}

	printf("Ne postoji ta drzava u datoteci!");

    return 0;
}

int Trazi(pokstablo root, int pop)
{
    pokstablo current = NULL;
	current = root;
	int br = 0;

	if (current != NULL)
	{
		if (current->populacija > pop)
		{
			Trazi(current->left, pop);
			printf("%d -> %s \n", current->populacija, current->grad);
			Trazi(current->right, pop);
		}
		else
		{
			Trazi(current->right, pop);

		}
	}

    return 0;
}