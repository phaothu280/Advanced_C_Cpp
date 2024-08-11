# malloc - calloc - realloc
<details><summary>Chi tiết</summary>
<p>

## So sánh malloc() và calloc()

![image](https://github.com/user-attachments/assets/e70c92fb-05f9-4b03-a582-0ab79df1221d)

**Khi nào sử dụng malloc? Khi nào sử dụng calloc?**

- Dùng malloc khi bạn cần hiệu suất cao hơn và có thể tự khởi tạo dữ liệu theo cách riêng.
- Dùng calloc khi bạn cần khởi tạo bộ nhớ với giá trị mặc định là 0 để tránh các lỗi liên quan đến giá trị rác.

</p>
</details>

# Memory Layout (Phân vùng nhớ)
<details><summary>Chi tiết</summary>
<p>

File do người dùng viết (file .c), file .exe và file .hex (file chứa chương trình nạp vào vi điều khiển) sẽ được lưu ở bộ nhớ ROM hoặc FLASH. Khi nhấn chạy chương trình thì những chương trình này sẽ copy sang bộ nhớ RAM rồi mới bắt đầu thực thi.

Memory layout của một chương trình C/C++ bao gồm 5 phần chính:

- Text
- Initialized Data (DS)
- Uninitialized Data (BSS)
- Stack
- Heap

![image](https://github.com/user-attachments/assets/8abfc269-497a-41e5-92ac-15645b942266)

## Text Segment
![image](https://github.com/user-attachments/assets/b553287e-3e6e-40a9-8f7e-8fda9b157845)

**Ví dụ**

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

Do con trỏ **ptr** được khai báo kiểu **char** nên khi ta cố gắng thay đổi giá trị của nó sẽ gặp lỗi.

## Initialized Data (DS)
![image](https://github.com/user-attachments/assets/a4e140a4-9a33-4853-9340-3ab6b4f374d7)

**Ví dụ**

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

## Uninitialized Data Segment (BSS)
![image](https://github.com/user-attachments/assets/d7869447-f493-4938-8a6e-8fa53300e6d6)

**Ví dụ**

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


## Stack
![image](https://github.com/user-attachments/assets/6116c8e3-29ff-4023-9086-24ce297567ab)

**Ví dụ**

```cpp
int total(int a, int b){
    int c;
    c = a + b;
    return c;
}
int main(int argc, char const *argv[])
{
    printf("a+b=%d\n",total(5,6));
    printf("a+b=%d\n",total(9,7));
    return 0;
}
```
Biến a, b là input parameter của hàm.

Biến c là biến cục bộ, khi ra khỏi hàm total() thì sẽ mất đi.

Khi chạy lệnh printf() đầu tiên, a=5 và được cấp phát địa chỉ (giả sử là 0x01), b=6 và được cấp phát địa chỉ (giả sử là 0x03), biến c cũng sẽ được cấp phát địa chỉ (giả sử là 0x04). Những địa chỉ này se được lưu ở phần vùng Stack. Sau khi return kết quả thì địa chỉ của các biến a, b, c sẽ bị thu hồi.

Khi chạy lệnh printf() thứ hai, a=9 và tiếp tục được cấp phát địa chỉ (có thể là 0x01 hoặc khác), tương tự b, c và sau khi return kết quả thì các địa chỉ cũng bi thu hồi.

## Heap
![image](https://github.com/user-attachments/assets/a0d41628-b991-414a-a497-1c89b557a2f2)

**Ví dụ 1**

![image](https://github.com/user-attachments/assets/cf8e4413-8dfc-4b0a-bfeb-3aa719f4538c)

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

**Ví dụ 2**

```cpp
#include <stdlib.h>

int main(int argc, char const *argv[]){
    int *arr_malloc, *arr_calloc;
    size_t size = 5;

    // Sử dụng malloc
    arr_malloc = (int*)malloc(size * sizeof(int));

    // Sử dụng calloc
    arr_calloc = (int*)calloc(size, sizeof(int));

    // Giải phóng bộ nhớ
    free(arr_malloc);
    free(arr_calloc);
    return 0;
}
```

**Ví dụ 3**

```cpp
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){  

    int soluongkytu = 0;

    char* ten = (char*) malloc(sizeof(char) * soluongkytu);

    for (int i = 0; i < 3; i++){
        printf("Nhap so luong ky tu trong ten: \n");
        scanf("%d", &soluongkytu);
        ten = realloc(ten, sizeof(char) * soluongkytu);
        printf("Nhap ten cua ban: \n");
        scanf("%s", ten);
        printf("Hello %s\n", ten);
    }
    return 0;
}
```
</p>
</details>

# So sánh vùng nhớ Stack và Heap
<details><summary>Chi tiết</summary>
<p>
    
![image](https://github.com/user-attachments/assets/e847c837-f67b-45f6-81c0-aad150fe10e8)

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
