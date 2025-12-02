//Implementation of multiple stacks in a single array in normal manner as well as efficient manner

//Normal (fixed partitioning) method

#include <stdio.h>
#include <stdlib.h>

struct MultiStackFixed {
    int numStacks;   // k
    int stackSize;   // capacity per stack
    int *arr;        // full array of size k * stackSize
    int *top;        // array of size k: top indices relative to each stack (-1 means empty)
};

struct MultiStackFixed* createMultiStackFixed(int k, int stackSize) {
    struct MultiStackFixed* ms = (struct MultiStackFixed*) malloc(sizeof(struct MultiStackFixed));
    if (!ms) { printf("Memory allocation failed\n"); exit(1); }

    ms->numStacks = k;
    ms->stackSize = stackSize;
    ms->arr = (int*) malloc(sizeof(int) * k * stackSize);
    ms->top = (int*) malloc(sizeof(int) * k);

    if (ms->arr == NULL || ms->top == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < k; i++) ms->top[i] = -1; // empty stacks
    return ms;
}

// helper: compute absolute index for stack 'sn' (0-based) and offset pos (0..stackSize-1)
static inline int index_for(int sn, int offset, int stackSize) {
    return sn * stackSize + offset;
}

int isFullFixed(struct MultiStackFixed* ms, int sn) {
    if (sn < 0 || sn >= ms->numStacks) { printf("Invalid stack number\n"); return 1; }
    return ms->top[sn] == ms->stackSize - 1;
}

int isEmptyFixed(struct MultiStackFixed* ms, int sn) {
    if (sn < 0 || sn >= ms->numStacks) { printf("Invalid stack number\n"); return 1; }
    return ms->top[sn] == -1;
}

void pushFixed(struct MultiStackFixed* ms, int sn, int value) {
    if (sn < 0 || sn >= ms->numStacks) { printf("Invalid stack number\n"); return; }
    if (isFullFixed(ms, sn)) {
        printf("Stack %d Overflow\n", sn);
        return;
    }
    ms->top[sn]++;
    int absIndex = index_for(sn, ms->top[sn], ms->stackSize);
    ms->arr[absIndex] = value;
}

int popFixed(struct MultiStackFixed* ms, int sn) {
    if (sn < 0 || sn >= ms->numStacks) { printf("Invalid stack number\n"); return -1; }
    if (isEmptyFixed(ms, sn)) {
        printf("Stack %d Underflow\n", sn);
        return -1;
    }
    int absIndex = index_for(sn, ms->top[sn], ms->stackSize);
    int val = ms->arr[absIndex];
    ms->top[sn]--;
    return val;
}

int peekFixed(struct MultiStackFixed* ms, int sn) {
    if (sn < 0 || sn >= ms->numStacks) { printf("Invalid stack number\n"); return -1; }
    if (isEmptyFixed(ms, sn)) {
        printf("Stack %d is empty\n", sn);
        return -1;
    }
    int absIndex = index_for(sn, ms->top[sn], ms->stackSize);
    return ms->arr[absIndex];
}

void displayFixed(struct MultiStackFixed* ms, int sn) {
    if (sn < 0 || sn >= ms->numStacks) { printf("Invalid stack number\n"); return; }
    if (isEmptyFixed(ms, sn)) {
        printf("Stack %d is empty\n", sn);
        return;
    }
    printf("Stack %d elements (top -> bottom): ", sn);
    for (int i = ms->top[sn]; i >= 0; i--) {
        printf("%d ", ms->arr[index_for(sn, i, ms->stackSize)]);
    }
    printf("\n");
}

// cleanup
void freeMultiStackFixed(struct MultiStackFixed* ms) {
    if (!ms) return;
    free(ms->arr);
    free(ms->top);
    free(ms);
}

// Example usage
int main() {
    int k = 3;
    int cap = 4; // each stack can hold 4 elements
    struct MultiStackFixed* ms = createMultiStackFixed(k, cap);

    pushFixed(ms, 0, 10);
    pushFixed(ms, 0, 20);
    pushFixed(ms, 1, 100);
    pushFixed(ms, 2, 1000);
    pushFixed(ms, 2, 2000);

    displayFixed(ms, 0);
    displayFixed(ms, 1);
    displayFixed(ms, 2);

    printf("Popped from stack 0: %d\n", popFixed(ms, 0));
    printf("Top of stack 2: %d\n", peekFixed(ms, 2));

    printf("Is stack 1 empty? %s\n", isEmptyFixed(ms, 1) ? "Yes" : "No");
    printf("Is stack 2 full? %s\n", isFullFixed(ms, 2) ? "Yes" : "No");

    freeMultiStackFixed(ms);
    return 0;
}


//Efficient (dynamic partitioning) method
#include <stdio.h>
#include <stdlib.h>

struct MultiStackEfficient {
    int numStacks;   // k
    int *arr;        // full array
    int *top;        // array of size k: top indices relative to each stack (-1 means empty)
    int *next;       // array of size k: next indices relative to each stack
    int freeTop;     // index of the next free slot in the array
};  
struct MultiStackEfficient* createMultiStackEfficient(int k, int totalSize) {
    struct MultiStackEfficient* ms = (struct MultiStackEfficient*) malloc(sizeof(struct MultiStackEfficient));
    if (!ms) { printf("Memory allocation failed\n"); exit(1); }

    ms->numStacks = k;
    ms->arr = (int*) malloc(sizeof(int) * totalSize);
    ms->top = (int*) malloc(sizeof(int) * k);
    ms->next = (int*) malloc(sizeof(int) * totalSize);

    if (ms->arr == NULL || ms->top == NULL || ms->next == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < k; i++) ms->top[i] = -1; // empty stacks

    for (int i = 0; i < totalSize - 1; i++) ms->next[i] = i + 1;
    ms->next[totalSize - 1] = -1; // end of free list
    ms->freeTop = 0; // start of free list

    return ms;
}
int isFullEfficient(struct MultiStackEfficient* ms) {
    return ms->freeTop == -1; // no free slots
}
int isEmptyEfficient(struct MultiStackEfficient* ms, int sn) {
    if (sn < 0 || sn >= ms->numStacks) { printf("Invalid stack number\n"); return 1; }
    return ms->top[sn] == -1;
}
void pushEfficient(struct MultiStackEfficient* ms, int sn, int value) {
    if (sn < 0 || sn >= ms->numStacks) { printf("Invalid stack number\n"); return; }
    if (isFullEfficient(ms)) {
        printf("Stack Overflow\n");
        return;
    }
    int freeIndex = ms->freeTop; // get index of free slot
    ms->freeTop = ms->next[freeIndex]; // update freeTop to next free slot

    ms->arr[freeIndex] = value; // store value
    ms->next[freeIndex] = ms->top[sn]; // link new element to previous top
    ms->top[sn] = freeIndex; // update top to new element
}
int popEfficient(struct MultiStackEfficient* ms, int sn) {
    if (sn < 0 || sn >= ms->numStacks) { printf("Invalid stack number\n"); return -1; }
    if (isEmptyEfficient(ms, sn)) {
        printf("Stack Underflow\n");
        return -1;
    }
    int topIndex = ms->top[sn]; // get top index
    int val = ms->arr[topIndex]; // get value

    ms->top[sn] = ms->next[topIndex]; // update top to next element
    ms->next[topIndex] = ms->freeTop; // add freed slot to free list
    ms->freeTop = topIndex; // update freeTop

    return val;
}
int peekEfficient(struct MultiStackEfficient* ms, int sn) {
    if (sn < 0 || sn >= ms->numStacks) { printf("Invalid stack number\n"); return -1; }
    if (isEmptyEfficient(ms, sn)) {
        printf("Stack is empty\n");
        return -1;
    }
    int topIndex = ms->top[sn];
    return ms->arr[topIndex];
}
void displayEfficient(struct MultiStackEfficient* ms, int sn) {
    if (sn < 0 || sn >= ms->numStacks) { printf("Invalid stack number\n"); return; }
    if (isEmptyEfficient(ms, sn)) {
        printf("Stack %d is empty\n", sn);
        return;
    }
    printf("Stack %d elements (top -> bottom): ", sn);
    int index = ms->top[sn];
    while (index != -1) {
        printf("%d ", ms->arr[index]);
        index = ms->next[index];
    }
    printf("\n");
}
// cleanup
void freeMultiStackEfficient(struct MultiStackEfficient* ms) {
    if (!ms) return;
    free(ms->arr);
    free(ms->top);
    free(ms->next);
    free(ms);
}
// Example usage
int main() {
    int k = 3;
    int totalSize = 10; // total capacity of the array
    struct MultiStackEfficient* ms = createMultiStackEfficient(k, totalSize);

    pushEfficient(ms, 0, 10);
    pushEfficient(ms, 0, 20);
    pushEfficient(ms, 1, 100);
    pushEfficient(ms, 2, 1000);
    pushEfficient(ms, 2, 2000);

    displayEfficient(ms, 0);
    displayEfficient(ms, 1);
    displayEfficient(ms, 2);

    printf("Popped from stack 0: %d\n", popEfficient(ms, 0));
    printf("Top of stack 2: %d\n", peekEfficient(ms, 2));

    printf("Is stack 1 empty? %s\n", isEmptyEfficient(ms, 1) ? "Yes" : "No");
    printf("Is stack 2 full? %s\n", isFullEfficient(ms) ? "Yes" : "No");

    freeMultiStackEfficient(ms);
    return 0;
}

