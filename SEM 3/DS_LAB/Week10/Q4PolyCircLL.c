/*
Q4 Given two polynomials, write a program to perform the following operations on
singly circular linked list with header node. Use menu driven approach to input two
polynomials, subtract, multiply and display the result.
*/

//program to perform the following operations on singly circular linked list with header node subtract, multiply and display the result.

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val,coeff;
    struct node *next;
} Node ;

void insertNode(Node * prev,int x, int z) {
    Node * new = (Node *) malloc(sizeof(Node));
    new->val = x;
    new->coeff = z;
    new->next = prev->next;
    prev->next = new;
}

void inputCirc(Node **list,int n) {
    int i,temp1,temp2;
    Node * temp = (Node *) malloc(sizeof(Node));
    (*list) -> next = temp;
    for (i=0;i<n;i++) {
        printf("Enter value and coefficient ");
        scanf("%d %d",&temp1,&temp2);
        if (i == 0) {
            temp->val = temp1;
            temp->coeff = temp2;
            temp->next = *list;
        }
        else {
            insertNode(temp,temp1,temp2);
            temp = temp->next;
        }
    }
}

void displayCirc(Node **list) {
    printf("The expression is: ");
    Node * temp = (Node *) malloc(sizeof(Node));
    temp = (*list)->next;
    while(temp != *list) {
        printf("(%dx^%d) + ",temp->val,temp->coeff);
        temp = temp->next;
    }
    printf("\n");
}

int getCoeff(Node *list, int exp) {
    //find coefficient of x power exp
    Node * head = list;
    list = list->next;
    while (list != head) {
        if (list->coeff == exp)
            return list->val;
        list = list->next;
    }
    return 0;
}

void sub(Node **list1, Node **list2, Node **list3) {
    //list 1 minus list 2
    Node * iter1 = (Node *) malloc(sizeof(Node));
    iter1 = (*list1)->next;
    Node * iter2 = (Node *) malloc(sizeof(Node));
    iter2 = (*list2)->next;
    Node * head3 = (Node *) malloc(sizeof(Node));
    *list3 = head3;
    head3->next = head3;

    while (iter1 != *list1 ) {    
        int x = getCoeff(*list2,iter1->coeff);
        if (x == 0) {
            Node * new = (Node *) malloc(sizeof(Node));
            new->next = head3->next;
            head3->next = new;
            new->val = iter1->val;
            new->coeff = iter1->coeff;
        }
        else {
            Node * new = (Node *) malloc(sizeof(Node));
            new->next = head3->next;
            head3->next = new;
            new->val = iter1->val - x;
            new->coeff = iter1->coeff;
        }
        iter1 = iter1->next;
        head3 = head3->next;
    }
    while (iter2 != *list2) {
        int x = getCoeff(*list3,iter2->coeff);
        if (x == 0) {
            Node * new = (Node *) malloc(sizeof(Node));
            new->next = head3->next;
            head3->next = new;
            new->val = - iter2->val;
            new->coeff = iter2->coeff;
        }
        iter2 = iter2->next;
        head3 = head3->next;
    }
}

void mult(Node **list1, Node **list2, Node **list4) {
    Node * iter1 = (Node *) malloc(sizeof(Node));
    iter1 = (*list1)->next;
    Node * iter2 = (Node *) malloc(sizeof(Node));
    iter2 = (*list2)->next;
    Node * head4 = (Node *) malloc(sizeof(Node));
    *list4 = head4;
    head4->next = head4;

    while (iter1 != *list1) {
        iter2 = (*list2) -> next;
        while (iter2 != *list2) {
            Node * new = (Node *) malloc(sizeof(Node));
            new->next = head4->next;
            head4->next = new;
            new->val = iter1->val *  iter2->val;
            new->coeff = iter1->coeff + iter2->coeff;

            iter2 = iter2->next;
        }
        iter1 = iter1->next;
    }
}

int main() {
    int n1,n2;
    Node * list1 = (Node *) malloc(sizeof(Node));
    Node * list2 = (Node *) malloc(sizeof(Node));
    Node * list3 = (Node *) malloc(sizeof(Node));
    Node * list4 = (Node *) malloc(sizeof(Node));


    printf("Enter length of first polynomial expression ");
    scanf("%d",&n1);
    inputCirc(&list1,n1);
    displayCirc(&list1);
    printf("Enter length of first polynomial expression ");
    scanf("%d",&n2);
    inputCirc(&list2,n2);
    displayCirc(&list2);
    printf("Expression after subtraction: ");
    sub(&list1,&list2,&list3);
    displayCirc(&list3);
    printf("Expression after multiplication: ");
    mult(&list1,&list2,&list4);
    displayCirc(&list4);
}

/*
typedef struct Node {
	int ele; 
	struct Node* next;
} NODE;

NODE add(NODE head,int n,int e){
	NODE temp,last;
	temp=(NODE)malloc(sizeof(struct node));
	temp->info=n;
	temp->ex=e;
	last=head->llink;
	temp->llink=last;
	last->rlink=temp;
	temp->rlink=head;

	head->llink=temp;
	return head;
}

NODE sum(NODE h1,NODE h2,NODE h3){
	NODE one,two;
	one=h1->rlink;
	two=h2->rlink;
	while(one!=h1 && two!=h2){
		if((one->ex)==(two->ex)){
			h3=add(h3,((one->info)+(two->info)),one->ex);
			one=one->rlink;
			two=two->rlink;
		}
		else if(one->ex>two->ex){
			h3=add(h3,one->info,one->ex);
			one=one->rlink;
		}
		else{
			h3=add(h3,two->info,two->ex);
			two=two->rlink;
		}
	}
	while(two!=h2){
		h3=add(h3,two->info,two->ex);
		two=two->rlink;
	}
	while(one!=h1){
		h3=add(h3,one->info,one->ex);
		one=one->rlink;
	}
	return h3;
}

void display(NODE head){
	printf("\ncontents of list are\n");
	NODE temp=NULL;
	temp=head->rlink;
	while(temp!=head){
		printf("%d %d\t",temp->info,temp->ex);
		temp=temp->rlink;
	}
}

int main(){
	int m,n,e,k;
	NODE h1,h2,h3,h4;
	h1=(NODE)malloc(sizeof(struct node));
	h2=(NODE)malloc(sizeof(struct node));
	h3=(NODE)malloc(sizeof(struct node));
	h4=(NODE)malloc(sizeof(struct node));
	h1->rlink=h1;
	h1->llink=h1;
	h2->rlink=h2;
	h2->llink=h2;
	h3->rlink=h3;
	h3->llink=h3;
	h4->rlink=h4;
	h4->llink=h4;
	printf("\nnumber of nodes in list1\n");
	scanf("%d",&n);
	while(n>0){
		scanf("%d",&m);
		scanf("%d",&e);
		h1=add(h1,m,e);
		n--;
	}
	display(h1);
	printf("\nnumber of nodes in list2\n");
	scanf("%d",&k);
	while(k>0){
		scanf("%d",&m);
		scanf("%d",&e);
		h2=add(h2,m,e);
		k--;
	}
	display(h2);
	printf("\nthe sum is\n");
	h3=sum(h1,h2,h3);
	display(h3);
	return 1;
}
*/
