#ifndef COMMON
#define COMMON

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <list>

#include <stdlib.h>

#define NUM_FRAMES 256
#define NUM_PAGES 256
#define TLB_NUM_ENTRIES 16
#define PAGE_FRAME_SIZE 256
#define PHYSICAL_MEMORY_SIZE NUM_FRAMES * PAGE_FRAME_SIZE

#define COMMANDS_FILE "addressesRANDOM.txt"

#define FIFO
//#define LRU
//#define LFU

using namespace std;

#endif // COMMON

