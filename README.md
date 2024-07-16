#LESSON 3: POINTER
Định nghĩa Pointer
Trong C, con trỏ (pointer) là một biến chứa địa chỉ bộ nhớ của một biến khác. Việc sử dụng con trỏ giúp thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.
Kích thước của Pointer
Kích thước của con trỏ phụ thuộc vào kiến trúc máy tính và trình biên dịch.
•	Hệ thống 32 – bit, kích thước của con trỏ là 4 byte.
•	Hệ thống 64 – bit, kích thước của con trỏ là 8 byte.
Các kiểu Pointer
1. Void Pointer
Void pointer thường dùng để trỏ tới bất kỳ địa chỉ nào mà không cần biết tới kiểu dữ liệu của giá trị tại địa chỉ đó.
Cú pháp:  void *ptr_void;
2. Function Pointer
Con trỏ hàm là một biến mà giữ địa chỉ của hàm, nghĩa là nó trỏ đến vùng nhớ trong bộ nhớ chứa mã máy của hàm được định nghĩa trong chương trình.
Trong C, con trỏ hàm cho phép bạn truyền một hàm như là một đối số cho một hàm khác, lưu trữ địa chỉ của hàm trong một cấu trúc dữ liệu hoặc thậm chí truyền hàm như một giá trị trả về từ một hàm khác.
3. Pointer to constant
Con trỏ hằng là một cách định nghĩa một con trỏ chỉ có thể đọc giá trị tại địa chỉ mà nó trỏ đến (Read Only) nhưng không thể thay đổi được giá trị đó.
Cú pháp: 
int const *ptr_const;
const int *ptr_const;
4. Constant Pointer
Hằng con trỏ định nghĩa một con trỏ mà địa chỉ nó trỏ đến không thể thay đổi, nghĩa là khi con trỏ này được khởi tạo thì nó sẽ không thể trỏ tới địa chỉ khác.
Cú pháp: int *const const_ptr = &value;

5. NULL Pointer
Null Pointer là một con trỏ không thể trỏ đến bất kỳ đối tượng hoặc vùng nhớ cụ thể nào.
Trong C, một con trỏ có thể được gán giá trị NULL để biểu diễn trạng thái NULL.
Sử dụng Null Pointer thường hữu ích để kiểm tra xem một con trỏ đã được khởi tạo và có trỏ đến một vùng nhớ hợp lệ chưa.
Tránh dereferencing (sử dụng giá trị mà con trỏ trỏ đến) một null pointer là quan trọng để tránh lỗi chương trình.
6. Pointer to Pointer
Con trỏ đến con trỏ (Pointer to Pointer) là một kiểu dữ liệu trong ngôn ngữ lập trình cho phép bạn lưu trữ địa chỉ của một con trỏ. Con trỏ đến con trỏ cung cấp một cấp bậc trỏ mới, cho phép bạn thay đổi giá trị của con trỏ gốc. Cấp bậc này có thể hữu ích trong nhiều tình huống, đặc biệt là khi bạn làm việc với các hàm cần thay đổi giá trị của con trỏ.

