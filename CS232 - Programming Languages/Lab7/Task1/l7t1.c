//Robert Florence
//CS 232
//Professor AJ
//3-14-16
//LAB7


#include "l7t1.h"

extern int number_of_sum;
extern int sum_of_num;

extern FILE *yyin; /* needed if using yyin in here */

char *targetWords[NUM_OF_WORDS] = {"bank","dollar","financ","budget","fund","stock","bond","invest"};

int main(int argc, char *argv[])
{
    int counter2;
    int occurencecounter[NUM_OF_WORDS];
    int sumarray[(NUM_OF_WORDS*50)];
    
    for (int i=0; i < NUM_OF_WORDS; i++) {
        occurencecounter[i]=0;
    }
    
    yyin = freopen(argv[1], "r", stdin);
    
    WORD word = NO_TOK;
    
    while((word = yylex()) != NO_TOK){
        
        if ((word > 0) && (word <= NUM_OF_WORDS)){
            
            printf("%s", targetWords[word-BANK]);
            occurencecounter[word-BANK]++;
        }
        
        if (word > NUM_OF_WORDS) {
            
            printf("%d",word);
            
            sumarray[number_of_sum] = word;
            
            number_of_sum++;
        }
        word = word-word;
    }
    
    sum_of_num = sum(sumarray,number_of_sum);
    
    counter2 = sum(occurencecounter, NUM_OF_WORDS);
    
    if (sum_of_num >= 1000) {
        
        printf("\n\nVERY INTERESTING READING!\nReported Sum is: %d\n\n",sum_of_num);
        
    } else {

        if (counter2 >= 3) {
        
    printf("\n\nPOTENTIALLY INTERESTING READING!!!\nSum is: %d\nOCCURENCES:\n",sum_of_num);
    for (int j = 0; j < NUM_OF_WORDS; j++) {
    
        if (occurencecounter[j]!=0) {
        
        printf("%s: %d\n",targetWords[j], occurencecounter[j]);
        
        }
    }
}
}
}

int sum(int sumarray[], int arrsize){
    int sum = 0;
    for (int i=0; i<arrsize; i++) {
        sum = sum + sumarray[i];
    }
    return sum;
    
}