
/*
 * Adam Blackwell
 * CS2600 Gene Cooperman
 *
 */

// Includes:
#include <stdlib.h>
#include <stdio.h>

// Templates.
void simulate (int size, int length, int sets);
void direct (int blocks1, int blockLength);
void associative (int groups, int lines, int blockLength);
int* splitAddress (int address, int group, int blockLength);

/*
 * The test sequence is:
 * 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72,
 * 76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41
 *
 * Test Run 1:
 * Assume a 128-byte, direct-mapped cache with 8-byte cache lines (cache blocks).
 *
 * Test Run 2:
 * Assume a 64-byte, 2-way set associative cache with 8-byte cache lines (cache
 * blocks).
 *
 * Test Run 3:
 * Assume a 128-byte, direct-mapped cache with 16-byte cache lines (cache blocks).
 *
 * Test Run 4:
 * Assume a 64-byte, fully associative cache with 8-byte cache lines (cache
 * blocks).
 *
 */

// Sample Address Sequence
// int addresses[] = {0, 4, 8, 12, 48, 16, 80, 8, 12, 0, 0, 6, 10};
int addresses[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41};

int addresseslength = sizeof(addresses);
int hit_counter = 0;
int miss_counter = 0;


int main () {
        // Sample Test Run One:
        printf("Direct Mapped\n");
        simulate(16, 4, 4);

        printf("\n 2 Way associative\n");
        simulate(16, 4, 2);

        printf("\n  Fully associative\n");
        simulate(16, 4, 1);

        printf("Total number of hits = %d\n", hit_counter);
        printf("Total number of misses = %d\n", miss_counter);

}

/*
 * Simulates a <size> byte <groups>-way associative cache,
 * with a cache block of length <length>.
 *
 * Assumed that s, n, and l are positive and s / l & s / n div
 *
 * "Note that a 1-way set associative cache is equivalent to
 * a direct-mapped cache. Also, an N-way set-associative cache
 * containing N total blocks is equivalent to a fully-associative cache."
 *
 * The total number of cache blocks or lines is equal to <s> over <l>.
 */
void simulate (int size, int length, int groups) {
  // How many blocks are there? Number of cache lines.
        int blocks = size/length;

        // Run it?
  associative(groups, blocks, length);

  // I used to have it run direct or associative, but I realized they were that
  // same with some arguments, read Note above.

}

/*
 * Set-associative cache.
 *   - g :: Groups = the number of groups.
 *   - b :: Blocks = number of cache blocks or cache lines.
 *   -   :: BlockLength = the length of a block.
 */
void associative (int groups, int blocks, int blockLength) {
  // Which cache write is it?
  int counter = 1;   // Counter.
  int subBlocks = blocks/groups; // Sub Blocks.
        int numParts = 4;   // Parts.
        int cache[groups][subBlocks][numParts];
        //cache = malloc(groups*subBlocks*numParts);


        // Loop through the cache and default all values to 0
        int x, y, z;
        for (x = 0; x < groups; x++) {
                for (y = 0; y < subBlocks; y++) {
                        for (z = 0; z < numParts; z++) {
                                cache[x][y][z] = 0;
                        }
                }
        }
        // printf("size after zeros: %d", cache):

        int i, j;
        int oldest = -1;
  int spot;
        int* cacheBlock;
  int* parts;

        for (i = 0; i < addresseslength; i++) {
          // Each Cache line has 4 parts:
          // A tag, group, valid bit, and a count.
                // Fields[] = { tag, group, valid bit, count }
                parts = splitAddress(addresses[i], groups, blockLength);
                int tag = *(parts+0);
                int group = *(parts+1);
                int hit = 0;

                for (j = 0; j < subBlocks; j++) {
                        // Is there a valid block in the group that matches the tag?
                        if (cache[group][j][2] && cache[group][j][1] == tag) {
                          // If match if found:
                          hit = 1;
                        }
                }

                // If it is here print a HIT else find a space for it.

                if (hit == 1) {
                        //printf("%d - HIT\n", addresses[i]);
                        printf("%d : %d :: %d - HIT\n", addresses[i], tag, group);
                        hit_counter++;

                  hit = 0;
                }       else {
                        // Check if there is an empty block, if so, get the group
                  // Else find the oldest block.
                        for (j = 0; j < subBlocks; j++) {
        if (oldest == -1 || cache[group][j][3] < oldest) {
          oldest = cache[group][j][3];
          spot = j;
        }
                                if (cache[group][j][2] == 0) {
                                        spot = j;
                                        break;
                                }
                        }

                        cache[group][spot][1] = tag;
                        cache[group][spot][2] = 1;
                        cache[group][spot][3] = counter++;
                        //printf("%d - MISS\n", addresses[i]);
                        printf("%d : %d :: %d - MISS\n", addresses[i], tag, group);
                        miss_counter++;

                }
        }
}

// SplitAddress breaks up an address into a group / block and tag.
//      Address - the address to break up
//      Groups - the number of groups in the cache
//              * if fully associative cache, the groups should be 1.
//      Block Length - the size of a line in the cache
int* splitAddress (int address, int groups, int blockLength) {
  // Split the number.
        int tagField = address/groups;
        int groupField = address % groups;

        // Produce the return value.
        int r[2] = { tagField, groupField};
        int* result = r;
  return result;
}
