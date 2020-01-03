// garbage-collector-test.c  A test file for garbage-collector.c

#include "heap-manager.h"
#include "garbage-collector.h"
#include <stdio.h>

int main() {
  char *p;
  initmemory(100);

  printf("malloc 4\n");
  p = (char *)myalloc(4);
  printallocation();

  printf("malloc 6; the malloc 4 is now garbage\n");
  p = (char *)myalloc(6);
  printallocation();

  printf("malloc 22; the malloc 6 is now garbage\n");
  p = (char *)myalloc(22);
  printallocation();

  printf("gc: Should free the first two blocks and coalesce them\n");
  gc();
  printallocation();

  return 0;
}
