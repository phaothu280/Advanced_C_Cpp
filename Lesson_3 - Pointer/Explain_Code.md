```cpp
#include <stdio.h>
#include <string.h>

typedef struct{
    char  ten[50];
    float diemTrungBinh;
    int   id;
}SinhVien_t;
```

Tạo 1 struct SinhVien chứa 3 member để lưu trữ thông tin của 1 sinh viên, bao gồm:

-	tên sinh viên (chuỗi ký tự)
-	điểm trung bình kiểu float
-	mã số id kiểu int

```cpp
int stringCompare(const char *str1,const char *str2){
    while (*str1 && (*str1 == *str2)){
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}
```
Tại sao tham số đầu vào lại là kiểu const char* mà không phải là char*?

Bằng cách sử dụng const char*, ta báo cho compiler biết rằng hàm này chỉ đọc dữ liệu, không sửa đổi nó. Khi đó, dữ liệu chuỗi được truyền vào sẽ không bị thay đổi trong quá trình so sánh. 

Dữ liệu trả về tại sao lại cần phải ép kiểu từ char sang unsigned char?

Kiểu char có thể là ký tự có dấu hoặc không dấu tùy thuộc vào việc triển khai của trình biên dịch. Khi kiểu char là có dấu (signed), các ký tự có giá trị lớn hơn 127 sẽ được biểu diễn bằng giá trị âm. Việc so sánh trực tiếp các giá trị này có thể dẫn đến kết quả không mong muốn.

Bằng cách ép kiểu sang const unsigned char, chúng ta đảm bảo rằng tất cả các giá trị ký tự đều là không dấu, từ đó giúp so sánh chính xác các ký tự, đặc biệt là các ký tự mở rộng.

Giá trị trả về của hàm:

- Giá trị âm nếu str1 nhỏ hơn str2.
- Giá trị 0 nếu str1 bằng str2.
- Giá trị dương nếu str1 lớn hơn str2.

```cpp
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
   if (sv1->diemTrungBinh > sv2->diemTrungBinh) return 1;
   return 0;
}

// Hàm so sánh theo ID
int compareByID(const void *a, const void *b) {
   SinhVien_t *sv1 = (SinhVien_t *)a;
   SinhVien_t *sv2 = (SinhVien_t *)b;
   return sv1->id - sv2->id;
}
```

Các hàm trên dùng để so sánh sinh viên dựa vào các tiêu chí như điểm trung bình, tên, mã ID.

Tại sao tham số đầu vào các hàm lại là con trỏ kiểu void mà không phải là các kiểu con trỏ khác?

Sử dụng void* giúp các hàm so sánh trở nên đa năng hơn. Chúng có thể được sử dụng để so sánh các kiểu dữ liệu khác nhau mà không cần phải viết lại hàm cho từng kiểu dữ liệu cụ thể. 

Trong hàm so sánh, chỉ cần ép kiểu con trỏ void* về kiểu dữ liệu cụ thể mà ta đang làm việc (ví dụ: SinhVien_t*).
const void *a và const void *b là các tham số con trỏ chung. Bên trong hàm, chúng được ép kiểu về const SinhVien_t * để có thể truy cập các thuộc tính của sinh viên.

```cpp
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
```
Hàm sort là một hàm sắp xếp chung có thể sắp xếp mảng các sinh viên dựa trên một hàm so sánh được truyền vào.

Tham số đầu vào

**SinhVien_t array[]**

- Đây là mảng các sinh viên (SinhVien_t) mà chúng ta muốn sắp xếp.
- Mỗi phần tử của mảng là một cấu trúc SinhVien_t chứa thông tin về một sinh viên.
  
**size_t size**

- Đây là kích thước của mảng, hay số lượng phần tử trong mảng.
- size_t là một kiểu dữ liệu không dấu, thường được sử dụng để biểu diễn kích thước của các đối tượng trong bộ nhớ.

**int (*compareFunc)(const void *, const void *)**__

- Đây là con trỏ hàm so sánh, nhận vào hai con trỏ kiểu const void* và trả về một số nguyên.
- Con trỏ hàm này cho phép hàm sort sử dụng bất kỳ hàm so sánh nào để xác định thứ tự của các phần tử.

Hàm sử dụng hai vòng lặp lồng để thực hiện sắp xếp.

- Vòng lặp ngoài chạy từ 0 đến size - 2.
- Vòng lặp trong chạy từ i + 1 đến size - 1.

Trong mỗi lần lặp, hàm so sánh hai phần tử array[i] và array[j] bằng cách gọi compareFunc(array + i, array + j).

Nếu hàm so sánh trả về giá trị lớn hơn 0, điều đó có nghĩa là array[i] lớn hơn array[j] theo thứ tự mong muốn và ta hoán đổi chúng bằng hàm swapSV(array + i, array + j) để hoán đổi hai phần tử array[i] và array[j].
