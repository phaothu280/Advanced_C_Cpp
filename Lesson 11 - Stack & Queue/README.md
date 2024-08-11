# Stack
<details><summary>Chi tiết</summary>
<p>

## Định nghĩa Stack (Ngăn xếp)

Stack (ngăn xếp) là một cấu trúc dữ liệu tuân theo nguyên tắc "Last In, First Out" (LIFO), nghĩa là phần tử cuối cùng được thêm vào stack sẽ là phần tử đầu tiên được lấy ra. 

Các thao tác cơ bản trên stack bao gồm:

- "push" để thêm một phần tử vào đỉnh của stack.
- "pop" để xóa một phần tử ở đỉnh stack.
- "top" để lấy giá trị của phần tử ở đỉnh stack.

![image](https://github.com/user-attachments/assets/fcf7c263-0f88-4899-993d-4d8946df2068)

## Các hàm sử dụng trong Stack

### Định nghĩa 1 Stack
```cpp
typedef struct{
    int* items;
    int size;
    int top;
} Stack;
```

### Khởi tạo 1 Stack mới
```cpp
void initialize(Stack *stack, int size){
    stack->items = (int*)malloc(sizeof(int)*size);
    stack->size  = size;
    stack->top   = -1;
}
```

### Kiểm tra Stack rỗng
```cpp
int isEmpty(Stack stack){
    return stack.top == -1;
}
```

### Kiểm tra Stack đầy
```cpp
int isFull(Stack stack){
    return stack.top == stack.size - 1;
}
```

### Thêm phần tử vào Stack
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

### Xóa phần tử ra khỏi Stack
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

### Lấy giá trị của phần tử ở đỉnh Stack
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

# Queue
<details><summary>Chi tiết</summary>
<p>

## Định nghĩa Queue (Hàng đợi)

Queue là một cấu trúc dữ liệu tuân theo nguyên tắc "First In, First Out" (FIFO), nghĩa là phần tử đầu tiên được thêm vào hàng đợi sẽ là phần tử đầu tiên được lấy ra. 

Các thao tác cơ bản trên hàng đợi bao gồm:

- "enqueue": thêm phần tử vào cuối hàng đợi.
- "dequeue": lấy phần tử từ đầu hàng đợi.
- "front": lấy giá trị của phần tử đứng đầu hàng đợi.

![image](https://github.com/user-attachments/assets/d37a83a8-107e-44bc-9ebb-07f6e229e20d)

## Các hàm sử dụng trong Queue

### Định nghĩa 1 hàng đợi
```cpp
typedef struct{
    int *item;
    int size;
    int front;
    int rear;
} Queue;
```

### Khởi tạo 1 hàng đợi mới
```cpp
void initialize(Queue *queue, int size){
    queue->item  = (int*)malloc(sizeof(int)*size);
    queue->size  = size;
    queue->front = -1;
    queue->rear  = -1;
}
```

### Kiểm tra hàng đợi rỗng
```cpp
int isEmpty(Queue queue){
    return (queue.front == -1) ? 1 : 0;
}
```

### Kiểm tra hàng đợi đầy
```cpp
int isFull(Queue queue){
    return (queue.rear + 1) % queue.size == queue.front;
}
```
 
### Thêm phần tử vào cuối hàng đợi
```cpp
void enqueue(Queue *queue, int data){
    if (isFull(*queue)) printf("Queue overflow\n");
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

### Xóa phần tử từ đầu hàng đợi
```cpp
int dequeue(Queue *queue){
    if (isEmpty(*queue)){
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
 
### Lấy giá trị của phần tử đứng đầu hàng đợi	
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
