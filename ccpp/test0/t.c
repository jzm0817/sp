
#include <stdio.h>


int main(int argc, char** argv){
    int a[0];
    size_t a_size = sizeof(a);
    // printf("%d\n", a_size);
    printf("%ld\n", a_size);
    return 0;
}