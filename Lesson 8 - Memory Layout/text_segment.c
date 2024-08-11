#include <stdio.h>

const int a = 10;

char *ptr = "Hello World";

int main(int argc, char const *argv[])
{
    printf("a = %d\n", a);

    //*ptr = "Hello";
    return 0;
}

//invalid conversion from 'const char*' to 'char' [-fpermissive]