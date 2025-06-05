#include <stdio.h>
#include <time.h>
#include <stdint.h>

int main() {
    printf("Розмір time_t: %zu байт\n", sizeof(time_t));
    time_t max = (time_t)(~((time_t)1 << (sizeof(time_t) * 8 - 1)));

    printf("Максимальне значення time_t: %lld\n", (long long)max);
    printf("Дата переповнення: %s", ctime(&max));

    return 0;
}
