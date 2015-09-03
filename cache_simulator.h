
#define CACHE_SIZE  16
#define BLOCK_SIZE 4
#define CACHE_LINES 4
void run_simulation (int size, int length, int sets);
void direct (int blocks1, int blockLength);
void memory_map (int groups, int lines, int blockLength);
int* get_result (int address, int group, int blockLength);
int read_cache_file();
