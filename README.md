# POINTER

## Định nghĩa
Trong C, con trỏ (pointer) là một biến chứa địa chỉ bộ nhớ của một biến khác. Việc sử dụng con trỏ giúp thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.
## Kích thước con trỏ
Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch.

•Hệ thống 32 – bit, kích thước của con trỏ là 4 byte.

•Hệ thống 64 – bit, kích thước của con trỏ là 8 byte.
## Các kiểu con trỏ
### 1.Con trỏ Void
Thường dùng để trỏ tới bất kỳ địa chỉ nào với bất kỳ kiểu dữ liệu của giá trị tại địa chỉ đó.

Muốn in ra giá trị thì phải sử dụng ép kiểu để đưa con trỏ void về đến kiểu dữ liệu của giá trị đó.

Cú pháp: ``` void *ptr_void; ```

Ví dụ:
```cpp
#include <stdio.h>

void sum(int a, int b){
    printf("%d + %d = %d\n", a, b, a+b);
}

int main(int argc, char const *argv[]){
    void *ptr_void;
    ptr_void = (void*)sum;
    ((void (*)(int,int))ptr_void)(9,3);

    int var_int = 10;
    ptr_void = &var_int;
    printf("Dia chi: %p, int: %d\n", ptr_void, *(int*)ptr_void);

    double var_double = 3.14;
    ptr_void = &var_double;
    printf("Dia chi: %p, double: %.3f\n", ptr_void, *(double*)ptr_void);

    char var_char = 'B';
    ptr_void = &var_char;
    printf("Dia chi: %p, char: %c\n", ptr_void, *(char*)ptr_void);

    return 0;
}
```
### 2.Con trỏ hàm

### 3.Con trỏ hằng

### 4.Hằng con trỏ

### 5.Con trỏ NULL

### 6.Pointer to pointer
