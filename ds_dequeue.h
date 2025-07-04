#ifndef DS_DEQUEUE_H
#define DS_DEQUEUE_H

// Dequeue is organized as a doubly linked list
typedef struct dequeue_node {
    struct dequeue_node *next;
    struct dequeue_node *prev;
    void *info;
} DEQUEUE_NODE;

typedef struct dequeue {
    DEQUEUE_NODE *front;
    DEQUEUE_NODE *back;
    int size;
} DEQUEUE;

void initDequeue(DEQUEUE **pDequeue);

void pushFront(DEQUEUE **pDequeue, void *newInfo);
void pushBack(DEQUEUE **pDequeue, void *newInfo);

void popFront(DEQUEUE **pDequeue, void(*printFunc)(void*));
void popBack(DEQUEUE **pDequeue, void(*printFunc)(void*));

int dequeueSize(DEQUEUE **pDequeue);

void printDequeue(DEQUEUE *pDequeue, void (*printFunc)(void*));
void clearDequeue(DEQUEUE **pDequeue, void(*freeFunc)(void*));

void insertAt(DEQUEUE **pDequeue, void *newInfo, int idx);
void removeAt(DEQUEUE **pDequeue, int idx);

void reverseDequeue(DEQUEUE **pDequeue);

void removeValue(DEQUEUE **pDequeue, void *key, int (*cmpFunc)(void*, void*), void(*freeFunc)(void*));
void find(DEQUEUE **pDequeue, void *key, int (*cmpFunc)(void*, void*), void (*printFunc)(void*));

#endif //DS_DEQUEUE_H