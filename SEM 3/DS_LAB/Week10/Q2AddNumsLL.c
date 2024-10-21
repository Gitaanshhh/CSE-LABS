/*
Q2 Add two long positive integers represented using circular doubly linked list with header node
*/

#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int ele; 
	struct Node* rlink, *llink;
} Node;

void insertf(Node **head, int ele){
	Node *newNode = calloc(1, sizeof(Node));
	newNode->ele = ele;
	newNode->rlink = newNode->llink = NULL;
	if (*head == NULL){
		*head = newNode;
		return;
	}
	(*head)->llink = newNode;
	newNode->rlink = *head;
	*head = newNode;
}

void display(Node **head){
	printf("List : ");
	if (*head == NULL){
		printf("Empty");
		return;
	}
	Node *i;
	for (i = *head; i!=NULL; i=i->rlink)
		printf("%d ",i->ele);
	printf("\n");
}

Node * Add (Node *A, Node *B){
    Node *C = NULL;
    int sum = 0;
    while (A!=NULL || B!=NULL){
        sum = sum*10 + A->ele+B->ele;
        A = A->rlink;
        B = B-> rlink;
    }
    for (int i = sum; i%10 != 0; i=i/10)
	    insertf(&C, i%10);
    return C;
}

int main(){
	Node *A = NULL, *B = NULL;
	int num1, num2, n1=0, n2=0;
	printf("Enter Numbers to Add : \n");
	printf("Number 1 : ");
	scanf("%d",&num1);
	printf("Number 2 : ");
	scanf("%d",&num2);
	for (int i = num1; i%10 != 0; i=i/10){
	    n1++;
	    insertf(&A, i%10);
	}
	for (int i = num2; i%10 != 0; i=i/10){
	    n2++;
	    insertf(&B, i%10);
	}
	while(n1 != n2){
	    if (n1>n2){
	        insertf(&B, 0);
	        n2++;
	    }
	   else {
	       insertf(&A, 0);
	       n1++;
	   }
	}
	display(&A);
	display(&B);
	Node *Sum = Add(A, B);
	display(&Sum);
	return 0;
}
