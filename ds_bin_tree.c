#include "ds_bin_tree.h"

#include <stdio.h>
#include <stdlib.h>

// Initializing a binary tree root node with a NULL value
void initBinaryTree(BinTree **pRootNode) {
    *pRootNode = NULL;
}

// Creating a new node and linking it to the binary tree
// "cmpFunc()" function must return a negative value (<0) if the first parameter is less than the second ->
// -> and a positive value (>0) if the first parameter is bigger than the second one
void addTreeNode(BinTree **pRootNode, void *newInfo, int (*cmpFunc)(void*, void*)) {
    BinTree *pNewNode = (BinTree*)malloc(sizeof(BinTree));
    pNewNode->info = newInfo;
    pNewNode->left = NULL;
    pNewNode->right = NULL;

    if (*pRootNode == NULL) {
        *pRootNode = pNewNode;
        return;
    }

    BinTree *pCurrentNode = *pRootNode;

    while (1) {
        if (cmpFunc(pNewNode->info, pCurrentNode->info) < 0) {
            if (pCurrentNode->left == NULL) {
                pCurrentNode->left = pNewNode;
                return;
            }

            pCurrentNode = pCurrentNode->left;
        } else {
            if (pCurrentNode->right == NULL) {
                pCurrentNode->right = pNewNode;
                return;
            }

            pCurrentNode = pCurrentNode->right;
        }
    }
}

// Recursively printing binary tree horizontally
// "Level" parameter must be initialized with 0
void printBinTree(BinTree *pRootNode, int level, void (*printFunc)(void*)) {
    if (pRootNode == NULL) return;

    printBinTree(pRootNode->right, level + 1, printFunc);
    printf("\n%*c", level * TAB_SIZE_FOR_PRINTING_TREE, ' ');
    printFunc(pRootNode->info);
    printBinTree(pRootNode->left, level + 1, printFunc);
}

// Finding a node in binary tree
// "cmpFunc()" must return 0 if nodes' information parts are the same ->
// -> a negative value (<0) if the first parameter is less tan the second one ->
// -> a positive value (>0) if the first parameter is bigger than the second one
// "neededInfo" parameter is the information part you are looking for
BinTree* findTreeNode(BinTree **pRootNode, void *neededInfo, int (*cmpFunc)(void*, void*)) {
    if (*pRootNode == NULL) return NULL;

    BinTree *pCurrentNode = *pRootNode;

    while (pCurrentNode != NULL) {
        int result = cmpFunc(pCurrentNode->info, neededInfo);

        if (result == 0) return pCurrentNode;

        if (result < 0) {
            pCurrentNode = pCurrentNode->left;
        } else {
            pCurrentNode = pCurrentNode->right;
        }
    }

    return NULL; // not in the binary tree
}
