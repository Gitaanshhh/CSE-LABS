/*
Q3 Create an expression tree for the given postfix expression and evaluate it.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct btree {
	char data;
	struct btree *rchild, *lchild;
} btree;

typedef struct {
	int tos;
	btree elements[20];
} stack;

void push(stack *s, btree ele){
	s->elements[++(s->tos)]=ele;
}

btree pop(stack *s){
	//free(s->elements[s->tos--]);
	return s->elements[s->tos];
}

btree *postfix_build(char postfix[50]){
	stack *s = calloc(1, sizeof(stack));
	btree *temp = calloc(1, sizeof(btree));
	temp->rchild = temp->lchild = NULL;
	char symbol;
	int i = 0;
	while(symbol = postfix[i] != '\0'){
		if ((symbol>='A' && symbol<='Z')||(symbol>='a' && symbol<='z')||(symbol>='0' && symbol<='9')){
			temp->data = symbol;
			push(s, *temp);
		}
		else {
			btree *temp1 = calloc(1, sizeof(btree));
			btree *temp2 = calloc(1, sizeof(btree));
			*temp1 = pop(s);
			*temp2 = pop(s);
			temp->rchild = temp1;
			temp->lchild = temp2;
			push(s, *temp);
		}
		i++;
	}
	btree *temp3 = calloc(1, sizeof(btree));
	*temp3 = pop(s);
	return temp3;
}

void inorder(btree *root){
	if(root){
		inorder(root->lchild);
		printf("%c ", root->data);
		inorder(root->rchild);
	}
}

int main(){
	char postfix[50];
	printf("Expression : ");
	scanf("%s",postfix);
	btree *root = NULL;
	root = postfix_build(postfix);

	printf("Inorder : ");
	inorder(root);
	printf("\n");

	// int result = eval(root);
	// printf("Result : %d", result);
	return 0;
}