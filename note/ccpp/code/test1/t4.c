#include <stdio.h>
#include <stdint.h>

int main(){
    int x = 20;
    int y = 10;
    int *a = &x;
    int *b = &y;

    *(a + 25) = *b;
}