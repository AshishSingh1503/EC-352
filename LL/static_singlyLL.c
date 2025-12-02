// static_sll.c
#include <stdio.h>

struct Node {
    int data;
    struct Node *next;
};

void printList(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    // Statically created nodes (on stack)
    struct Node n1, n2, n3;

    n1.data = 10;
    n2.data = 20;
    n3.data = 30;

    // Link them: n1 -> n2 -> n3 -> NULL
    n1.next = &n2;
    n2.next = &n3;
    n3.next = NULL;

    struct Node *head = &n1;

    printf("Static Singly Linked List:\n");
    printList(head);

    return 0;
}
