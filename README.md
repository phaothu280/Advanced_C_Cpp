<details><summary><b>Pointer</b></summary>
<p>
    
## Định nghĩa
Trong C, con trỏ (pointer) là một biến chứa địa chỉ của một đối tượng khác. Việc sử dụng con trỏ giúp thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.
## Kích thước con trỏ
**Kích thước của con trỏ phụ thuộc vào kiến trúc vi xử lý.**

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
## Các kiểu con trỏ
### 1.Con trỏ Void
<details><summary></summary>
<p>
	
Thường dùng để **trỏ tới bất kỳ địa chỉ** nào với bất kỳ kiểu dữ liệu của giá trị tại địa chỉ đó.

Muốn in ra giá trị thì phải sử dụng ép kiểu để đưa con trỏ void về đến kiểu dữ liệu của giá trị đó.

Cú pháp: ``` void *ptr_void; ```

Ví dụ:
```cpp
#include <stdio.h>

void sum(int a, int b){
    printf("%d + %d = %d\n", a, b, a+b);
}

int main(int argc, char const *argv[]){
    void *ptr_void = NULL;
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
</p>
</details>

### 2.Con trỏ hàm
<details><summary></summary>
<p>
	
Con trỏ hàm là một biến mà **giữ địa chỉ của hàm**.

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
</p>
</details>

### 3.Con trỏ hằng
<details><summary></summary>
<p

Con trỏ hằng là một cách định nghĩa một con trỏ **chỉ có thể đọc giá trị tại địa chỉ mà nó trỏ đến (Read Only)** nhưng không thể thay đổi được giá trị đó.

Đối với biến là hằng số thì phải luôn dùng con trỏ hằng khi trỏ đến.

Cú pháp: 
```cpp
<data_type> const *ptr_const;
const <data_type> *ptr_const;
```

**Ví dụ**
```cpp
#include <stdio.h>

int value = 10;
const int *ptr_const = &value;

int main(int argc, char const *argv[])
{
    printf("%p\n", ptr_const);
    printf("%d\n", *ptr_const);

    *ptr_const = 20;
    printf("%d\n", *ptr_const);
    return 0;
}
```
Kết quả sau khi chạy sẽ gặp lỗi: ```assignment of read-only location '*ptr_const'```

</p>
</details>

### 4.Hằng con trỏ
<details><summary></summary>
<p
    
Hằng con trỏ là một con trỏ mà **trỏ đến 1 địa chỉ cố định**, nghĩa là khi con trỏ này được khởi tạo thì nó sẽ không thể trỏ tới địa chỉ khác.

Cú pháp:
```cpp
int *const const_ptr = &value;
```

**Ví dụ**
```cpp
#include <stdio.h>

int value1 = 10;
int value2 = 20;
int *const const_ptr = &value1;

int main(int argc, char const *argv[])
{
    printf("%p\n", const_ptr);
    printf("%d\n", *const_ptr);

    const_ptr = &value2;
    printf("%p\n", const_ptr);
    return 0;
}
```
Kết quả sau khi chạy sẽ gặp lỗi: ```assignment of read-only variable 'const_ptr'```

</p>
</details>

### 5.Con trỏ NULL
<details><summary></summary>
<p
    
Khi khai báo con trỏ mà chưa sử dụng ngay hoặc sử dụng xong thì phải gán NULL.
```cpp
int *ptr_null = NULL;
//  ptr_null = 0x00: địa chỉ khởi tạo
// *ptr_null = 0   : giá trị tại địa chỉ khởi tạo
```
</p>
</details>

### 6.Pointer to pointer
<details><summary></summary>
<p
    
Là một kiểu dữ liệu trong ngôn ngữ lập trình cho phép bạn lưu trữ địa chỉ của một con trỏ. 

Con trỏ đến con trỏ cung cấp một cấp bậc trỏ mới, cho phép bạn thay đổi giá trị của con trỏ gốc. 

Cấp bậc này có thể hữu ích trong nhiều tình huống, đặc biệt là khi bạn làm việc với các hàm cần thay đổi giá trị của con trỏ.
</p>
</details>

</p>
</details>



<details><summary><b>Static - Extern - Volatile - Register</b></summary>
<p>

## Static
### Cú pháp
```cpp
static <data_type> <name_variable>;
static <data_type> <name_function>;
```

### static local variables
Khi 1 biến cục bộ được khai báo với từ khóa static:

- Giữ giá trị của biến qua các lần gọi hàm.
- Giữ phạm vi của biến chỉ trong hàm đó.

Biến cục bộ static chỉ có thể được gọi trong nội bộ hàm khởi tạo ra nó. Mỗi lần hàm được gọi, giá trị của biến chính bằng giá trị tại lần gần nhất hàm được gọi.

**Ví dụ:**
```cpp
#include <stdio.h>

int *ptr = NULL;

void Func(){
    static int a=0;
    ptr = &a;
    a++;
    printf("a = %d\n",a);
}

int main(int argc, char const *argv[]){
    Func();     // in ra "a = 1"
    Func();     // in ra "a = 2"
    *ptr = 20;  // a = 20
    Func();     // in ra "a = 21"
    return 0;
}
```

### static global variables
Khi **'static'** được sử dụng với các biến toàn cục, nó sẽ hạn chế phạm vi của biến chỉ có thể gọi trong file nguồn hiện tại.

**Ví dụ:**

File Ex1.c
```cpp
#include <stdio.h>

extern void display();
extern int value1;
extern int value2;

int main(int argc, char const *argv[]){
    value1 = 10;
    value2 = 20;
    display();
    return 0;
}
```

```cpp
#include <stdio.h>

static int value1 = 5;
int value2 = 5;

void display(){
    printf("value1=%d\n",value1);
    printf("value2=%d\n",value2);
}
```
```cpp
undefined reference to `value1'
```
Dễ thấy file Ex1.c khi chạy sẽ gặp lỗi do cố gắng sử dụng extern để gọi 1 biến toàn cục đã được khai báo với static trong 1 file nguồn khác.

## Extern
### Định nghĩa
Từ khóa **'extern'** được sử dụng cho 1 biến hoặc hàm với mục đích là thông báo rằng biến hoặc hàm này đã được định nghĩa ở một nơi khác trong chương trình hoặc trong 1 file nguồn khác. 

Cho phép các file nguồn khác nhau trong cùng một chương trình chia sẽ và sử dụng các biến và hàm mà không cần định nghĩa lại.

**Extern chỉ cho phép khai báo chứ không định nghĩa.**

Biến được tham chiếu phải được khai báo ở cấp độ cao nhất (toàn cục), và có thể nằm trong một file khác.

### Cú pháp
```cpp
extern <data_type> <name_variable>;
```

**Ví dụ:**

File main.c
```cpp
#include <stdio.h>

extern int var_global;
extern void Func();

int main(int argc, char const *argv[]){
    var_global = 3;
    Func();
    return 0;
}
```
File File1.c
```cpp
#include <stdio.h>
int var_global = 1;
void Func(){
    printf("%d\n",var_global);
}
```
Thực hiện **make file**: ```gcc main.c File1.c -o main```

### Ứng dụng
**Chia sẻ biến và hàm giữa các file nguồn**

- Extern cho phép bạn chia sẻ biến và hàm giữa nhiều file nguồn trong một chương trình.
- Điều này hữu ích khi bạn muốn tách chương trình thành các phần nhỏ để quản lý dễ dàng hơn

**Chia sẻ biến và hàm giữa các module hoặc thư viện**

- Extern có thể được sử dụng để kết nối các module hoặc thư viện trong một dự án lớn.

**Khai báo hàm trong trường hợp định nghĩa sau:**

- Nếu ban muốn sử dụng một hàm trước khi nó được định nghĩa trong mã nguồn, bạn có thể sử dụng extern để khai báo hàm.

**Biến toàn cục giữa các tệp nguồn**

- Khi có một biến toàn cục được sử dụng trong nhiều file nguồn, extern giúp các file nguồn biết về sự tồn tại của biến đó.

**Chia sẻ hằng số giữa các file nguồn**

- Nếu bạn có một hằng số được sử dụng ở nhiều nơi, bạn có thể sử dụng extern để chia sẻ giá trị của hằng số đó giữa các file nguồn.

## Volatile
### Định nghĩa
Volatile có nghĩa là không dự đoán được. Một biến sử dụng với volatile có nghĩa là nói với compiler là biến này **có thể sẽ được thay đổi ở bởi yếu tố bên ngoài chương trình** như hardward (ngắt, nhấn button,…) hoặc một luồng khác. Việc này ngăn chặn trình biên dịch tối ưu hóa hoặc xóa bỏ các thao tác trên biến đó, giữ cho các thao tác trên biến được thực hiện như đã được định nghĩa.

Một biến cần được khai báo dưới dạng biến volatile khi nào? Khi mà giá trị của nó có thể thay đổi một cách không báo trước. Việc khai báo biến volatile là rất cần thiết để tránh những lỗi sai khó phát hiện do tính năng optimization của compiler.

Biến Volatile rất cần thiết trong lập trình nhúng, vì khi đó có các tác vụ như ngắt ảnh hưởng tới giá trị của biến. Trong lập trình C cơ bản thì rất ít gặp.

### Cú pháp
```cpp
volatile <data_type> <name_variable>;
```

Ví dụ:
```cpp
volatile int flag;

void interrupt_handler(){
    flag = 1; // giá trị của flag có thể thay đổi bởi ngắt
}
```

## Register
### Định nghĩa

![image](https://github.com/user-attachments/assets/5325937f-1104-4845-9bda-7f1e7c1589b9)

Register trong C/C++ được sử dụng để định nghĩa các biến cục bộ mà nên được lưu giữ trong một thanh ghi thay vì RAM.

Từ khóa “register” làm tăng hiệu năng (performance) của chương trình.

### Cú pháp
```cpp
register <data_type> <name_variable>;
```

**Ví dụ:**
```cpp
#include <stdio.h>
#include <time.h>

int main() {
    // Lưu thời điểm bắt đầu
    clock_t start_time = clock();
    int i;
    //register int i;

    // Đoạn mã của chương trình
    for (i = 0; i < 2000000; ++i) {
        // Thực hiện một số công việc bất kỳ
    }

    // Lưu thời điểm kết thúc
    clock_t end_time = clock();

    // Tính thời gian chạy bằng miligiây
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Thoi gian chay cua chuong trinh: %f giay\n", time_taken);
    return 0;
}
```

Khi chưa register ```Thoi gian chay cua chuong trinh: 0.005 giay```

Khi có register ```Thoi gian chay cua chuong trinh: 0.001 giay```

</p>
</details>



<details><summary><b>goto - thư viện setjmp</b></summary>
<p>

## goto trong C
### Định nghĩa
Từ khóa **"goto"** cho phép chương trình nhảy đến một label đã được đặt trước đó cùng một hàm.

"goto" cung cấp khả năng kiểm soát luồng hoạt động của mã nguồn, nhưng việc sử dụng goto thường được xem là không tốt vì nó có thể làm cho mã nguồn trở nên khó đọc và khó bảo trì.

**Ví dụ**
```cpp
int main(){
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

#### Thực hiện Finite State Machine
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
setjmp.h là một thư viện trong ngôn ngữ lập trình C, cung cấp hai hàm chính là **setjmp** và **longjmp**.

### Hàm setjmp
- setjmp lưu trạng thái hiện tại của môi trường thực thi vào một biến kiểu jmp_buf.
- setjmp thường được sử dụng để thiết lập một điểm quay lại (checkpoint) trong chương trình.
- setjmp trả về giá trị 0 khi được gọi lần đầu tiên và giá trị khác 0 khi quay lại từ longjmp.

```setjmp(jmp_buf buf);```

### Hàm longjmp
longjmp là hàm dùng để nhảy trở lại vị trí đã lưu bởi setjmp và tiếp tục thực thi chương trình từ đó.

```cpp
void longjmp(jmp_buf buf, int value);
// buf  : biến 'jmp_buf' đã được lưu bởi 'setjmp'
// value: giá trị trả về từ 'setjmp'. Nếu value=0 thì 'setjmp' trả về 1
```

**Ví dụ**
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
Cả hai hàm setjmp và longjmp thường được sử dụng để thực hiện xử lý ngoại lệ trong C thông qua 3 keywords chính là: **try, catch, throw**.

```cpp
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception_code;

#define TRY if ((exception_code = setjmp(buf)) == 0)
#define CATCH(x) else if (exception_code == x)
#define THROW(x) longjmp(buf,x)
```

**Ví dụ**
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



<details><summary><b>Bitmask</b></summary>
<p>

## Định nghĩa
Bitmask là một kỹ thuật sử dụng các bit để lưu trữ và thao tác với các cờ (flags) hoặc trạng thái.

Có thể sử dụng bitmask để đặt, xóa, kiểm tra trạng thái của các bit cụ thể trong 1 word.

Bitmask thường được sử dụng để tối ưu hóa bộ nhớ, thực hiện các phép toán logic trên một cụm bit, và quản lý các trạng thái, quyền truy cập, hoặc các thuộc tính khác của một đối tượng.

## Các toán tử bitwise
![image](https://github.com/user-attachments/assets/e9b5fc2e-0d94-4708-bbe1-740f7a21d417)

![image](https://github.com/user-attachments/assets/c8549e26-9a0b-4835-a886-d11a6bed9fb1)

</p>
</details>



<details><summary><b>Struct - Union</b></summary>
<p>

## Struct
<details><summary>Chi tiết</summary>
<p>
	
struct là một cấu trúc dữ liệu cho phép tự định nghĩa một kiểu dữ liệu mới bằng cách nhóm các biến có các kiểu dữ liệu khác nhau lại với nhau.

struct cho phép tạo ra một thực thể dữ liệu lớn hơn và có tổ chức hơn từ các thành viên (members) của nó.

### Cú pháp

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

### Truy xuất dữ liệu
Sử dụng "." để truy xuất tới thành viên khi khai báo biến bình thường (int, char,…).

Sử dụng "->" để truy xuất tới thành viên khi khai báo biến là con trỏ.

### Kích thước của struct
Kích thước Struct bằng tổng các kích thước của các member và padding (nếu có).

**Ví dụ 1**
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

**Ví dụ 2**
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

**Ví dụ 3**
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

**Ví dụ 4**
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

### Địa chỉ của Struct
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

## Union
<details><summary>Chi tiết</summary>
<p>
	
Union là một cấu trúc dữ liệu giúp kết hợp nhiều kiểu dữ liệu khác nhau vào một cùng một vùng nhớ. 

Mục đích chính của union là tiết kiệm bộ nhớ bằng cách chia sẻ cùng một vùng nhớ cho các thành viên của nó. Điều này có nghĩa là, trong một thời điểm, chỉ một thành viên của union có thể được sử dụng.

### Cú pháp

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

### Kích thước Union
Kích thước của Union chính là tổng của kích thước của member có kích thước lớn nhất và padding (nếu có).

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

### Sử dụng vùng nhớ trong Union

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

```cpp
// 0x005FFE9C  0x005FFE9D  0x005FFE9E  0x005FFE9F
//  11111010    11111111    11111111    11111111
```

member var1 có kiểu dữ liệu là uint8_t nên chỉ lấy 8 bit ở địa chỉ 0x005FFE9C -> var1 = 0b11111010 = 250

member var2 có kiểu dữ liệu là uint32_t nên giữ nguyên giá trị

member var3 có kiểu dữ liệu là uint16_t nên chỉ lấy 16 bit ở địa chỉ 0x005FFE9C và 0x005FFE9D -> var3 = 0b11111111 11111010 = 65530

</p>
</details>

## So sánh Struct và Union
<details><summary>Chi tiết</summary>
<p>
	
### Giống

Đều do lập trình viên tự định nghĩa (user defined type).

Đều sử dụng dấu “.” hoặc “ ” để truy cập các phần tử (hoặc có thể gọi là thuộc tính).

## Khác
![image](https://github.com/user-attachments/assets/10994e8c-37ff-4a6b-b947-3d2fa16eee65)

</p>
</details>

</p>
</details>



<details><summary><b>Cấp phát động với malloc - calloc - realloc</b></summary>
<p>
	
![image](https://github.com/user-attachments/assets/5108cbb1-ac28-4304-9d25-6c9817c06c57)

</p>
</details>



<details><summary><b>Memory layout (Phân vùng nhớ)</b></summary>
<p>

File do người dùng viết (file .c), file .exe và file .hex (file chứa chương trình nạp vào vi điều khiển) sẽ được lưu ở bộ nhớ ROM hoặc FLASH. Khi nhấn chạy chương trình thì những chương trình này sẽ copy sang bộ nhớ RAM rồi mới bắt đầu thực thi.


Memory layout của một chương trình C/C++ gồm 5 phần chính:

- Text
- Initialized Data (DS)
- Uninitialized Data (BSS)
- Stack
- Heap

![image](https://github.com/user-attachments/assets/0092a0ac-943b-40f1-b376-caacf7bc470c)

## 1.Text Segment
![image](https://github.com/user-attachments/assets/5af24f47-6c8b-4b6b-ad10-dd6b08401e32)


```cpp
#include <stdio.h>
const int a = 10;
char *ptr = "Hello World";
int main(int argc, char const *argv[]){
    printf("a = %d\n", a);
    *ptr = "Hello";
    return 0;
}
```

Kết quả sau khi chạy sẽ hiện lỗi ```invalid conversion from 'const char*' to 'char' [-fpermissive]```

Do con trỏ ptr được khai báo kiểu char nên khi ta cố gắng thay đổi giá trị của nó sẽ gặp lỗi.

## 2.Initialized Data Segment (DS)
![image](https://github.com/user-attachments/assets/5f4e8151-4160-4de8-8648-672bc55adee3)

```cpp
int a = 5;
static b = 6;
void test(){
    static int c = 7;
}
int main(int argc, char const *argv[]){
    /* code */
    return 0;
}
```

Biến a là biến toàn cục, khởi tạo là 5, và được cấp phát 1 địa chỉ cố định (giả sử là 0x02).

Biến b là static toàn cục và c là biến static cục bộ cũng sẽ được cấp phát địa chỉ.

Các địa chỉ trên sẽ bị thu hồi khi chương trình kết thúc.

Biến a, b, c đều có thể thay đổi trong quá trình thực thi (đọc – ghi).

## 3.Uninitialized Data Segment (BSS)
![image](https://github.com/user-attachments/assets/cbcccc8e-8113-42cf-8c1d-64153ba4fb8a)

```cpp
#include <stdio.h>

typedef struct{
    int x;
    int y;
} Point_Data;

static Point_Data p1 = {5,7};

int a = 0;
int b;

static int global = 0;
static int global_2;

void test(){
    static int local = 0;
    static int local_2;
}

int main() {
    printf("a: %d\n", a);
    printf("global: %d\n", global);
    return 0;
}
```
Tất cả các biến khai báo như trên đều sẽ được lưu trữ ở phân vùng BSS.

2 biến x,y trong struct Point_Data sẽ nằm phân vùng BSS mặc dù sau đó được khởi tạo giá trị là 5,7.

## 4.Stack (Automatic Variable Storage)
![image](https://github.com/user-attachments/assets/bc290383-e76f-490a-805e-ed4d7c567aae)

```cpp
int total(int a, int b){
    int c;
    c = a + b;
    return c;
}
int main(int argc, char const *argv[]){
    printf("a+b=%d\n",total(5,6));
    printf("a+b=%d\n",total(9,7));
    return 0;
}
```
Biến a, b là input parameter của hàm.

Biến c là biến cục bộ, khi ra khỏi hàm total() thì sẽ mất đi.
Khi chạy lệnh printf() đầu tiên, a=5 và được cấp phát địa chỉ (giả sử là 0x01), b=6 và được cấp phát địa chỉ (giả sử là 0x03), biến c cũng sẽ được cấp phát địa chỉ (giả sử là 0x04). Những địa chỉ này se được lưu ở phần vùng Stack. Sau khi return kết quả thì địa chỉ của các biến a, b, c sẽ bị thu hồi.

Khi chạy lệnh printf() thứ hai, a=9 và tiếp tục được cấp phát địa chỉ (có thể là 0x01 hoặc khác), tương tự b, c và sau khi return kết quả thì các địa chỉ cũng bi thu hồi.

## 5.Heap (Dynamic Memory Allocation)
![image](https://github.com/user-attachments/assets/96602d39-cc3f-4f94-a285-a3556b22fccb)

**Ví dụ**

![image](https://github.com/user-attachments/assets/71fe3f16-6945-418a-86b0-41fc87872ea6)

```cpp
&arr[0] = 889248      &arr[0] = 7377312
&arr[1] = 889252      &arr[1] = 7377316
&arr[2] = 889256      &arr[2] = 7377320
&arr[3] = 889260      &arr[3] = 7377324
&arr[4] = 889264      &arr[4] = 7377328
----------------      ----------------
&arr[0] = 889728      &arr[0] = 7377312
&arr[1] = 889732      &arr[1] = 7377316
&arr[2] = 889736      &arr[2] = 7377320
&arr[3] = 889740      &arr[3] = 7377324
&arr[4] = 889744      &arr[4] = 7377328
```
Trong đoạn mã nguồn bên trái, sử dụng malloc() để cấp phát động 5 ô nhớ cho 1 mảng gồm 5 phần tử. Sau khi chương trình thực thi, ta thấy địa chỉ của các phần tử sau 2 lần in ra là khác nhau. Nguyên nhân là do người dùng chưa giải phóng bộ nhớ nên sau khi chạy hàm generate_array() lần đầu tiên, hệ thống sẽ phải tìm các địa chỉ khác còn trống để cấp phát cho các phần tử của mảng cho lần thực thi tiếp theo.

Ở mã nguồn bên phải, địa chỉ của các phần tử sau khi thực thi là giống nhau. Nguyên nhân là do người dùng đã giải phóng bộ nhớ (hàm free()) nên sau lần chạy hàm generate_array() đầu tiên, hệ thống đã thu hồi địa chỉ và các địa chỉ đó sẽ trống và được cấp phát cho lần thực thi tiếp theo.

## So sánh vùng nhớ Stack và Heap
![image](https://github.com/user-attachments/assets/8c97367c-f81e-42aa-a80c-9a156ca6ef55)

**Khi nào sử dụng Heap? Khi nào sử dụng Stack?**

**Sử dụng Stack**: Khi bạn biết trước kích thước của dữ liệu và dữ liệu này có vòng đời ngắn, được sử dụng trong phạm vi hàm.

```cpp
void function() {
    int a = 10; // Biến cục bộ "a" được lưu trên stack
    int b[20];  // Mảng tĩnh "b" có kích thước cố định được lưu trên stack
}
```

**Sử dụng Heap**: Khi bạn cần quản lý bộ nhớ với kích thước động và vòng đời của dữ liệu dài, tồn tại ngoài phạm vi của một hàm.

```cpp
void function() {
    int* ptr = (int*)malloc(sizeof(int) * 10); // Cấp phát mảng động trên heap
    // Sử dụng mảng "ptr"
    free(ptr); // Giải phóng bộ nhớ
}
```

</p>
</details>



<details><summary><b>JSON</b></summary>
<p>

## Khái niệm
JSON là viết tắt của “JavaScript Object Notation” (Ghi chú về đối tượng JavaScript).

Là một định dạng truyền tải dữ liệu phổ biến trong lập trình và giao tiếp giữa các máy chủ và trình duyệt web, cũng như giữa các hệ thống khác.

JSON được thiết kế để dễ đọc và dễ viết cho con người, dễ phân tích cho máy tính với cú pháp dựa trên một cặp **key – value**.

**Ví dụ**
```cpp
{
  "name": "John Doe",
  "age": 30.1234,
  "city": "New York",
  "isStudent": true,
  "grades": [85, 90, 78]
}
```

## Định dạng của JSON

### Kiểu dữ liệu

- NULL: ```null```
- Boolean: ```true``` hoặc ```false```
- Number: có thể là số nguyên hoặc số thập phân. Số không được bao bọc bởi dấu ngoặc.
```cpp
42
3.14
30.000
```
- String: Chuỗi ký tự, được bao bọc bởi dấu nháy đơn ('') hoặc dấu nháy kép ("").
```cpp
"Hello, World!"
```
- Array: Một danh sách các giá trị, giữa mỗi giá trị sử dụng dấu phẩy. Mảng được bao bọc bởi dấu ngoặc vuông ([]).
```cpp
[1, 2, 3, 4, 5]
```
- Object (đối tượng): Một tập hợp **các cặp key - value**, giữa mỗi cặp sử dụng dấu **hai chấm (:)**. Đối tượng được **bao bọc bởi dấu ngoặc nhọn ({})**.
```cpp
{
  "name": "John",
  "age": 30,
  "city": "New York"
}
```

### Key - Value

- Mỗi cặp key - value được phân tách bằng dấu hai chấm (:).
- Các cặp key - value trong object được phân tách bằng dấu phẩy (,).

```cpp
{
  "key1":"value1",
  "key2":"value2",
  "key3":"value3"
}
```

### Dấu ngoặc

- Dấu ngoặc nhọn ({}) được sử dụng để bao bọc đối tượng.
- Dấu ngoặc vuông ([]) được sử dụng để bao bọc mảng.

### Dấu phẩy

Dấu phẩy được sử dụng để phân tách giữa các thành phần trong mảng hoặc các cặp key-value trong đối tượng.

### Khoảng trắng

Khoảng trắng, dấu xuống dòng và tab không ảnh hưởng đến tính chính xác của JSON và thường được sử dụng để làm cho JSON dễ đọc hơn.

### Nhận xét

JSON không hỗ trợ cú pháp nhận xét nội dung. Bất kỳ văn bản nào sau dấu nhận xét (// hoặc /* */) không được hiểu là hợp lệ trong JSON.

## Khai báo kiểu dữ liệu để sử dụng cho JSON

```cpp
typedef enum{
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JSONType;

typedef struct JSONValue{
    JSONType type;
    union{
        int     boolean;
        double  number;
        char    *string;
        struct{
            struct JSONValue *values;
            size_t count;
        } array;
        struct{
            char   **keys;
            struct JSONValue *values;
            size_t count;
        } object;
    } value;
} JSONValue;
```

### 1. JSONType

Là một kiểu liệt kê (enum) xác định các loại giá trị mà một đối tượng JSON có thể có, bao gồm các giá trị như sau:

- JSON_NULL: Đại diện cho giá trị null trong JSON.
- JSON_BOOLEAN: Đại diện cho giá trị true hoặc false trong JSON.
- JSON_NUMBER: Đại diện cho một số (có thể là số nguyên hoặc số thực) trong JSON.
- JSON_STRING: Đại diện cho một chuỗi ký tự trong JSON.
- JSON_ARRAY: Đại diện cho một mảng các giá trị JSON khác.
- JSON_OBJECT: Đại diện cho một đối tượng (object) JSON, bao gồm các cặp khóa-giá trị.

### 2. JSONValue

Là một cấu trúc dữ liệu (struct) đại diện cho một giá trị JSON bất kỳ. Nó bao gồm hai thành phần chính:

- type: Kiểu dữ liệu JSONType, xác định loại giá trị mà đối tượng JSON này đại diện.
- value: Một union lưu trữ giá trị thực tế, có thể là một số, chuỗi, mảng, đối tượng, hoặc các kiểu khác dựa trên loại được xác định bởi type.

Mỗi thành phần của union value sẽ lưu trữ một giá trị tương ứng với loại của nó, ví dụ:

- Nếu ```type``` là ```JSON_NUMBER```, ```value.number``` sẽ lưu giá trị số.
- Nếu ```type``` là ```JSON_STRING```, ```value.string``` sẽ lưu trữ một chuỗi.
- Nếu ```type``` là ```JSON_ARRAY```, ```value.array``` sẽ lưu trữ một mảng các giá trị JSON khác.
- Nếu ```type``` là ```JSON_OBJECT```, ```value.object``` sẽ lưu trữ một đối tượng JSON.

</p>
</details>



<details><summary><b>Linked List</b></summary>
<p>

## Định nghĩa

Danh sách liên kết (Linked List) là một cấu trúc dữ liệu trong lập trình máy tính, được sử dụng để tổ chức và lưu trữ dữ liệu. Một Linked list bao gồm một chuỗi các nút (nodes) được phân bổ động, được sắp xếp theo cách mà mỗi node sẽ chứa một giá trị và một con trỏ (pointer) trỏ đến node tiếp theo nó. Nếu con trỏ là NULL thì nó là node cuối cùng trong danh sách.

Có hai loại linked list chính:

- Singly Linked List (Danh sách liên kết đơn): Mỗi nút chỉ chứa một con trỏ đến nút tiếp theo trong chuỗi.
- Doubly Linked List (Danh sách liên kết đôi): Mỗi nút chứa hai con trỏ, một trỏ đến nút tiếp theo và một trỏ đến nút trước đó.

Một linked list cung cấp một cách linh hoạt để thêm, xóa và chèn các phần tử mà không cần phải di chuyển toàn bộ dãy số như mảng. Tuy nhiên, nó cũng có một số nhược điểm, như việc cần thêm một con trỏ cho mỗi nút, tăng độ phức tạp của bộ nhớ và có thể dẫn đến hiệu suất kém hơn trong một số trường hợp so với mảng.

Một danh sách được liên kết được giữ bằng cách sử dụng một biến con trỏ cục bộ trỏ đến mục đầu tiên của danh sách. Nếu con trỏ đó cũng là NULL thì danh sách được coi là trống.

![image](https://github.com/user-attachments/assets/c2669fde-dacb-4f2b-9cd8-cb861c7e9e3e)

## Các hàm trong Linked List
### Định nghĩa 1 node trong singly linked list
```cpp
typedef struct Node{
    int data;
    struct Node *next;
} Node_t;
```
### Khởi tạo 1 node mới
```cpp
// khởi tạo giá trị ban đầu và trả địa chỉ về cho node được cấp phát.
Node_t *createNode(int data){
    Node_t *temp = (Node_t*)malloc(sizeof(Node_t));
    temp->data = data;
    temp->next = NULL;
    // node vừa tạo chưa liên kết với phần tử nào nên phần liên kết gán bằng NULL
    return temp;
}
```
### Thêm node mới vào đầu danh sách
```cpp
void push_front(Node_t **head, int data){
    Node_t *new_node = createNode(data);
    if (*head == NULL){
        *head = new_node;
    }
    else{
        new_node->next = *head;
        *head = new_node;
    }
}
```
### Thêm node mới vào cuối danh sách
```cpp
void push_back(Node_t **head, int data){
    Node_t *new_node = createNode(data);
    if (*head == NULL){
        *head = new_node;
    }
    else{
        Node_t *p = *head;
        while (p->next != NULL){
            p = p->next;
        }
        p->next = createNode(data);
    }
}
```
### Thêm node mới vào vị trí bất kỳ trong danh sách
```cpp
void insert(Node_t **head, int data, int position){
    Node_t *new_node = createNode(data);
    Node_t *p = *head;
    int k = 0;

    while (p->next != NULL && k != position-1){
        p = p->next;
        k++;
    }
    
    if (k == position-1){
        new_node->next = p->next;
        p->next = new_node;
    }
    else return;
}
```
### Xóa node đầu tiên trong danh sách
```cpp
void pop_front(Node_t **head){
    Node_t *new_head = (*head)->next;
    free(*head);
    *head = new_head;
}
```
### Xóa node cuối cùng trong danh sách
```cpp
void pop_back(Node_t **head){
    if (*head == NULL){
        free(*head);
    }
    else{
        Node_t *p = *head;
        while (p->next->next != NULL){
            p = p->next;
        }
        free(p->next);
        p->next = NULL;
    }
}
```
### Xóa node bất kỳ trong danh sách
```cpp
void delete_node(Node_t **head, int position){
    Node_t *p = *head;
    int k = 0;

    while (p != NULL && k != position-1){
        p = p->next;
        k++;
    }

    if (k == position-1){
        Node_t *node_delete = p->next;
        p->next = p->next->next;
        free(node_delete);
    }
    else return;
}
```
### Xóa toàn bộ node trong danh sách
```cpp
void clear_all(Node_t **head){
    Node_t *p = *head;
    while (p != NULL){
        Node_t *temp = p->next;
        free(p);
        p = temp;
    }
    *head = NULL;
}
```
### Tính kích thước của danh sách
```cpp
int size(Node_t *head){
    Node_t *p = head;
    int count = 0;
    while (p != NULL){
        count++;
        p = p->next;
    }
    return count;
}
```

</p>
</details>



<details><summary><b>Stack - Queue</b></summary>
<p>

## Stack
<details><summary>Chi tiết</summary>
<p>

### Định nghĩa Stack (Ngăn xếp)

Stack (ngăn xếp) là một cấu trúc dữ liệu tuân theo nguyên tắc "Last In, First Out" (LIFO), nghĩa là phần tử cuối cùng được thêm vào stack sẽ là phần tử đầu tiên được lấy ra. 

Các thao tác cơ bản trên stack bao gồm:

- "push" để thêm một phần tử vào đỉnh của stack.
- "pop" để xóa một phần tử ở đỉnh stack.
- "top" để lấy giá trị của phần tử ở đỉnh stack.

![image](https://github.com/user-attachments/assets/fcf7c263-0f88-4899-993d-4d8946df2068)

### Các hàm sử dụng trong Stack

#### Định nghĩa 1 Stack
```cpp
typedef struct{
    int* items;
    int size;
    int top;
} Stack;
```

#### Khởi tạo 1 Stack mới
```cpp
void initialize(Stack *stack, int size){
    stack->items = (int*)malloc(sizeof(int)*size);
    stack->size  = size;
    stack->top   = -1;
}
```

#### Kiểm tra Stack rỗng
```cpp
int isEmpty(Stack stack){
    return stack.top == -1;
}
```

#### Kiểm tra Stack đầy
```cpp
int isFull(Stack stack){
    return stack.top == stack.size - 1;
}
```

#### Thêm phần tử vào Stack
```cpp
void push(Stack *stack, int value){
    if (!isFull(*stack)){
        stack->items[++stack->top] = value;
    } 
    else{
        printf("Stack overflow\n");
    }
}
```

#### Xóa phần tử ra khỏi Stack
```cpp
int pop(Stack *stack){
    if (!isEmpty(*stack)){
        return stack->items[stack->top--];
    } 
    else{
        printf("Stack underflow\n");
        return -1;
    }
}
```

#### Lấy giá trị của phần tử ở đỉnh Stack
```cpp
int top(Stack stack){
    if (!isEmpty(stack)){
        return stack.items[stack.top];
    } 
    else{
        printf("Stack is empty\n");
        return -1;
    }
}
```

</p>
</details>

## Queue
<details><summary>Chi tiết</summary>
<p>

### Định nghĩa Queue (Hàng đợi)

Queue là một cấu trúc dữ liệu tuân theo nguyên tắc "First In, First Out" (FIFO), nghĩa là phần tử đầu tiên được thêm vào hàng đợi sẽ là phần tử đầu tiên được lấy ra. 

Các thao tác cơ bản trên hàng đợi bao gồm:

- "enqueue": thêm phần tử vào cuối hàng đợi.
- "dequeue": lấy phần tử từ đầu hàng đợi.
- "front": lấy giá trị của phần tử đứng đầu hàng đợi.

### Các hàm sử dụng trong Queue

#### Định nghĩa 1 hàng đợi
```cpp
typedef struct{
    int *item;    // mảng tượng trưng chứa các giá trị của phần tử trong queue
    int size;     // kích thước của queue
    int front;    // phần tử đầu queue
    int rear;     // phần tử cuối queue
} Queue;
```

#### Khởi tạo 1 hàng đợi mới
```cpp
Queue *initialize(int size){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->item  = (int*)malloc(size * sizeof(int));
    queue->size  = size;
    queue->front = queue->rear = -1;
    return queue;
}
```

#### Kiểm tra hàng đợi rỗng
```cpp
int isEmpty(Queue queue){
    return (queue.front == -1);
}
```

#### Kiểm tra hàng đợi đầy
```cpp
int isFull(Queue queue){
    return (queue.rear + 1) % queue.size == queue.front;
}
```
 
#### Thêm phần tử vào cuối hàng đợi
```cpp
void enqueue(Queue *queue, int data){
    if (isFull(*queue)){
        // nếu queue đầy thì không cho thêm phần tử vào
        printf("Queue overflow\n");
    } 
    else{
        if (isEmpty(*queue)){
            queue->front = queue->rear = 0;
        }
        else{
            queue->rear = (queue->rear + 1) % queue->size;
        }
        queue->item[queue->rear] = data;
    }
}
```

#### Xóa phần tử từ đầu hàng đợi
```cpp
int dequeue(Queue *queue){
    if (isEmpty(*queue)){
        // nếu queue rỗng thì không cho xóa
        printf("Queue underflow\n");
        return -1;
    }
    else{
        int dequeue_value = queue->item[queue->front];
        if (queue->front == queue->rear){
            queue->front = queue->rear = -1;
        }
        else{
            queue->front = (queue->front + 1) % queue->size;
        }
        return dequeue_value;
    }
}
```
 
#### Lấy giá trị của phần tử đứng đầu hàng đợi	
```cpp
int front(Queue queue){
    if (isEmpty(queue)){
        printf("Queue is empty\n");
        return -1;
    }
    else{
        return queue.item[queue.front];
    }
}
```

</p>
</details>

</p>
</details>
