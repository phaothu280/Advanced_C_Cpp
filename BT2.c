#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception_code;
const char *error_message;

typedef enum{
    NO_ERROR,
    FILE_ERROR,
    NETWORK_ERROR,
    CALCULATION_ERROR
} ErrorCodes;

#define TRY if ((exception_code = setjmp(buf)) == 0)
#define CATCH(x) else if (exception_code == x)
#define THROW(x,message) {      \
    error_message = #message;   \
    longjmp(buf,x);             \
} 

void readFile(){
    printf("read file...\n");
    THROW(FILE_ERROR, "Error read file: File not found!");
}

void networkOperation(){
    printf("network operation...\n");
    THROW(NETWORK_ERROR, "Error network: cannot connect!");
}

void calculateData(){
    printf("calculate data...\n");
    THROW(CALCULATION_ERROR, "Error calculation: Data not found");
}

int main(int argc, char const *argv[]){
    TRY{
        readFile();
        networkOperation();
        calculateData();
    }
    CATCH(FILE_ERROR){
        printf("File error: %s\n", error_message);
    }
    CATCH(NETWORK_ERROR){
        printf("Network error: %s\n", error_message);
    }
    CATCH(CALCULATION_ERROR){
        printf("Calculation error: %s\n", error_message);
    }
    return 0;
}
