//Implementation of stack using linked list


#include <stdio.h>
#include <stdlib.h>

// Node of linked list
struct Node {
    int data;
    struct Node* next;
};

// Stack structure (points to top of list)
struct Stack {
    struct Node* top;
};

// Create an empty stack
struct Stack* createStack() {
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
    if (!s) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    s->top = NULL;
    return s;
}

// Push operation
void push(struct Stack* s, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed (Stack Overflow)\n");
        return;
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
    printf("%d pushed to stack\n", value);
}

// Pop operation
int pop(struct Stack* s) {
    if (s->top == NULL) {
        printf("Stack Underflow\n");
        return -1;
    }
    struct Node* temp = s->top;
    int popped = temp->data;
    s->top = temp->next;
    free(temp);
    return popped;
}

// Peek operation
int peek(struct Stack* s) {
    if (s->top == NULL) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->top->data;
}

// Check if stack is empty
int isEmpty(struct Stack* s) {
    return s->top == NULL;
}

// Display stack elements
void display(struct Stack* s) {
    if (s->top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements (top -> bottom): ");
    struct Node* current = s->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Example usage
int main() {
    struct Stack* s = createStack();

    push(s, 10);
    push(s, 20);
    push(s, 30);
    display(s);

    printf("Top element is %d\n", peek(s));

    printf("Popped element is %d\n", pop(s));
    display(s);

    printf("Is stack empty? %s\n", isEmpty(s) ? "Yes" : "No");

    return 0;
}
