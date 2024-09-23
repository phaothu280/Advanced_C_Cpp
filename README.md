<details><summary><b>✨ Compiler</b></summary>
<p>

<details><summary><b>📚 Giới thiệu về compiler</b></summary>
<p>

Các ngôn ngữ lập trình thường dùng như C/C++, Java, Python, C#... được gọi là ngôn ngữ bậc cao. Khi code xong nhấn run thì chương trình chạy trên monitor, tưởng chừng như rất đơn giản nhưng thực chất phải trải qua rất nhiều bước xử lý phức tạp.

Ngoài ra, để viết code thì thường sử dụng các IDE (Arduino IDE, VSCode, PyCharm, Android Studio,...). Các IDE thường sẽ tích hợp 2 thứ:

- Editor: trình soạn thảo văn bản, cung cấp giao diện để viết và chỉnh sửa mã nguồn.
- Compiler: thực hiện chuyển đổi các ngôn ngữ bậc cao sang ngôn ngữ máy (0 và 1) để máy tính có thể hiểu được. Mỗi ngôn ngữ lập trình đều sẽ có một bộ biên dịch khác nhau, ví dụ: trong Arduino IDE thì sử dụng AVR-gcc, C/C++ sử dụng gcc/g++,...

Quá trình biên dịch của gcc sẽ trải qua 4 bước chính:

- Preprocessor
- Compiler
- Assembler
- Linker

![image](https://github.com/user-attachments/assets/a6150e07-e937-45c3-bf4f-0ee195113ff5)

</p>
</details>

<details><summary><b>📚 Compiler process</b></summary>
<p>

<details><summary><b>🔍 1. Quá trình tiền xử lý (Preprocessor)</b></summary>
<p>

- Nhận mã nguồn.
- Xóa bỏ tất cả chú thích, comment trong chương trình.
- Các đoạn mã khi được thêm vào (#include) sẽ được copy vào file .i
- Các định nghĩa (#define) cũng sẽ được copy vào file .i
- Câu lệnh: ``` gcc -E file.c -o file.i ```

💻
File **test.c**
```cpp
#include <stdio.h>

void display(){
    printf("This is file test.c\n");
}
```

File **main.c**
```cpp
#include <stdio.h>
#include "test.c"

// create size array
#define SIZE 20
int array[SIZE];

// create the function
void test(){
    printf("Hello world\n");
}

int SIZE2 = 30;

int main(int argc, char const *argv[]){
    int array2[SIZE2];
    display();
    test();
    return 0;
}
```

📝 Thực hiện câu lệnh để tạo file main.i: ``` gcc -E main.c -o main.i ```

File **main.i**
```cpp
# 1650 "D:/C++/msys64/ucrt64/include/stdio.h" 2 3
# 2 "main.c" 2
# 1 "test.c" 1


# 3 "test.c"
void display(){
    printf("This is file test.c\n");
}
# 3 "main.c" 2

int array[20];

void test(){
    printf("Hello world\n");
}

int SIZE2 = 30;

int main(int argc, char const *argv[])
{
    int array2[SIZE2];
    display();
    test();
    return 0;
}
```
📝 Toàn bộ source của thư viện stdio và file test.c đều được copy vào file main.i

📝 2 comment đều đã bị xóa.

📝 Định nghĩa ``` SIZE ``` cũng được thay thế bằng giá trị 20 -> ``` int array[20] ```

<br>

</p>
</details>

<details><summary><b>🔍 2. Quá trình dịch ngôn ngữ bậc cao sang Assembly (Compiler)</b></summary>
<p>

- Phân tích cú pháp (syntax) sau đó chuyển sang Assembly code – hợp ngữ, là ngôn ngữ bậc thấp gần với tập lệnh của bộ vi xử lý.
- Câu lệnh: ``` gcc -S main.i -o main.s ```

File **main.s**
```cpp
	.file	"main.c"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "This is file test.c\0"
	.text
	.globl	display
	.def	display;	.scl	2;	.type	32;	.endef
	.seh_proc	display
display:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	array
	.bss
	.align 32
...
```

<br>

</p>
</details>

<details><summary><b>🔍 3. Quá trình dịch Assembly sang ngôn ngữ máy (Assembler)</b></summary>
<p>

- Dịch chương trình sang mã máy 0 và 1.
- Một tệp mã máy (.obj) được sinh ra trong hệ thống sau đó.
- Câu lệnh: ``` gcc -c main.s -o main.o ```

File **main.o**
![image](https://github.com/user-attachments/assets/42711a58-af7e-4fd9-aece-795dda6cec99)

📝 Khi code trên VĐK thì đây chính là chương trình sẽ ghi vào bộ nhớ Flash của VĐK. Khi cấp nguồn cho VĐK thì nó sẽ tiến hành khởi tạo các PC, Stack Pointer và copy chương trình này vào bộ nhớ Flash và RAM rồi sau đó mới bắt đầu đi đến từng địa chỉ để thực thi.

<br>

</p>
</details>

<details><summary><b>🔍 4. Quá trình liên kết (Linker)</b></summary>
<p>

- Trong giai đoạn này mã máy của một chương trình dịch từ nhiều nguồn (file .c hoặc file thư viện .lib) được liên kết lại với nhau để tạo thành chương trình đích duy nhất.
- Mã máy của các hàm thư viện gọi trong chương trình cũng được đưa vào chương trình cuối trong giai đoạn này.
- Các lỗi liên quan đến việc gọi hàm hay sử dụng biến tổng thể mà không tồn tại sẽ bị phát hiện. Kể cả lỗi viết chương trình chính không có hàm main() cũng được phát hiện trong liên kết.
- Câu lệnh: ``` gcc main.o -o main ```

<br>

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>✨ Macro</b></summary>
<p>

<details><summary><b>📚 Giới thiệu về Macro</b></summary>
<p>

- Macro là từ dùng để chỉ những thông tin được xử lý ở quá trình tiền xử lý (Preprocessor), được sử dụng để thay thế một đoạn mã trước khi chương trình được biên dịch.
- Macro giúp tạo ra các định nghĩa chung, thường để tránh việc viết lại mã nhiều lần hoặc để làm cho mã dễ bảo trì hơn. 

</p>
</details>

<details><summary><b>📚 Các nhóm chỉ thị Macro</b></summary>
<p>

<details><summary><b>🔍 Chi thị bao hàm tệp (#include)</b></summary>
<p>

- Chỉ thị #include dùng để chèn nội dung của một file khác vào mã nguồn chương trình.
- Tái sử dụng mã nguồn.
- Phân chia chương trình thành các phần nhỏ, giúp quản lý mã nguồn hiệu quả.
- Khi sử dụng **<>** thì preprocessor sẽ thêm nội dung những file.h trong thư mục cài đặt. 
```cpp
#include <stdio.h>
#include <stdlib.h>
```
- Khi sử dụng dấu **""**, bộ tiền xử lý sẽ tìm file name trong thư mục chứa project. Nếu tìm không thấy thì nó sẽ tiếp tục tìm trong các file có sẵn trong thư mục cài đặt.

``` #include "uart.h" ```

<br>

</p>
</details>

<details><summary><b>🔍 Chi thị định nghĩa Macro (#define)</b></summary>
<p>

Chỉ thị #define dùng để thay thế một chuỗi mã nguồn bằng một chuỗi khác trước khi chương trình biên dịch. Nó giúp giảm lặp lại mã, dễ bảo trì chương trình.

💻
File **main.c**
```cpp
#include <stdio.h>

#define CREATE_FUNC(name,cmd)   \
void name(){                    \
    printf(cmd);                \
}

CREATE_FUNC(test1, "this is function test1()\n");
CREATE_FUNC(test2, "this is function test2()\n");
CREATE_FUNC(test3, "this is function test3()\n");

int main(int argc, char const *argv[])
{
    test1();
    test2();
    test3();
    return 0;
}
```
File **main.i**
```cpp
# 8 "main.c"
void test1(){ printf("this is function test1()\n"); };
void test2(){ printf("this is function test2()\n"); };
void test3(){ printf("this is function test3()\n"); };

int main(int argc, char const *argv[])
{
    test1();
    test2();
    test3();
    return 0;
}
```

<br>

💻
```cpp
// Macro
#define sum(a,b) a+b
```
```cpp
// Function
int sum(int a, int b){ 
	return a+b;
}
```
📝 Cả 2 đều cho ra kết quả giống nhau. Vậy câu hỏi đặt ra là:

🤔 Sự khác nhau giữa Macro và Function là gì❓ 

🤔 Khi nào sử dụng Macro? Khi nào sử dụng Function❓ 

<br>

**Sử dụng Function**
```cpp
#include <stdio.h>

int sum(int a, int b){   // 0xc1 - 0xc9
    return a+b;
}

int main(int argc, char const *argv[]){
    int a;         // 0x01              
    int b;         // 0x05
    int c = a+b;   // 0x09
    sum(5,7);       
    return 0;
}
```
📝 Khi sử dụng hàm thì compiler sẽ cấp 1 vùng nhớ cho hàm (giả sử 0xc1 – 0xc9).

📝 Trong hàm main(), PC sẽ đi đến từng địa chỉ: 0x01 -> 0x02 -> 0x03 -> 0x04 ->... -> 0x09. Khi đến hàm sum(), địa chỉ 0x0A sẽ được lưu vào main stack pointer, sau đó PC nhảy đến 0xc1 để thực hiện sum.

📝 Khi thực hiện xong hàm sum() thì sẽ vào main stack pointer và lấy lại địa chỉ 0x0A để PC tiếp tục thực thi từ đó.

<br>

**Sử dụng Macro**
```cpp
#include <stdio.h>

#define sum(a,b) a+b        

int main(int argc, char const *argv[])
{
    int a;         // 0x01              
    int b;         // 0x05
    int c = a+b;   // 0x09
    5+7;           // 0x0A
    5+4;           // 0x0B
    return 0;
}
```
📝 Khi sử dụng Macro thì PC sẽ trỏ đến những địa chỉ liền kề nhau do đó sẽ tốn bộ nhớ để lưu giá trị sau mỗi lần gọi macro nhưng tốc độ xử lý sẽ nhanh hơn khi sử dụng hàm do không cần phải lưu vào main stack pointer.

<br>

<table>
  <tr>
    <th style="text-align: center;">Macro</th>
    <th style="text-align: center;">Function</th>
  </tr>
  <tr>
    <td style="text-align: center;">Tốn nhiều bộ nhớ để lưu chương trình</td>
    <td style="text-align: center;">Không tốn nhiều bộ nhớ trên RAM</td>
  </tr>
  <tr>
    <td style="text-align: center;">Tốc độ xử lý nhanh</td>
    <td style="text-align: center;">Tốc độ xử lý chậm</td>
  </tr>
</table>

<br>

</p>
</details>

<details><summary><b>🔍 Chi thị hủy định nghĩa Macro (#undef)</b></summary>
<p>

Chỉ thị #undef dùng để hủy định nghĩa của một macro đã được định nghĩa trước đó bằng #define.

💻
```cpp
#include <stdio.h>

#define data 30

int main(int argc, char const *argv[])
{
    printf("Data = %d\n", data);

    #undef data

    #define data 50

    printf("Data = %d\n", data);

    return 0;
}
```

<br>

</p>
</details>

<details><summary><b>🔍 Chỉ thị biên dịch có điều kiện (#if, #elif, #else, #ifdef, #ifndef)</b></summary>
<p>

- Chỉ thị #ifdef dùng để kiểm tra một macro đã được định nghĩa hay chưa, nếu macro đã được định nghĩa thì mã nguồn sau #ifdef sẽ được biên dịch.
- Chỉ thị #ifndef dùng để kiểm tra một macro đã được định nghĩa hay chưa, nếu macro chưa được định nghĩa thì mã nguồn sau #ifndef sẽ được biên dịch.

💻
```cpp
#include <stdio.h>

//#define SIZE 30

#ifndef SIZE
#define SIZE 5

int arr[SIZE] = {1,2,3,4,5};

#endif

int main(int argc, char const *argv[])
{

    for (int i=0; i<SIZE; i++){
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    return 0;
}
```

<br>

- Chỉ thị #if sử dụng để bắt đầu một điều kiện tiền xử lý.Nếu điều kiện trong #if là đúng, các dòng mã nguồn sau #if sẽ được biên dịch. Nếu sai, các dòng mã nguồn sẽ bị bỏ qua đến khi gặp #endif.
- Chỉ thị #elif dùng để thêm một điều kiện mới khi điều kiện trước đó trong #if hoặc #elif là sai.
- Chỉ thị #else dùng khi không có điều kiện nào ở trên đúng.

🤔 Muốn build một source để có thể nạp cho nhiều chip, thay vì mỗi con chip viết một source thì mình có thể sử dụng ``` #if, #elif, #else ```

💻
```cpp
#include <stdio.h>

typedef enum{
    LOW,
    HIGH
} Status;

typedef enum{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
} Pin;

#define ESP32      1
#define STM32      2
#define ATmega324  3

#define MCU STM32

int main(int argc, char const *argv[])
{
    while(1){
        #if MCU == STM32
            void digitalWrite(Pin pin, Status state) {
                if (state == HIGH){
                    GPIOA->BSRR = (1 << pin);  // Đặt bit tương ứng để thiết lập chân
                } 
                else {
                    GPIOA->BSRR = (1 << (pin + 16));  // Đặt bit tương ứng để reset chân
                }
            }

        #elif MCU == ESP32
            void digitalWrite(Pin pin, Status state) {
                if (state == HIGH) {
                    GPIO.out_w1ts = (1 << pin);  // Đặt bit tương ứng để thiết lập chân HIGH
                } 
                else {
                    GPIO.out_w1tc = (1 << pin);  // Đặt bit tương ứng để reset chân LOW
                }
            }

        #else
            void digitalWrite(Pin pin, Status state) {
                if (state == HIGH) {
                    PORTA |= (1 << pin);  // Đặt bit tương ứng để thiết lập chân HIGH
                } 
                else {
                    PORTA &= ~(1 << pin);  // Xóa bit tương ứng để reset chân LOW
                }
            }
            
        #endif
    }
    return 0;
}
```

<br>

</p>
</details>

<details><summary><b>🔍 Một số toán tử Macro</b></summary>
<p>

- Sử dụng **##** để nối chuỗi.
- Sử dụng **#** để chuẩn hóa đoạn văn bản lên chuỗi.

💻
File **main.c**
```cpp
#include <stdio.h>

#define CREATE_VAR(name)    \
int    int_##name;          \
char   char_##name;         \
double double_##name     

// ## dùng để nối chuỗi

#define CREATE_STRING(cmd) printf(#cmd)

// # chuẩn hóa đoạn văn bản lên chuỗi

int main(int argc, char const *argv[])
{
    CREATE_VAR(test);  
    CREATE_STRING(abc);
    return 0;
}
```
File **main.i**
```cpp
# 20 "main.c"
int main(int argc, char const *argv[])
{
    int int_test; char char_test; double double_test;
    printf("abc");
    return 0;
}
```

<br>

- Variadic macro: là một dạng macro cho phép nhận một số lượng biến tham số có thể thay đổi.

💻 Tính tổng
```cpp
#define sum(a,b) a+b

#define sum(a,b,c) a+b+c
```
📝 Khi tính tổng 2 số thì dùng ``` sum(a,b) ```

📝 Khi tính tổng 3 số thì dùng ``` sum(a,b,c) ```

🤔 Vậy muốn tính tổng nhiều số thì hàm sum thay đổi thế nào❓ 

➡️Sử dụng variadic macro để giải quyết vấn đề trên.

```cpp
#include <stdio.h>

#define sum(...)                        \
do{                                     \
    int arr[] = {__VA_ARGS__, 0};       \
    int tong = 0;                       \
    int i = 0;                          \
    while (arr[i] != 0) {               \
        tong += arr[i];                 \
        i++;                            \
    }                                   \
    printf("Tong = %d\n", tong);        \
} while (0)

int main(int argc, char const *argv[]) {
    sum(1, 2);                          
    sum(1, 2, 3);                       
    sum(1, 3, 5, 7, 9, 10, 15);        
    return 0;
}
```

📝 Cách trên có thể tính tổng nhiều số nhưng với điều kiện các số đưa vào không được có số 0 chen ở giữa vì khi có số 0 thì việc thực hiện tính toán sẽ dừng lại ngay lập tức.

📝 Có thể khắc phục bằng cách kết hợp cả macro variadic và thư viện STDARG (sẽ nói đến ở bài sau).

<br>

💻 Tạo menu
```cpp
#include <stdio.h>

#define PRINT_MENU_ITEM(number, item) printf("%d. %s\n", number, item)

#define PRINT_MENU(...)                             \
        const char* items[] = {__VA_ARGS__};        \
        int n = sizeof(items) / sizeof(items[0]);   \
        for (int i = 0; i < n; i++) {               \
            PRINT_MENU_ITEM(i + 1, items[i]);       \
        }

#define CASE_OPTION(number, function) case number: function(); break;

#define HANDLE_OPTION(option, ...)              \
    switch (option) {                           \
        __VA_ARGS__                             \
        default: printf("Invalid option!\n");   \
    }

void feature1() { printf("Feature 1 selected\n"); }
void feature2() { printf("Feature 2 selected\n"); }
void feature3() { printf("Feature 3 selected\n"); }
void feature4() { printf("Feature 4 selected\n"); }

int main(int argc, char const *argv[])
{   
    PRINT_MENU("Option 1", "Option 2", "Option 3", "Option 4", "Exit");

    int option;
    scanf("%d", &option);

    HANDLE_OPTION(option, 
        CASE_OPTION(1,feature1)
        CASE_OPTION(2,feature2)
        CASE_OPTION(3,feature3)
        CASE_OPTION(4,feature4)
        )
    return 0;
}
```

<br>

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>✨ Thư viện STDARG</b></summary>
<p>

<details><summary><b>📚 Giới thiệu thư viện stdarg</b></summary>
<p>

- Tương tự với macro variadic.
- Cung cấp các hàm, macros để làm việc với các hàm có số lượng tham số đầu vào không xác định.
- Các hàm như printf, scanf là ví dụ điển hình.

</p>
</details>

<details><summary><b>📚 Các Macro trong thư viện stdarg</b></summary>
<p>

<details><summary><b>🔍 va_list</b></summary>
<p>

Là một kiểu dữ liệu để đại diện cho danh sách các đối số biến đổi.

``` va_list args ```

📝 Bản chất va_list có thể được định nghĩa như sau: ``` typedef char* va_list = "int label, ..." ```

📝 Khi thay thế các số trực tiếp vào ``` ... ```, ví dụ ``` 1, 5, 9 ``` thì trở thành ``` typedef char* va_list = "int count, 1, 5, 9" ```

📝 Địa chỉ: 0x01(i) 0x02(n) 0x03(t) 0x04(c) 0x05(o) 0x06(u) 0x07(n) 0x08(t) 0x09(,) 0x0A(1) 0x0B(,) 0x0C(5) 0x0D(,) 0x0E(9)

📝 args: có thể hiểu là một con trỏ được cấp phát động bộ nhớ để truy cập vào từng ký tự trên

</p>
</details>

<details><summary><b>🔍 va_start</b></summary>
<p>

Bắt đầu một danh sách đối số biến đổi. Nó cần được gọi trước khi truy cập các đối số biến đổi đầu tiên.

``` va_start(args, label) ```

📝 label: chính là tên biến mà ta truyền vào, ví dụ ``` int count ``` thì label là ``` count ```, ``` int a ``` thì label là ``` a ```

📝 ``` va_start ``` thực hiện so sánh chuỗi phía trên với label (so sánh từng ký tự) để tìm kiếm đâu là nơi bắt đầu của những số cần thao tác chính. 

📝 Khi con trỏ ``` args ``` trỏ đến địa chỉ 0x09 (,) thì những số phía sau (1,5,9) sẽ được lưu vào mảng khác: arr[] = {'1', '5', '9'}

</p>
</details>

<details><summary><b>🔍 va_arg</b></summary>
<p>

Truy cập một đối số trong danh sách. Hàm này nhận một đối số của kiểu được xác định bởi tham số thứ hai.

``` va_arg(args, <data_type>) ```

📝 ``` va_arg ``` sẽ truy cập đến từng phần tử trong mảng và thực hiện ép kiểu về kiểu dữ liệu chúng ta muốn (int, double, char*)

📝 Mỗi lần gọi ``` va_arg(args, <data_type>) ``` thì sẽ thực hiện truy cập và lấy ra 1 phần tử trong mảng

</p>
</details>

<details><summary><b>🔍 va_copy</b></summary>
<p>

```cpp
va_list args;
va_list check;
va_copy(check,args);
```

📝 ``` va_copy ``` giúp con trỏ ``` check ``` copy địa chỉ mà con trỏ ``` args ``` đang trỏ đến 

</p>
</details>

<details><summary><b>🔍 va_end</b></summary>
<p>

Kết thúc việc sử dụng danh sách đối số biến đổi. Nó cần được gọi trước khi kết thúc hàm.

``` va_end(args) ```

📝 Thu hồi địa chỉ con trỏ ``` args ```

</p>
</details>

</p>
</details>

<details><summary><b>📚 Ví dụ</b></summary>
<p>

💻 **Tổng ``` n ``` số (Cách 1: chỉ sử dụng thư viện STDARG)**
```cpp
#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...){                                
    va_list args; 
    
    va_start(args, count);

    int result = 0;

    for (int i=0; i<count; i++){
        result += va_arg(args, int);
    }

    va_end(args);   

    return result;
}

int main(int argc, char const *argv[])
{
    printf("Tong = %d\n",sum(7, 1, 2, 3, 4, 5, 10, 15));
    return 0;
}
```

<br>

💻 **Tổng ``` n ``` số (Cách 2: thư viện STDARG kết hợp variadic với ``` số 0 ``` ở cuối để nhận biết kết thúc việc tính tổng)**
```cpp
#include <stdio.h>
#include <stdarg.h>

#define tong(...)   sum(__VA_ARGS__, 0)

int sum(int count,...){
    va_list args;

    va_start(args, count);

    int result = count;
    int value;

    while ((value = va_arg(args, int)) != 0)
    {
        result += value;
    }

    va_end(args);

    return result;
}

int main()
{
    printf("Tong: %d\n", tong(3, 0, -1, 2, 33, 4, 5));
    return 0;
}
```

<br>

💻 **Tổng ``` n ``` số (Cách 3: thư viện STDARG kết hợp variadic với ``` ký tự bất kỳ ``` ở cuối để nhận biết kết thúc việc tính tổng)**
```cpp
#include <stdio.h>
#include <stdarg.h>

#define tong(...)   sum(__VA_ARGS__, '\n')

int sum(int count,...) {
    va_list args;
    va_list check;
    
    va_start(args, count);
    va_copy(check, args);

    int result = count;
    
    while (va_arg(check, char*) != (char*)'\n')
    {
        result += va_arg(args,int);
    }

    va_end(args);

    return result;
}

int main(int argc, char const *argv[])
{
    printf("Tong: %d\n", tong(3, 0, -1, 2, 0, 4, 5));
    return 0;
}
```

<br>

💻
```cpp
#include <stdio.h>
#include <stdarg.h>

typedef struct Data{
    int x;
    double y;
} Data;

void display(int count, ...) {
    va_list args;

    va_start(args, count);

    for (int i = 0; i < count; i++)
    {
        Data tmp = va_arg(args,Data);
        printf("Data.x at %d is: %d\n", i,tmp.x);
        printf("Data.y at %d is: %f\n", i,tmp.y);
    }
   
    va_end(args);
}

int main(int argc, char const *argv[])
{
    display(3, (Data){2,5.0} , (Data){10,57.0}, (Data){29,36.0});
    return 0;
}
```

<br>

💻
```cpp
#include <stdio.h>
#include <stdarg.h>

typedef enum {
    TEMPERATURE_SENSOR,
    PRESSURE_SENSOR
} SensorType;

void processSensorData(SensorType type, ...) {
    va_list args;
    va_start(args, type);

    switch (type){
        case TEMPERATURE_SENSOR:{
            int numArgs  = va_arg(args, int);
            int sensorId = va_arg(args, int);
            double temperature = va_arg(args, double); 

            printf("Temperature Sensor ID: %d, Reading: %.2f degrees\n", sensorId, temperature);
            if (numArgs > 2){
                // Xử lý thêm tham số nếu có
                char *additionalInfo = va_arg(args, char*);
                printf("Additional Info: %s\n", additionalInfo);
            }
            break;
        }
        case PRESSURE_SENSOR:{
            int numArgs = va_arg(args, int);
            int sensorId = va_arg(args, int);
            int pressure = va_arg(args, int);

            printf("Pressure Sensor ID: %d, Reading: %d Pa\n", sensorId, pressure);
            if (numArgs > 2) {
                // Xử lý thêm tham số nếu có
                char *unit = va_arg(args, char*);
                printf("Unit: %s\n", unit);
            }
            break;
        }
    }

    va_end(args);
}

int main(int argc, char const *argv[])
{
    processSensorData(TEMPERATURE_SENSOR, 3, 1, 36.5, "Room Temperature");
    processSensorData(PRESSURE_SENSOR, 4, 2, 101325, 123, "aads");
    return 0;
}
```

<br>

💻
```cpp
#include <stdio.h>
#include <stdarg.h>

typedef enum {
    TURN_ON,
    TURN_OFF,
    SET_LEVEL,
    SEND_MESSAGE
} CommandType;

void sendCommand(CommandType command, ...) {
    va_list args;
    va_start(args, command);

    switch (command) {
        case TURN_ON:
        case TURN_OFF: {
            int deviceID = va_arg(args, int);
            printf("Command: %s Device ID: %d\n", command == TURN_ON ? "Turn On" : "Turn Off", deviceID);
            break;
        }
        case SET_LEVEL: {
            int deviceID = va_arg(args, int);
            int level = va_arg(args, int);
            printf("Set Level of Device ID %d to %d\n", deviceID, level);
            break;
        }
        case SEND_MESSAGE: {
            char* message = va_arg(args, char*);
            printf("Send Message: %s\n", message);
            break;
        }
    }

    va_end(args);
}

int main() {
    sendCommand(TURN_ON, 1);
    sendCommand(TURN_OFF, 5);
    sendCommand(SET_LEVEL, 3, 75);
    sendCommand(SEND_MESSAGE, "Hello World");
    return 0;
}
```
<br>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>✨ Thư viện assert</b></summary>
<p>

- Cung cấp macro assert dùng để kiểm tra một điều kiện.
- Nếu điều kiện đúng thì chương trình tiếp tục thực thi.
- Nếu điều kiện sai thì chương trình dừng lại ngay lập tức và thông báo một thông điệp lỗi.
- Dùng trong debug, dùng ``` #define NDEBUG ``` để tắt debug

💻
```cpp
#include <stdio.h>
#include <assert.h>

#define LOG(condition, cmd) assert(condition && #cmd)

double divide(int a, int b){
    LOG(b != 0, Mau bang 0);
    return (double)a/b;
}

int main(int argc, char const *argv[])
{
    int x = 6;    
    LOG(x==5, X phai bang 5);
    printf("x = %d\n", x);    
    
    printf("kq: %f\n", divide(6,0));
    return 0;
}
```

📝 Có thể thấy rằng khi sử dụng assert để kiểm tra lỗi, nếu có lỗi thì chương trình dừng ngay lập tức và không thực thi tiếp bất kỳ tác vụ nào.

📝 Để hạn chế vấn đề trên thì nên sử dụng TRY, CATCH, THROW (sẽ nói ở bài **Thư viện setjmp**).

<br>

💻
```cpp
#include <stdio.h>
#include <assert.h>

#define ASSERT_IN_RANGE(val, min, max) assert((val) >= (min) && (val) <= (max))

void setLevel(int level) {
    ASSERT_IN_RANGE(level, 1, 10);
    // Thiết lập cấp độ
}
```

<br>

💻
```cpp
#include <assert.h>
#include <stdint.h>

#define ASSERT_SIZE(type, size) assert(sizeof(type) == (size))

void checkTypeSizes() {
    ASSERT_SIZE(int, 4);
    // Kiểm tra các kích thước kiểu dữ liệu khác
}
```

<br>

</p>
</details>

<br>

<details><summary><b>✨ Pointer</b></summary>
<p>

<details><summary><b>📚 Khái niệm về con trỏ</b></summary>
<p>

- Con trỏ (pointer) là một biến chứa địa chỉ của một đối tượng (biến hoặc hàm) khác.
- Việc sử dụng con trỏ giúp thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.

</p>
</details>

<details><summary><b>📚 Kích thước con trỏ</b></summary>
<p>

- Kích thước của con trỏ phụ thuộc vào **kiến trúc vi xử lý** hoặc **kiến trúc máy tính và trình biên dịch**.
- Hệ thống 32-bit, kích thước của con trỏ là 4 byte.
- Hệ thống 64-bit, kích thước của con trỏ là 8 byte.
- SMT32: kiến trúc 32-bit (ARM Cortex-M) nên kích thước con trỏ là 4 byte.
- STM8: kiến trúc 8-bit nên kích thước con trỏ là 1 byte.

🖥️
```cpp
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char const *argv[]){
    printf("%d bytes\n", sizeof(int *));
    printf("%d bytes\n", sizeof(uint8_t *));
    printf("%d bytes\n", sizeof(int16_t *));
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
<br>

</p>
</details>

<details><summary><b>📚 Ứng dụng con trỏ</b></summary>
<p>

**Nhập số từ bàn phím**
```cpp
#include <stdio.h>

void input(int *a, int *b){
    printf("Nhap so 1: "); scanf("%d", a);
    printf("Nhap so 2: "); scanf("%d", b);
}

int main(int argc, char const *argv[])
{
    int a,b;
    input(&a,&b);
    return 0;
}
```

<br>

**Hoán đổi 2 số**
```cpp
#include <stdio.h>

void swap1(int a, int b){
    int temp = a;
    a = b;
    b = temp;
}
// Khi gọi hàm sẽ khởi tạo 2 địa chỉ, gs là 0xc1 và 0xf2 để lưu giá trị a,b
// Thực hiện copy giá trị của biến a,b trong hàm main và đưa vào 2 địa chỉ trên
// a,b ở đây là 2 tham số truyền vào của hàm nên sẽ lưu ở Stack và bị thu hồi vùng nhớ khi kết thúc việc gọi hàm
// Vì vậy, gọi hàm này sẽ không hoán đổi 2 số

void swap2(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
// Khi gọi hàm sẽ truy cập đến 2 địa chỉ 0x01 và 0xb4 để lấy giá trị và thực hiện hoán đổi

int main(int argc, char const *argv[])
{
    int a = 10;	// địa chỉ 0x01
    int b = 20; // địa chỉ 0xb4

    // swap1(a,b);
    swap2(&a,&b);
    printf("value a is: %d\n", a);
    printf("value b is: %d\n", b);
    return 0;
}
```

</p>
</details>

<details><summary><b>📚 Các kiểu con trỏ</b></summary>
<p>

<details><summary><b>🔍 Con trỏ Void (Void Pointer)</b></summary>
<p>
	
- Thường dùng để **trỏ tới bất kỳ địa chỉ** với bất kỳ kiểu dữ liệu của giá trị tại địa chỉ đó.
- Muốn in ra giá trị thì phải sử dụng ép kiểu để đưa con trỏ void về đến kiểu dữ liệu của giá trị đó.
- Cú pháp: ``` void *ptr_void; ```

🖥️
```cpp 
#include <stdio.h>

void sum(int a, int b){
    printf("%d + %d = %d\n", a, b, a+b);
}

int main(int argc, char const *argv[])
{
    void *ptr_void;
    ptr_void = (void*)sum;
    ((void (*)(int,int))ptr_void)(9,3);

    int var_int = 10;
    ptr_void = &var_int;
    printf("Dia chi: %p, int: %d\n", ptr_void, *(int*)ptr_void);

    double var_double = 3.14;
    ptr_void = &var_double;
    printf("Dia chi: %p, double: %.3f\n", ptr_void, *(double*)ptr_void);

    char var_char = 'A';
    ptr_void = &var_char;
    printf("Dia chi: %p, char: %c\n", ptr_void, *(char*)ptr_void);

    char arr[] = "hello";
    ptr_void = arr;

    // printf("chuoi: %c\n", *(char*)(ptr_void+1));
    
    printf("Chuoi: ");
    for (int i=0; i<(sizeof(arr)/sizeof(arr[0])); i++){
        printf("%c\n", *(char*)(ptr_void+i));
    }
    printf("\n");

    void *ptr[] = {&var_int, &var_double, &var_char, sum, arr};
    printf("ptr[0] = %d\n", *(int*)ptr[0]);
    printf("ptr[1] = %f\n", *(double*)ptr[1]);
    printf("ptr[2] = %c\n", *(char*)ptr[2]);

    ((void (*)(int,int))ptr[3])(9,3);

    for (int i=0; i<(sizeof(arr)/sizeof(arr[0])); i++){
        printf("%c", *(char*)(ptr[4]+i));
    }
    return 0;
}

```
```cpp
9 + 3 = 12
Dia chi: 00000075E7BFF70C, int: 10
Dia chi: 00000075E7BFF700, double: 3.140   
Dia chi: 00000075E7BFF6FF, char: A
Chuoi:
h
e
l
l
o

ptr[0] = 10
ptr[1] = 3.140000
ptr[2] = A
9 + 3 = 12
hello
```
</p>
</details>

<details><summary><b>🔍 Con trỏ hàm (Function Pointer)</b></summary>
<p>
	
- Con trỏ hàm là một biến mà **giữ địa chỉ của hàm**.
- Cần chỉ định kiểu dữ liệu của hàm mà con trỏ đó sẽ tham chiếu đến khi khai báo, bao gồm kiểu trả về và các tham số của hàm. Sau đó, ta có thể gán con trỏ hàm này cho một hàm cụ thể.
- Khi gọi con trỏ hàm, chương trình sẽ thực thi hàm mà con trỏ đang tham chiếu đến.
- Cú pháp:
```cpp
<return_type> (* func_pointer)(input_1_data type, input_2_data type,....);

int (*ptr)(int,double);

void (*array[])(int,int);
```

🖥️
```cpp
#include <stdio.h>
// Hàm mẫu 1
void greetEnglish(){
    printf("Hello!\n");
}

// Hàm mẫu 2
void greetFrench(){
    printf("Bonjour!\n");
}

int main(){
    // Khai báo con trỏ hàm
    void (*ptrToGreet)();
    
    // Gán địa chỉ của hàm greetEnglish cho con trỏ hàm
    ptrToGreet = greetEnglish;
    
    // Gọi hàm thông qua con trỏ hàm
    ptrToGreet();  // In ra: Hello!

    // Gán địa chỉ của hàm greetFrench cho con trỏ hàm
    ptrToGreet = greetFrench;
    
    // Gọi hàm thông qua con trỏ hàm
    (*ptrToGreet)();  // In ra: Bonjour!    
    
    return 0;
}
```
```cpp
Hello!
Bonjour!
```

<br>

🖥️
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
    printf("%d / %d = %0.3f\n", a, b, a/(double)b);
}

int main(int argc, char const *argv[])
{
    int a = 10, b = 20;

    // cách 1
    void (*ptr)(int,int);
    ptr = tong;
    ptr(a,b);

    ptr = hieu;
    ptr(a,b);

    ptr = tich;
    ptr(a,b);

    ptr = thuong;
    ptr(a,b);
    printf("\n");


    // cách 2
    tinhtoan(tong,a,b);
    tinhtoan(hieu,a,b);
    tinhtoan(tich,a,b);
    tinhtoan(thuong,a,b);
    printf("\n");


    // cách 3
    void (*calculate[])(int,int) = {tong, hieu, tich, thuong};
    calculate[0](a,b);
    calculate[1](a,b);
    calculate[2](a,b);
    calculate[3](a,b);
    return 0;
}

void tinhtoan(void (*pheptoan)(int,int), int a, int b){
    pheptoan(a,b);
}
```
```cpp
10 + 20 = 30
10 - 20 = -10
10 x 20 = 200
10 / 20 = 0.500

10 + 20 = 30
10 - 20 = -10
10 x 20 = 200
10 / 20 = 0.500

10 + 20 = 30
10 - 20 = -10
10 x 20 = 200
10 / 20 = 0.500
```
</p>
</details>

<details><summary><b>🔍 Con trỏ hằng (Pointer to constant)</b></summary>
<p

- Con trỏ hằng là một cách định nghĩa một con trỏ **chỉ có thể đọc giá trị tại địa chỉ mà nó trỏ đến (Read Only)** nhưng không thể thay đổi được giá trị đó.
- Đối với biến là hằng số thì phải luôn dùng con trỏ hằng khi trỏ đến.
- Cú pháp: 
```cpp
<data_type> const *ptr_const;
const <data_type> *ptr_const;
```

🖥️
```cpp
#include <stdio.h>

int value1 = 10;
int value2 = 3;
const int *ptr_const = &value1;

int main(int argc, char const *argv[])
{
    printf("%p\n", ptr_const);
    printf("%d\n", *ptr_const);

    value1 = 5;
    printf("%p\n", ptr_const);
    printf("%d\n", *ptr_const);

    //*ptr_const = 5;       // wrong
    ptr_const = &value2; // right
    printf("%p\n", ptr_const);
    printf("%d\n", *ptr_const);
    return 0;
}

```
📝 Kết quả sau khi chạy sẽ gặp lỗi: ```assignment of read-only location '*ptr_const'```

</p>
</details>

<details><summary><b>🔍 Hằng con trỏ (Constant to Pointer)</b></summary>
<p
    
- Hằng con trỏ là một con trỏ mà **trỏ đến 1 địa chỉ cố định**, nghĩa là khi con trỏ này được khởi tạo thì nó sẽ không thể trỏ tới địa chỉ khác.
- Cú pháp: ``` int *const const_ptr = &value; ```

💻
```cpp
#include <stdio.h>

int value1 = 10;
int value2 = 20;
int *const const_ptr = &value1;

int main(int argc, char const *argv[]){
    printf("%p\n", const_ptr);
    printf("%d\n", *const_ptr);

    *const_ptr = 5;
    printf("%p\n", const_ptr);
    printf("%d\n", *const_ptr);
    
    // const_ptr = &value2; // wrong
    // printf("%p\n", const_ptr);
    return 0;
}

```
📝 Kết quả sau khi chạy sẽ gặp lỗi: ```assignment of read-only variable 'const_ptr'```

</p>
</details>

<details><summary><b>🔍 Con trỏ NULL (Null Pointer)</b></summary>
<p
    
- Khi khai báo con trỏ mà chưa sử dụng ngay hoặc sử dụng xong thì phải gán NULL.

💻
```cpp
int *ptr_null = NULL;
//  ptr_null = 0x00: địa chỉ khởi tạo
// *ptr_null = 0   : giá trị tại địa chỉ khởi tạo
```
</p>
</details>

<details><summary><b>🔍 Pointer to pointer</b></summary>
<p
    
- Là một kiểu dữ liệu trong ngôn ngữ lập trình cho phép bạn lưu trữ địa chỉ của một con trỏ.
- Con trỏ đến con trỏ cung cấp một cấp bậc trỏ mới, cho phép bạn thay đổi giá trị của con trỏ gốc.
- Cấp bậc này có thể hữu ích trong nhiều tình huống, đặc biệt là khi bạn làm việc với các hàm cần thay đổi giá trị của con trỏ.

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>✨ Các biến đặc biệt</b></summary>
<p>

<details><summary><b>📚 Extern</b></summary>
<p>

<details><summary><b>🔍 Khái niệm</b></summary>
<p>

- **extern** có thể sử dụng cho một đối tượng (biến hoặc hàm), nếu là **biến** thì phải được **khai báo toàn cục** với mục đích là thông báo rằng biến hoặc hàm này đã được định nghĩa ở một nơi khác trong chương trình hoặc trong 1 file nguồn khác.
- **extern** cho phép các file nguồn khác nhau trong cùng một chương trình chia sẽ và sử dụng các biến và hàm mà không cần định nghĩa lại.
- **extern** chỉ cho phép khai báo chứ không định nghĩa.
- Cú pháp: ``` extern <data_type> <name_variable>; ```

💻

File **File1.c**
```cpp
#include <stdio.h>

int a = 10;

void display1(){ printf("This is file1.c\n"); }
```

File **File2.c**
```cpp
#include <stdio.h>

int b = 10;

void display2(){ printf("This is file2.c\n"); }
```

File **main.c**
```cpp
#include <stdio.h>
#include "File1.c"
#include "File2.c"

int main(int argc, char const *argv[])
{
    a = 20;
    printf("a = %d\n",a);

    b = 50;
    printf("b = %d\n",b);

    display1();
    display2();
    return 0;
}

``` 

📝 Muốn gọi đối tượng khác (biến hoặc hàm) đã được khai báo trong file khác thì sử dụng #include.

🤔 Vậy nếu có nhiều file hơn trong project thì làm sao❓

➡️ Có thể #include tất cả file vào.

➡️ Tuy nhiên, nếu không nhớ biến hoặc hàm nằm ở file nào thì việc làm trên thì vừa mất thời gian vừa tốn bộ nhớ để khởi tạo một số hàm hoặc biến không cần thiết.

➡️ Sử dụng **extern** và thực hiện liên kết các file.

💻 

File **main.c**
```cpp
#include <stdio.h>

extern int a;
extern int b;

extern void display1();
extern void display2();

int main(int argc, char const *argv[])
{
    a = 20;
    printf("a = %d\n",a);

    b = 50;
    printf("b = %d\n",b);

    display1();
    display2();
    return 0;
}
```

📝 Thực hiện liên kết file: ``` gcc main.c File1.c File2.c -o main ```

📝 Lệnh trên sẽ tự động:

- Thực hiện tiền xử lý (-E).
- Tạo mã assembly (-S).
- Tạo object file (-o).
- Liên kết tất cả các file main.o, File1.o, File2.o để tạo ra file thực thi main.

</p>
</details>

<details><summary><b>🔍 Ứng dụng</b></summary>
<p>

- Thiết kế thư viện.
- Chia sẻ biến và hàm giữa các file nguồn hoặc giữa các module và thư viện.
- Sử dụng một hàm trước khi nó được định nghĩa trong mã nguồn.
- Chia sẻ hằng số giữa các file nguồn.

💻

File **File1.h**
```cpp
#ifndef _FILE1_H
#define _FILE1_H

extern int a;

void display1();

#endif
```

File **File1.c**
```cpp
#include <stdio.h>
#include "File1.h"

int a = 10;

void display1(){
    printf("This is file1.c\n");
}
```

File **File2.h**
```cpp
#ifndef _FILE2_H
#define _FILE2_H

extern int b;

void display2();

#endif
File **File2.c**
#include <stdio.h>
#include "File2.h"

int b = 10;

void display2(){
    printf("This is file2.c\n");
}
```

File **main.c**
```cpp
#include <stdio.h>
#include "File1.h"
#include "File2.h"

extern void display1();
extern void display2();

int main(int argc, char const *argv[])
{
    a = 20;
    printf("a = %d\n",a);

    b = 50;
    printf("b = %d\n",b);

    display1();
    display2();
    return 0;
}
```

📝 Có thể không cần sử dụng extern đối với các hàm vì khi liên kết các file rồi thì có thể gọi thoải mái các hàm nằm ở những file khác nhau.

<br>

</p>
</details>

</p>
</details>

<details><summary><b>📚 Static</b></summary>
<p>

<details><summary><b>🔍 Cú pháp</b></summary>
<p>

```cpp
static <data_type> <name_variable>;
static <data_type> <name_function>;
```

</p>
</details>

<details><summary><b>🔍 Static local</b></summary>
<p>
	
Khi 1 biến cục bộ được khai báo với từ khóa static:

- Biến chỉ được khởi tạo một lần, nghĩa là địa chỉ của nó sẽ tồn tại xuyên suốt chương trình.
- Giữ phạm vi của biến chỉ trong hàm đó.
- Giữ giá trị của biến qua các lần gọi hàm.

Biến cục bộ static chỉ có thể được gọi trong nội bộ hàm khởi tạo ra nó. Mỗi lần hàm được gọi, giá trị của biến chính bằng giá trị tại lần gần nhất hàm được gọi.

💻
```cpp
#include <stdio.h>

void count(){
    int a = 5;
    a++;
    printf("a = %d\n",a);
}

int main(int argc, char const *argv[])
{
    count();
    count();
    count();
    return 0;
}
```

Kết quả in ra:
```cpp
a = 6
a = 6
a = 6
```

📝 Kết quả 3 lần gọi hàm đều giống nhau vì biến ``` a ``` biến cục bộ, sẽ được lưu trong Stack và địa chỉ sẽ bị thu hồi sau khi hàm thực thi xong.

🤔 Vậy muốn giữ giá trị của biến sau nhiều lần gọi hàm thì làm sao❓

➡️ Thêm từ khóa **static** khi khai báo biến.

💻
```cpp
#include <stdio.h>

void count(){
    static int a = 5;
    a++;
    printf("a = %d\n",a);
}

int main(int argc, char const *argv[])
{
    count();
    count();
    count();
    return 0;
}
```

Kết quả in ra:
```cpp
a = 6
a = 7
a = 8
```

📝 Khi thêm ``` static ```, ở lần gọi hàm đầu tiên, biến ``` a ``` sẽ được cấp phát địa chỉ, giả sử 0x01 và địa chỉ tồn tại cho đến hết chương trình.

📝 Khi gọi hàm từ lần 2 trở đi, nó sẽ không thực thi câu lệnh ``` static int a = 5 ``` vì địa chỉ biến a đã được cấp phát trước đó mà sẽ bắt đầu thực thi từ câu lệnh tiếp theo (``` a++ ```).

🤔 Làm thế nào thay đổi giá trị của biến cục bộ ``` a ``` từ bên ngoài❓

➡️ Rất đơn giản, sử dụng con trỏ.
 
💻
```cpp
#include <stdio.h>

int *ptr = NULL;

void count(){
    static int a = 5;
    ptr = &a;
    a++;
    printf("a = %d\n",a);
}

int main(int argc, char const *argv[]){
    count();     // in ra "a = 6"
    count();     // in ra "a = 7"
    count();     // in ra "a = 8"

    *ptr = 99;  // truy cập địa chỉ 0x01 và thay đổi giá trị biến a thành 99
    count();     // in ra "a = 100"
    ptr = NULL;
    return 0;
}
```

</p>
</details>

<details><summary><b>🔍 Static global</b></summary>
<p>

Khi **'static'** được sử dụng với các biến toàn cục, nó sẽ hạn chế phạm vi của biến chỉ có thể gọi trong file nguồn hiện tại.

💻

File **file1.h**
```cpp
#ifndef _FILE1_H
#define _FILE1_H

static int a;

static void display();

void test();

#endif
```

File **file1.c**
```cpp
#include <stdio.h>
#include "file1.h"

static int a = 10;

static void display(){
    printf("This is file1.c\n");
}

void test(){
    printf("Hello world\n");
}
```

File **main.c**
```cpp
#include <stdio.h>

extern int a;
extern void display();
extern void test();

int main(int argc, char const *argv[])
{
    printf("a = %d\n",a);
    display();
    test();
    return 0;
}

```

📝 Kết quả sau khi chạy: 
```cpp
undefined reference to `display'
undefined reference to `a'
```

📝 Dễ thấy file main.c khi chạy sẽ gặp lỗi do cố gắng sử dụng extern để gọi 1 biến toàn cục hoặc hàm đã được khai báo với static trong 1 file nguồn khác.

<br>

</p>
</details>

<details><summary><b>🔍 Ứng dụng</b></summary>
<p>

- Thiết kế thư viện.
- Quản lý tài nguyên bộ nhớ tốt hơn và tránh xung đột tên biến giữa các module khác nhau.
- Khi khai báo biến toàn cục với static trong một file C, biến chỉ có thể truy cập trong file đó, ngăn ngừa các vấn đề chia sẻ biến không mong muốn giữa các file.
- Dùng cho biến cục bộ trong một hàm để giữ lại giá trị của biến giữa các lần gọi hàm (persistence).

<br>

</p>
</details>

</p>
</details>

<details><summary><b>📚 Volatile</b></summary>
<p>

- **volatile** báo cho compiler biết rằng biến này **có thể sẽ được thay đổi ở bởi yếu tố bên ngoài chương trình** như hardward (ngắt, nhấn button,…) hoặc một luồng khác.
- **volatile** ngăn chặn compiler tối ưu hóa hoặc xóa bỏ các thao tác trên biến đó, giữ cho các thao tác trên biến được thực hiện như đã được định nghĩa.
- Cú pháp: ``` volatile <data_type> <name_variable>; ```

🤔 Một biến cần được khai báo dưới dạng biến volatile khi nào❓

➡️ Khi giá trị của nó có thể thay đổi một cách không báo trước. Việc khai báo biến volatile là rất cần thiết để tránh những lỗi sai khó phát hiện do tính năng optimization của compiler.

Biến Volatile rất cần thiết trong lập trình nhúng, vì khi đó có các tác vụ như ngắt ảnh hưởng tới giá trị của biến. Trong lập trình C cơ bản thì rất ít gặp.

💻
```cpp
#include "stm32f4xx.h"                  // Device header

uint8_t *addr = (uint8_t*)0x20000000;
volatile uint8_t var = 0;
int main(){
	
	while (1){
		var = *addr;
		if (var != 0){
			break;
		}
	}
}
```
📝 Khi khai báo biến ``` var ``` mà không có từ khóa ``` volatile ```, nếu giá trị của biến không thay đổi hoặc thay đổi ngay lần đầu chạy debug (thông qua thay đổi giá trị tại địa chỉ 0x20000000) thì compiler sẽ tối ưu hóa biến này khi nhận thấy biến này không có sự thay đổi giá trị ở những lần chạy kế tiếp.

📝 Khi khai báo biến ``` var ``` có từ khóa ``` volatile ```, trong quá trình chạy, nếu giá trị biến thay đổi đột ngột thì chương trình vẫn cập nhật vì compiler chưa tối ưu hóa biến này.

<br>

</p>
</details>

<details><summary><b>📚 Register</b></summary>
<p>

📝 Trong kiến trúc của vi xử lý thì ALU (Arithmetic Logic Unit) đóng vai trò xử lý các tính toán số học và nó chỉ làm việc với các dự liệu được lưu trữ trong thanh ghi (Register).

📝 Khi khai báo các biến trong chương trình thì những biến này được lưu ở RAM. Nếu có thêm phép tính (``` ++ ``` hoặc ``` -- ```) thì nó chỉ lưu thông tin của phép tính này chứ chưa thực hiện.

![image](https://github.com/user-attachments/assets/a57d1e72-86f1-405d-853c-660e459a37f0)

📝 Giai đoạn 1: Nạp giá trị từ RAM vào Register

📝 Giai đoạn 2: Đưa dữ liệu từ Register sang ALU để bắt đầu xử lý.

📝 Giai đoạn 3: Khi ALU xử lý xong thì trả ngược dữ liệu về Register.

📝 Giai đoạn 4: Trả giá trị vừa xử lý từ Register về lại vùng nhớ RAM.

- **register** được sử dụng để định nghĩa các biến cục bộ mà nên được lưu giữ trong một thanh ghi thay vì RAM.
- **register** làm tăng hiệu năng (performance) của chương trình.
- Cú pháp: ``` register <data_type> <name_variable>; ```

💻
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

📝 Khi chưa register ```Thoi gian chay cua chuong trinh: 0.005 giay```

📝 Khi có register ```Thoi gian chay cua chuong trinh: 0.001 giay```

</p>
</details>

</p>
</details>

<br>

<details><summary><b>✨ goto - thư viện setjmp</b></summary>
<p>

<details><summary><b>📚 goto trong C</b></summary>
<p>

<details><summary><b>🔍 Khái niệm</b></summary>
<p>

- Từ khóa **"goto"** cho phép chương trình nhảy đến một label đã được đặt trước đó cùng một hàm.
- "goto" cung cấp khả năng kiểm soát luồng hoạt động của mã nguồn, nhưng việc sử dụng goto thường được xem là không tốt vì nó có thể làm cho mã nguồn trở nên khó đọc và khó bảo trì.

💻
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
📝 Trong ví dụ này, goto được sử dụng để tạo một vòng lặp đơn giản. Khi i đạt đến giá trị 5, control sẽ chuyển đến nhãn "end" và kết thúc chương trình.

</p>
</details>

<details><summary><b>🔍 Ứng dụng</b></summary>
<p>

**Thoát khỏi vòng lặp nhiều cấp độ**

Trong một số trường hợp, việc thoát khỏi nhiều cấp độ vòng lặp có thể trở nên phức tạp nếu sử dụng cấu trúc kiểm soát vòng lặp thông thường. Trong tình huống như vậy, goto có thể được sử dụng để dễ dàng thoát khỏi nhiều cấp độ vòng lặp.

💻
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

**Xử lý lỗi và giải phóng bộ nhớ**

Trong trường hợp xử lý lỗi, có thể sử dụng goto để dễ dàng giải phóng bộ nhớ đã được cấp phát trước khi thoát khỏi hàm.

💻
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

**Thực hiện Finite State Machine**
Trong một số trường hợp, đặc biệt là khi triển khai Finite State Machines, goto có thể được sử dụng để chuyển đến các trạng thái khác nhau một cách dễ dàng.

💻
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

<br>

</p>
</details>

</p>
</details>

<details><summary><b>📚 Thư viện setjmp</b></summary>
<p>

<details><summary><b>🔍 Hàm setjmp</b></summary>
<p>

- setjmp lưu trạng thái hiện tại của môi trường thực thi vào một biến kiểu jmp_buf.
- setjmp thường được sử dụng để thiết lập một điểm quay lại (checkpoint) trong chương trình.
- setjmp trả về giá trị 0 khi được gọi lần đầu tiên và giá trị khác 0 khi quay lại từ longjmp.

```setjmp(jmp_buf buf);```

</p>
</details>

<details><summary><b>🔍 Hàm longjmp</b></summary>
<p>

- longjmp là hàm dùng để nhảy trở lại vị trí đã lưu bởi setjmp và tiếp tục thực thi chương trình từ đó.

```cpp
void longjmp(jmp_buf buf, int value);
// buf  : biến 'jmp_buf' đã được lưu bởi 'setjmp'
// value: giá trị trả về từ 'setjmp'. Nếu value=0 thì 'setjmp' trả về 1
```

💻
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

</p>
</details>

<details><summary><b>🔍 Xử lý ngoại lệ</b></summary>
<p>

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

<br>

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>✨ Bitmask</b></summary>
<p>

<details><summary><b>📚 Khái niệm</b></summary>
<p>

- Bitmask là một kỹ thuật sử dụng các bit để lưu trữ và thao tác với các cờ (flags) hoặc trạng thái.
- Có thể sử dụng bitmask để đặt, xóa, kiểm tra trạng thái của các bit cụ thể trong 1 word.
- Bitmask thường được sử dụng để tối ưu hóa bộ nhớ, thực hiện các phép toán logic trên một cụm bit, và quản lý các trạng thái, quyền truy cập, hoặc các thuộc tính khác của một đối tượng.

<br>

</p>
</details>

<details><summary><b>📚 Các toán tử bitwise</b></summary>
<p>

![image](https://github.com/user-attachments/assets/e9b5fc2e-0d94-4708-bbe1-740f7a21d417)

![image](https://github.com/user-attachments/assets/c8549e26-9a0b-4835-a886-d11a6bed9fb1)

<br>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>✨ Struct - Union</b></summary>
<p>

<details><summary><b>📚 Struct</b></summary>
<p>

<details><summary><b>🔍 Cơ bản về Struct</b></summary>
<p>
	
- struct là một cấu trúc dữ liệu cho phép tự định nghĩa một kiểu dữ liệu mới bằng cách nhóm các biến có các kiểu dữ liệu khác nhau lại với nhau.
- struct cho phép tạo ra một thực thể dữ liệu lớn hơn và có tổ chức hơn từ các thành viên (members) của nó.
- Cú pháp:

**Cách 1**
```cpp
struct structureName{       struct student_t{       struct student_t sv1;
    dataType1 member1;          char ten[30];       struct student_t sv2;
    dataType2 member2;          int tuoi;           ...
    ...                         int MSSV;           hoặc
};                          };                      struct student_t sv[50];
```

**Cách 2**
```cpp
typedef struct{             typedef struct{         student_t sv1;
    dataType1 member1;          char ten[30];       student_t sv2;
    dataType2 member2;          int tuoi;           ...
    ...                         int MSSV;           student_t sv[20];
}structureName;             }student_t;
```

- Địa chỉ của struct chính là địa chỉ của member đầu tiên.

- Truy xuất dữ liệu:

◆ Sử dụng "." để truy xuất tới thành viên khi khai báo biến bình thường (int, char,…).

◆ Sử dụng "->" để truy xuất tới thành viên khi khai báo biến là con trỏ.

<br>

</p>
</details>

<details><summary><b>🔍 Data Structure Alignment</b></summary>
<p>

Data alignment là quá trình sắp xếp các member của một struct sao cho mỗi member nằm ở địa chỉ phù hợp với yêu cầu căn chỉnh của nó. Điều này giúp CPU truy xuất dữ liệu nhanh hơn và tránh các lỗi tiềm ẩn khi truy cập bộ nhớ.

Bộ xử lý thường yêu cầu các thành phần dữ liệu nằm trên địa chỉ được căn chỉnh theo bội số của kích thước phần tử đó. Ví dụ:

- double (8 byte): thường yêu cầu được căn chỉnh trên địa chỉ chia hết cho 8 (0x00, 0x08, 0x10,...)
- int, int32_t, uint32_t (4 byte): thường yêu cầu được căn chỉnh trên địa chỉ chia hết cho 4 (0x00, 0x04, 0x08,...).
- float, uint16_t (2 byte): thường yêu cầu được căn chỉnh trên địa chỉ chia hết cho 2 (0x00, 0x02, 0x04,...).
- char, uint8_t (1 byte): không yêu cầu căn chỉnh đặc biệt

<br>

</p>
</details>

<details><summary><b>🔍 Data Padding</b></summary>
<p>

Để đảm bảo rằng mỗi thành phần của struct tuân thủ yêu cầu căn chỉnh, trình biên dịch có thể thêm padding (phần đệm) giữa các thành phần của struct. Đây là các byte trống, không chứa dữ liệu, được thêm vào để đảm bảo mỗi biến được căn chỉnh đúng.

<br>

</p>
</details>

<details><summary><b>🔍 Kích thước của struct</b></summary>
<p>

Kích thước Struct bằng tổng các kích thước của các member và padding (nếu có).

💻
```cpp
#include <stdio.h>
#include <stdint.h>

typedef struct{
    uint32_t var1;  // 4 byte
    uint8_t  var2;  // 1 byte
    uint16_t var3;  // 2 byte
} frame;

int main(int argc, char const *argv[])
{
    printf("Size of frame: %d\n", sizeof(frame));

    frame frame;
    printf("Address of var1: %p\n", &frame.var1);
    printf("Address of var2: %p\n", &frame.var2);
    printf("Address of var3: %p\n", &frame.var3);
    return 0;
}
```

**Kết quả:**
```cpp
Size of frame: 8
Address of var1: 00000048F3DFF6D8
Address of var2: 00000048F3DFF6DC
Address of var3: 00000048F3DFF6DE
```

**Giải thích:**

![image](https://github.com/user-attachments/assets/0f6e0cdf-c716-41f1-a3db-fa700344513b)

📝 Lần 1 quét 4 bytes và var1 sử dụng.

📝 Lần 2 quét 4 bytes, var2 chỉ sử dụng 1 byte, thừa 3 bytes bộ nhớ đệm.	

📝 var3 sử dụng 2 bytes (dựa vào căn chỉnh) trong 3 bytes trên và còn thừa 1 byte bộ nhớ đệm.

📝 Tổng kích thước struct frame trên là 8 bytes nhưng thực tế chỉ sử dụng 7 bytes.

<br>

💻
```cpp
#include <stdio.h>
#include <stdint.h>

typedef struct{
    uint8_t  var1;  // 1 byte
    uint32_t var2;  // 4 byte
    uint16_t var3;  // 2 byte
} frame;

int main(int argc, char const *argv[])
{
    printf("Size of frame: %d\n", sizeof(frame));

    frame frame;
    printf("Address of var1: %p\n", &frame.var1);
    printf("Address of var2: %p\n", &frame.var2);
    printf("Address of var3: %p\n", &frame.var3);
    return 0;
}
```

**Kết quả:**
```cpp
Size of frame: 8
Address of var1: 00000048F3DFF6D8
Address of var2: 00000048F3DFF6DC
Address of var3: 00000048F3DFF6DE
```

**Giải thích:**

![image](https://github.com/user-attachments/assets/0b61bf95-9f0a-406c-8ad5-0263c7f55ad8)

📝 Lần 1 quét 4 bytes và var1 sử dụng 1 byte trong 4 byte, thừa 3 byte.

📝 Lần 2 quét 4 bytes, var2 sử dụng hết.

📝 Lần 3 quét 4 bytes, var3 sử dụng 2 trong 4 bytes và thừa 2 byte.

📝 Tổng kích thước struct frame trên là 12 bytes nhưng thực tế chỉ sử dụng 7 bytes.

<br>

💻
```cpp
#include <stdio.h>
#include <stdint.h>

typedef struct{
    uint8_t  var1[9];   // 1 byte
    uint32_t var2[2];   // 4 byte
    uint16_t var3[10];  // 2 byte
} frame;

int main(int argc, char const *argv[])
{
    printf("Size of frame: %d\n", sizeof(frame));

    frame frame;

    for (int i=0; i<9; i++){
        printf("Address of var1[%d]: %p\n", i, &frame.var1[i]);
    }

    printf("\n");

    for (int i=0; i<2; i++){
        printf("Address of var2[%d]: %p\n", i, &frame.var2[i]);
    }

    printf("\n");

    for (int i=0; i<10; i++){
        printf("Address of var3[%d]: %p\n", i, &frame.var3[i]);
    }    
    
    return 0;
}
```

**Kết quả:**
```cpp
Size of frame: 40
Address of var1[0]: 0000006003DFFC80
Address of var1[1]: 0000006003DFFC81
Address of var1[2]: 0000006003DFFC82
Address of var1[3]: 0000006003DFFC83
Address of var1[4]: 0000006003DFFC84
Address of var1[5]: 0000006003DFFC85
Address of var1[6]: 0000006003DFFC86
Address of var1[7]: 0000006003DFFC87
Address of var1[8]: 0000006003DFFC88

Address of var2[0]: 0000006003DFFC8C
Address of var2[1]: 0000006003DFFC90

Address of var3[0]: 0000006003DFFC94
Address of var3[1]: 0000006003DFFC96
Address of var3[2]: 0000006003DFFC98
Address of var3[3]: 0000006003DFFC9A
Address of var3[4]: 0000006003DFFC9C
Address of var3[5]: 0000006003DFFC9E
Address of var3[6]: 0000006003DFFCA0
Address of var3[7]: 0000006003DFFCA2
Address of var3[8]: 0000006003DFFCA4
Address of var3[9]: 0000006003DFFCA6
```

**Giải thích:**

![image](https://github.com/user-attachments/assets/af1f44b2-c870-4fd1-a125-7b76f0ffcbb7)

<br>

💻
```cpp
#include <stdio.h>
#include <stdint.h>

typedef struct{
    uint8_t  var1[9];   // 1 byte   8 + 2 + 6 padding
    uint64_t var2[3];   // 8 byte   24
    uint16_t var3[10];  // 2 byte   8 + 8 + 4 + 4 padding
    uint32_t var4[2];   // 4 byte   8
} frame;

int main(int argc, char const *argv[])
{
    printf("Size of frame: %d\n", sizeof(frame));   
    return 0;
}
```

**Kết quả:** ```72 byte```

<br>

</p>
</details>

</p>
</details>

<details><summary><b>📚 Union</b></summary>
<p>

<details><summary><b>🔍 Cơ bản về Union</b></summary>
<p>

- Union là một cấu trúc dữ liệu giúp kết hợp nhiều kiểu dữ liệu khác nhau vào một cùng một vùng nhớ.
- Mục đích chính của union là tiết kiệm bộ nhớ bằng cách chia sẻ cùng một vùng nhớ cho các thành viên của nó. Điều này có nghĩa là, trong một thời điểm, chỉ một thành viên của union có thể được sử dụng.
- Cú pháp:

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

<br>

</p>
</details>

<details><summary><b>🔍 Kích thước Union</b></summary>
<p>

Kích thước của Union chính là tổng của kích thước của member có kích thước lớn nhất và padding (nếu có).

💻
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
    printf("Size = %d\n",sizeof(frame));
    return 0;
}
```
Kết quả: ```4 byte```

<br>

💻
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
    printf("Size = %d\n",sizeof(frame));
    return 0;
}
```
**Kết quả:** ```24 byte```

<br>

</p>
</details>

<details><summary><b>🔍 Sử dụng vùng nhớ trong Union</b></summary>
<p>

💻
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
**Kết quả**
```cpp
Data.var1 = 7
Data.var2 = 7
Data.var3 = 7
```

**Giải thích**

📝 Khi gán 5 cho member var1 thì tại địa chỉ 0x5FFE9C sẽ có giá trị 5.

📝 Khi gán 6 cho member var2, do các member sử dụng chung vùng nhớ nên tại địa chỉ 0x5FFE9C thì giá trị 6 sẽ ghi đè lên 5.

📝 Tương tự với member var3, giá trị cuối cùng tại địa chỉ 0x5FFE9C là 7 nên giá trị của các member đều sẽ là 7.

<br>

💻
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
**Kết quả:**
```cpp
Data.var1 = 250
Data.var2 = 4294967290
Data.var3 = 65530
```

**Giải thích**

📝 4294967290 = 0b11111111 111111111 11111111 1111010

📝 Do các member dùng chung vùng nhớ nên giá trị các member bằng nhau và kích thước của union frame là 4 byte nên dữ liệu sẽ được như sau:

```cpp
// 0x005FFE9C  0x005FFE9D  0x005FFE9E  0x005FFE9F
//  11111010    11111111    11111111    11111111
```

📝 member var1 có kiểu dữ liệu là uint8_t nên chỉ lấy 8 bit ở địa chỉ 0x005FFE9C -> var1 = 0b11111010 = 250

📝 member var2 có kiểu dữ liệu là uint32_t nên giữ nguyên giá trị

📝 member var3 có kiểu dữ liệu là uint16_t nên chỉ lấy 16 bit ở địa chỉ 0x005FFE9C và 0x005FFE9D -> var3 = 0b11111111 11111010 = 65530

<br>

</p>
</details>

</p>
</details>

<details><summary><b>📚 So sánh Struct và Union</b></summary>
<p>

<details><summary><b>🔍 Giống nhau</b></summary>
<p>
	
- Đều do lập trình viên tự định nghĩa (user defined type).
- Đều sử dụng dấu "." hoặc "->" để truy cập các phần tử (hoặc có thể gọi là thuộc tính).

</p>
</details>

<details><summary><b>🔍 Khác nhau</b></summary>
<p>

|           |   Struct  |   Union   |
|-----------|-----------|-----------|
| keyword    | Dùng keyword 'struct' để định nghĩa   | Dùng keyword 'union' để định nghĩa    |
| size    | Tổng các kích thước của các member và padding (nếu có)    | Tổng của kích thước của member có kích thước lớn nhất và padding (nếu có)    |
| Memory   | Mỗi member có vùng nhớ riêng biệt    | Các member dùng chung 1 vùng nhớ    |
| Modify    | Thay đổi giá trị 1 member không ảnh hưởng các member khác   | Thay đổi giá trị bất kỳ member nào cũng ảnh hưởng các member khác    |
| Truy cập   | Truy cập bất kỳ member ở thời điểm nào cũng được    | Trong một lúc chỉ truy cập được một member     |

![image](https://github.com/user-attachments/assets/10994e8c-37ff-4a6b-b947-3d2fa16eee65)

</p>
</details>

</p>
</details>

</p>
</details>

</p>
</details>

<br>

<details><summary><b>✨ Cấp phát động với malloc - calloc - realloc</b></summary>
<p>
	
![image](https://github.com/user-attachments/assets/5108cbb1-ac28-4304-9d25-6c9817c06c57)


</p>
</details>

<br>

<details><summary><b>✨ Memory layout (Phân vùng nhớ)</b></summary>
<p>

File do người dùng viết (file .c), file .exe và file .hex (file chứa chương trình nạp vào vi điều khiển) sẽ được lưu ở bộ nhớ ROM hoặc FLASH. Khi nhấn chạy chương trình thì những chương trình này sẽ copy sang bộ nhớ RAM rồi mới bắt đầu thực thi.


Memory layout của một chương trình C/C++ gồm 5 phần chính:

- Text
- Initialized Data (DS)
- Uninitialized Data (BSS)
- Stack
- Heap

![image](https://github.com/user-attachments/assets/0092a0ac-943b-40f1-b376-caacf7bc470c)

## 📚 1.Text Segment
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

## 📚 2.Initialized Data Segment (DS)
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

## 📚 3.Uninitialized Data Segment (BSS)
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

## 📚 4.Stack (Automatic Variable Storage)
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

## 📚 5.Heap (Dynamic Memory Allocation)
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

## 📚 So sánh vùng nhớ Stack và Heap
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

<br>

<details><summary><b>✨ JSON</b></summary>
<p>

## 📚 Khái niệm
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

## 📚 Định dạng của JSON

### ▷ Kiểu dữ liệu

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

### ▷ Key - Value

- Mỗi cặp key - value được phân tách bằng dấu hai chấm (:).
- Các cặp key - value trong object được phân tách bằng dấu phẩy (,).

```cpp
{
  "key1":"value1",
  "key2":"value2",
  "key3":"value3"
}
```

### ▷ Dấu ngoặc

- Dấu ngoặc nhọn ({}) được sử dụng để bao bọc đối tượng.
- Dấu ngoặc vuông ([]) được sử dụng để bao bọc mảng.

### ▷ Dấu phẩy

Dấu phẩy được sử dụng để phân tách giữa các thành phần trong mảng hoặc các cặp key-value trong đối tượng.

### ▷ Khoảng trắng

Khoảng trắng, dấu xuống dòng và tab không ảnh hưởng đến tính chính xác của JSON và thường được sử dụng để làm cho JSON dễ đọc hơn.

### ▷ Nhận xét

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

### ▷ 1. JSONType

Là một kiểu liệt kê (enum) xác định các loại giá trị mà một đối tượng JSON có thể có, bao gồm các giá trị như sau:

- JSON_NULL: Đại diện cho giá trị null trong JSON.
- JSON_BOOLEAN: Đại diện cho giá trị true hoặc false trong JSON.
- JSON_NUMBER: Đại diện cho một số (có thể là số nguyên hoặc số thực) trong JSON.
- JSON_STRING: Đại diện cho một chuỗi ký tự trong JSON.
- JSON_ARRAY: Đại diện cho một mảng các giá trị JSON khác.
- JSON_OBJECT: Đại diện cho một đối tượng (object) JSON, bao gồm các cặp khóa-giá trị.

### ▷ 2. JSONValue

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

<br>

<details><summary><b>✨ Linked List</b></summary>
<p>

## 📚 Định nghĩa

Danh sách liên kết (Linked List) là một cấu trúc dữ liệu trong lập trình máy tính, được sử dụng để tổ chức và lưu trữ dữ liệu. Một Linked list bao gồm một chuỗi các nút (nodes) được phân bổ động, được sắp xếp theo cách mà mỗi node sẽ chứa một giá trị và một con trỏ (pointer) trỏ đến node tiếp theo nó. Nếu con trỏ là NULL thì nó là node cuối cùng trong danh sách.

Có hai loại linked list chính:

- Singly Linked List (Danh sách liên kết đơn): Mỗi nút chỉ chứa một con trỏ đến nút tiếp theo trong chuỗi.
- Doubly Linked List (Danh sách liên kết đôi): Mỗi nút chứa hai con trỏ, một trỏ đến nút tiếp theo và một trỏ đến nút trước đó.

Một linked list cung cấp một cách linh hoạt để thêm, xóa và chèn các phần tử mà không cần phải di chuyển toàn bộ dãy số như mảng. Tuy nhiên, nó cũng có một số nhược điểm, như việc cần thêm một con trỏ cho mỗi nút, tăng độ phức tạp của bộ nhớ và có thể dẫn đến hiệu suất kém hơn trong một số trường hợp so với mảng.

Một danh sách được liên kết được giữ bằng cách sử dụng một biến con trỏ cục bộ trỏ đến mục đầu tiên của danh sách. Nếu con trỏ đó cũng là NULL thì danh sách được coi là trống.

![image](https://github.com/user-attachments/assets/c2669fde-dacb-4f2b-9cd8-cb861c7e9e3e)

## 📚 Các hàm trong Linked List
### ▷ Định nghĩa 1 node trong singly linked list
```cpp
typedef struct Node{
    int data;
    struct Node *next;
} Node_t;
```
### ▷ Khởi tạo 1 node mới
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
### ▷ Thêm node mới vào đầu danh sách
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
### ▷ Thêm node mới vào cuối danh sách
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
### ▷ Thêm node mới vào vị trí bất kỳ trong danh sách
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
### ▷ Xóa node đầu tiên trong danh sách
```cpp
void pop_front(Node_t **head){
    Node_t *new_head = (*head)->next;
    free(*head);
    *head = new_head;
}
```
### ▷ Xóa node cuối cùng trong danh sách
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
### ▷ Xóa node bất kỳ trong danh sách
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
### ▷ Xóa toàn bộ node trong danh sách
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
### ▷ Tính kích thước của danh sách
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

<br>

<details><summary><b>✨ Stack - Queue</b></summary>
<p>

## 📚 Stack
<details><summary>Chi tiết</summary>
<p>

### ▷ Định nghĩa Stack (Ngăn xếp)

Stack (ngăn xếp) là một cấu trúc dữ liệu tuân theo nguyên tắc "Last In, First Out" (LIFO), nghĩa là phần tử cuối cùng được thêm vào stack sẽ là phần tử đầu tiên được lấy ra. 

Các thao tác cơ bản trên stack bao gồm:

- "push" để thêm một phần tử vào đỉnh của stack.
- "pop" để xóa một phần tử ở đỉnh stack.
- "top" để lấy giá trị của phần tử ở đỉnh stack.

![image](https://github.com/user-attachments/assets/fcf7c263-0f88-4899-993d-4d8946df2068)

```cpp
typedef struct{
    int *items;
    int size;
    int top;	// chỉ số của phần tử ở đỉnh stack
} Stack;
```

### ▷ Khởi tạo 1 Stack mới
```cpp
void initialize(Stack *stack, int size){
    stack->items = (int*)malloc(sizeof(int)*size);
    stack->size  = size;
    stack->top   = -1;
}
```

### ▷ Kiểm tra Stack rỗng
```cpp
int isEmpty(Stack stack){
    return stack.top == -1;
}
```

### ▷ Kiểm tra Stack đầy
```cpp
int isFull(Stack stack){
    return stack.top == (stack.size - 1);
}
```

### ▷ Thêm phần tử vào Stack
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

### ▷ Xóa phần tử ra khỏi Stack
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

### ▷ Lấy giá trị của phần tử ở đỉnh Stack
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

## 📚 Queue
<details><summary>Chi tiết</summary>
<p>

### ▷ Định nghĩa Queue (Hàng đợi)

Queue là một cấu trúc dữ liệu tuân theo nguyên tắc "First In, First Out" (FIFO), nghĩa là phần tử đầu tiên được thêm vào hàng đợi sẽ là phần tử đầu tiên được lấy ra. 

Các thao tác cơ bản trên hàng đợi bao gồm:

- "enqueue": thêm phần tử vào cuối hàng đợi.
- "dequeue": lấy phần tử từ đầu hàng đợi.
- "front": lấy giá trị của phần tử đứng đầu hàng đợi.

```cpp
typedef struct{
    int *item;    // mảng tượng trưng chứa các giá trị của phần tử trong queue
    int size;     // kích thước của queue
    int front;    // vị trí phần tử đầu queue
    int rear;     // vị trí phần tử cuối queue
} Queue;
```

### ▷ Khởi tạo 1 hàng đợi mới
```cpp
Queue *initialize(int size){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->item  = (int*)malloc(size * sizeof(int));
    queue->size  = size;
    queue->front = queue->rear = -1;
    return queue;
}
```

### ▷ Kiểm tra hàng đợi rỗng
```cpp
int isEmpty(Queue queue){
    return (queue.front == -1);
}
```

### ▷ Kiểm tra hàng đợi đầy
```cpp
int isFull(Queue queue){
    return (queue.rear + 1) % queue.size == queue.front;
}
```
 
### ▷ Thêm phần tử vào cuối hàng đợi
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

### ▷ Xóa phần tử từ đầu hàng đợi
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
 
### ▷ Lấy giá trị của phần tử đứng đầu hàng đợi	
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

<br>

<details><summary><b>✨ Thao tác với file</b></summary>
<p>



</p>
</details>

<br>

<details><summary><b>✨ Thuật toán tìm kiếm nhị phân (Binary Search)</b></summary>
<p>



</p>
</details>

<br>

<details><summary><b>✨ Class</b></summary>
<p>



</p>
</details>

<br>

<details><summary><b>✨ OOP</b></summary>
<p>



</p>
</details>

<br>

<details><summary><b>✨ STL</b></summary>
<p>

## Vector
<details><summary><b>Chi tiết</b></summary>
<p>

</p>
</details>

## List
<details><summary><b>Chi tiết</b></summary>
<p>

</p>
</details>

## Map
<details><summary><b>Chi tiết</b></summary>
<p>

</p>
</details>

## Array
<details><summary><b>Chi tiết</b></summary>
<p>

</p>
</details>

## Iterator
<details><summary><b>Chi tiết</b></summary>
<p>

</p>
</details>

</p>
</details>
