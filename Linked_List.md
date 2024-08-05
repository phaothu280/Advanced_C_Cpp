```cpp
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node_t;

// khởi tạo 1 node mới
// Để tạo thêm 1 node mới, ta sẽ tiến hành khởi tạo giá trị ban đầu và trả địa chỉ về cho node được cấp phát.
Node_t *createNode(int data){
    Node_t *temp = (Node_t*)malloc(1*sizeof(Node_t));
    temp->data = data;
    temp->next = NULL;
    // node vừa tạo chưa thêm vào danh sách nên chưa liên kết với phần tử nào cả nên phần liên kết gán bằng NULL
    return temp;
}

// thêm 1 node mới vào đầu danh sách
void push_front(Node_t **head, int data){
    Node_t *new_node = createNode(data);
    if (*head == NULL){
        *head = new_node;
    }
    else{
        new_node->next = *head;
        *head = new_node;
    }
}

// thêm 1 node mới vào cuối danh sách
void push_back(Node_t **head, int data){
    Node_t *new_node = createNode(data);
    if (*head == NULL){
        *head = new_node;
    }
    else{
        Node_t *p = *head;
        while (p->next != NULL){
            p = p->next;
        }
        p->next = createNode(data);
    }
}

// thêm 1 node vào vị trí bất kỳ của List
void insert(Node_t **head, int data, int position){
    Node_t *new_node = createNode(data);
    Node_t *p = *head;
    int k = 0;

    while (p->next != NULL && k != position-1){
        p = p->next;
        k++;
    }
    
    if (k == position-1){
        new_node->next = p->next;
        p->next = new_node;
    }
    else return;
}

// xóa node đầu tiên
void pop_front(Node_t **head){
    Node_t *new_head = (*head)->next;
    free(*head);
    *head = new_head;
}

// xóa node cuối cùng
void pop_back(Node_t **head){
    if (*head == NULL) return;
    else{
        Node_t *p = *head;
        while (p->next->next != NULL){
            p = p->next;
        }
        free(p->next);
        p->next = NULL;
    }
}

// xóa node bất kỳ
void delete_node(Node_t **head, int position){
    Node_t *p = *head;
    int k = 0;

    while (p != NULL && k != position-1){
        p = p->next;
        k++;
    }

    if (k == position-1){
        Node_t *node_delete = p->next;
        p->next = p->next->next;
        free(node_delete);
    }
    else return;
}

// xóa toàn bộ node trong linked list
void clear_all(Node_t **head){
    Node_t *p = *head;
    while (p != NULL){
        Node_t *temp = p->next;
        free(p);
        p = temp;
    }
    *head = NULL;
}

// kích thước linked list
int size(Node_t *head){
    Node_t *p = head;
    int count = 0;

    while (p != NULL){
        count++;
        p = p->next;
    }
    return count;
}

void printList(Node_t *head){
    Node_t *pt = head;
    int i = 0;
    while (pt != NULL){
        printf("Node %d, Data = %d\n", i, pt->data);
        pt = pt->next;
        i++;
    }
}

int main(int argc, char const *argv[]){
    Node_t *head   = createNode(1);
    Node_t *second = createNode(2);
    Node_t *third  = createNode(3);

    head->next = second;
    second->next = third;

    printList(head);
    printf("Size of linked list: %d\n", size(head));
    printf("\n");

    push_front(&head, 4);
    printList(head);
    printf("Size of linked list: %d\n", size(head));
    printf("\n");

    push_back(&head, 5);
    printList(head);
    printf("Size of linked list: %d\n", size(head));
    printf("\n");

    insert(&head, 10, 2);
    insert(&head, 8, 4);
    printList(head);
    printf("Size of linked list: %d\n", size(head));
    printf("\n");

    pop_front(&head);
    printList(head);
    printf("Size of linked list: %d\n", size(head));
    printf("\n");

    pop_back(&head);
    printList(head);
    printf("Size of linked list: %d\n", size(head));
    printf("\n");

    delete_node(&head,2);
    printList(head);
    printf("Size of linked list: %d\n", size(head));
    printf("\n");

    clear_all(&head);
    printList(head);
    printf("Size of linked list: %d\n", size(head));
    printf("\n");

    return 0;
}

```
