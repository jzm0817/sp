
#include <cstdio>
#include <cstdint>
#include <iostream>

char ga[] = "abcdefghijklmn";

void my_array_func(char ca[10]){
    printf("typeid(ca): %s \n", typeid(ca).name());
    printf("       &ca: %p \n", &ca);
    printf("sizeof(ca): %lu \n", sizeof(ca));
    printf("  (*(&ca)): %p \n", (*(&ca)));
    printf("  & ca[0]): %p \n", &(ca[0]));
    printf("  &(ca[1]): %p \n", &(ca[1]));
    printf("      ++ca: %p \n", ++ca);
    printf("\n");
}

void my_pointer_func(char * pa){
    printf("typeid(pa): %s \n", typeid(pa).name());
    printf("       &pa: %p \n", &pa);
    printf("sizeof(pa): %lu \n", sizeof(pa));
    printf("  (*(&pa)): %p \n", (*(&pa)));
    printf("  &(pa[0]): %p \n", &(pa[0]));
    printf("  &(pa[1]): %p \n", &(pa[1]));
    printf("      ++pa: %p \n", ++pa);   
    printf("\n");
}

int main(){
    // int i = 2;
    // printf("%s \n ", typeid(i).name());
    printf("sizeof(ga): %lu \n", sizeof(ga));
    printf("sizeof(char*): %lu\n", sizeof(char *));
    printf("typeid(ga): %s \n", typeid(ga).name());
    printf("typeid(char *): %s \n", typeid(char *).name());
    printf("       &ga: %p \n", &ga);
    printf("  (*(&ga)): %p \n", (*(&ga)));
    printf("  &(ga[0]): %p \n", &(ga[0]));
    printf("  &(ga[1]): %p \n", &(ga[1]));
    printf("\n");

    my_array_func(ga);
    my_pointer_func(ga);
}