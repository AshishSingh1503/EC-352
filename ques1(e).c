// Linear Queue Using Array

#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int size;
    int front;
    int rear;
    int *arr;
};

struct Queue* createQueue(int size) {
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->size = size;
    q->front = -1;
    q->rear  = -1;
    q->arr = (int*)malloc(size * sizeof(int));
    return q;
}

int isFull(struct Queue *q) {
    return q->rear == q->size - 1;
}

int isEmpty(struct Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

void enqueue(struct Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->arr[q->rear] = value;
    printf("%d enqueued\n", value);
}

int dequeue(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int value = q->arr[q->front];
    q->front++;
    return value;
}

void display(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->arr[i]);
    }
    printf("\n");
}

int main() {
    struct Queue *q = createQueue(5);

    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    display(q);

    printf("Dequeued: %d\n", dequeue(q));
    display(q);

    return 0;
}


// Circular Queue Using Array

#include <stdio.h>
#include <stdlib.h>

struct CircularQueue {
    int size;
    int front;
    int rear;
    int *arr;
};

struct CircularQueue* createCircularQueue(int size) {
    struct CircularQueue *q = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    q->size = size;
    q->front = 0;
    q->rear  = 0;
    q->arr = (int*)malloc(size * sizeof(int));
    return q;
}

int isFullC(struct CircularQueue *q) {
    return (q->rear + 1) % q->size == q->front;
}

int isEmptyC(struct CircularQueue *q) {
    return q->front == q->rear;
}

void enqueueC(struct CircularQueue *q, int value) {
    if (isFullC(q)) {
        printf("Circular Queue Overflow\n");
        return;
    }
    q->rear = (q->rear + 1) % q->size;
    q->arr[q->rear] = value;
    printf("%d enqueued\n", value);
}

int dequeueC(struct CircularQueue *q) {
    if (isEmptyC(q)) {
        printf("Circular Queue Underflow\n");
        return -1;
    }
    q->front = (q->front + 1) % q->size;
    return q->arr[q->front];
}

void displayC(struct CircularQueue *q) {
    if (isEmptyC(q)) {
        printf("Circular Queue is empty\n");
        return;
    }

    printf("Circular Queue elements: ");
    int i = (q->front + 1) % q->size;
    while (i != (q->rear + 1) % q->size) {
        printf("%d ", q->arr[i]);
        i = (i + 1) % q->size;
    }
    printf("\n");
}

int main() {
    struct CircularQueue *q = createCircularQueue(5);

    enqueueC(q, 10);
    enqueueC(q, 20);
    enqueueC(q, 30);
    displayC(q);

    printf("Dequeued: %d\n", dequeueC(q));
    displayC(q);

    return 0;
}
