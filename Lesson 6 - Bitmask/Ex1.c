#include <stdio.h>
#include <stdint.h>
                                          //    0    1
#define GENDER    1 << 0  // bit 0: giới tính  nữ   nam     0b00000001
#define SHIRT     1 << 1  // bit 1: áo thun   không  có     0b00000010
#define HAT       1 << 2  // bit 2: nón       không  có     0b00000100
#define SHOES     1 << 3  // bit 3: giày      không  có     0b00001000
#define FEATURE1  1 << 4  // bit 4: tính năng 1             0b00010000
#define FEATURE2  1 << 5  // bit 5: tính năng 2             0b00100000
#define FEATURE3  1 << 6  // bit 6: tính năng 3             0b01000000
#define FEATURE4  1 << 7  // bit 7: tính năng 4             0b10000000

// enable bit
void enableFeature(uint8_t *options, uint8_t feature){
    *options |= feature;
}

// disable bit
void disableFeature(uint8_t *options, uint8_t feature){
    *options &= ~feature;
}

// check bit
int8_t isFeatureEnabled(uint8_t options, uint8_t feature){
    return ((options & feature) != 0) ? 1 : 0;
}

// liệt kê các tính năng đa bật
void listSelectedFeatures(uint8_t options){
    printf("Selected Features: \n");

    const char* featureName[] = {
        "Gender",
        "Shirt",
        "Hat",
        "Shoes",
        "Feature 1",
        "Feature 2",
        "Feature 3",
        "Feature 4"
    };

    for (int i=0; i<8; i++){
        if ((options >> i) & 1){
            printf("%s\n", featureName[i]);
        }
    }
}

int main(int argc, char const *argv[])
{
    uint8_t options = 0; // 0b00000000

    // Thêm tính năng
    enableFeature(&options, GENDER | HAT | FEATURE1);

    // Loại bỏ tính năng
    disableFeature(&options, HAT);

    // Liệt kệ các tính năng đã chọn
    listSelectedFeatures(options);
    
    return 0;
}
