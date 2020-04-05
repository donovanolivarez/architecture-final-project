#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cacheProj.h"

int main(int argc, char *argv[]) {
	struct CacheAttr *cache;
	char *fileName = "null";
	FILE* file;
	cache = initCache();
	
	if (cache==NULL) {
		printf("Malloc Error");
		exit(1);
	}

	parseCommand(cache, &fileName, argc, argv);

	if ((file = fopen(fileName, "r")) == NULL) {
		printf("Cannot open file '%s'!", fileName);
		exit(1);
	}

	calcNumOfBlks(cache);
	calcIndexSize(cache);
	calcTagSize(cache);
	calcOverheadMem(cache);
    calcImplementationMem(cache);
    calcCost(cache);
    printHeader();
    printf("Trace File: %s\n\n", fileName );
    printGeneric(cache);
    printCalcValues(cache);
    parseFile(cache, file);

	free(cache);
	fclose(file);
	return 0;
}