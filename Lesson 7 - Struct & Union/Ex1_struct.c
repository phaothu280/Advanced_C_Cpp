#include <stdio.h>
#include <stdint.h>

typedef struct{
    uint8_t  var2[9];   // 1 byte
    uint16_t var1[10];  // 2 byte
    uint32_t var3[2];   // 4 byte
} frame;


int main(int argc, char const *argv[]){
    frame data;
    printf("Size = %lu\n",sizeof(frame));
    printf("Dia chi struct  : %p\n", &data);
    printf("Dia chi member 1: %p\n", &(data.var2));
    printf("Dia chi phan tu thu 3 cua member 2: %p\n", &(data.var1[2]));
    return 0;
}
