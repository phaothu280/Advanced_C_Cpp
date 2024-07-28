#include <stdio.h>
#include <stdint.h>

#define COLOR_RED     0
#define COLOR_BLUE    1
#define COLOR_BLACK   2
#define COLOR_WHITE   3

#define POWER_100HP   0
#define POWER_150HP   1
#define POWER_50HP    2

#define ENGINE_1_5L   0
#define ENGINE_2_0L   1

typedef uint8_t CarColor;
typedef uint8_t CarPower;
typedef uint8_t CarEngine;

#define SUNROOF_MASK         1 << 0
#define PREMIUM_AUDIO_MASK   1 << 1
#define SPORTS_PACKAGE_MASK  1 << 2
// Thêm các bit masks khác tùy thuộc vào tùy chọn

typedef struct{
    uint8_t additionalOptions : 3; // 3-bit cho tùy chọn bổ sung
    CarColor  color  : 2; // 2-bit cho màu sắc
    CarPower  power  : 2; // 2-bit cho năng lượng
    CarEngine engine : 1; // 1-bit cho động cơ
} CarOptions;

void configureCar(CarOptions *car, CarColor color, CarPower power, CarEngine engine, uint8_t options) {
    car->color = color;
    car->power = power;
    car->engine = engine;
    car->additionalOptions = options;
}

void setOption(CarOptions *car, uint8_t optionMask) {
    car->additionalOptions |= optionMask;
}

void resetOption(CarOptions *car, uint8_t optionMask) {
    car->additionalOptions &= ~optionMask;
}

void displayCarOptions(const CarOptions car) {
    const char *colors[] = {"Red", "Blue", "Black", "White"};
    const char *powers[] = {"100HP", "150HP", "200HP"};
    const char *engines[] = {"1.5L", "2.0L"};

    printf("Car Configuration: \n");
    printf("Color: %s\n", colors[car.color]);
    printf("Power: %s\n", powers[car.power]);
    printf("Engine: %s\n", engines[car.engine]);
    printf("Sunroof: %s\n", (car.additionalOptions & SUNROOF_MASK) ? "Yes" : "No");
    printf("Premium Audio: %s\n", (car.additionalOptions & PREMIUM_AUDIO_MASK) ? "Yes" : "No");
    printf("Sports Package: %s\n", (car.additionalOptions & SPORTS_PACKAGE_MASK) ? "Yes" : "No");
}

int main() {
    CarOptions myCar;

    configureCar(&myCar, COLOR_BLACK, POWER_150HP, ENGINE_2_0L, 0); 
    setOption(&myCar, SUNROOF_MASK);
    setOption(&myCar, PREMIUM_AUDIO_MASK);
    displayCarOptions(myCar);

    resetOption(&myCar, PREMIUM_AUDIO_MASK); 
    displayCarOptions(myCar);

    printf("size of my car: %d\n", sizeof(CarOptions));
    return 0;
}
