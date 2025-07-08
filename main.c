#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ds_stack.h"
#include "ds_queue.h"
#include "ds_dequeue.h"
#include "ds_bin_tree.h"

typedef struct info_part {
    char *name;
    int age;
} INFO_PART;

void printInfo(INFO_PART *elementInfo);
void printInfoBTree(INFO_PART *elementInfo);

void freeInfo(INFO_PART *elementInfo);

int compareByAge(INFO_PART *key, INFO_PART *pNode);
int compareByAgeForBinTree(INFO_PART *info1, INFO_PART *info2);

int main() {
    // -----------------------------------------------
    // "ds_stack" LIBRARY USAGE EXAMPLE
    // -----------------------------------------------
    STACK_NODE *pStack;

    initStack(&pStack);

    // Pushing elements of INFO_STACK type to stack
    INFO_PART *stack_el_1 = malloc(sizeof(INFO_PART));
    stack_el_1->name = strdup("John");
    stack_el_1->age = 18;

    pushToStack(&pStack, stack_el_1);

    INFO_PART *stack_el_2 = malloc(sizeof(INFO_PART));
    stack_el_2->name = strdup("Mary");
    stack_el_2->age = 21;

    pushToStack(&pStack, stack_el_2);

    INFO_PART *stack_el_3 = malloc(sizeof(INFO_PART));
    stack_el_3->name = strdup("Michael");
    stack_el_3->age = 25;

    pushToStack(&pStack, stack_el_3);

    printf("Size of stack: %d\n", stackSize(pStack)); // Size of stack: 3

    // printInfo - is a custom function
    popFromStack(&pStack, printInfo); // Michael - 25 years
    popFromStack(&pStack, printInfo); // Mary - 21 years

    printf("Size of stack: %d\n", stackSize(pStack)); // Size of stack: 1

    clearStack(&pStack);
    printf("Size of stack: %d\n", stackSize(pStack)); // Size of stack: 0

    // Manually freeing dynamic memory after INFO_PART elements
    free(stack_el_1->name);
    free(stack_el_1);
    free(stack_el_2->name);
    free(stack_el_2);
    free(stack_el_3->name);
    free(stack_el_3);
    // -----------------------------------------------

    // -----------------------------------------------
    // "ds_queue" LIBRARY USAGE EXAMPLE
    // -----------------------------------------------
    QUEUE_NODE *pQueue;
    initQueue(&pQueue);

    INFO_PART *queue_el_1 = malloc(sizeof(INFO_PART));
    queue_el_1->name = strdup("Derick");
    queue_el_1->age = 35;

    pushToQueue(&pQueue, queue_el_1);

    INFO_PART *queue_el_2 = malloc(sizeof(INFO_PART));
    queue_el_2->name = strdup("Kate");
    queue_el_2->age = 29;

    pushToQueue(&pQueue, queue_el_2);

    INFO_PART *queue_el_3 = malloc(sizeof(INFO_PART));
    queue_el_3->name = strdup("Noah");
    queue_el_3->age = 24;

    pushToQueue(&pQueue, queue_el_3);

    printf("\nSize of queue: %d\n", queueSize(pQueue)); // Size of queue: 3

    popFromQueue(&pQueue, printInfo); // Derick - 35 years.
    popFromQueue(&pQueue, printInfo); // Kate - 29 years.

    printf("Size of queue: %d\n", queueSize(pQueue)); // Size of queue: 1

    clearQueue(&pQueue);
    printf("Size of queue: %d\n", queueSize(pQueue)); // Size of queue: 0

    free(queue_el_1->name);
    free(queue_el_1);
    free(queue_el_2->name);
    free(queue_el_2);
    free(queue_el_3->name);
    free(queue_el_3);
    // -----------------------------------------------

    // -----------------------------------------------
    // "ds_dequeue" LIBRARY USAGE EXAMPLE
    // -----------------------------------------------
    DEQUEUE *pDequeue;
    initDequeue(&pDequeue);

    INFO_PART *dequeue_el_1 = malloc(sizeof(INFO_PART));
    dequeue_el_1->name = strdup("Alex");
    dequeue_el_1->age = 18;

    INFO_PART *dequeue_el_2 = malloc(sizeof(INFO_PART));
    dequeue_el_2->name = strdup("Henry");
    dequeue_el_2->age = 23;

    INFO_PART *dequeue_el_3 = malloc(sizeof(INFO_PART));
    dequeue_el_3->name = strdup("Lucas");
    dequeue_el_3->age = 19;

    INFO_PART *dequeue_el_4 = malloc(sizeof(INFO_PART));
    dequeue_el_4->name = strdup("Mia");
    dequeue_el_4->age = 27;

    pushFront(&pDequeue, dequeue_el_1);    // Alex
    pushFront(&pDequeue, dequeue_el_2);    // Henry
    pushBack(&pDequeue, dequeue_el_3);     // Lucas
    insertAt(&pDequeue, dequeue_el_4, 1);  // Mia

    printDequeue(pDequeue, printInfo);
    // Prints:
    // 0. Henry - 23 years.
    // 1. Mia - 27 years.
    // 2. Alex - 18 years.
    // 3. Lucas - 19 years.

    reverseDequeue(&pDequeue);
    // 0. Lucas - 19 years.
    // 1. Alex - 18 years.
    // 2. Mia - 27 years.
    // 3. Henry - 23 years.

    INFO_PART *pKey = malloc(sizeof(INFO_PART));
    pKey->age = 19;

    find(&pDequeue, pKey, compareByAge, printInfo); // 0. Lucas - 19 years.

    removeValue(&pDequeue, pKey, compareByAge, freeInfo);
    // 0. Alex - 18 years.
    // 1. Mia - 27 years.
    // 2. Henry - 23 years.

    removeAt(&pDequeue, 1);
    // 0. Alex - 18 years.
    // 1. Henry - 23 years.

    popFront(&pDequeue, printInfo);     // Alex - 18 years.
    // 0. Henry - 23 years.

    clearDequeue(&pDequeue, freeInfo);  // pDequeue is NULL now
    // -----------------------------------------------

    // -----------------------------------------------
    // "ds_bin_tree" LIBRARY USAGE EXAMPLE
    // -----------------------------------------------
    BinTree *pRoot;
    initBinaryTree(&pRoot); // Initializing the binary tree

    INFO_PART *tree_el_1 = malloc(sizeof(INFO_PART));
    tree_el_1->name = strdup("Adil");
    tree_el_1->age = 36;

    INFO_PART *tree_el_2 = malloc(sizeof(INFO_PART));
    tree_el_2->name = strdup("Mohammed");
    tree_el_2->age = 24;

    INFO_PART *tree_el_3 = malloc(sizeof(INFO_PART));
    tree_el_3->name = strdup("Marcus");
    tree_el_3->age = 45;

    INFO_PART *tree_el_4 = malloc(sizeof(INFO_PART));
    tree_el_4->name = strdup("Terry");
    tree_el_4->age = 52;

    addTreeNode(&pRoot, tree_el_1, compareByAgeForBinTree);
    addTreeNode(&pRoot, tree_el_2, compareByAgeForBinTree);
    addTreeNode(&pRoot, tree_el_3, compareByAgeForBinTree);

    printBinTree(pRoot, 0, printInfoBTree); //    "Level" parameter must be initialized with 0

    // -----------------------------------------------

    return 0;
}

// Custom function that prints the information part of stack/queue/dequeue element
void printInfo(INFO_PART *elementInfo) {
    printf("%s - %d years.\n", elementInfo->name, elementInfo->age);
}

// Custom function that prints the information part of binary tree element
void printInfoBTree(INFO_PART *elementInfo) {
    printf("%s (%d)", elementInfo->name, elementInfo->age);
}

// Custom function that frees the allocated memory after information part of node
void freeInfo(INFO_PART *elementInfo) {
    free(elementInfo->name);
    free(elementInfo);
}

// Custom comparison function
int compareByAge(INFO_PART *key, INFO_PART *pNode) {
    return key->age == pNode->age;
}

// Custom comparison function of binary tree nodes
int compareByAgeForBinTree(INFO_PART *info1, INFO_PART *info2) {
    return info1->age - info2->age;
}