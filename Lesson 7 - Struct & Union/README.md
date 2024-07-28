# Struct
<details><summary>Chi tiết</summary>
<p>
    
## Định nghĩa

struct là một cấu trúc dữ liệu cho phép tự định nghĩa một kiểu dữ liệu mới bằng cách nhóm các biến có các kiểu dữ liệu khác nhau lại với nhau.

struct cho phép tạo ra một thực thể dữ liệu lớn hơn và có tổ chức hơn từ các thành viên (members) của nó.

## Cú pháp

**Cách 1**
```cpp
struct structureName{       struct student_t{       struct student_t sv1;
    dataType1 member1;          char ten[30];       struct student_t sv2;
    dataType2 member2;          int tuoi;           ...
    ...                         int MSSV;           hoặc
};                          };                     struct student_t sv[50];
```

**Cách 2**
```cpp
typedef struct{             typedef struct{         student_t sv1;
    dataType1 member1;          char ten[30];       student_t sv2;
    dataType2 member2;          int tuoi;           ...
    ...                         int MSSV;           student_t sv[20];
}structureName;             }student_t;
```

## Kích thước Struct
Kích thước Struct bằng tổng các kích thước của các member và padding (nếu có).

**Ví dụ 1**

<details><summary></summary>
<p>
    
```cpp
typedef struct{
    uint32_t var1;  // 4 byte
    uint8_t  var2;  // 1 byte
    uint16_t var3;  // 2 byte
} frame;
```

Kết quả: ```8 byte```

Giải thích:

![image](https://github.com/user-attachments/assets/fb82664c-da75-4cb2-8fbe-1c11ea12fea4)

Lần 1 quét 4 bytes và var1 sử dụng.

Lần 2 quét 4 bytes, var2 chỉ sử dụng 1 byte, thừa 3 bytes bộ nhớ đệm.	

var3 sử dụng 2 bytes trong 3 bytes trên và còn thừa 1 byte bộ nhớ đệm.

Tổng kích thước struct frame trên là 8 bytes nhưng thực tế chỉ sử dụng 7 bytes.

</p>
</details>

**Ví dụ 2**

<details><summary></summary>
<p>

```cpp
typedef struct{
    uint8_t  var2;  // 1 byte
    uint32_t var3;  // 4 byte
    uint16_t var1;  // 2 byte
} frame;
```

Kết quả: ```12 byte```

Giải thích:

![image](https://github.com/user-attachments/assets/5f951d03-fc44-4b38-835c-b9ac5e787174)

Lần 1 quét 4 bytes và var1 sử dụng 1 byte trong 4 byte, thừa 3 byte.

Lần 2 quét 4 bytes, var3 sử dụng hết.

Lần 3 quét 4 bytes, var1 sử dụng 1 trong 4 bytes và thừa 3 byte.

Tổng kích thước struct frame trên là 12 bytes nhưng thực tế chỉ sử dụng 7 bytes.

</p>
</details>

**Ví dụ 3**

<details><summary></summary>
<p>

```cpp
typedef struct{
    uint8_t  var2[9];   // 1 byte
    uint32_t var3[2];   // 4 byte
    uint16_t var1[10];  // 2 byte
} frame;
```

Kết quả: ```40 byte```

Giải thích:

![image](https://github.com/user-attachments/assets/7c9ecf6b-479a-4d1c-8064-367934d35d4e)

</p>
</details>

**Ví dụ 4**
<details><summary></summary>
<p>

```cpp
typedef struct{
    uint8_t  var2[9];   // 1 byte
    uint64_t var4[3];   // 8 byte
    uint16_t var1[10];  // 2 byte
    uint32_t var3[2];   // 4 byte
} frame;
```

Kết quả: ```72 byte```

Giải thích:

![image](https://github.com/user-attachments/assets/0723e3e4-bb78-4de7-9737-fcf15e96158e)

</p>
</details>

## Địa chỉ của Struct
Địa chỉ của struct chính là địa chỉ của member đầu tiên

```cpp
#include <stdio.h>
#include <stdint.h>

typedef struct{
    uint8_t  var2[9];   // 1 byte
    uint16_t var1[10];  // 2 byte
    uint32_t var3[2];   // 4 byte
} frame;

int main(int argc, char const *argv[]){
    frame data;
    printf("Dia chi struct  : %p\n", &data);
    printf("Dia chi member 1: %p\n", &(data.var2));
    return 0;
}
```
**Kết quả in ra**
```cpp
Dia chi struct  : 00000000005FFE70
Dia chi member 1: 00000000005FFE70
```

Các phần tử trong mảng **var2** đều có kiểu dữ liệu **uint8_t** nên sẽ chiếm 1 byte ô nhớ.

![image](https://github.com/user-attachments/assets/56e7cf17-c6e2-4354-9950-a23d817bc965)

Các phần tử trong mảng **var1** đều có kiểu dữ liệu **uint16_t** nên sẽ chiếm 2 byte ô nhớ.

![image](https://github.com/user-attachments/assets/c7a36f7f-7068-4ff6-967c-4e636162b557)

</p>
</details>

# Union
<details><summary>Chi tiết</summary>
<p>

## Định nghĩa

Union là một cấu trúc dữ liệu giúp kết hợp nhiều kiểu dữ liệu khác nhau vào một cùng một vùng nhớ. 

Mục đích chính của union là tiết kiệm bộ nhớ bằng cách chia sẻ cùng một vùng nhớ cho các thành viên của nó. Điều này có nghĩa là, trong một thời điểm, chỉ một thành viên của union có thể được sử dụng.

## Cú pháp

**Cách 1**
```cpp
union unionName{       	    union student_t{       union student_t sv1;
    dataType1 member1;          char ten[30];       union student_t sv2;
    dataType2 member2;          int tuoi;           ...
    ...                         int MSSV;           hoặc
};                           };                     union student_t sv[50];
```

**Cách 2**
```cpp
typedef union{             typedef union{           student_t sv1;
    dataType1 member1;          char ten[30];       student_t sv2;
    dataType2 member2;          int tuoi;           ...
    ...                         int MSSV;           student_t sv[20];
}unionName;                }student_t;
```

## Kích thước Union
Kích thước của Union chính là kích thước của member có kích thước lớn nhất.

**Ví dụ 1**
```cpp
#include <stdio.h>
#include <stdint.h>

typedef union{     //  Scope
    uint8_t  var1; //  0 - 255
    uint32_t var2; //  0 - 4294967295
    uint16_t var3; //  0 - 65535
} frame;

int main(int argc, char const *argv[]){
    frame data;
    printf("Size = %lu\n",sizeof(frame));
    return 0;
}
```
Kết quả: ```4 byte```

**Ví dụ 2**
```cpp
#include <stdio.h>
#include <stdint.h>

typedef union{        
    uint8_t  var1[3]; //  3 byte + 1 padding
    uint32_t var2[6]; //  4 byte * 6
    uint16_t var3[9]; //  4 byte (01) + 4 byte (23) + 4 byte (45) + 4 byte (67) + 2 byte (8) + 2 padding
} frame;

int main(int argc, char const *argv[]){
    frame data;
    printf("Size = %lu\n",sizeof(frame));
    return 0;
}
```
Kết quả: ```24 byte```

## Sử dụng vùng nhớ trong Union

**Ví dụ 1**
```cpp
#include <stdio.h>
#include <stdint.h>

typedef union{     //  Scope
    uint8_t  var1; //  0 - 255
    uint32_t var2; //  0 - 4294967295
    uint16_t var3; //  0 - 65535
} frame;

int main(int argc, char const *argv[]){
    frame data;
    data.var1 = 5;
    data.var2 = 6;
    data.var3 = 7;

// 0x005FFE9C  0x005FFE9D  0x005FFE9E  0x005FFE9F
//      5
//      6
//      7

    printf("Data.var1 = %d\n", data.var1);
    printf("Data.var2 = %u\n", data.var2);
    printf("Data.var3 = %d\n", data.var3);
    return 0;
}
```
**Kết quả in ra:**
```cpp
Data.var1 = 7
Data.var2 = 7
Data.var3 = 7
```

**Giải thích**

Khi gán 5 cho member var1 thì tại địa chỉ 0x5FFE9C sẽ có giá trị 5.

Khi gán 6 cho member var2, do các member sử dụng chung vùng nhớ nên tại địa chỉ 0x5FFE9C thì giá trị 6 sẽ ghi đè lên 5.

Tương tự với member var3, giá trị cuối cùng tại địa chỉ 0x5FFE9C là 7 nên giá trị của các member đều sẽ là 7.

**Ví dụ 2**
```cpp
#include <stdio.h>
#include <stdint.h>

typedef union{     //  Scope
    uint8_t  var1; //  0 - 255
    uint32_t var2; //  0 - 4294967295
    uint16_t var3; //  0 - 65535
} frame;

int main(int argc, char const *argv[])
{
    frame data;
    data.var2 = 4294967290;

    printf("Data.var1 = %d\n", data.var1);
    printf("Data.var2 = %u\n", data.var2);
    printf("Data.var3 = %d\n", data.var3);
    return 0;
}
```
**Kết quả in ra:**
```cpp
Data.var1 = 250
Data.var2 = 4294967290
Data.var3 = 65530
```

**Giải thích**

4294967290 = 0b11111111 111111111 11111111 1111010

Do các member dùng chung vùng nhớ nên giá trị các member bằng nhau và kích thước của union frame là 4 byte nên dữ liệu sẽ được như sau:

// 0x005FFE9C  0x005FFE9D  0x005FFE9E  0x005FFE9F
//  11111010    11111111    11111111    11111111

member var1 có kiểu dữ liệu là uint8_t nên chỉ lấy 8 bit ở địa chỉ 0x005FFE9C -> var1 = 0b11111010 = 250

member var2 có kiểu dữ liệu là uint32_t nên giữ nguyên giá trị

member var3 có kiểu dữ liệu là uint16_t nên chỉ lấy 16 bit ở địa chỉ 0x005FFE9C và 0x005FFE9D -> var3 = 0b11111111 11111010 = 65530

</p>
</details>

# Sự khác nhau giữa Struct và Union
<details><summary>Chi tiết</summary>
<p>

</p>
</details>
