# JSON

## Khái niệm

- JSON là viết tắt của “JavaScript Object Notation” (Ghi chú về đối tượng JavaScript).
- Là một định dạng truyền tải dữ liệu phổ biến trong lập trình và giao tiếp giữa các máy chủ và trình duyệt web, cũng như giữa các hệ thống khác.
- JSON được thiết kế để dễ đọc và dễ viết cho con người, dễ phân tích cho máy tính với cú pháp dựa trên một cặp **key – value**.

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
