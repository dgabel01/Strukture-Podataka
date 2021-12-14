#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Element;
typedef struct Element *position;
typedef struct Element{
    int x;
    position left;
    position right;
    
}_el;

position unosNovog(position, int);
position stvoriNovi(int);
int inorderIspis(position);
int preorderIspis(position);
int postorderIspis(position);
//int levelOrder(position);
position Trazi(int, position);
position Brisi(int, position);
position nadiMax(position);


int main()
{
    position stablo = NULL;
	position trazeni_element = NULL;
	int izbor = 0;
	int temp = 0;

	while (izbor != 7)
	{
		printf("\nMENU\n1- Novi element\n2 - Inorder ispis\n3 -Preorder ispis\n4 - Postorder ispis\n5 - Brisanje\n6 - Nadi element\n7 - Izlaz");
		printf("Unesite zeljenu operaciju :\n ");
		scanf("%d", &izbor);

		switch(izbor){
		case 1:
			printf("Vrijednost novog elementa : ");
			scanf("%d", &temp);

			stablo = unosNovog(stablo, temp);
			break;

		case 2:
			if (inorderIspis(stablo) != 0)
				printf("Greska!\n");
			break;	
		case 3:
			if (preorderIspis(stablo) != 0)
				printf("Greska!\n");
			break;
		case 4:
			if (postorderIspis(stablo) != 0)
				printf("Greska!\n");
			break;
		case 5:
			printf("Unesite element koji zelite izbrisati : ");
			scanf("%d", &temp);
			stablo = Brisi(temp, stablo);
			break;
		case 6:
			printf("Unesite element koji zelite pronaci : ");
			scanf("%d", &temp);
			trazeni_element = Trazi(temp, stablo);

			if (trazeni_element != NULL)
				printf("Element %d je na adresi %x !!!\n", temp, (unsigned int)trazeni_element);
			else
				printf("Trazeni element ne postoji!!!\n");
			break;
		case 7:
			break;
		default:
			printf("Neispravan unos, pokusati ponovno!\n");	

		}
		


    return 0;
}



position unosNovog(position S, int el)
{
    if(S == NULL)
    {
        S = stvoriNovi(el);
        return S;
    }

    if(el < S->x)
    {
        S->left = unosNovog(S->left,el);
        return S;
    }
    if(el > S->x)
    {
        S->right = unosNovog(S->right, el);
        return S;
    }

}


position stvoriNovi(int el)
{
    position temp = NULL;
    temp =(position)malloc(sizeof(_el));
    if(temp == NULL)
        printf("Greška u alokaciji!\n");
    
    temp->x = el;
    temp->left = NULL;
    temp->right = NULL;
}


position Trazi(int el, position s)
{
    if(s == NULL)
        return s;

    if(s->x > el)
        return Trazi(el, s->left);
    if(s->x < el)
        return Trazi(el,s->right);    
    return s;

}


position Brisi(int el, position s)
{
    position temp = NULL;

	if (s == NULL)
		return NULL;

	if (el < s->x)
	{
		s->left = Brisi(el, s->left);
		return s;
	}
	if (el > s->x)
	{
		s->right = Brisi(el, stablo->right);
		return s;
	}
	if (s == NULL)
	{
		printf("Nema stabla!\n");
		return s;
	}

	//provjera broja djece
	if ((s->left != NULL) && (s->right != NULL))
	{
		temp = nadiMax(s->left);
		s->x = temp->x;

		s->left = Brisi(s->x, s->left);

		return s;
	}

	temp = s;

	if (s->left == NULL)
		s = s->right;
	else
		s = s->left;

	free(temp);
	

	return s;
    
    
}

position nadiMax(position c)  // c za izbrisat
{
    if (c != NULL)
	{
		if (c->right != NULL)
		{
			c = c->right;
			nadiMax(c);
		}
	}

	return c;

}

int inorderIspis(poisition s)
{
    if (s != NULL)
    {
        inorderIspis(s->left);
        printf("%d", s->x);
        inorderIspis(s->right);
    }

    return 0;
}


int preorderIspis(position s)
{
    if(s!= NULL)
    {
        printf("%d",s->x);
        preorderIspis(s->left);
        preorderIspis(s->right);
    }

    return 0;
}


int postorderIspis(position s)
{
    if(s!= NULL)
    {
        postorderIspis(s->left);
        postorderIspis(s->right);
        printf("%d",s->x);
    }

}