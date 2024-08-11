#include <stdio.h>
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
