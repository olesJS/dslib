#include "ds_hash_table.h"

#include <stdlib.h>
#include <stdio.h>

// Allocating memory and setting parameters for hash table
// Requires two hash functions that will be set for hash table
HASH_TABLE* initHashTable(int numberOfCells, double loadCoef, int (*fHash)(void*), int (*sHash)(void*)) {
    HASH_TABLE* newHashTable = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));

    if (numberOfCells > 0) {
        newHashTable->size = numberOfCells;
    } else {
        printf("\nERROR: HASH TABLE SIZE\n");
        return NULL;
    }

    if (loadCoef > 0 && loadCoef < 1) {
        newHashTable->maxLoadCoefficient = loadCoef;
    } else {
        printf("\nERROR: HASH TABLE LOAD COEFFICIENT\n");
        return NULL;
    }

    newHashTable->hashCells = (HASH_CELL*)malloc(sizeof(HASH_CELL) * numberOfCells);

    for (int i = 0; i < numberOfCells; i++) {
        newHashTable->hashCells[i].flag = EMPTY_CELL;
    }

    newHashTable->firstHash = fHash;
    newHashTable->secondHash = sHash;

    return newHashTable;
}

// Deleting cells of hash table and freeing dynamic memory after hash table
void deleteHashTable(HASH_TABLE** pHashTable, void (*freeFunc)(void*)) {
    if (pHashTable == NULL) {
        printf("\nERROR: HASH TABLE POINTER IS NULL\n");
        return;
    }

    for (int i = 0; i < (*pHashTable)->size; i++) {
        HASH_CELL *pCurrentCell = &(*pHashTable)->hashCells[i];

        if (pCurrentCell->flag == OCCUPIED_CELL) {
            freeFunc(pCurrentCell->info);
        }
    }

    free((*pHashTable)->hashCells);
    (*pHashTable)->hashCells = NULL;
    free(*pHashTable);
    *pHashTable = NULL; // <------ problem here
}

// Calculating hash code of required cell
int doubleHash(HASH_TABLE* pHashTable, void* elementInfo, int iteration) {
    if (pHashTable == NULL) return 0;

    return (pHashTable->firstHash(elementInfo) + pHashTable->secondHash(elementInfo) * iteration) % pHashTable->size;
}

// Printing all cells with their information part (or their status if they are not occupied)
// Requires custom print function for information part: printFunc(void*)
void printHashTable(HASH_TABLE* pHashTable, void (*printFunc)(void*)) {
    if (pHashTable == NULL) {
        printf("\nERROR: HASH TABLE POINTER IS NULL\n");
        return;
    }

    for (int i = 0; i < pHashTable->size; i++) {
        printf("\n%d. ", i);

        switch (pHashTable->hashCells[i].flag) {
            case EMPTY_CELL:
                printf("EMPTY");
                break;
            case OCCUPIED_CELL:
                printFunc(pHashTable->hashCells[i].info);
                break;
            case DELETED_CELL:
                printf("DELETED");
                break;
        }
    }
}

// Adding new element to hash table
void addNewElementHT(HASH_TABLE* pHashTable, void* newInfo) {
    if (pHashTable == NULL) {
        printf("\nERROR: HASH TABLE POINTER IS NULL\n");
        return;
    }

    if ((double)(pHashTable->occupiedCells + 1) / pHashTable->size > pHashTable->maxLoadCoefficient) {
        printf("\nERROR: HASH TABLE WILL BE OVERLOADED\n");
        return;
    }

    for (int i = 0; i < pHashTable->size; i++) {
        HASH_CELL* pCurrentCell = &pHashTable->hashCells[doubleHash(pHashTable, newInfo, i)];

        if (pCurrentCell->flag == EMPTY_CELL || pCurrentCell->flag == DELETED_CELL) {
            pCurrentCell->info = newInfo;
            pCurrentCell->flag = OCCUPIED_CELL;
            pHashTable->occupiedCells++;
            return;
        }
    }
}

// Deleting element from hash table
// Requires custom function that frees dynamic memory after information part of cell: freeFunc(void*)
void deleteElementHT(HASH_TABLE* pHashTable, void* seekInfo, void (*freeFunc)(void*)) {
    if (pHashTable == NULL) {
        printf("\nERROR: HASH TABLE POINTER IS NULL\n");
        return;
    }

    for (int i = 0; i < pHashTable->size; i++) {
        HASH_CELL *pCurrentCell = &pHashTable->hashCells[doubleHash(pHashTable, seekInfo, i)];

        if (pCurrentCell->flag == OCCUPIED_CELL || pCurrentCell->info == seekInfo) {
            freeFunc(pCurrentCell->info);
            pCurrentCell->info = NULL;
            pCurrentCell->flag = DELETED_CELL;
            pHashTable->occupiedCells--;
            return;
        }
    }
}

// Prints an element if it is in hash table
// Requires custom print function for information part: printFunc(void*)
void findCell(HASH_TABLE* pHashTable, void* seekInfo, void (*printFunc)(void*)) {
    if (pHashTable == NULL) {
        printf("\nERROR: HASH TABLE POINTER IS NULL\n");
        return;
    }

    for (int i = 0; i < pHashTable->size; i++) {
        HASH_CELL *pCurrentCell = &pHashTable->hashCells[doubleHash(pHashTable, seekInfo, i)];

        if (pCurrentCell->info == seekInfo || pCurrentCell->flag == OCCUPIED_CELL) {
            printf("\n%d. ", doubleHash(pHashTable, seekInfo, i));
            printFunc(pCurrentCell->info);
            return;
        }
    }

    printf("\nCELL WAS NOT FOUND IN HASH TABLE\n");
}

// Returns load coefficient of hash table in the moment
double getLoadCoefficient(HASH_TABLE* pHashTable) {
    if (pHashTable == NULL) {
        printf("\nERROR: HASH TABLE POINTER IS NULL\n");
        return -1;
    }

    return (double)pHashTable->occupiedCells / (double)pHashTable->size;
}

// Deleting and freeing memory after occupied cells
// Saves the hash table and its structure
// Requires custom function that frees dynamic memory after information part of cell: freeFunc(void*)
void clearHashTable(HASH_TABLE* pHashTable, void (*freeFunc)(void*)) {
    if (pHashTable == NULL) return;

    for (int i = 0; i < pHashTable->size; i++) {
        HASH_CELL* pCurrentCell = &pHashTable->hashCells[i];

        if (pCurrentCell->flag == OCCUPIED_CELL) {
            freeFunc(pCurrentCell->info);
        }

        pCurrentCell->flag = EMPTY_CELL;
    }

    pHashTable->occupiedCells = 0;
}

// Creates a new hash table with new size
// Returns the pointer to new hash table
// Deletes the old hash table
// Requires two new hash functions that will be set for resized hash table
// Requires functions that creates a deep copy of information part: void* copyFunc(void*)
// Requires custom function that frees dynamic memory after information part of cell: freeFunc(void*)
HASH_TABLE* resizeHashTable(HASH_TABLE** pHashTable, int newSize, int (*newFirstHash)(void*), int (*newSecondHash)(void*), void* (*copyFunc)(void*), void (*freeFunc)(void*)) {
    if (pHashTable == NULL) {
        printf("\nERROR: HASH TABLE POINTER IS NULL\n");
        return NULL;
    }

    if ((double)(*pHashTable)->occupiedCells / newSize > (*pHashTable)->maxLoadCoefficient) {
        printf("\nERROR: HASH TABLE WILL OVERLOAD WITH NEW SIZE\n");
        return NULL;
    }

    HASH_TABLE *pResizedHashTable = initHashTable(newSize, (*pHashTable)->maxLoadCoefficient, newFirstHash, newSecondHash);

    if (pResizedHashTable == NULL) {
        printf("\nERROR: MEMORY ALLOCATION FOR RESIZED HASH TABLE FAILED\n");
        return NULL;
    }

    for (int i = 0; i < (*pHashTable)->size; i++) {
        if ((*pHashTable)->hashCells[i].flag == OCCUPIED_CELL) {
            void* infoCopy = copyFunc((*pHashTable)->hashCells[i].info);

            addNewElementHT(pResizedHashTable, infoCopy);
        }
    }

    deleteHashTable(pHashTable, freeFunc);
    return pResizedHashTable;
}