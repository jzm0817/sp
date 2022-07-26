
#include <stdio.h>
#include <stdint.h>

int main(){
    const int a = 20;
    int * ptr0 = &a;
    const int * ptr1 = &a;


    printf("    a: %d \n", a);
    printf("   &a: %p \n", &a);
    printf(" ptr0: %p \n", ptr0);
    printf("*ptr0: %d \n", *ptr0);
    printf(" ptr1: %p \n", ptr1);
    printf("*ptr1: %d \n", *ptr1);

    // *ptr0 = 2;
    *ptr1 = 2;

    printf("    a: %d \n", a);
    printf("   &a: %p \n", &a);
    printf(" ptr0: %p \n", ptr0);
    printf("*ptr0: %d \n", *ptr0);
    printf(" ptr1: %p \n", ptr1);
    printf("*ptr1: %d \n", *ptr1);
}
