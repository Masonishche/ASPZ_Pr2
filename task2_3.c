#include <stdio.h>
#include <stdlib.h>

int global_data = 42;         // data segment
static int static_data;       // BSS segment

int main() {
    int stack_var = 1;
    int *heap_var = malloc(sizeof(int));
    *heap_var = 5;

    printf("Stack variable address : %p\n", (void*)&stack_var);
    printf("Heap variable address  : %p\n", (void*)heap_var);
    printf("Data segment address   : %p\n", (void*)&global_data);
    printf("BSS segment address    : %p\n", (void*)&static_data);

    free(heap_var);
    return 0;
}
