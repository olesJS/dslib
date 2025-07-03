#include "ds_dequeue.h"

#include <stdio.h>
#include <stdlib.h>

void initDequeue(DEQUEUE **pDequeue) {
    *pDequeue = (DEQUEUE*)malloc(sizeof(DEQUEUE));
    (*pDequeue)->front = NULL;
    (*pDequeue)->back = NULL;
    (*pDequeue)->size = 0;
}

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

    if ((*pDequeue)->back == NULL) {
        (*pDequeue)->back = pNewNode;
    }

    (*pDequeue)->size += 1;
}

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

    if ((*pDequeue)->front == NULL) {
        (*pDequeue)->front = pNewNode;
    }

    (*pDequeue)->size += 1;
}

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

int dequeueSize(DEQUEUE **pDequeue) {
    return (*pDequeue)->size;
}

void printDequeue(DEQUEUE *pDequeue, void (*printFunc)(void*)) {
    DEQUEUE_NODE *pCurrentNode = pDequeue->front;
    int index = 0;

    while (pCurrentNode != NULL) {
        printf("\n%d. ", index++);
        printFunc(pCurrentNode->info);
        pCurrentNode = pCurrentNode->next;
    }
}

void insertAt(DEQUEUE **pDequeue, void *newInfo, int index) {
    if (index > ((*pDequeue)->size - 1) || index < 0) {
        printf("\nERROR: INDEX IS OUT OF BONDS!\n");
        return;
    }

    DEQUEUE_NODE *pCurrentNode = (*pDequeue)->front;

    for (int i = 0; i < index; i++) {
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

void removeAt(DEQUEUE **pDequeue, int index) {
    if (index > ((*pDequeue)->size - 1) || index < 0) {
        printf("\nERROR: INDEX IS OUT OF BONDS!\n");
        return;
    }

    DEQUEUE_NODE *pCurrentNode = (*pDequeue)->front;

    for (int i = 0; i < index; i++) {
        pCurrentNode = pCurrentNode->next;
    }

    if (pCurrentNode->prev == NULL) {
        (*pDequeue)->front = pCurrentNode->next;
        free(pCurrentNode);
        pCurrentNode = NULL;
        return;
    }

    if (pCurrentNode->next == NULL) {
        (*pDequeue)->back = pCurrentNode->prev;
        free(pCurrentNode);
        pCurrentNode = NULL;
        return;
    }

    pCurrentNode->prev->next = pCurrentNode->next;
    pCurrentNode->next->prev = pCurrentNode->prev;
    free(pCurrentNode);
    pCurrentNode = NULL;

    (*pDequeue)->size -= 1;
}