#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cacheProj.h"


int strToHex(char* h) {

	int value = 0;
	int len = strlen(h);
	for (int i = 0; i < len; i++) {
		int n = h[i] - '0';
		if (h[i] == '0') {
			value = value + 0;
		}
		else if (n > 0 && n < 10) {
			int pos = len - 1 - i;
			value = value + (int)(n * pow(16, pos));
		}
		else {
			int num = (int)h[i] - 87;
			int pos = len - 1 - i;
			value = value + (int)(num * pow(16, pos));
		}
	}
	return value;
}

void parseFile(CacheAttr* cacheAttr, FILE* file) {
	char line[128];
	int ct = 0;
	while (fgets(line, sizeof line, file) != NULL) {
		if (line[0] == 'E' && ct < 20) {
			struct Addresses address;
			char h[9] = {'\0'};
			char l[3] = {'\0'};

			memcpy(l, &line[5], 2);
			memcpy(h, &line[10], 8);

			int len = atoi(l);
			// strcpy(address.hexAddr, h);
			// address.readLength = len;
			// address.hexVal = strToHex(h);
			
			printf("%#010x: (%d)\n", strToHex(h), len);

			// cacheAttr->first20Addresses[ct] = address;
			ct++;
		}
	}
}

void parseCommand(CacheAttr *cacheAttr, char **fileName, int argc, char *argv[]) {

	for (int i = 1; i < argc; i = i + 2) {
		if (strcmp(argv[i], "-f") == 0) {
			//file
			*fileName = argv[i + 1];
		}
		else if (strcmp(argv[i], "-s") == 0) {
			//cache Range: 1KB - 8MB
			int c = atoi(argv[i + 1]) * 1024; //multiply by KB 2^10 = 1024
			if (c >= pow(2, 10) && c <= (8 * pow(2, 20))) {
				cacheAttr->cacheSize = c;
			}
			else {
				printf("Cache size needs to be in the range of 1 KB - 8 MB; takes input as KB");
				exit(1);
			}
		}
		else if (strcmp(argv[i], "-b") == 0) {
			//blk size in bytes Range: 4-64 bytes
			if (atoi(argv[i + 1]) >= 4 && atoi(argv[i + 1]) <= 64) {
				cacheAttr->blockSize = atoi(argv[i + 1]);
			}
			else {
				printf("Block size needs to be in the range of 4 - 64 bytes; takes input as a byte");
				exit(1);
			}
		}
		else if (strcmp(argv[i], "-a") == 0) {
			//associativity
			int a = atoi(argv[i + 1]);
			if ( a == 1 || a == 2 || a == 4 || a == 8 || a == 16) {
				cacheAttr->assoc = a;
			}
			else {
				printf("Associativity can only be 1, 2, 4, 8, or 16");
				exit(1);
			}
			
		}
		else if (strcmp(argv[i], "-r") == 0) {
			//replacement policy
			if (strcmp(argv[i + 1], "RR") == 0 ) {
				strcpy(cacheAttr->policy, "Round Robin");

			}
			else if(strcmp(argv[i + 1], "RND") == 0){
				strcpy(cacheAttr->policy, "Random");
			}
			else {
				printf("Policy can only be RR or RND");
				exit(1);
			}
		}
		else {
			printf("\n'%s' is not an option", argv[i]);
			printf("Usage: %s -f <file> -s <cache size 1024-8192 KB> -b <blk size 4-64 bytes> -a <associativity: [1,2,4,8,16]> -r <replacement policy: RR, RND>", argv[0]);
			exit(1);
		}
	}

}// Lorin

void calcNumOfBlks(CacheAttr *cacheAttr) {
	cacheAttr->totalBlocks = cacheAttr->cacheSize / cacheAttr->blockSize;
}
void calcTagSize(CacheAttr *cacheAttr) {
	cacheAttr->tagSize = CPU_SIZE - (int)log2(cacheAttr->blockSize) - (int)log2(cacheAttr->indexSize);
}
void calcIndexSize(CacheAttr *cacheAttr) {
	cacheAttr->indexSize = cacheAttr->cacheSize / (cacheAttr->blockSize * cacheAttr->assoc);
}

void calcOverheadMem(CacheAttr *cacheAttr) {
	//In Bytes
	cacheAttr->overheadMemorySize = (cacheAttr->totalBlocks * (cacheAttr->tagSize + 1)) / 8;
}


/*
int main(int argc, char *argv[]) {
	struct CacheAttr *cache;
	char *fileName = "null";
	FILE* file;
	cache = (struct CacheAttr*)malloc(sizeof(struct CacheAttr));
	
	if (cache==NULL) {
		printf("Malloc Error");
		exit(1);
	}

	parseCommand(cache, &fileName, argc, argv);

	if ((file = fopen(fileName, "r")) == NULL) {
		printf("Cannot open file '%s'!", fileName);
		exit(1);
	}

	parseFile(cache, file);

	calcNumOfBlks(cache);
	calcIndexSize(cache);
	calcTagSize(cache);
	calcOverheadMem(cache);

	printf("Cache size: %d\n", cache->cacheSize);
	printf("Blk size: %d\n", cache->blockSize);
	printf("Association: %d\n", cache->assoc);
	printf("Policy: %s\n\n", cache->policy);

	printf("Total Num of Blks: %d\n", cache->totalBlocks);
	printf("Index Size: %d Index bits: %d\n", cache->indexSize, (int)log2(cache->indexSize));
	printf("Tag Size: %d\n", cache->tagSize);
	printf("Overhead: %d\n", cache->overheadMemorySize);

	printf("-------------------------------------------------------");
	for (int i = 0; i < 20; i++) {
		printf("%d len: %d hex: %s Val: %d\n", i, cache->first20Addresses[i].readLength, cache->first20Addresses[i].hexAddr, cache->first20Addresses[i].hexVal);
	}

	free(cache);
	fclose(file);
	return 0;
}
*/