#include "ds_queue.h"
#include <stdlib.h>

// Accesing the last node of queue
QUEUE_NODE* getBackNode(QUEUE_NODE **pQueueNode) {
    QUEUE_NODE *pResultNode = *pQueueNode;

    while (pResultNode->next != NULL) {
        pResultNode = pResultNode->next;
    }

    return pResultNode;
}

// Initializing queue with a NULL value
void initQueue(QUEUE_NODE **pQueueNode) {
    *pQueueNode = NULL;
}

// Inserting new element to the back of queue
void pushToQueue(QUEUE_NODE **pQueueNode, void *newInfo) {
    QUEUE_NODE *pNewNode = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));

    pNewNode->info = newInfo;
    pNewNode->next = NULL;

    if (*pQueueNode == NULL) {
        *pQueueNode = pNewNode;
        return;
    }

    QUEUE_NODE *pLastNode = getBackNode(pQueueNode);
    pLastNode->next = pNewNode;
}

// Deleting the front element of queue
// The second parameter of this function is a custom function that prints the information part of the queue element
void popFromQueue(QUEUE_NODE **pQueueNode, void (*printFunc)(void*)) {
    if (*pQueueNode == NULL) return;

    QUEUE_NODE *pFirstNode = *pQueueNode;
    *pQueueNode = (*pQueueNode)->next;

    printFunc(pFirstNode->info);
    free(pFirstNode);
}

// Returns the number of elements in the queue
int queueSize(QUEUE_NODE *pQueueNode) {
    int counter = 0;
    QUEUE_NODE *pCurrentNode = pQueueNode;

    while (pCurrentNode != NULL) {
        counter++;
        pCurrentNode = pCurrentNode->next;
    }

    return counter;
}

// Removing all elements and cleaning up dynamic memory from the queue
void clearQueue(QUEUE_NODE **pNode) {
    QUEUE_NODE *pCurrentNode = *pNode;

    while (*pNode != NULL) {
        *pNode = (*pNode)->next;
        free(pCurrentNode);
        pCurrentNode = *pNode;
    }
}