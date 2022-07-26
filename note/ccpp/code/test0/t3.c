// test for bit sfield

#include <stdio.h>
#include <stdint.h>

int main(){
    struct bitfield{
        uint8_t en   : 1;
        uint8_t clk;
        uint8_t ep   : 4;
        uint8_t mode : 3; 
      
    };
    
    struct normal
    {   
        uint8_t en;
        uint8_t ep;
        uint8_t mode;
    };
    
    printf("%d Byte is occupied\n", sizeof(struct normal));
    printf("%d Byte is occupied\n", sizeof(struct bitfield));

}


