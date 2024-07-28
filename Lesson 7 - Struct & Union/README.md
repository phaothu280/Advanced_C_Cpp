# Struct
## Kích thước Struct
Kích thước Struct bằng tổng các kích thước của các member và padding (nếu có).

## Ví dụ
**Ví dụ 1**

<details><summary></summary>
<p>
    
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

</p>
</details>

**Ví dụ 2**

<details><summary></summary>
<p>

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

</p>
</details>

**Ví dụ 3**

<details><summary></summary>
<p>

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

</p>
</details>

**Ví dụ 4**
<details><summary></summary>
<p>

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

</p>
</details>

