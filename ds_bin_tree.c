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
BinTree** findTreeNode(BinTree **pRootNode, void *neededInfo, int (*cmpFunc)(void*, void*)) {
    if (*pRootNode == NULL) {
        printf("\nERROR: FIND_TREE_NODE (ROOT NODE POINTER IS NULL)");
        return NULL;
    }

    BinTree **pCurrentNode = pRootNode;

    while (pCurrentNode != NULL) {
        int result = cmpFunc(neededInfo, (*pCurrentNode)->info);

        if (result == 0) return pCurrentNode;

        if (result < 0) {
            pCurrentNode = &((*pCurrentNode)->left);
        } else {
            pCurrentNode = &((*pCurrentNode)->right);
        }
    }

    return NULL; // not in the binary tree
}

// Deleting a node in BST
// "freeFunc()" frees dynamic memory after information part of the binary tree node
// "copyFunc()" creates and returns a copy of information part of node
void deleteTreeNode(BinTree **pNodeToDelete, void (*freeFunc)(void*), void* (*copyFunc)(void*)) {
    if (*pNodeToDelete == NULL) {
        printf("\nERROR: DELETE_TREE_NODE (PASSED UNEXISTING NODE)\n");
        return;
    }

    if ((*pNodeToDelete)->left == NULL && (*pNodeToDelete)->right == NULL) { // a leaf node
        freeFunc((*pNodeToDelete)->info);
        free(*pNodeToDelete);
        *pNodeToDelete = NULL;
        return;
    }

    if ((*pNodeToDelete)->left == NULL) { // has only right child
        BinTree *tempNode = (*pNodeToDelete)->right;
        freeFunc((*pNodeToDelete)->info);
        free(*pNodeToDelete);
        *pNodeToDelete = tempNode;
        return;
    }

    if ((*pNodeToDelete)->right == NULL) { // has only left child
        BinTree *tempNode = (*pNodeToDelete)->left;
        freeFunc((*pNodeToDelete)->info);
        free(*pNodeToDelete);
        *pNodeToDelete = tempNode;
        return;
    }

    // has two children
    BinTree *pLeftSubtree = *pNodeToDelete;
    BinTree *pLeftSubMax = (*pNodeToDelete)->left;

    while (pLeftSubMax->right != NULL) {
        pLeftSubtree = pLeftSubMax;
        pLeftSubMax = pLeftSubMax->right;
    }

    freeFunc((*pNodeToDelete)->info);
    (*pNodeToDelete)->info = copyFunc(pLeftSubMax->info);
    freeFunc(pLeftSubMax->info);

    if (pLeftSubtree == *pNodeToDelete) {
        pLeftSubtree->left = pLeftSubMax->left;
    } else {
        pLeftSubtree->right = pLeftSubMax->left;
    }

    free(pLeftSubMax);
}

// Deleting and clearing memory after all nodes of binary tree
// The function is recursive and uses postorder traversal
void clearBinaryTree(BinTree **pRootNode, void (*freeFunc)(void*)) {
    if (*pRootNode == NULL) return;

    clearBinaryTree(&(*pRootNode)->left, freeFunc);
    clearBinaryTree(&(*pRootNode)->right, freeFunc);

    freeFunc((*pRootNode)->info);
    free(*pRootNode);
    *pRootNode = NULL;
}

// Returns information part of node with minimal key in BST
void* getMinValueBST(BinTree *pRootNode) {
    if (pRootNode == NULL) return NULL;

    BinTree *pCurrentNode = pRootNode;
    while (pCurrentNode->left != NULL) pCurrentNode = pCurrentNode->left;

    return pCurrentNode->info;
}

// Returns information part of node with maximal key in BST
void* getMaxValueBST(BinTree *pRootNode) {
    if (pRootNode == NULL) return NULL;

    BinTree *pCurrentNode = pRootNode;
    while (pCurrentNode->right != NULL) pCurrentNode = pCurrentNode->right;

    return pCurrentNode->info;
}

// Recursively (inorder) counts number of nodes in binary tree
void countNodesBST(BinTree *pRootNode, int *counter) {
    if (pRootNode == NULL) return;

    countNodesBST(pRootNode->left, counter);
    (*counter)++;
    countNodesBST(pRootNode->right, counter);
}

// Recursively (inorder) counts number of leaves in binary tree
void countLeavesBST(BinTree *pRootNode, int *counter) {
    if (pRootNode == NULL) return;

    countLeavesBST(pRootNode->left, counter);
    if (pRootNode->left == NULL && pRootNode->right == NULL) (*counter)++;
    countLeavesBST(pRootNode->right, counter);
}

// Counts the height (depth) of binary tree
int countHeightBST(BinTree *pRootNode) {
    if (pRootNode == NULL) return 0;

    int leftHeight = countHeightBST(pRootNode->left);
    int rightHeight = countHeightBST(pRootNode->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Checks if binary search tree is balanced or not
int isBalancedBST(BinTree *pRootNode) {
    if (pRootNode == NULL) return 1;

    int leftHeight = countHeightBST(pRootNode->left);
    int rightHeight = countHeightBST(pRootNode->right);

    int difference = leftHeight - rightHeight;
    if (difference > 1 || difference < -1) return 0;

    return isBalancedBST(pRootNode->left) && isBalancedBST(pRootNode->right);
}

// Prints tree traversed inorder
void inorderTraversalBST(BinTree *pRootNode, void (*printFunc)(void*)) {
    if (pRootNode == NULL) return;

    inorderTraversalBST(pRootNode->left, printFunc);
    printFunc(pRootNode->info);
    inorderTraversalBST(pRootNode->right, printFunc);
}

// Prints tree traversed preorder
void preorderTraversalBST(BinTree *pRootNode, void (*printFunc)(void*)) {
    if (pRootNode == NULL) return;

    printFunc(pRootNode->info);
    inorderTraversalBST(pRootNode->left, printFunc);
    inorderTraversalBST(pRootNode->right, printFunc);
}

// Prints tree traversed postorder
void postorderTraversalBST(BinTree *pRootNode, void (*printFunc)(void*)) {
    if (pRootNode == NULL) return;

    inorderTraversalBST(pRootNode->left, printFunc);
    inorderTraversalBST(pRootNode->right, printFunc);
    printFunc(pRootNode->info);
}

void storeInorder(BinTree **pRootNode, void** nodesList, int *idx, void* (*copyFunc)(void*)) {
    if (*pRootNode == NULL) return;

    storeInorder(&(*pRootNode)->left, nodesList, idx, copyFunc);
    nodesList[(*idx)++] = copyFunc((*pRootNode)->info);
    storeInorder(&(*pRootNode)->right, nodesList, idx, copyFunc);
}

BinTree* buildBalancedBST(void** nodesList, int startIdx, int endIdx) {
    if (startIdx > endIdx) return NULL;

    int midIdx = (startIdx + endIdx) / 2;
    BinTree* pRoot = (BinTree*)malloc(sizeof(BinTree));
    pRoot->info = nodesList[midIdx];

    pRoot->left = buildBalancedBST(nodesList, startIdx, midIdx - 1);
    pRoot->right = buildBalancedBST(nodesList, midIdx + 1, endIdx);

    return pRoot;
}

BinTree* balanceBST(BinTree *pRoot, void* (*copyFunc)(void*)) {
    int treeSize = 0;
    countNodesBST(pRoot, &treeSize);

    void** nodesList = malloc(sizeof(void*) * treeSize);

    int idx = 0;
    storeInorder(&pRoot, nodesList, &idx, copyFunc);

    return buildBalancedBST(nodesList, 0, treeSize - 1);
}