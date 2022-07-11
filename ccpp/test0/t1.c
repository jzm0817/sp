// test code : zero length array 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct buff
{
    // int len;
    // int key;
    int len;
    char a[0];    // zero length array 
    /* data */
};


int main(int argc, char ** argv){

    struct buff * buf;
    printf("%d\n", sizeof(struct buff));
    printf("%d\n", sizeof(char));
    printf("%d\n", sizeof(int));
    buf = (struct buff *)malloc(sizeof(struct buff) + 20);
    buf -> len = 20;
    strcpy(buf -> a, "hello world!\n");
    puts(buf -> a);

    free(buf);
    return 0;
}


