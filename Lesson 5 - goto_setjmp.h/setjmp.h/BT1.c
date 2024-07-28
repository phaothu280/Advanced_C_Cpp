#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception_code;
const char *error_code;

#define TRY if ((exception_code = setjmp(buf)) == 0)
#define CATCH(x) else if (exception_code == x)
#define THROW(x,ERROR) {    \
    error_code = #ERROR;    \
    longjmp(buf,x);         \
} 

double divide(int a, int b){
    if (!b){
        THROW(1, Error: Divide by 0!);
    }
    else if (a>=256 || b>=256){
        THROW(2, Error Overflow!);
    }
    return a/((double)b);
}
void input(int *a, int *b){
    printf("Nhap a: "); scanf("%d",a);
    printf("Nhap b: "); scanf("%d",b);    
}

int main(int argc, char const *argv[]){
    int a,b;
    while (1){
        input(&a,&b);
        TRY{
            if (a==0 && b==0) goto exit_loop;
            double result = divide(a,b);
            printf("Result = %0.3f\n",result);
            printf("\n");
        }
        CATCH(1){
            printf("%s\n", error_code);
        }
        CATCH(2){
            printf("%s\n", error_code);
        }
    }

    exit_loop:
        printf("Stop\n");
        
    return 0;
}
