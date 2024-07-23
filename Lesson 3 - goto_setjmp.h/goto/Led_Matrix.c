#include <stdio.h>

void delay(){
    double start;
    while (start < 60000000) start++;    
}

char first_sentence[]  = "HELLO";
char second_sentence[] = "FASHION";
char third_sentence[]  = "SUITABLE";

int letter_H[8][8] = {  
	{1,0,0,0,1,0,0,0},
    {1,0,0,0,1,0,0,0},
    {1,0,0,0,1,0,0,0},
    {1,1,1,1,1,0,0,0},
    {1,0,0,0,1,0,0,0},
    {1,0,0,0,1,0,0,0},
    {1,0,0,0,1,0,0,0},
    {1,0,0,0,1,0,0,0},  
};

int letter_F[8][8] = {  
	{1,1,1,1,1,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,1,1,1,1,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},  
};

int letter_S[8][8] = {  
	{0,1,1,1,1,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {0,1,1,1,0,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
	{1,1,1,1,0,0,0,0},  
};

int button = 0;

typedef enum{
    FIRST,
    SECOND,
    THIRD
} Sentence_t;

int main(){

    Sentence_t sentence = FIRST;

    while(1){
        switch (sentence){
        	case FIRST:
            	for (int index=0; index<sizeof(first_sentence); index++){
                	if (first_sentence[index] == 'H'){
                		for (int i=0; i<8; i++){    
                        	for (int j=0; j<8; j++){
                            	if (letter_H[i][j] == 1){
                                	printf("Turn on led at [%d][%d]\n", i,j);
                                	if (button == 1) goto exit_loops;
                            	}
                        	}
                        	// tat den
                    	}
                	}
                	if (first_sentence[index] == 'E'){
                    	// in ra chu e
                	}
            	}
            	printf("first sentence is done\n");
            	delay();
            	goto logic;

			case SECOND:
				for (int index=0; index<sizeof(second_sentence); index++){
					if (second_sentence[index] == 'F'){
						for (int i=0; i<8; i++){    
							for (int j=0; j<8; j++) {
								if (letter_F[i][j] == 1) {
									printf("Turn on led at [%d][%d]\n", i,j);
									if (button == 1) goto exit_loops;
								}
							}
							// tat den led
						}
					}
					if (second_sentence[index] == 'A'){
						// in ra chu A
					}
				}
				printf("second sentence is done\n");
				delay();
				goto logic;

			case THIRD:
				for (int index=0; index<sizeof(third_sentence); index++){
					if (third_sentence[index] == 'S'){
						for (int i=0; i<8; i++){    
							for (int j=0; j<8; j++){
								if (letter_S[i][j] == 1) {
									printf("Turn on led at [%d][%d]\n", i,j);
									if (button == 1) goto exit_loops;
								}
							}
							// tat den led
						}
					}
					if (third_sentence[index] == 'U'){
						// in ra chu H
					}
				}
				printf("third sentence is done\n");
				delay();
				//button = 1;
				goto logic;
			}

        logic:
            if (sentence == FIRST) 		 sentence = SECOND;
            else if (sentence == SECOND) sentence = THIRD;
            else if (sentence == THIRD)  sentence = FIRST;
            goto exit;
            
        exit_loops:
            printf("Stop!\n");
            break;
        
        exit:;
    }
	return 0;
}