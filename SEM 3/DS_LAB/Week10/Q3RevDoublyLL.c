/*
Q3 Reverse a doubly linked list containing words in the data field.
*/

#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
	int ele; 
	struct Node* rlink, *llink;
} Node;

void insertr(Node **head, int ele){
	Node *newNode = calloc(1, sizeof(Node));
	newNode->ele = ele;
	newNode->rlink = newNode->llink = NULL;
	if (*head == NULL){
		*head = newNode;
		return;
	}
	Node *i;
	for (i = *head; i->rlink!=NULL; i=i->rlink);
	i->rlink = newNode;
	newNode->llink = i;
}

void display(Node **head){
	printf("List : ");
	if (*head == NULL){
		printf("Empty");
		return;
	}
	Node *i;
	for (i = *head; i->rlink!=NULL; i=i->rlink)
		printf("%d ",i->ele);
	printf("%d ",i->ele);
}

void rev(Node **head){	
	Node *i, *temp, *prev = *head;
	for (i = *head; i!=NULL; i=temp){
		temp = i->rlink; //The actual next node - pre rev
		i->rlink = i->llink;
		i->llink = temp;
		prev = i;
	}
	*head = prev;   
}

int main(){
	Node *head = NULL;
	int ch, ele;
	printf("1. Insert Rear, 2. Reverse, 3. Display, 4. Exit");
	do {
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("Enter the Element:");
				scanf("%d",&ele);
				insertr(&head,ele);
				break;
			case 2: rev(&head);
			case 3: display(&head);
			case 4: break;
			default: printf("Wrong choice.");
		}
	} while(ch!=4);
	return 0;
}