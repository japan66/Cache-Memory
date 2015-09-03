#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cache_simulator.h"

int  i = 0, totalNums;
int addresses[488]; // wc -l cache.txt // get the number of Addresses
int atoi ( const char * str );
char line[5];  /* declare a char array */
int hit_counter = 0;
int miss_counter = 0;

int read_cache_file()
{
	FILE *file;
  file = fopen("cache.txt", "r");   // reading the cache file from the cahche .h
  int uv[] = {};
  while (fgets(line, sizeof line, file) != NULL) {
		uv[] = strtoul(line, NULL, 16);
		printf("%u\n", uv[]);
  	addresses[i] = uv[];
    i++;
  }
  totalNums = i;
  fclose(file);
	return uv[];
}





int main(int argc, char *argv[]) {
  int values[] = read_cache_file();
  for (i=0; i<=sizeof(values); i++) {
    printf("value = %u\n", values[i]);
  }
	return 0;
}
