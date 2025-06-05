#include <stdio.h>
#include <unistd.h>

void d() {
    int d_var;
    printf("Function d(): &d_var = %p\n", (void*)&d_var);
    pause();
}

void c() {
    int c_var;
    printf("Function c(): &c_var = %p\n", (void*)&c_var);
    d();
}

void b() {
    int b_var;
    printf("Function b(): &b_var = %p\n", (void*)&b_var);
    c();
}

int main() {
    int main_var;
    printf("Function main(): &main_var = %p\n", (void*)&main_var);
    b();
    return 0;
}
