#ifndef DS_HASH_TABLE_H
#define DS_HASH_TABLE_H

// "ds_hash_table" uses DOUBLE HASHING for working with hash tables

typedef enum hash_cell_flag {
    DELETED_CELL = -1,
    EMPTY_CELL = 0,
    OCCUPIED_CELL = 1
} HASH_CELL_FLAG;

typedef struct hash_cell {
    HASH_CELL_FLAG flag;
    void* info; // Information part
} HASH_CELL;

typedef struct hash_table {
    int size;   // Number of cells in the hash table
    int occupiedCells;  // Count of occupied cells
    double maxLoadCoefficient;

    HASH_CELL *hashCells;

    int (*firstHash)(void*);    // First custom hash function
    int (*secondHash)(void*);   // Second custom hash function
} HASH_TABLE;

HASH_TABLE* initHashTable(int numberOfCells, double loadCoef, int (*fHash)(void*), int (*sHash)(void*));
void deleteHashTable(HASH_TABLE** pHashTable, void (*freeFunc)(void*));

void printHashTable(HASH_TABLE* pHashTable, void (*printFunc)(void*));

void addNewElementHT(HASH_TABLE* pHashTable, void* newInfo);
void deleteElementHT(HASH_TABLE* pHashTable, void* seekInfo, void (*freeFunc)(void*));

void findCell(HASH_TABLE* pHashTable, void* seekInfo, void (*printFunc)(void*));

double getLoadCoefficient(HASH_TABLE* pHashTable);

void clearHashTable(HASH_TABLE* pHashTable, void (*freeFunc)(void*));

HASH_TABLE* resizeHashTable(HASH_TABLE** pHashTable, int newSize, int (*newFirstHash)(void*), int (*newSecondHash)(void*), void* (*copyFunc)(void*), void (*freeFunc)(void*));

#endif //DS_HASH_TABLE_H
