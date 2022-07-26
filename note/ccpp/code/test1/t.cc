
#include <stdio.h>
#include <stdint.h>

void func1(char ca[]);
void func2(const char * pa);

const char * ga = "Hello_world!";

int main(){
    char ca[] = "Hello_world!";
    const char * pa = "Hello_world!";

    func1(ca);
    func2(pa);

    printf("&ga:%p\n", &ga);
    printf("&(ga[0]):%p\n", &(ga[0]));
    printf("&(ga[1]):%p\n", &(ga[1]));
    printf("*(&(ga[0])):%c\n", *(&(ga[0])));
    printf("*(&(ga[1])):%c\n", *(&(ga[1])));
    printf("sizeof(ga): %lu Byte\n", sizeof(pa));
    printf("sizeof(const char *): %lu Byte\n", sizeof(const char *));
    printf("sizeof(const int *): %lu Byte\n", sizeof(const int *));
    printf("sizeof(const char): %lu Byte\n", sizeof(const char));
    printf("sizeof(const int): %lu Byte\n", sizeof(const int));
    printf("sizeof(int): %lu Byte\n", sizeof(int));
    printf("sizeof(uint16_t): %lu Byte\n", sizeof(uint16_t));
}


void func1(char ca[]){
    printf("&ca:%p\n", &ca);
    printf("&(ca[0]):%p\n", &(ca[0]));
    printf("&(ca[1]):%p\n", &(ca[1]));
}

void func2(const char * pa){
    printf("&pa:%p\n", &pa);
    printf("&(pa[0]):%p\n", &(pa[0]));
    printf("&(pa[1]):%p\n", &(pa[1]));
    printf("pa+1:%p\n", pa + 1);
    printf("++pa:%p\n", ++pa);
}