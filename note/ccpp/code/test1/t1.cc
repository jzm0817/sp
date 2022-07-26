#include <stdio.h>
#include <stdint.h>

#define X 2
#define Y 3
#define Z 5

int main(){

    typedef uint16_t my_type;
    my_type array_mul[X][Y][Z] = {0};

    printf("sizeof(my_type): %lu \n", sizeof(my_type));
    printf("sizeof(array_mul): %lu \n", sizeof(array_mul));

    my_type (*e)[Y][Z] = array_mul;
    my_type (*r)[Z] = array_mul[0];
    my_type *t = array_mul[0][0];

    printf("array_mul: %p \n", array_mul);
    printf("e    : %p \n", e);
    printf("e + 1: %p \n", e + 1);
    printf("r    : %p \n", r);
    printf("r + 1: %p \n", r + 1);
    printf("t    : %p \n", t);
    printf("t + 1: %p \n", t + 1);

}