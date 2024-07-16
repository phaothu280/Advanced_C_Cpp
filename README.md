# POINTER

## 1.Định nghĩa
Trong C, con trỏ (pointer) là một biến chứa địa chỉ bộ nhớ của một biến khác. Việc sử dụng con trỏ giúp thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.
## 2.Kích thước con trỏ
Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch.

•Hệ thống 32 – bit, kích thước của con trỏ là 4 byte.

•Hệ thống 64 – bit, kích thước của con trỏ là 8 byte.
## 3.Các kiểu con trỏ
### a.Void Pointer
Thường dùng để trỏ tới bất kỳ địa chỉ nào với bất kỳ kiểu dữ liệu của giá trị tại địa chỉ đó.

Cú pháp: ```cpp void *ptr_void; ```
