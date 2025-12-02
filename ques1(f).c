// Queue implementation using a sorted array (priority queue behavior)

#include <stdio.h>
#include <stdlib.h>

struct SortedQueue {
    int size;
    int count;     // number of elements in queue
    int *arr;
};

struct SortedQueue* createSortedQueue(int size) {
    struct SortedQueue *q = (struct SortedQueue*)malloc(sizeof(struct SortedQueue));
    q->size = size;
    q->count = 0;
    q->arr = (int*)malloc(size * sizeof(int));
    return q;
}

int isFull(struct SortedQueue *q) {
    return q->count == q->size;
}

int isEmpty(struct SortedQueue *q) {
    return q->count == 0;
}

// Enqueue with sorting
void enqueue(struct SortedQueue *q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }

    int i = q->count - 1;

    // Shift elements to maintain sorted order (ascending)
    while (i >= 0 && q->arr[i] > value) {
        q->arr[i + 1] = q->arr[i];
        i--;
    }

    // Insert in correct position
    q->arr[i + 1] = value;
    q->count++;

    printf("%d enqueued (sorted)\n", value);
}

// Dequeue always removes the smallest element
int dequeue(struct SortedQueue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }

    int value = q->arr[0];

    // Shift everything left by one
    for (int i = 0; i < q->count - 1; i++) {
        q->arr[i] = q->arr[i + 1];
    }

    q->count--;
    return value;
}

int peek(struct SortedQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->arr[0];
}

void display(struct SortedQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Sorted Queue elements: ");
    for (int i = 0; i < q->count; i++) {
        printf("%d ", q->arr[i]);
    }
    printf("\n");
}

int main() {
    struct SortedQueue *q = createSortedQueue(10);

    enqueue(q, 30);
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 5);
    display(q);

    printf("Dequeued: %d\n", dequeue(q));
    display(q);

    printf("Peek: %d\n", peek(q));

    return 0;
}
