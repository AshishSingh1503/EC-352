// dynamic_cll.c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node* createNode(int value) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void insertEndCLL(struct Node **headRef, int value) {
    struct Node *newNode = createNode(value);

    if (*headRef == NULL) {
        *headRef = newNode;
        newNode->next = newNode;   // circular to itself
        return;
    }

    struct Node *temp = *headRef;
    while (temp->next != *headRef)
        temp = temp->next;

    temp->next = newNode;
    newNode->next = *headRef;
}

void printCLL(struct Node *head) {
    if (head == NULL) return;

    struct Node *temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(back to head)\n");
}

void freeCLL(struct Node *head) {
    if (head == NULL) return;

    struct Node *curr = head->next;
    struct Node *nextNode;

    while (curr != head) {
        nextNode = curr->next;
        free(curr);
        curr = nextNode;
    }
    free(head);
}

int main() {
    struct Node *head = NULL;

    insertEndCLL(&head, 10);
    insertEndCLL(&head, 20);
    insertEndCLL(&head, 30);
    insertEndCLL(&head, 40);

    printf("Dynamic Circular Linked List:\n");
    printCLL(head);

    freeCLL(head);
    return 0;
}
