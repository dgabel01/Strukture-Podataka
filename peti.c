#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#deifne MAX 40

typedef struct _node* position;
typedef struct _node {
	int el;
	position next;
}node;

int Push(position, position);
int Pop(position);
position stvoriElement();
int procitajDatoteku(char);
int racunPostfixa(position, char*);

int main()
{
	node stack;
	stack.next = NULL;
	char filename[MAX];
	char* postfix;

	printf("Unesite ime datoteke: ");
	scanf("%s", filename);

	postfix = procitajDatoteku(filename);

	racunPostfixa(&stack, postfix);

	printf("\nrezultat = %d\n", stack.next->el);

	return 0;
}

int Push(position stack, position current) {
	current->next = stack->next;
	stack->next = current;

	return 0;
}

int Pop(position stack) {
	int broj = 0;
	broj = stack->next->el;

	position temp;
	temp = stack->next;
	stack->next = stack->next->next;
	free(temp);

	return broj;
}

position stvoriElement() {
	position temp = malloc(sizeof(node));
	
	if (temp == NULL)
		return NULL;
	
	temp->next = NULL;
	return temp;
}

int procitajDatoteku(char filename[MAX]) {
	FILE* fp;
	strcat(filename, ".txt");

	fp = fopen(filename, "r");

	char* postfix = (char*)malloc(MAX * sizeof(char));


	fgets(postfix, MAX, fp);

	fclose(fp);

	return postfix;
}

int racunPostfixa(position stack, char* row) {
	int n = 0, a = 0, b = 0;
	char c;
	position temp;

	while (strlen(row) > 0) {
		sscanf(row, " %c %n", &c, &n);
		row += n; 

		if (c - '+' == 0 || c - '-' == 0 || c - '*' == 0) { 
			a = Pop(stack);
			b = Pop(stack);

			printf("\n\ta = %d b = %d\n", a, b);

			if (c - '+' == 0) {
				a += b;
				printf("\n\t a + b = %d\n", a);
			}
			else if (c - '-' == 0) {
				a -= b;
				printf("\n\t a - b = %d\n", a);
			}
			else if (c - '*' == 0){
				a = a * b;
				printf("\n\t a * b = %d\n", a);
			}

			temp = stvoriElement();
			temp->el = a;
			Push(stack, temp);
		}
		else { 
			temp = stvoriElement();
			temp->el = c - '0';
			Push(stack, temp);
		}
	}

	return 0;
}