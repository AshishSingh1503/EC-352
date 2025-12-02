// static_cll.c
#include <stdio.h>

struct Node {
    int data;
    struct Node *next;
};

void printCLL(struct Node *head) {
    if (head == NULL) return;

    struct Node *temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(back to head)\n");
}

int main() {
    struct Node n1, n2, n3;

    n1.data = 1;
    n2.data = 2;
    n3.data = 3;

    // Make it circular: n1 -> n2 -> n3 -> n1
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n1;

    struct Node *head = &n1;

    printf("Static Circular Linked List:\n");
    printCLL(head);

    return 0;
}
