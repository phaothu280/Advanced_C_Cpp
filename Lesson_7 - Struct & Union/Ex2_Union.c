#include <stdio.h>
#include <stdint.h>

typedef union{     //  Scope
    uint8_t  var1; //  0 - 255
    uint32_t var2; //  0 - 4294967295
    uint16_t var3; //  0 - 65535
} frame;

// kích thước của union chính là kích thước của member lớn nhất.
// các member dùng chung vùng nhớ

int main(int argc, char const *argv[])
{
    frame data;
    // printf("Size = %lu\n",sizeof(frame));
    // printf("Dia chi: %p\n",&data);
    // printf("Dia chi data.var1: %p\n", &(data.var1));
    // printf("Dia chi data.var3: %p\n", &(data.var3));

    //data.var1 = 5;
    data.var2 = 4294967290;
    //data.var3 = 7;

// 0x005FFE9C  0x005FFE9D  0x005FFE9E  0x005FFE9F
//      5
//      6
//      7

// 0x005FFE9C  0x005FFE9D  0x005FFE9E  0x005FFE9F
//  11111010    11111111    11111111    11111111

    printf("Data.var1 = %d\n", data.var1);
    printf("Data.var2 = %u\n", data.var2);
    printf("Data.var3 = %d\n", data.var3);
    return 0;
}
