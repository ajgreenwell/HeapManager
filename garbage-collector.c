#include "garbage-collector.h"
#include "heap-manager.h"
#include <stdio.h>

void *stackBottom() {
  unsigned long bottom;
  FILE *statfp = fopen("/proc/self/stat", "r");
  fscanf(statfp,
         "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
         "%*u %*u %*u %*u %*u %*u %*d %*d "
         "%*d %*d %*d %*d %*u %*u %*d "
         "%*u %*u %*u %lu", &bottom);
  fclose(statfp);
  return (void *) bottom;
}

int isHeapNode(int *p) {
  return firstBlock() <= p && p <= lastBlock();
}

int isMarked(int *header) {
  return *header % 4 == 3;
}

void markBlock(int *header) {
  *header = *header / 4 * 4 + 3;
}

void unmarkBlock(int *header) {
  *header = *header / 4 * 4;
}

void mark(int *p) {
  int *block1 = firstBlock();
  int *block2 = nextBlock(block1);
  while (block2 < p) {
    block1 = block2;
    block2 = nextBlock(block2);
  }
  if (isAllocated(block1) && !isMarked(block1)) {
    int i, blockSize = getBlockSize(block1);
    markBlock(block1);

    // For every int sized word inside this block, check if it points to a heapnode.
    // If it does, recursively mark the block that contains that heapnode.
    for (i = 1; i < blockSize / sizeof(int); i++) {
      int *node = (int *) *(block1 + i);
      if (isHeapNode(node))
        mark(node);
    }
  }
}

void sweep() {
  int *block = firstBlock();
  int *end = lastBlock();
  while (block < end) {
    if (!isMarked(block)) {
      unmarkBlock(block);
      myfree(block + 1);
    }
    block = nextBlock(block);
  }
}

void gc() {
  int **bottomOfStack = (int **) stackBottom();
  int *dummy;
  int **p = &dummy;
  while (p < bottomOfStack) {
    if (isHeapNode(*p))
      mark(*p);
    p++;
  }
  sweep();
  coalesce();
}
