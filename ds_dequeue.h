#ifndef DS_DEQUEUE_H
#define DS_DEQUEUE_H

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

void insertAt(DEQUEUE **pDequeue, void *newInfo, int index);
void removeAt(DEQUEUE **pDequeue, int index);

#endif //DS_DEQUEUE_H
