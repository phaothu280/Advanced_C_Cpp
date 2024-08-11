# Lesson 4 - Static_Extern_Register_Volatile
<details><summary>Chi tiết</summary>
<p>

## Static
### Cú pháp
```cpp
static <data_type> <name_variable>;
static <data_type> <name_function>;
```

### static local variables
Khi 1 biến cục bộ được khai báo với từ khóa static:

- giữ giá trị của biến qua các lần gọi hàm.
- giữ phạm vi của biến chỉ trong hàm đó.

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
Khi **'static'** được sử dụng với các biến toàn cục, nó sẽ hạn chế phạm vi của biến và chỉ có thể gọi trong file nguồn hiện tại.

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
File Ex2.c
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

Register trong C/C++ được sử dụng để **định nghĩa các biến cục bộ mà nên được lưu giữ trong một thanh ghi** thay vì RAM.

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
