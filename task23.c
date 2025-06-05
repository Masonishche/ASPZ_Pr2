#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void segfault_handler(int sig) {
    printf("Caught signal %d (Segmentation fault?)\n", sig);
    exit(1);
}

int main() {
    signal(SIGSEGV, segfault_handler);

    printf("Trying to write to NULL pointer...\n");
    int *p = NULL;
    *p = 42;  // This will cause segmentation fault

    return 0;
}
