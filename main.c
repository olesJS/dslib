#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ds_stack.h"

typedef struct stack_info_part {
    char *name;
    int age;
} INFO_STACK;

void printStack(INFO_STACK *stack_element);

int main() {
    // "ds_stack" library usage example
    STACK_NODE *pStack;

    initStack(&pStack);

    // Pushing elements of INFO_STACK type to stack
    INFO_STACK *stack_el_1 = malloc(sizeof(INFO_STACK));
    stack_el_1->name = strdup("John");
    stack_el_1->age = 18;

    pushToStack(&pStack, stack_el_1);

    INFO_STACK *stack_el_2 = malloc(sizeof(INFO_STACK));
    stack_el_2->name = strdup("Mary");
    stack_el_2->age = 21;

    pushToStack(&pStack, stack_el_2);

    INFO_STACK *stack_el_3 = malloc(sizeof(INFO_STACK));
    stack_el_3->name = strdup("Michael");
    stack_el_3->age = 25;

    pushToStack(&pStack, stack_el_3);

    printf("Size of stack: %d\n", stackSize(pStack)); // Size of stack: 3

    // printStack - is a custom function
    popFromStack(&pStack, printStack); // Michael - 25 years
    popFromStack(&pStack, printStack); // Mary - 21 years

    printf("Size of stack: %d\n", stackSize(pStack)); // Size of stack: 1

    clearStack(&pStack);
    printf("Size of stack: %d\n", stackSize(pStack)); // Size of stack: 0

    // Manually freeing dynamic memory after INFO_STACK elements
    free(stack_el_1->name);
    free(stack_el_1);
    free(stack_el_2->name);
    free(stack_el_2);
    free(stack_el_3->name);
    free(stack_el_3);

    return 0;
}

// Custom function that prints the information part of stack element
void printStack(INFO_STACK *stack_element) {
    printf("%s - %d years.\n", stack_element->name, stack_element->age);
}