#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *item;
    int size;
    int front;
    int rear;
} Queue;

void initialize(Queue *queue, int size){
    queue->item  = (int*)malloc(sizeof(int)*size);
    queue->size  = size;
    queue->front = -1;
    queue->rear  = -1;
}

int isEmpty(Queue queue){
    return (queue.front == -1) ? 1 : 0;
}

int isFull(Queue queue){
    return (queue.rear + 1) % queue.size == queue.front;
}

// thêm phần tử vào cuối hàng đợi
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

// lấy phần tử từ đầu hàng đợi
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

// lấy giá trị của phần tử đứng đầu hàng đợi (front)
int front(Queue queue){
    if (isEmpty(queue)){
        printf("Queue is empty\n");
        return -1;
    }
    else{
        return queue.item[queue.front];
    }
}

int main(int argc, char const *argv[])
{
    Queue queue;

    initialize(&queue,3);
    enqueue(&queue, 10);
    enqueue(&queue, 15);
    enqueue(&queue, 20);

    printf("Front element: %d\n", front(queue));

    printf("Dequeue element: %d\n", dequeue(&queue));
    printf("Dequeue element: %d\n", dequeue(&queue));

    printf("Front element: %d\n", front(queue));

    enqueue(&queue, 40);
    enqueue(&queue, 50);
    printf("Dequeue element: %d\n", dequeue(&queue));
    printf("Front element: %d\n", front(queue));

    return 0;
}

// 10 15 20

// 20 40 50

// 40 50