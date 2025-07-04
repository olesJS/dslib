#include "ds_dequeue.h"

#include <stdio.h>
#include <stdlib.h>

// Initializing dequeue with NULL values and allocating dynamic memory
void initDequeue(DEQUEUE **pDequeue) {
    *pDequeue = (DEQUEUE*)malloc(sizeof(DEQUEUE));

    (*pDequeue)->front = NULL;
    (*pDequeue)->back = NULL;
    (*pDequeue)->size = 0;
}

// Inserting new element to the front of dequeue
void pushFront(DEQUEUE **pDequeue, void *newInfo) {
    DEQUEUE_NODE *pNewNode = (DEQUEUE_NODE*)malloc(sizeof(DEQUEUE_NODE));

    pNewNode->info = newInfo;
    pNewNode->prev = NULL;

    pNewNode->next = (*pDequeue)->front;

    if ((*pDequeue)->front != NULL) {
        (*pDequeue)->front->prev = pNewNode;
    } else {
        (*pDequeue)->back = pNewNode;
    }

    (*pDequeue)->front = pNewNode;

    if ((*pDequeue)->back == NULL) (*pDequeue)->back = pNewNode;

    (*pDequeue)->size += 1;
}

// Inserting new element to the back of dequeue
void pushBack(DEQUEUE **pDequeue, void *newInfo) {
    DEQUEUE_NODE *pNewNode = (DEQUEUE_NODE*)malloc(sizeof(DEQUEUE_NODE));

    pNewNode->info = newInfo;
    pNewNode->next = NULL;

    pNewNode->prev = (*pDequeue)->back;

    if ((*pDequeue)->back != NULL) {
        (*pDequeue)->back->next = pNewNode;
    } else {
        (*pDequeue)->front = pNewNode;
    }

    (*pDequeue)->back = pNewNode;

    if ((*pDequeue)->front == NULL) (*pDequeue)->front = pNewNode;

    (*pDequeue)->size += 1;
}

// Deleting the front element of dequeue
// The second parameter of this function is a custom function that prints the information part of the dequeue element
void popFront(DEQUEUE **pDequeue, void(*printFunc)(void*)) {
    if ((*pDequeue)->front == NULL) return;

    DEQUEUE_NODE *pFirstNode = (*pDequeue)->front;
    (*pDequeue)->front = (*pDequeue)->front->next;

    if ((*pDequeue)->front != NULL) {
        (*pDequeue)->front->prev = NULL;
    } else {
        (*pDequeue)->back = NULL;
    }

    printFunc(pFirstNode->info);
    free(pFirstNode);
    (*pDequeue)->size -= 1;
}

// Deleting the back element of dequeue
// The second parameter of this function is a custom function that prints the information part of the dequeue element
void popBack(DEQUEUE **pDequeue, void(*printFunc)(void*)) {
    if ((*pDequeue)->back == NULL) return;

    DEQUEUE_NODE *pLastNode = (*pDequeue)->back;
    (*pDequeue)->back = (*pDequeue)->back->prev;

    if ((*pDequeue)->back != NULL) {
        (*pDequeue)->back->next = NULL;
    } else {
        (*pDequeue)->front = NULL;
    }

    printFunc(pLastNode->info);
    free(pLastNode);
    (*pDequeue)->size -= 1;
}

// Getting size (number of elements) of the dequeue
int dequeueSize(DEQUEUE **pDequeue) {
    return (*pDequeue)->size;
}

// Printing all dequeue elements with their indexes
void printDequeue(DEQUEUE *pDequeue, void (*printFunc)(void*)) {
    DEQUEUE_NODE *pCurrentNode = pDequeue->front;
    int index = 0;

    while (pCurrentNode != NULL) {
        printf("\n%d. ", index++);
        printFunc(pCurrentNode->info);
        pCurrentNode = pCurrentNode->next;
    }
}

// Removing all dequeue elements and cleaning up dynamic memory from the dequeue
void clearDequeue(DEQUEUE **pDequeue, void(*freeFunc)(void*)) {
    DEQUEUE_NODE *pCurrentNode = (*pDequeue)->front;
    DEQUEUE_NODE *pNextNode;

    while (pCurrentNode != NULL) {
        pNextNode = pCurrentNode->next;

        freeFunc(pCurrentNode->info);
        free(pCurrentNode);

        pCurrentNode = pNextNode;
    }

    free(*pDequeue);
    *pDequeue = NULL;
}

// Inserting new element to dequeue in required position (by index)
void insertAt(DEQUEUE **pDequeue, void *newInfo, int idx) {
    if (idx > (*pDequeue)->size || idx < 0) {
        printf("\nERROR: INDEX IS OUT OF BOUNDS!\n");
        return;
    }

    DEQUEUE_NODE *pCurrentNode = (*pDequeue)->front;

    for (int i = 0; i < idx; i++) {
        pCurrentNode = pCurrentNode->next;
    }

    DEQUEUE_NODE *pNewNode = (DEQUEUE_NODE*)malloc(sizeof(DEQUEUE_NODE));

    pNewNode->info = newInfo;
    pNewNode->prev = pCurrentNode->prev;

    pCurrentNode->prev = pNewNode;
    pNewNode->next = pCurrentNode;

    if (pNewNode->prev != NULL) {
        pNewNode->prev->next = pNewNode;
    } else {
        (*pDequeue)->front = pNewNode;
    }

    (*pDequeue)->size += 1;
}

// Deleting element by its index
void removeAt(DEQUEUE **pDequeue, int idx) {
    if (idx > ((*pDequeue)->size - 1) || idx < 0) {
        printf("\nERROR: INDEX IS OUT OF BOUNDS!\n");
        return;
    }

    DEQUEUE_NODE *pCurrentNode = (*pDequeue)->front;

    for (int i = 0; i < idx; i++) {
        pCurrentNode = pCurrentNode->next;
    }

    if (pCurrentNode->prev == NULL) {
        (*pDequeue)->front = pCurrentNode->next;
        free(pCurrentNode);
        pCurrentNode = NULL;
        (*pDequeue)->size -= 1;
        return;
    }

    if (pCurrentNode->next == NULL) {
        (*pDequeue)->back = pCurrentNode->prev;
        free(pCurrentNode);
        pCurrentNode = NULL;
        (*pDequeue)->size -= 1;
        return;
    }

    pCurrentNode->prev->next = pCurrentNode->next;
    pCurrentNode->next->prev = pCurrentNode->prev;
    free(pCurrentNode);
    pCurrentNode = NULL;

    (*pDequeue)->size -= 1;
}

// Reversing dequeue
void reverseDequeue(DEQUEUE **pDequeue) {
    DEQUEUE_NODE *pCurrentNode = (*pDequeue)->front;

    while (pCurrentNode != NULL) {
        DEQUEUE_NODE *pNextNode = pCurrentNode->next;
        pCurrentNode->next = pCurrentNode->prev;
        pCurrentNode->prev = pNextNode;

        pCurrentNode = pNextNode;
    }

    DEQUEUE_NODE *pFrontNode = (*pDequeue)->front;
    (*pDequeue)->front = (*pDequeue)->back;
    (*pDequeue)->back = pFrontNode;
}

// Delete all elements containing the key value from dequeue
// cmpFunc(void*, void*) is a custom function that returns int value different from 0 if compared elements are matching
// Parameter "key" is the value you want to delete from dequeue
void removeValue(DEQUEUE **pDequeue, void *key, int (*cmpFunc)(void*, void*), void(*freeFunc)(void*)) {
    DEQUEUE_NODE *pCurrentNode = (*pDequeue)->front;

    while (pCurrentNode != NULL) {
        DEQUEUE_NODE *pNextNode = pCurrentNode->next;

        if (cmpFunc(key, pCurrentNode->info)) {
            if (pCurrentNode->prev != NULL) {
                pCurrentNode->prev->next = pCurrentNode->next;
            } else {
                (*pDequeue)->front = pCurrentNode->next;
            }

            if (pCurrentNode->next != NULL) {
                pCurrentNode->next->prev = pCurrentNode->prev;
            } else {
                (*pDequeue)->back = pCurrentNode->prev;
            }

            freeFunc(pCurrentNode->info);
            free(pCurrentNode);

            (*pDequeue)->size -= 1;
        }

        pCurrentNode = pNextNode;
    }
}

// Find element by value
// cmpFunc(void*, void*) is a custom function that returns int value different from 0 if compared elements are matching
// Parameter "key" is the value you are looking for
void find(DEQUEUE **pDequeue, void *key, int (*cmpFunc)(void*, void*), void (*printFunc)(void*)) {
    DEQUEUE_NODE *pCurrentNode = (*pDequeue)->front;
    int idx = 0;    // index of the element in dequeue

    while (pCurrentNode != NULL) {
        if (cmpFunc(key, pCurrentNode->info)) {
            printf("\n%d. ", idx);
            printFunc(pCurrentNode->info);
        }

        idx++;
        pCurrentNode = pCurrentNode->next;
    }
}