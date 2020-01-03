# HeapManager

This repository contains two main components:


    1. An SDK for creating and managing a simulated heap. This is composed of
       a number of functions that can be called to explicitly allocate, free
       and coalesce dynamic memory blocks. See [heap-manager.c](/heap-manager.c)
       for the source code.
    2. A garbage collector that can automatically detect unused memory on the
       heap and deallocate it appropriately. See [garbage-collector.c](/garbage-collector.c)
       for the source code.


# How To

For a quick demonstration of how each of these components function, run the following
sequences of commands:


    1. To see the heap manager in action:

       ```
       gcc heap-manager-test.c heap-manager.c -o heap-manager-demo
       ./heap-manager-demo
       ```

    2. To see the garbage collector in action:

       ```
       gcc garbage-collector-test.c garbage-collector.c heap-manager.c -o garbage-collector-demo
       ./garbage-collector-demo
       ```

In order to use any of the functions implemented in either [heap-manager.c](/heap-manager.c)
or [garbage-collector.c](/garbage-collector.c), simply include their corresponding
header files, [heap-manager.h](/heap-manager.h) & [garbage-collector.h](/garbage-collector.h).
