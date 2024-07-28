# Struct
## Kích thước Struct
Kích thước Struct bằng tổng các kích thước của các member và padding (nếu có).

## Ví dụ
**Ví dụ 1**

```cpp
typedef struct{
    uint32_t var1;  // 4 byte
    uint8_t  var2;  // 1 byte
    uint16_t var3;  // 2 byte
} frame;
```

![image](https://github.com/user-attachments/assets/fb82664c-da75-4cb2-8fbe-1c11ea12fea4)

Giải thích:

Lần 1 quét 4 bytes và var1 sử dụng.

Lần 2 quét 4 bytes, var2 chỉ sử dụng 1 byte, thừa 3 bytes bộ nhớ đệm.	

var3 sử dụng 2 bytes trong 3 bytes trên và còn thừa 1 byte bộ nhớ đệm.

Tổng kích thước struct frame trên là 8 bytes nhưng thực tế chỉ sử dụng 7 bytes.

