// Stack implementation using two queues

#include <stdio.h>
#include <stdlib.h>

// Queue structure
struct Queue {
    int size;
    int front;
    int rear;
    int *arr;
};

struct Queue* createQueue(int size) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->size = size;
    q->front = q->rear = -1;
    q->arr = (int*)malloc(size * sizeof(int));
    return q;
}

int isEmptyQ(struct Queue* q) {
    return q->front == -1;
}

int isFullQ(struct Queue* q) {
    return q->rear == q->size - 1;
}

void enqueue(struct Queue* q, int value) {
    if (isFullQ(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->arr[q->rear] = value;
}

int dequeue(struct Queue* q) {
    if (isEmptyQ(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int value = q->arr[q->front];
    q->front++;

    if (q->front > q->rear)
        q->front = q->rear = -1;

    return value;
}

struct Stack {
    struct Queue* q1;
    struct Queue* q2;
};

struct Stack* createStack(int size) {
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
    s->q1 = createQueue(size);
    s->q2 = createQueue(size);
    return s;
}

void push(struct Stack* s, int value) {
    // Step 1: enqueue into q2
    enqueue(s->q2, value);

    // Step 2: move all elements of q1 → q2
    while (!isEmptyQ(s->q1)) {
        enqueue(s->q2, dequeue(s->q1));
    }

    // Step 3: swap q1 and q2
    struct Queue* temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    printf("%d pushed\n", value);
}

int pop(struct Stack* s) {
    if (isEmptyQ(s->q1)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return dequeue(s->q1);
}

int peek(struct Stack* s) {
    if (isEmptyQ(s->q1)) {
        printf("Stack is Empty\n");
        return -1;
    }
    return s->q1->arr[s->q1->front];
}

void display(struct Stack* s) {
    if (isEmptyQ(s->q1)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements (top -> bottom): ");
    for (int i = s->q1->front; i <= s->q1->rear; i++) {
        printf("%d ", s->q1->arr[i]);
    }
    printf("\n");
}


int main() {
    struct Stack* s = createStack(10);

    push(s, 10);
    push(s, 20);
    push(s, 30);
    display(s);

    printf("Popped: %d\n", pop(s));
    display(s);

    printf("Top element: %d\n", peek(s));

    return 0;
}

// Stack implementation using single queue
#include <stdio.h>
#include <stdlib.h>

struct QueueS {
    int size;
    int front;
    int rear;
    int *arr;
};
struct QueueS* createQueueS(int size) {
    struct QueueS* q = (struct QueueS*)malloc(sizeof(struct QueueS));
    q->size = size;
    q->front = q->rear = -1;
    q->arr = (int*)malloc(size * sizeof(int));
    return q;
}
int isEmptyQS(struct QueueS* q) {
    return q->front == -1;
}
int isFullQS(struct QueueS* q) {
    return q->rear == q->size - 1;
}
void enqueueS(struct QueueS* q, int value) {
    if (isFullQS(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->arr[q->rear] = value;
}
int dequeueS(struct QueueS* q) {
    if (isEmptyQS(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int value = q->arr[q->front];
    q->front++;

    if (q->front > q->rear)
        q->front = q->rear = -1;

    return value;
}
struct StackS {
    struct QueueS* q;
};
struct StackS* createStackS(int size) {
    struct StackS* s = (struct StackS*)malloc(sizeof(struct StackS));
    s->q = createQueueS(size);
    return s;
}
void pushS(struct StackS* s, int value) {
    enqueueS(s->q, value);
    printf("%d pushed\n", value);
}

int popS(struct StackS* s) {
    if (isEmptyQS(s->q)) {
        printf("Stack Underflow\n");
        return -1;
    }

    int size = s->q->rear - s->q->front + 1;

    // Rotate the queue to bring the last added element to front
    for (int i = 0; i < size - 1; i++) {
        int val = dequeueS(s->q);
        enqueueS(s->q, val);
    }

    // Now dequeue the front element which is the last added element
    return dequeueS(s->q);
}
int peekS(struct StackS* s) {
    if (isEmptyQS(s->q)) {
        printf("Stack is Empty\n");
        return -1;
    }

    int size = s->q->rear - s->q->front + 1;
    int topElement;

    // Rotate the queue to bring the last added element to front
    for (int i = 0; i < size; i++) {
        int val = dequeueS(s->q);
        enqueueS(s->q, val);
        if (i == size - 1)
            topElement = val; // last added element
    }

    return topElement;
}
void displayS(struct StackS* s) {
    if (isEmptyQS(s->q)) {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack elements (top -> bottom): ");
    for (int i = s->q->front; i <= s->q->rear; i++) {
        printf("%d ", s->q->arr[i]);
    }
    printf("\n");
}   
int main_single_queue() {
    struct StackS* s = createStackS(10);

    pushS(s, 10);
    pushS(s, 20);
    pushS(s, 30);
    displayS(s);

    printf("Popped: %d\n", popS(s));
    displayS(s);

    printf("Top element: %d\n", peekS(s));

    return 0;
}

