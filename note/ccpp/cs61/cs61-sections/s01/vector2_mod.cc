#include <vector>     // include declaration of `std::vector`
#include <cstdio>
#include <cassert>
#include "hexdump.hh"


int main(){

    const char *string_s[] {"Helloooooo", "world!"};
    // const char * text = "text"
    const char &string_ss = *(string_s[0]);
    // const char ** string_s = {"Hello"};
    printf("sizeof(string_s):%lu\n", sizeof(string_s));
    printf("&(string_ss):0x%x\n", &(string_ss));
    printf("sizeof(string_ss):%ld\n", sizeof(string_ss));
    printf("&(string_s[0]):0x%x\n", &(string_s[0])); 
    printf("&(string_s[1]):0x%x\n", &(string_s[1])); 
    printf("string_s[0]:%s\n", (string_s[0])); 
    printf("string_s[1]:%s\n", (string_s[1])); 
    printf("*(string_s[0] + 2):%c\n", *(string_s[0] + 2)); 
    printf("string_s[0] + 2:%s\n", (string_s[0] + 2)); 

    printf("sizeof(string_s):%ld\n", sizeof(string_s));

    std::vector<const char*> vec;

    for (int i = 0; i != 2; i++){
        vec.push_back(string_s[i]);
        // vec[i] = string_s[i];
    }

    // vec = {"Hello", "world!"};

    printf("sizeof(vec[0]): %lu\n", sizeof(vec[0]));
    printf("sizeof(vec[1]): %lu\n", sizeof(vec[1]));
    printf("sizeof(vec): %lu\n", sizeof(vec));


    for (int i = 0; i != vec.size(); i++){
        printf("vec[%d]:%s %lu Byte in %x\n", i , (vec[i]), sizeof(vec[i]), &vec[i]);
        printf("%s\n%s\n", *(&vec[i]), *((&vec[i]) + 1));
            for (int j = 0; vec[i][j] != '\0'; j++){
                printf("%c \n", vec[i][j]);
            }   
    }

}