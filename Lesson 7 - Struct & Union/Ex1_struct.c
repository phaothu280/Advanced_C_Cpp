#include <stdio.h>
#include <stdint.h>

typedef struct{
    uint8_t  var2[9];   // 1 byte
    uint16_t var1[10];  // 2 byte
    uint32_t var3[2];   // 4 byte
} frame;
// kích thước của struct bằng tổng kích thước các member và padding (nếu có)

// địa chỉ của struct cũng chính là địa chỉ của member đầu tiên

// 0x0005FFE70  0x0005FFE71  0x0005FFE72  0x0005FFE73  ...  0x0005FFE78
//   var2[0]      var2[1]      var2[2]      var2[3]           var2[8]

// 0x0005FFE79  0x0005FFE7A  0x0005FFE7B  0x0005FFE7C  0x0005FFE7D  0x0005FFE7E  
//          var1[0]                   var1[1]                   var1[2]

// 0x0005FFE7F  0x0005FFE80  0x0005FFE81  0x0005FFE82  ... 0x0005FFE8B  0x0005FFE8C
//          var1[3]                   var1[4]                       var1[9]




int main(int argc, char const *argv[]){
    frame data;
    printf("Size = %lu\n",sizeof(frame));
    printf("Dia chi struct  : %p\n", &data);
    printf("Dia chi member 1: %p\n", &(data.var2));
    return 0;
}
