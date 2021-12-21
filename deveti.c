
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
pokStabla Replace(pokStabla);
int slucajniBroj(int, int);
void inorderDat(pokStabla);
void pomocniInorder(pokStabla, FILE*);
pokStabla stvoriNoviCvor(int);
void inorderPrint(pokStabla);

int main()
{
    
    int i;
    int nizSlucajnih[MAX];
    pokStabla root = NULL;
    root = Insert(root, 2);
    Insert(root, 5);
    Insert(root, 7);
    Insert(root, 8);
    Insert(root, 11);
    Insert(root, 1);
    Insert(root, 4);
    Insert(root, 3);
    Insert(root, 2);
    Insert(root, 7);
    //nedovrseno
    for(i=0;i<10;i++){
        nizSlucajnih[i] = slucajniBroj(10,90);
        printf("%d\n", nizSlucajnih[i]);
    }
    

    
    pokStabla root = NULL;
    root = Insert(root, nizSlucajnih[0]);
    for(i=1;i<10;i++){
        Insert(root, nizSlucajnih[i]);
    }
     inorderDat(root); 

     Replace(root);
     inorderDat(root);
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


pokStabla Replace(pokStabla root)
{
    if(root == NULL)
        return 0;

    int trenutnibroj = root->broj;
    root->broj = Replace(root->left) + Replace(root->right);   

    return root->broj + trenutnibroj;
}

void inorderPrint(pokStabla root)

    if(root == NULL{
        return 0;
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


