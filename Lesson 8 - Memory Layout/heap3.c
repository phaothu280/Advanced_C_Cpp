#include <stdio.h>
#include <stdlib.h>

void create_array1(){
    int array[3];
    for (int i = 0; i < 3; i++){
        printf("&array[%d]: %p\n", i, (array+i));
    }
    printf("----------------------\n");
}

void create_array2(){
    int *array = (int*)malloc(3*sizeof(int));
    for (int i = 0; i < 3; i++){
        printf("&array[%d]: %p\n", i, (array+i));
    }
    printf("----------------------\n");
    free(array);
}

int main(int argc, char const *argv[]){  
    create_array1();
    create_array1();
    create_array2();
    create_array2();
    return 0;
}
