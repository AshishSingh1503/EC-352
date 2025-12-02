// Implementation of stack using array.

#include <stdio.h>
#include <stdlib.h>

struct stack
{
    int size;
    int top;
    int *arr;
};
struct stack* createStack(int size)
{
    struct stack* s = (struct stack*)malloc(sizeof(struct stack));
    s->size = size;
    s->top = -1;
    s->arr = (int*)malloc(size * sizeof(int));
    return s;
}

void push(struct stack* s, int value)
{
    if (s->top == s->size - 1) {
        printf("Stack overflow\n");
        return;
    }
    s->arr[++s->top] = value;
}

int pop(struct stack* s)
{
    if (s->top == -1) {
        printf("Stack underflow\n");
        return -1; // Indicating an error
    }
    return s->arr[s->top--];
}
int peek(struct stack* s)
{
    if (s->top == -1) {
        printf("Stack is empty\n");
        return -1; // Indicating an error
    }
    return s->arr[s->top];
}
int isEmpty(struct stack* s)
{
    return s->top == -1;
}
int isFull(struct stack* s)
{
    return s->top == s->size - 1;
}
void display(struct stack* s)
{
    if (s->top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}
int main()
{
    struct stack* s = createStack(5);

    push(s, 10);
    push(s, 20);
    push(s, 30);
    display(s);

    printf("Top element is %d\n", peek(s));

    printf("Popped element is %d\n", pop(s));
    display(s);

    printf("Is stack empty? %s\n", isEmpty(s) ? "Yes" : "No");
    printf("Is stack full? %s\n", isFull(s) ? "Yes" : "No");

    return 0;
}


