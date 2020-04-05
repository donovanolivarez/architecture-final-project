#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cacheProj.h"

void printHeader()
{
    printf("Cache Simulator - CS 3853 - Group #20\n\n");
}

CacheAttr *initCache()
{
    CacheAttr *newCache = (CacheAttr *)malloc(sizeof(CacheAttr));

    // Addresses newAddresses = (Addresses *)malloc(20 * sizeof(Addresses));
    // newCache->first20Addresses = newAddresses;
    // newCache->addrIndex = 0;
    return newCache;
}

void calcImplementationMem(CacheAttr *cacheAttr)
{
    cacheAttr->implementationSize = ((float)cacheAttr->overheadMemorySize / 1024) + cacheAttr->cacheSize / 1024;
}

void printGeneric(CacheAttr *cacheAttr)
{
    printf("***** Cache Input Parameters *****\n\n");
    
    printf("%-30s %ld KB\n", "Cache Size:", (cacheAttr->cacheSize / 1024));
    printf("%-30s %d bytes\n", "Block Size:", cacheAttr->blockSize);
    printf("%-30s %d\n", "Associativity:", cacheAttr->assoc);
    printf("%-30s %s\n\n", "Policy:", cacheAttr->policy);
}

void printCalcValues(CacheAttr *cacheAttr)
{
    printf("***** Cache Calculated Values *****\n\n");

    printf("%-30s %d\n", "Total # Blocks:", cacheAttr->totalBlocks);
    printf("%-30s %d bits\n", "Tag Size:", cacheAttr->tagSize);
    printf("%-30s %d bits, Total Rows: %d\n", "Index Size:", indexSizeToBits(cacheAttr), cacheAttr->indexSize);
    printf("%-30s %d\n", "Total # Rows:", cacheAttr->indexSize);
    printf("%-30s %d bytes\n", "Overhead Size:", cacheAttr->overheadMemorySize);
    printf("%-30s %.2lf KB (%d bytes)\n", "Implementation Memory Size:", cacheAttr->implementationSize, (int)cacheAttr->implementationSize * 1024);
    printf("%-30s $%.2lf\n\n", "Cost:", cacheAttr->cost);
}

void printResults(CacheAttr *cacheAttr)
{
    // NYI
}

int indexSizeToBits(CacheAttr *cacheAttr)
{
    return (int)log2(cacheAttr->indexSize);
}
