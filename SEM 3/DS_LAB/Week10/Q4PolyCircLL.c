/*
Q4 Given two polynomials, write a program to perform the following operations on
singly circular linked list with header node. Use menu driven approach to input two
polynomials, subtract, multiply and display the result.
*/

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