#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cache_simulator.h"

int  i = 0, totalNums;
int addresses[488]; // wc -l cache.txt // get the number of Addresses
int atoi ( const char * str );
char line[5];  /* declare a char array */

int main(int argc, char *argv[]) {

	if (!read_cache_file())
	{
		printf("Direct Mapped\n");
		run_simulation(64, 16, 4);

		printf("\n---------------------------------------------------\n");

		printf("\n2 Way memory_map\n");
		run_simulation(64, 8, 4); // set 2 for 2 way associative

		printf("\n---------------------------------------------------\n");


		printf("\nFully memory_map\n");
		run_simulation(64, 8, 1); // set to 1 for fully associative

		printf("\n---------------------------------------------------\n");

	}
	return 0;
}

int read_cache_file()
{
	FILE *file;
  file = fopen("cache.txt", "r");   // reading the cache file from the cahche .h 

  while (fgets(line, sizeof line, file) != NULL) {
		int uv = strtoul(line, NULL, 16);
		//printf("%u\n", uv);
  	addresses[i] = uv;
    i++;
  }
  totalNums = i;
  fclose(file);

	return 0;
}

void run_simulation(int size, int length, int groups) {
	int blocks = size/length; //block of the memory 
	memory_map(groups, blocks, length);        //memory mapping the address of the memory is group 
}

void memory_map(int groups, int blocks, int blockLength) {
  int counter = 1;
  int memoryblock = blocks/groups;
  int numParts = 4;
  int cache[groups][memoryblock][numParts];

  int x, y, z;
  for (x = 0; x < groups; x++) {
  	for (y = 0; y < memoryblock; y++) {
    	for (z = 0; z < numParts; z++) {
      	cache[x][y][z] = 0;
      }
    }
	}
// assining the tag group and the logic of hit and miss 
  int i, j, last = -1, a,c;
  int* parts;

	for (i = 0; i < sizeof(addresses)/sizeof(addresses[0]); i++) {
    parts = get_result(addresses[i], groups, blockLength);
    int tag = *(parts + 0);
    int group = *(parts + 1);
    int hit=0 ;
	  for (j = 0; j < memoryblock; j++) {
    	if (cache[group][j][2] && cache[group][j][1] == tag) {
      	hit = 1;
		;

      }
    }
    if (hit == 1) {
      printf("%d\t: %d\t: %d\t- HIT\n", addresses[i], tag, group);
      //hit = 0; //reset Hit
    } else {
      for (j = 0; j < memoryblock; j++) {
      	if (last == -1 || cache[group][j][3] < last) {
        	last = cache[group][j][3];
          a = j;
        }
        if (cache[group][j][2] == 0) {
        	a = j;
          break;
        }
      }
      cache[group][a][1] = tag;
      cache[group][a][2] = 1;
      cache[group][a][3] = counter++;
      printf("%d\t: %d\t: %d\t- MISS\n", addresses[i], tag, group);
    }
  }
}

int* get_result (int address, int groups, int blockLength) // main coding 
{
  int tagField, groupField;
	tagField = address/groups;
  groupField = address % groups;
  int r[2] = { tagField, groupField};
  int* result = r;
  return result;
}
