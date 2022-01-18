#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 40

struct _cvorStabla;
typedef struct _cvorStabla* pokStabla;
typedef struct _cvorStabla
{
    int broj;
    pokStabla left;
    pokStabla right;

}cvorStabla;


pokStabla Insert(pokStabla, int);
int Replace(pokStabla);
int slucajniBroj(int, int);
void inorderDat(pokStabla);
void pomocniInorder(pokStabla, FILE*);
pokStabla stvoriNoviCvor(int);
void inorderPrint(pokStabla);

int main()
{
   pokStabla root = NULL;
   FILE* fp = fopen("stablo.txt", "w");
   if(fp == NULL){
       printf("Greška pri otvaranju datoteke!\n");
   } 

   int izbor;

   printf("1 -zadani brojevi,  2 - slucajni brojevi   3 - izlaz\n");
   scanf("%d", &izbor);

   while(1){
       switch(izbor){
           case 1:
           root = Insert(root, 2);
           root = Insert(root, 5);
           root = Insert(root, 7);
           root = Insert(root, 8);
           root = Insert(root, 11);
           root = Insert(root, 1);
           root = Insert(root, 4);
           root = Insert(root, 2);
           root = Insert(root, 3);
           root = Insert(root, 7);
           inorderDat(root);
           Replace(root);
           inorderDat(root);
           break;
           
           case 2:
           root = Insert(root, slucajniBroj(10,90));
           root = Insert(root, slucajniBroj(10,90));
           root = Insert(root, slucajniBroj(10,90));
           root = Insert(root, slucajniBroj(10,90));
           root = Insert(root, slucajniBroj(10,90));
           root = Insert(root, slucajniBroj(10,90));
           root = Insert(root, slucajniBroj(10,90));
           root = Insert(root, slucajniBroj(10,90));
           root = Insert(root, slucajniBroj(10,90));
           root = Insert(root, slucajniBroj(10,90));
           break;

           case 3:
           exit(1);
           break;
          
           default:
             printf("Krivi unos!\n");
    
       }

   }

   fclose(fp);
    return 0;
}




pokStabla Insert(pokStabla root, int el)
{
    if(root == NULL){
        return stvoriNoviCvor(el);
    }

    else if(el < root->broj){
        Insert(root->right, el);
    }

    else if(el >= root->broj){

        Insert(root->left, el);
    }
    return root;
}

pokStabla stvoriNoviCvor(int el)
{
    pokStabla tmp;
    tmp = (pokStabla)malloc(sizeof(cvorStabla));

    if(tmp == NULL){
        printf("Greška pri alokaciji memorije!\n");
        return tmp;

}
    else{
    tmp->broj = el;
    tmp->left = NULL;
    tmp->right = NULL;}

    return tmp;
}


int Replace(pokStabla root)
{

	pokStabla current = NULL;
	current = root;
	int sum = 0, value = 0;

	if (current->left == NULL && current->right == NULL)
	{
		sum = current->broj;
		current->broj = 0;
		return sum;

	}
	else if (current->left != NULL && current->right == NULL)
	{

		sum = Replace(current->left);
		value = current->broj + sum;
		current->broj = sum;
		return value;

	}
	else if (current->left == NULL && current->right != NULL)
	{

		sum = Replace(current->right);
		value = current->broj + sum;
		current->broj = sum;
		return value;

	}
	else
	{
		sum = Replace(current->left) + Replace(current->right);
		value = current->broj + sum;
		current->broj = sum;
		return value;
	}
   
    return 0;
}

void inorderPrint(pokStabla root)
{

    if(root == NULL){
        exit(3);
    }

    inorderPrint(root->left);
    printf("%d\n",root->broj);
    inorderPrint(root->right);
}

void pomocniInorder(pokStabla root, FILE* fp)
{
    if(root != NULL){
        pomocniInorder(root->left,fp);
        //fprintf(fp,)
        putw(root->broj,fp);                 
        pomocniInorder(root->right,fp);
    }
   
   
}

void inorderDat(pokStabla root)
{
   char filename[MAX];
    printf("Unijeti ime datoteke sa .txt nastavkom:\n");
    scanf("%s", filename);
       
    FILE* fp;
    fp = fopen(filename, "w");
    if(fp!=NULL){
    pomocniInorder(root, fp);
    fclose(fp);}
    else printf("Greškapri otvaranju datoteke!\n");
    
}


int slucajniBroj (int min, int max)
{
    int num = (rand() % (max - min + 1)) + min;  

    return num;
}
