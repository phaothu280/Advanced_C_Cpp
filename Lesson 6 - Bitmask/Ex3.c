#include <stdio.h>
#include <stdint.h>

typedef enum{
    LOW,
    HIGH
} Status;

typedef struct {
    uint8_t LED1 : 1;   
    uint8_t LED2 : 1;
    uint8_t LED3 : 1;
    uint8_t LED4 : 1;
    uint8_t LED5 : 1;
    uint8_t LED6 : 1;
    uint8_t LED7 : 1;
    uint8_t LED8 : 1;
} LEDStatus;

void displayAllStatusLed(LEDStatus led){
    uint8_t *ledPtr = (uint8_t *)&led;

    for (int i=0; i<8; i++){
        printf("LED%d: %d\n", i+1, (*ledPtr >> i) & 1);
    }
}

int main(int argc, char const *argv[])
{
    // bật led 2,6,7
    LEDStatus ledStatus = {
        .LED2 = HIGH,
        .LED6 = HIGH,
        .LED7 = HIGH
    };

    // tắt led 6
    ledStatus.LED6 = LOW;

    // hiển thị trạng thái các led
    displayAllStatusLed(ledStatus);

    return 0;
}
