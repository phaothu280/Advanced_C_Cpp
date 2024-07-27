#include <stdio.h>
#include <time.h>

// hàm delay theo giây, ví dụ: delay(2000) -> 2s
void delay(unsigned int milliseconds) {
    unsigned int start = clock();
    while (clock() - start < milliseconds);
}

char first_sentence[]  = "HI";
char second_sentence[] = "FASHION";
char third_sentence[]  = "SUITABLE";

int letter_H[8][8] = {  
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},  
};

int letter_I[8][8] = {  
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {1,1,1,1,1,1,1,1},  
};

int letter_F[8][8] = {  
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},  
};

int letter_S[8][8] = {  
    {0,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,0},  
};

// mô phỏng nút nhấn bấm dừng chương trình
int button = 0;

// khởi tạo kiểu liệt kê đại diện cho 3 câu cần hiển thị
typedef enum{
	FIRST,
	SECOND,
	THIRD
} Sentence;

// hàm in ký tự ra led ma trận 8x8
void print_char(const int matrix[8][8]){
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			if (matrix[i][j] == 1){
				printf("*");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[]){
	// Biến `sentence` được khởi tạo với giá trị `FIRST`, đại diện cho câu đầu tiên cần hiển thị.
	Sentence sentence = FIRST;

	while(1){
		switch(sentence){
			case FIRST:
				for (int index=0; index<sizeof(first_sentence); index++){
					if (first_sentence[index] == 'H'){
						print_char(letter_H);
					}
					else if (first_sentence[index] == 'I'){
						print_char(letter_I);
					}
					if (button == 1) goto exit_loops;
				}
				printf("First sentence is done\n");
				printf("\n");
				delay(2000);
				goto logic;

			case SECOND:
				for (int index=0; index<sizeof(second_sentence); index++){
					if (second_sentence[index] == 'F'){
						print_char(letter_F);
					}
					else if (second_sentence[index] == 'A'){
						// in ra ký tự 'A'
					}
					if (button == 1) goto exit_loops;
				}
				printf("Second sentence is done\n");
				printf("\n");
				delay(2000);
				goto logic;

			case THIRD:
				for (int index=0; index<sizeof(third_sentence); index++){
					if (third_sentence[index] == 'S'){
						print_char(letter_S);
					}
					else if (third_sentence[index] == 'U'){
						// in ra ký tự 'U'
					}
					if (button == 1) goto exit_loops;
				}
				printf("Third sentence is done\n");
				printf("\n");
				delay(2000);
				goto logic;
		}

		logic:
			if (sentence == FIRST) 		 sentence = SECOND;
			else if (sentence == SECOND) sentence = THIRD;
			else if (sentence == THIRD)  sentence = FIRST;
			goto exit;
		
		exit_loops:
			printf("Stop\n");
			break;
		
		exit:;
	}

	return 0;
}
