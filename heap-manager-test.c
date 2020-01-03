// heap-manager-test.c  A test file for  heap-manager.c

#include "heap-manager.h"
#include <stdio.h>

void printresult(int *p) {
	if (p == NULL)
		printf("allocation failed.\n");
	else
		printallocation();
	printf("\n");
}

int main() {
    int *p1, *p2;

    printf("initial allocation\n");
    initmemory(56);
    printallocation();

    printf("malloc 20\n");
    p1 = (int *)myalloc(20);
	printresult(p1);

    printf("malloc 10\n");
    p2 = (int *)myalloc(10);
	printresult(p2);

    printf("free (malloc 20)\n");
    myfree(p1); p1 = NULL;
	printallocation();

    printf("malloc 4\n");
    p1 = (int *)myalloc(4);
	printresult(p1);

    printf("free (malloc 10)\n");
    myfree(p2); p2 = NULL;
	printallocation();

    printf("malloc 30: should fail\n");
    // this will fail because we need a block of at least 40
    p2 = (int *)myalloc(30);
	printresult(p2);

    printf("coalesce\n");
    coalesce();
    printallocation();

    printf("malloc 30 \n");  // now this succeeds
    p2 = (int *) myalloc(30);
	printresult(p2);

    printf("free everything\n");
    myfree(p1); p1 = NULL;
    myfree(p2); p2 = NULL;
    printallocation();

    printf("malloc 56: should fail\n");
    // this will fail
    p1 = (int *)myalloc(56);
	printresult(p1);

    printf("coalesce\n");
    coalesce();
    printallocation();

    printf("malloc 56\n");
    p1 = (int *)myalloc(56);
	printresult(p1);
}
