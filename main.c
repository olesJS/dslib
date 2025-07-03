#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ds_stack.h"
#include "ds_queue.h"

typedef struct info_part {
    char *name;
    int age;
} INFO_PART;

void printInfo(INFO_PART *elementInfo);

int main() {
    // "ds_stack" LIBRARY USAGE EXAMPLE
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

    // "ds_queue" LIBRARY USAGE EXAMPLE
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

    return 0;
}

// Custom function that prints the information part of stack/queue element
void printInfo(INFO_PART *elementInfo) {
    printf("%s - %d years.\n", elementInfo->name, elementInfo->age);
}