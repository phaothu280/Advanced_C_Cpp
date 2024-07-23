# POINTER
<details><summary>Chi tiết</summary>
<p>

## Định nghĩa
Trong C, con trỏ (pointer) là một biến chứa địa chỉ bộ nhớ của một biến khác. Việc sử dụng con trỏ giúp thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.
## Kích thước con trỏ
**Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch.**

Hệ thống 32 – bit, kích thước của con trỏ là 4 byte.

Hệ thống 64 – bit, kích thước của con trỏ là 8 byte.

```cpp
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[]){
    printf("%d bytes\n", sizeof(int *));
    printf("%d bytes\n", sizeof(char *));
    printf("%d bytes\n", sizeof(float *));
    printf("%d bytes\n", sizeof(double *));
    printf("%d bytes\n", sizeof(long *));
    printf("%d bytes\n", sizeof(short *));
    printf("%d bytes\n", sizeof(long long *));
    printf("%d bytes\n", sizeof(bool *));
    return 0;
}
```
```cpp
4 bytes
4 bytes
4 bytes
4 bytes
4 bytes
4 bytes
4 bytes
4 bytes
```
## Các kiểu con trỏ
### 1.Con trỏ Void
Thường dùng để **trỏ tới bất kỳ địa chỉ** nào với **bất kỳ kiểu dữ liệu** của giá trị tại địa chỉ đó.

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
```cpp
9 + 3 = 12
Dia chi: 00000000005FFE94, int: 10
Dia chi: 00000000005FFE88, double: 3.140
Dia chi: 00000000005FFE87, char: B
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
```cpp
7 + 10 = 17
7 - 10 = -3
7 x 7 = 49
6 / 5 = 1.200
```
### 3.Con trỏ hằng
Con trỏ hằng là một cách định nghĩa một con trỏ **chỉ có thể đọc giá trị tại địa chỉ mà nó trỏ đến (Read Only)** nhưng không thể thay đổi được giá trị đó.

Đối với biến là hằng số thì phải luôn dùng con trỏ hằng khi trỏ đến.

Cú pháp: 
```cpp
<data_type> const *ptr_const;
const <data_type> *ptr_const;
```
### 4.Hằng con trỏ
Hằng con trỏ là một con trỏ mà **trỏ đến 1 địa chỉ cố định**, nghĩa là khi con trỏ này được khởi tạo thì nó sẽ không thể trỏ tới địa chỉ khác.

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
    while (*str1 && (*str1 == *str2)){    // so sánh từng ký tự của mỗi chuỗi
        str1++;  // tăng địa chỉ để truy cập vào ký tự tiếp theo khi 2 ký tự giống nhau
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2; // lấy mã Ascii để so sánh
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

// Hàm sắp xếp sinh viên dựa theo tiêu chí (tên hoặc điểm hoặc ID)
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
```cpp
ID: 100,  Ten: Hoang,   Diem tb: 7.50
ID: 101,  Ten: Tuan,   Diem tb: 6.50
ID: 102,  Ten: Vy,   Diem tb: 5.50

ID: 102,  Ten: Vy,   Diem tb: 5.50
ID: 101,  Ten: Tuan,   Diem tb: 6.50
ID: 100,  Ten: Hoang,   Diem tb: 7.50

ID: 100,  Ten: Hoang,   Diem tb: 7.50
ID: 101,  Ten: Tuan,   Diem tb: 6.50
ID: 102,  Ten: Vy,   Diem tb: 5.50
```

</p>
</details>

# Goto - setjmp.h
<details><summary>Chi tiết</summary>
<p>

## Goto trong C
### Định nghĩa

Từ khóa **"goto"** cho phép chương trình nhảy đến một label đã được đặt trước đó cùng một hàm. 

"goto" cung cấp khả năng kiểm soát luồng hoạt động của mã nguồn, nhưng việc sử dụng goto thường được xem là không tốt vì nó có thể làm cho mã nguồn trở nên khó đọc và khó bảo trì. 

**Ví dụ:**
```cpp
    int i=0;
    
    // đặt label start
    start:
        if (i >= 5){
            goto end;       // chuyển control đến lable "end"
        }
        printf("%d\n",i);
        i++;
        goto start;

    // đặt label end
    end:
        printf("The end\n");// chuyển control đến label "start"
    return 0;
}
```
Trong ví dụ này, goto được sử dụng để tạo một vòng lặp đơn giản. Khi i đạt đến giá trị 5, control sẽ chuyển đến nhãn "end" và kết thúc chương trình.

### Các ứng dụng của goto
#### Thoát khỏi vòng lặp nhiều cấp độ
Trong một số trường hợp, việc thoát khỏi nhiều cấp độ vòng lặp có thể trở nên phức tạp nếu sử dụng cấu trúc kiểm soát vòng lặp thông thường. Trong tình huống như vậy, goto có thể được sử dụng để dễ dàng thoát khỏi nhiều cấp độ vòng lặp.
```cpp
int main(int argc, char const *argv[]){
    int count=0;

    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            if (i==5 && j==5) goto exit_loops;
            else{
                printf("i=%d  j=%d\n", i, j);
            }
        }
    }
    
    exit_loops:
    return 0;
}
```

#### Xử lý lỗi và giải phóng bộ nhớ
Trong trường hợp xử lý lỗi, có thể sử dụng goto để dễ dàng giải phóng bộ nhớ đã được cấp phát trước khi thoát khỏi hàm.
```cpp
void process_data() {
    int *data = malloc(sizeof(int) * 100);
    if (data == NULL) {
        goto cleanup;
    }

    // Xử lý dữ liệu ở đây

    cleanup:
    free(data);
}
```

#### Thực hiện Finite State Machines (FSM)
Trong một số trường hợp, đặc biệt là khi triển khai Finite State Machines, goto có thể được sử dụng để chuyển đến các trạng thái khác nhau một cách dễ dàng.
```cpp
switch (current_state) {
    case STATE_A:
        // Xử lý State A
        if (condition) {
            goto STATE_B;
        }
        break;

    case STATE_B:
        // Xử lý State B
        break;
}
```

## Thư viện setjmp
### Định nghĩa
setjmp.h là một thư viện trong ngôn ngữ lập trình C, cung cấp hai hàm chính là **setjmp** và **longjmp**.

```cpp
setjmp(jmp_buf buf);
```
```cpp
void longjmp(SETJMP_FLOAT128 *_Buf, int _Value);
```

**Ví dụ:**
```cpp
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception_code;

double thuong(int a, int b){
	if (!b){
		longjmp(buf,1);
	}
	return a/(double)b;
}

int checkArray(int *arr, int size){
    	if (size <= 0){
        	longjmp(buf,2);
	}
    	return 1;
}

int main(int argc, char const *argv[]){
	// khi bắt đầu thì setjmp(buf) luôn bằng 0

	if ((exception_code = setjmp(buf)) == 0){
		int array[0];
		double ketqua = thuong(8,0);
		printf("Ket qua: %0.3f\n", ketqua);
		checkArray(array,0);
	}
	else if (exception_code == 1){
		printf("ERROR! Mau bang 0\n");
	}
	else if (exception_code == 2){
		printf("ERROR! Array bang 0\n");
	}
	return 0;
}
```

### Xử lý ngoại lệ
Cả hai hàm **setjmp** và **longjmp** thường được sử dụng để thực hiện xử lý ngoại lệ trong C thông qua 3 keywords chính là: **try**, **catch**, **throw**.
```cpp
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception_code;

#define TRY if ((exception_code = setjmp(buf)) == 0)
#define CATCH(x) else if (exception_code == x)
#define THROW(x) longjmp(buf,x)
```

**Ví dụ:**
```cpp
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception_code;

#define TRY if ((exception_code = setjmp(buf)) == 0)
#define CATCH(x) else if (exception_code == x)
#define THROW(x) longjmp(buf,x)

double thuong(int a, int b){
    if (b == 0){
        THROW(1);
    }
    return a/(double)b;
}

int checkArray(int *arr, int size){
    if (size <= 0){
        THROW(2);
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    
    TRY{
        int array[0];
        double ketqua = thuong(8,1);
        printf("Ket qua = %0.3f\n",ketqua);
        checkArray(array,0);
    }
    CATCH(1){
        printf("Error\n");
    }
    CATCH(2){
        printf("Error! Array = 0\n");
    }

    return 0;
}
```

</p>
</details>

# Static - Extern - Register - Volatile
<details><summary></summary>
<p>


</p>
</details>

# Bitmask
<details><summary></summary>
<p>


</p>
</details>
