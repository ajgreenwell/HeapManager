#include "heap-manager.h"
#include <stdio.h>
#include <stdlib.h>

int *heapStart = NULL;
int *heapEnd = NULL;

int isAllocated(int *p) {
  return *p % 2 == 1;
}

int getBlockSize(int *header) {
  return *header & -2;
}

int *nextBlock(int *p) {
  return p + (getBlockSize(p) / sizeof(int));
}

int *firstBlock() {
  return heapStart + 1;
}

int *lastBlock() {
  return heapEnd - 1;
}

int nextMultipleOfEight(int start) {
  int remainder = start % 8;
  if (remainder == 0) return start;
  return start + (8 - remainder);
}

void initmemory(int size) {
  // allocate memory and set start/end points of heap
  int amountToAllocate = nextMultipleOfEight(size + (3 * sizeof(int)));
  heapStart = (int *) malloc(amountToAllocate);
  heapEnd = heapStart + (amountToAllocate / sizeof(int));
  // init first block
  int *first = firstBlock();
  *first = amountToAllocate - (2 * sizeof(int));
  // init sentinel block
  int *last = lastBlock();
  *last = 1;
}

void *myalloc(int length) {
  int *block = firstBlock();
  int *end = lastBlock();
  int amountToAllocate = nextMultipleOfEight(length + sizeof(int));
  while (block != end) {
    // if this block is not allocated and has enough space, allocate here
    if (!isAllocated(block) && getBlockSize(block) >= amountToAllocate) {
      int *newHeader = block + (amountToAllocate / sizeof(int));
      *newHeader = *block - amountToAllocate;
      *block = amountToAllocate + 1;
      return (void *) (block + 1);
    }
    block = nextBlock(block);
  }
  return NULL;
}

void myfree(void *ptr) {
  int* header = (int *) ptr - 1;
  *header = getBlockSize(header);
}

void coalesce() {
  int *block1 = firstBlock();
  int *block2 = nextBlock(block1);
  int *end = lastBlock();
  while (block2 != end) {
    if (!isAllocated(block1) && !isAllocated(block2))
      *block1 = getBlockSize(block1) + getBlockSize(block2);
    else block1 = nextBlock(block1);
    block2 = nextBlock(block2);
  }
}

void printallocation() {
  int *block = firstBlock();
  int *end = lastBlock();
  int idx = 0;
  while (block != end) {
    int size = getBlockSize(block);
    if (isAllocated(block))
      printf("Block %d: size %-6d allocated\n", idx, size);
    else
      printf("Block %d: size %-6d unallocated\n", idx, size);
    block = nextBlock(block);
    idx++;
  }
  printf("\n");
}
