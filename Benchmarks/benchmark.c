// Wie lang brauche ich um X elemente in die Deque zu legen
// Wie lang brauche ich um X elemente aus der Deque zu nehmen
// abhängig ob Y elemente in der Deque schon befinden...

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "deque.c"
#define testLengh 100
double timerArray[testLengh+1]; 

void DoBenchmark_PutItemIn(int Y, int X) {
    FILE* f = fopen("BenchmarkFile_Array_ItemInput.txt", "w");
    printf("I have created a file");
    //create Deque
    deque_t myDeque = createDeque();
    //add Y in deque
    for(int i = 0; i<Y; i++) {
        deque_add_front((void*)i, &myDeque);
    }    
    printf("I have added Y into deque");
    //Start Benchmark and add X
    clock_t begin = clock();
    for(int o = 0; o<testLengh; o++) {
        for(int i = 0; i<X/testLengh; i++) {
        deque_add_front((void*)i,&myDeque);
        }
        clock_t zwischen = clock();
        timerArray[o] = (double)(zwischen-begin)/CLOCKS_PER_SEC;
    }
    clock_t end = clock();
    printf("I have done the test");
    timerArray[testLengh] = (double)(end-begin)/CLOCKS_PER_SEC;
    
    for(int i = 0; i < testLengh+1;i++) {
        fprintf(f, "%d", timerArray[i]);
    }
    fclose(f);
    printf("I have given you the test");
}

void main() {
    DoBenchmark_PutItemIn(1000000, 5000000);
}
