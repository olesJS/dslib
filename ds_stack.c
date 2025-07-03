#include "ds_stack.h"
#include <stdlib.h>

// Initializing stack with a NULL value
void initStack(STACK_NODE **pNode) {
    *pNode = NULL;
}

// Inserting new element to the top of stack
void pushToStack(STACK_NODE **pStartNode, void *newInfo) {
    STACK_NODE *pNewStackNode = (STACK_NODE*)malloc(sizeof(STACK_NODE));

    pNewStackNode->info = newInfo;
    pNewStackNode->next = *pStartNode;

    *pStartNode = pNewStackNode;
}

// Deleting the top element of stack
// The second parameter of this function is a custom function that prints the information part of the stack element
void popFromStack(STACK_NODE **pStartNode, void (*printFunc)(void*)) {
    if (*pStartNode == NULL) return;

    STACK_NODE* pResultNode = *pStartNode;

    *pStartNode = (*pStartNode)->next;
    printFunc(pResultNode->info);

    free(pResultNode);
}

// Returns the number of elements in the stack
int stackSize(STACK_NODE *pStartNode) {
    int size = 0;

    STACK_NODE *pNode = pStartNode;
    while (pNode != NULL) {
        size++;
        pNode = pNode->next;
    }

    return size;
}

// Removing all elements and cleaning up dynamic memory from the stack
void clearStack(STACK_NODE **pStartNode) {
    STACK_NODE *pCurrentNode = *pStartNode;

    while (*pStartNode != NULL) {
        *pStartNode = (*pStartNode)->next;
        free(pCurrentNode);
        pCurrentNode = *pStartNode;
    }
}
