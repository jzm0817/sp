

#include <iostream>
#include <cstdio>

int main(){
    struct empty {

    };

    printf("%d\n", sizeof(struct empty));
    // std::cout << sizeof(struct empty) << '\n';
}