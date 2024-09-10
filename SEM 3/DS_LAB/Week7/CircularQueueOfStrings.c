/*Implement a circular queue of Strings using structures. Include functions insertcq,
deletecq and displaycq.*/

#include <stdio.h>

#define MAX 20

// Empty -> f, r = -1
// Full -> f-1 = r


typedef struct {
	char Data[MAX];
	int front;
	int rear;
} queue;

void insertq(queue * q,char * Data)
{
	if(q->rear==q->front-1) //rear+1)%MAX
		printf("\nOverflow\n");
	else
	{
		q->Data[(++q->rear)%MAX]=*Data;
		if(q->front==-1)
			q->front=0;
	}
}

char * deleteq(queue * q)
{
	char * Data = '\0';
	if(q->front==-1)
		printf("\nUnderflow!!!\n");
	else if(q->front==q->rear)
	{
		Data=q->Data[(q->front)%MAX];
		q->front=q->rear=-1;
		return Data;
	}
	else return q->Data[(q->front++)%MAX];
	return Data;
}

void displayq(queue q)
{
	int i;
	if(q.front==-1)
		printf("\nQueue is Empty!!!");
	else
	{
		printf("\nQueue is:\n");
		for(i=q.front%MAX;i<=q.rear%MAX;i++)
			printf("%d\n",q.Data[i]);
	}
}

int main()
{
	queue q;
	q.front=-1;
	q.rear=-1;
	int ch,flag=1;
	while(flag)
	{
		printf("\n\n1. Insert Queue\n2. Delete Queue\n3. Display Queue\n4. Exit\n\n");
		printf("Enter your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("\nEnter the Element:");
				char Data[20];
				scanf("%s",Data);
				insertq(&q,&Data);
				break;
			case 2:
				Data=deleteq(&q);
				printf("\nRemoved %s from the Queue\n",Data);
				break;
			case 3:
				displayq(q);
				break;
			case 4:
				flag=0;
				break;
			default:
				printf("\nWrong choice!!! Try Again.\n");
		}
	}
	return 0;
}