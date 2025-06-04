#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>

static sigjmp_buf jump_buffer;
static int segfault_occurred = 0;

void segfault_handler(int sig) {
    segfault_occurred = 1;
    fprintf(stderr, "\n>>> Segmentation fault! Signal: %d\n", sig);
    siglongjmp(jump_buffer, 1);
}

void demonstrate_segfaults() {
    // Test 1: Null pointer access
    if (sigsetjmp(jump_buffer, 1)) {
        fprintf(stderr, "Test 1: Null pointer access - FAILED\n");
    } else {
        int *null_ptr = NULL;
        *null_ptr = 42;
        fprintf(stderr, "Test 1: Null pointer access - PASSED (unexpected)\n");
    }

    // Test 2: Write to read-only memory
    if (sigsetjmp(jump_buffer, 1)) {
        fprintf(stderr, "Test 2: Write to read-only memory - FAILED\n");
    } else {
        char *ro_mem = "CONSTANT_DATA";
        ro_mem[0] = 'X';
        fprintf(stderr, "Test 2: Write to read-only memory - PASSED (unexpected)\n");
    }

    // Test 3: Stack overflow
    if (sigsetjmp(jump_buffer, 1)) {
        fprintf(stderr, "Test 3: Stack overflow - FAILED\n");
    } else {
        char stack_array[1024 * 1024];
        memset(stack_array, 0, sizeof(stack_array));
        fprintf(stderr, "Test 3: Stack overflow - PASSED (unexpected)\n");
    }

    // Test 4: Heap corruption
    if (sigsetjmp(jump_buffer, 1)) {
        fprintf(stderr, "Test 4: Heap corruption - FAILED\n");
    } else {
        char *heap_mem = malloc(10);
        memset(heap_mem, 'A', 1000);
        free(heap_mem);
        fprintf(stderr, "Test 4: Heap corruption - PASSED (unexpected)\n");
    }
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = segfault_handler;
    sa.sa_flags = SA_NODEFER;
    
    if (sigaction(SIGSEGV, &sa, NULL)) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    printf("===== Memory Segmentation Fault Demonstrator =====\n");
    printf("Demonstrating different memory access violations\n\n");
    
    demonstrate_segfaults();
    
    if (!segfault_occurred) {
        printf("\nAll tests passed (unexpected - no segfaults triggered)\n");
    } else {
        printf("\nSegmentation faults demonstration completed\n");
    }
    
    return EXIT_SUCCESS;
}