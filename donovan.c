#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cacheProj.h"

/*
void printAddresses(CacheAttr *cacheAttr) {
    int i;

    for (i = 0; i < 20; i ++) {
        // printf("%s: (%d)\n", cacheAttr->first20Addresses[i].hexAddr, cacheAttr->first20Addresses[i].readLength);
    }
}
*/

void calcCost(CacheAttr *cacheAttr) {
    cacheAttr->cost = cacheAttr->implementationSize * COST_PER_KB;
}


/*
void freeCache(CacheAttr **cacheAttr) {
    free(*cacheAttr);
    *cacheAttr = NULL;
}
*/