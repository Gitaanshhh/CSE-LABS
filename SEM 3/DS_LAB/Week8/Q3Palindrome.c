/*
Q3 Write a program to check whether given string is a palindrome using a dequeue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *Data;
	int front;
	int rear;
	int size;
} Queue;


void insertr(Queue *q, char str){
	if(q->rear==q->front-1)
		printf("Queue is Full");
	else{
		q->Data[(q->rear)] = str;
		//strcpy(q->Data[(q->rear)], str);
		if(q->front==-1)
			q->front=0;
	}
}

char delete(Queue *q){
	if(q->front==-1){
		printf("Empty Queue. ");
		return '\0';
		//strcpy(str, '\0');
	}
	else if(q->front==q->rear){
		char str;
		strcpy(str, q->Data[(q->front)]);
		q->front=q->rear=-1;
		return str;
	}
	else {
		char str;
		strcpy(str, q->Data[(q->front++)]);
		return str;
	}
}

void display(Queue q){
	int i;
	if(q.front==-1)
		printf("Empty Queue. ");
	else{
		printf("\nQueue is:\n");
		for(i=q.front;i<=q.rear;i++)
			printf("%s ",q.Data[i]);
	}
}

int main(){
	char str[20];
	printf("Enter String : ");
	scanf("%s", str);

	Queue q;
	q.front=-1;
	q.rear=-1;
	q.size = strlen(str);
	q.Data = (char *)malloc(n*sizeof(char));
	
	return 0;
}