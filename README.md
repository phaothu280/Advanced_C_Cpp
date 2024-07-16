# POINTER

## Định nghĩa
Trong C, con trỏ (pointer) là một biến chứa địa chỉ bộ nhớ của một biến khác. Việc sử dụng con trỏ giúp thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.
## Kích thước con trỏ
Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch.

Hệ thống 32 – bit, kích thước của con trỏ là 4 byte.

Hệ thống 64 – bit, kích thước của con trỏ là 8 byte.

```cpp
#include <stdio.h>

int main() {
    int  *a;
    char *b;
    printf("Size of pointer a is %d bytes and b is %d bytes\n", sizeof(a), sizeof(b));
    return 0;
}
```
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
Con trỏ hàm là một biến mà giữ địa chỉ của hàm.

Khi khai báo một con trỏ hàm, ta sẽ cần chỉ định kiểu dữ liệu của hàm mà con trỏ đó sẽ tham chiếu đến, bao gồm kiểu trả về và các tham số của hàm. Sau đó, ta có thể gán con trỏ hàm này cho một hàm cụ thể. Khi gọi con trỏ hàm, chương trình sẽ thực thi hàm mà con trỏ đang tham chiếu đến.

Cú pháp:
```cpp
<return_type> (* func_pointer)(input_1_data type, input_2_data type,....);

int (*ptr)(int,double);
void (*array[])(int,int);
```

Ví dụ:
```cpp
#include <stdio.h>

void tong(int a, int b){
    printf("%d + %d = %d\n", a, b, a+b);
}

void hieu(int a, int b){
    printf("%d - %d = %d\n", a, b, a-b);
}

void tich(int a, int b){
    printf("%d x %d = %d\n", a, b, a*b);
}

void thuong(int a, int b){
    printf("%d/%d = %0.3f\n", a, b, a/(double)b);
}

int main(int argc, char const *argv[]){
    // khai báo con trỏ ptr có kiểu trả về là void
    // tham số truyền vào là 2 tham số kiểu integer
    void (*pheptoan[])(int,int) = {&tong, &hieu, &tich, &thuong};
    pheptoan[0](7,10);
    pheptoan[1](7,10);
    pheptoan[2](7,7);
    pheptoan[3](6,5);
    return 0;
}
```
### 3.Con trỏ hằng
Con trỏ hằng là một cách định nghĩa một con trỏ chỉ có thể đọc giá trị tại địa chỉ mà nó trỏ đến (Read Only) nhưng không thể thay đổi được giá trị đó.

Đối với biến là hằng số thì phải luôn dùng con trỏ hằng khi trỏ đến.

Cú pháp: 
```cpp
<kiểu_dữ_liệu> const *ptr_const;
const <kiểu_dữ_liệu> *ptr_const;
```
### 4.Hằng con trỏ
Hằng con trỏ là một con trỏ mà trỏ đến 1 địa chỉ cố định, nghĩa là khi con trỏ này được khởi tạo thì nó sẽ không thể trỏ tới địa chỉ khác.

Cú pháp:
```cpp
int *const const_ptr = &value;
```
### 5.Con trỏ NULL
Khi khai báo con trỏ mà chưa sử dụng ngay hoặc sử dụng xong thì phải gán NULL.
```cpp
int *ptr_null = NULL;
//  ptr_null = 0x00: địa chỉ khởi tạo
// *ptr_null = 0   : giá trị tại địa chỉ khởi tạo
```
### 6.Pointer to pointer
Là một kiểu dữ liệu trong ngôn ngữ lập trình cho phép bạn lưu trữ địa chỉ của một con trỏ. 

Con trỏ đến con trỏ cung cấp một cấp bậc trỏ mới, cho phép bạn thay đổi giá trị của con trỏ gốc. 

Cấp bậc này có thể hữu ích trong nhiều tình huống, đặc biệt là khi bạn làm việc với các hàm cần thay đổi giá trị của con trỏ.

## Ví dụ về con trỏ
```cpp
#include <stdio.h>
#include <string.h>

typedef struct{
    char  ten[50];
    float diemTrungBinh;
    int   id;
}SinhVien_t;

int stringCompare(const char *str1,const char *str2){
    while (*str1 && (*str1 == *str2)){
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

// Hàm so sánh theo tên
int compareByName(const void *a,const void *b){
    SinhVien_t *sv1 = (SinhVien_t *)a;
    SinhVien_t *sv2 = (SinhVien_t *)b;
    return stringCompare(sv1->ten, sv2->ten);
}

// Hàm so sánh theo điểm trung bình
int compareByDiemTrungBinh(const void *a, const void *b) {
   SinhVien_t *sv1 = (SinhVien_t *)a;
   SinhVien_t *sv2 = (SinhVien_t *)b;
   if (sv1->diemTrungBinh > sv2->diemTrungBinh)
   {
       return 1;
   }
  
   return 0;
}

// Hàm so sánh theo ID
int compareByID(const void *a, const void *b) {
   SinhVien_t *sv1 = (SinhVien_t *)a;
   SinhVien_t *sv2 = (SinhVien_t *)b;
   return sv1->id - sv2->id;
}

// Hàm hoán vị
void swapSV(SinhVien_t *a, SinhVien_t *b){
    SinhVien_t temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// Hàm sắp xếp chung
void sort(SinhVien_t array[], size_t size, int (*compareFunc)(const void *, const void *)){
    int i,j;
    for (i=0; i<size-1; i++){
        for (j=i+1; j<size; j++){
            if (compareFunc(array+i,array+j) > 0){
                swapSV(array+i,array+j);
            }
        }
    }
}

void display(SinhVien_t *array, size_t size){
    for (size_t i = 0; i < size; i++){
        printf("ID: %d,  Ten: %s,   Diem tb: %.2f\n", array[i].id, array[i].ten, array[i].diemTrungBinh);
    }
    printf("\n");
}

int main(int argc, char const *argv[]){
    SinhVien_t danhsanhSV[] = {
        {
            .ten = "Hoang",
            .diemTrungBinh = 7.5,
            .id = 100
        },
        {
            .ten = "Tuan",
            .diemTrungBinh = 6.5,
            .id = 101
        },
        {
            .ten = "Vy",
            .diemTrungBinh = 5.5,
            .id = 102
        }
    };
    size_t size = sizeof(danhsanhSV) / sizeof(danhsanhSV[0]);
    
    // Sắp xếp theo tên
    sort(danhsanhSV, size, compareByName);
    display(danhsanhSV, size);

    // Sắp xếp theo điểm trung bình
    sort(danhsanhSV, size, compareByDiemTrungBinh);
    display(danhsanhSV, size);

    // Sắp xếp theo ID
    sort(danhsanhSV, size, compareByID);
    display(danhsanhSV, size);

    return 0;
}
```
