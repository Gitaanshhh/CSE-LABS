#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int * items;
    int front,rear,size;
} Queue;

void insert(Queue * q,int x) {
    if (q->front == -1)
        q->front = 0;
    q->rear = q->rear + 1;
    q->items[q->rear] = x;
}

int delete(Queue * q) {
    int item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    else q->front = q->front + 1;
    return item;
}
a
bool search(Queue *q, int N, int K) {
    // Iterate through the queue in groups of 3
    for (int i = q->front; i <= q->rear; i += 3) 
        if ((K >= q->items[i] && K < q->items[i + 2]) && ((K + 1) >= q->items[i] && (K + 1) < q->items[i + 2])) 
            return true;
    return false; 
}

int main() {
    int T;
    printf("Enter the number of test cases: ");
    scanf("%d", &T);

    while (T--) {
        int N, K;
        printf("Enter N (number of people) and K (Vignesh's position): ");
        scanf("%d", &N);
        scanf("%d", &K);

        Queue q;
        q.size = N;
        q.items = (int *)malloc(q.size * sizeof(int));
        q.front = -1;
        q.rear = -1;

        for (int i = 0; i < N; i++)
            insert(&q, i + 1);

        if (search(&q, N, K))
            printf("Yes\n");
        else printf("No\n");

        free(q.items);
    }

    return 0;
}
