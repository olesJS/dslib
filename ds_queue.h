#ifndef DS_QUEUE_H
#define DS_QUEUE_H

typedef struct queue_node {
    struct queue_node *next;
    void *info;
} QUEUE_NODE;

void initQueue(QUEUE_NODE **pQueueNode);

void pushToQueue(QUEUE_NODE **pQueueNode, void *newInfo);
void popFromQueue(QUEUE_NODE **pQueueNode, void (*printFunc)(void*));

int queueSize(QUEUE_NODE *pQueueNode);

void clearQueue(QUEUE_NODE **pNode);

#endif //DS_QUEUE_H
