
#include <stdio.h>

int main(){
    char *cp = "hello";
    const char *cpp = "world";
    cpp = cp;
    cp = cpp;
    printf("sizeof(cp):%lu\n", sizeof(cpp));
    printf("cp: %p\n", cpp);
    printf("cp + 1: %p\n", cpp + 1);
    printf("cp + 2: %p\n", cpp + 2);
    printf("*(cp + 1): %c\n", *(cpp + 1));
    printf("*(cp + 2): %c\n", *(cpp + 2));
}     