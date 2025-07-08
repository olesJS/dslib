#ifndef DS_BIN_TREE_H
#define DS_BIN_TREE_H

#define TAB_SIZE_FOR_PRINTING_TREE 15

typedef struct bin_tree {
    void *info;
    struct bin_tree *left;
    struct bin_tree *right;
} BinTree;

void initBinaryTree(BinTree **pRootNode);
void addTreeNode(BinTree **pRootNode, void *newInfo, int (*cmpFunc)(void*, void*));

void printBinTree(BinTree *pRootNode, int level, void (*printFunc)(void*));

BinTree* findTreeNode(BinTree **pRootNode, void *neededInfo, int (*cmpFunc)(void*, void*));

#endif //DS_BIN_TREE_H
