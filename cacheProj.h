#pragma once
/*******************************************************************
Made by: David Crouch, Lorin Rodriguez, and Donovan Olivarez

*******************************************************************/

// Typedefs
#define TRUE 1
#define FALSE 0
#define COST_PER_KB .05f
#define CPU_SIZE 32

// structs
typedef struct Addresses
{
    char hexAddr[10];
    int hexVal;
    int readLength;
}Addresses;

typedef struct CacheAttr
{
    long cacheSize; // in KB
    int blockSize; // bytes
    int assoc; 
    char policy[20];

    int totalBlocks;
    int tagSize;
    int indexSize;
    int overheadMemorySize; // in B
    float implementationSize; // in KB

    float cacheHitRate;
    float CPI;
    float cost;
    float unusedCacheSpace;

    // Addresses first20Addresses[20];
    // int addrIndex;
}CacheAttr;

// functions
void printHeader(); // David
void printAddresses(CacheAttr *cacheAttr); //Donovan
CacheAttr *initCache(); // David
void freeCache(CacheAttr *cacheAttr); //Donovan
void parseFile(CacheAttr *cacheAttr, FILE *file);
void parseCommand(CacheAttr* cacheAttr, char **fileName, int argc, char* argv[]); // Lorin
void calcNumOfBlks(CacheAttr* cacheAttr); // Lorin
void calcTagSize(CacheAttr* cacheAttr); // Lorin
void calcIndexSize(CacheAttr* cacheAttr); // Lorin
void calcOverheadMem(CacheAttr* cacheAttr); // Lorin
void calcImplementationMem(CacheAttr* cacheAttr); // David
void calcCost(CacheAttr* cacheAttr);
int indexSizeToBits(CacheAttr* cacheAttr);

void printGeneric(CacheAttr* cacheAttr); // David
void printCalcValues(CacheAttr* cacheAttr); // David
void printResults(CacheAttr* cacheAttr); // David