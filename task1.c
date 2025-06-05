#include <stdio.h>
#include <time.h>
#include <stdint.h>

int main() {
    printf("Size of time_t: %zu bytes\n", sizeof(time_t));

    time_t max = (time_t)(~((time_t)1 << (sizeof(time_t) * 8 - 1)));
    printf("Maximum time_t value: %lld\n", (long long)max);

    printf("Overflow date: %s", ctime(&max));
    return 0;
}
