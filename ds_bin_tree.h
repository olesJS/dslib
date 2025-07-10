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
void deleteTreeNode(BinTree **pNodeToDelete, void (*freeFunc)(void*), void* (*copyFunc)(void*));

void printBinTree(BinTree *pRootNode, int level, void (*printFunc)(void*));

void clearBinaryTree(BinTree **pRootNode, void (*freeFunc)(void*));

BinTree** findTreeNode(BinTree **pRootNode, void *neededInfo, int (*cmpFunc)(void*, void*));

void* getMinValueBST(BinTree *pRootNode);
void* getMaxValueBST(BinTree *pRootNode);

void countNodesBST(BinTree *pRootNode, int *counter);
void countLeavesBST(BinTree *pRootNode, int *counter);
int countHeightBST(BinTree *pRootNode);
int isBalancedBST(BinTree *pRootNode);

void inorderTraversalBST(BinTree *pRootNode, void (*printFunc)(void*));
void preorderTraversalBST(BinTree *pRootNode, void (*printFunc)(void*));
void postorderTraversalBST(BinTree *pRootNode, void (*printFunc)(void*));

BinTree* balanceBST(BinTree *pRoot, void* (*copyFunc)(void*));

#endif //DS_BIN_TREE_H
