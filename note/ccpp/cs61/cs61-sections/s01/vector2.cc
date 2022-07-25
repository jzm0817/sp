#include <vector>     // include declaration of `std::vector`
#include <cstdio>
#include <cassert>
#include "hexdump.hh"

int main() {
    // Your code here
    const char * char_s = "HI";
    // std::vector<const char *> a (5, char_s);
    // std::vector<const char *> a {char_s, char_s, char_s, char_s, char_s};
    std::vector<const char *> a;
    while (a.size() != 5){
        a.push_back(char_s);
    } 

    for(size_t i = 0; i != a.size(); ++i){
        printf("%s%s", i ? ", " : "", a[i]);
    }
    printf("\n");
    printf("%ld\n", sizeof(a[0]));
}
