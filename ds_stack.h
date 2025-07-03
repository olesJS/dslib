#ifndef DS_STACK_H
#define DS_STACK_H

typedef struct stack_node {
    struct stack_node *next;
    void *info;
} STACK_NODE;

void initStack(STACK_NODE **pNode);

void pushToStack(STACK_NODE **pStartNode, void *newInfo);
void popFromStack(STACK_NODE **pStartNode, void (*printFunc)(void*));

int stackSize(STACK_NODE *pStartNode);

void clearStack(STACK_NODE **pStartNode);

#endif //DS_STACK_H
