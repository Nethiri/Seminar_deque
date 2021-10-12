// Wie lang brauche ich um X elemente in die Deque zu legen
// Wie lang brauche ich um X elemente aus der Deque zu nehmen
// abhängig ob Y elemente in der Deque schon befinden...

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//#include "BlockdynDque.c"
//#include "deque.c"
#include "LinkedListDynDeque.c"

#define testLengh 100
double timerArray[testLengh+1]; 

/*
void DoBenchmark_PutItemIn_Linked(int Y, int X) {
    FILE* f = fopen("BenchmarkFile_Linked_ItemInput.txt", "w");
    printf("I have created a file\n");
    //create Deque
    LinkedDeque_t myDeque = createDeque();
    //add Y in deque
    for(int i = 0; i<Y; i++) {
        deque_add_front(&myDeque, (void*)i);
    }
    printf("I have added Y into deque");
    
    //Start Benchmark and add X
    clock_t begin = clock();
    for(int o = 0; o<testLengh; o++) {
        for(int i = 0; i<X/testLengh; i++) {
            deque_add_front(&myDeque, (void*)i);
        }
        clock_t zwischen = clock();
        timerArray[o] = (double)(zwischen-begin) / (double)(CLOCKS_PER_SEC);
        //printf("Zwischen = %d, Zwischen-Begin = %d\n",zwischen, (zwischen-begin));
    }
    clock_t end = clock();
    printf("I have done the test\n");
    timerArray[testLengh] = (double)(end-begin) / (double)(CLOCKS_PER_SEC);
    
    for(int i = 0; i < testLengh+1;i++) {
        fprintf(f, "%lf\n", timerArray[i]);
    }
    printf("I have given you the test\n");
    fclose(f);
}
*/
/*
void DoBenchmark_PutItemIn_Array(int Y, int X) {
    FILE* f = fopen("BenchmarkFile_Array_ItemInput.txt", "w");
    printf("I have created a file\n");
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
            deque_add_front((void*)i, &myDeque);
        }
        clock_t zwischen = clock();
        //printf("Zwischen = %d, Zwischen-Begin = %lf\n",zwischen, (double)(zwischen-begin) / (double)(CLOCKS_PER_SEC));
        timerArray[o] = (double)(zwischen-begin) / (double)(CLOCKS_PER_SEC);
        
    }
    clock_t end = clock();
    printf("I have done the test\n");
    timerArray[testLengh] = (double)(end-begin) / (double)(CLOCKS_PER_SEC);
    
    for(int i = 0; i < testLengh+1;i++) {
        //printf("Printed: %lf\n", timerArray[i]);
        fprintf(f, "%lf\n", timerArray[i]);
    }
    printf("I have given you the test\n");
    fclose(f);
}
*/
/*
void DoBenchmark_PutItemIn_Block(int Y, int X) {
    FILE* f = fopen("BenchmarkFile_Block_ItemInput.txt", "w");
    printf("I have created a file\n");
    //create Deque
    ctrItems_t myDeque = initDeque();
    //time_t begin, end, zwischen;

    //add Y in deque
    for(int i = 0; i<Y; i++) {
        deque_add_front(&myDeque, (void*)i);
    }
    printf("I have added Y into deque");
    
    

    //Start Benchmark and add X
    clock_t begin = clock();    
   

    for(int o = 0; o<testLengh; o++) {
        for(int i = 0; i<X/testLengh; i++) {
            deque_add_front(&myDeque, (void*)i);
        }
        clock_t zwischen = clock();
        
        timerArray[o] = (double)(zwischen-begin) / (double)(CLOCKS_PER_SEC);
       
        //printf("Zwischen = %d, Zwischen-Begin = %lf\n",zwischen, (double)(zwischen-begin) / (double)(CLOCKS_PER_SEC));
        

    }

    clock_t end = clock();
    
    
    printf("I have done the test\n");
    timerArray[testLengh] = (double)(end-begin) / (double)(CLOCKS_PER_SEC);
   

    for(int i = 0; i < testLengh+1;i++) {
        fprintf(f, "%lf\n", timerArray[i]);
    }
    printf("I have given you the test\n");
    fclose(f);
}
*/

/*
void DoBenchmark_PutOut_Block(int X) {
    FILE* f = fopen("BenchmarkFile_Block_ItemOutput.txt", "w");
    printf("I have created a file\n");
    //create Deque
    ctrItems_t myDeque = initDeque();
    //time_t begin, end, zwischen;

    //add Y in deque
    for(int i = 0; i<X; i++) {
        deque_add_front(&myDeque, (void*)i);
    }
    printf("I have added X into deque");
    
    

    //Start Benchmark and add X
    clock_t begin = clock();    
    int itemsFound = 0;

    for(int o = 0; o<testLengh; o++) {
        for(int i = 0; i<X/testLengh; i++) {
            void* data = deque_pop_front(&myDeque);
            if(data != NULL) {
                itemsFound++;
            }
        }
        clock_t zwischen = clock();
        
        timerArray[o] = (double)(zwischen-begin) / (double)(CLOCKS_PER_SEC);
       
        //printf("Zwischen = %d, Zwischen-Begin = %lf\n",zwischen, (double)(zwischen-begin) / (double)(CLOCKS_PER_SEC));
    }

    clock_t end = clock();
    
    
    printf("I have done the test\n");
    printf("I have found: %d items...\n", itemsFound);
    timerArray[testLengh] = (double)(end-begin) / (double)(CLOCKS_PER_SEC);
   

    for(int i = 0; i < testLengh+1;i++) {
        fprintf(f, "%lf\n", timerArray[i]);
    }
    printf("I have given you the test\n");
    fclose(f);
}
*/
/*
void DoBenchmark_PutItemOut_Array(int X) {
    FILE* f = fopen("BenchmarkFile_Array_ItemOutPut.txt", "w");
    printf("I have created a file\n");
    //create Deque
    deque_t myDeque = createDeque();
    //add Y in deque
    for(int i = 0; i<X; i++) {
        deque_add_front((void*)i, &myDeque);
    }
    printf("I have added Y into deque");
    
    //Start Benchmark and add X
    clock_t begin = clock();
    int itemsFound = 0;
    for(int o = 0; o<testLengh; o++) {
        for(int i = 0; i<X/testLengh; i++) {
            void* data = deque_del_front(&myDeque);
            if(data != NULL) {
                itemsFound++;
            }
        }
        clock_t zwischen = clock();
        //printf("Zwischen = %d, Zwischen-Begin = %lf\n",zwischen, (double)(zwischen-begin) / (double)(CLOCKS_PER_SEC));
        timerArray[o] = (double)(zwischen-begin) / (double)(CLOCKS_PER_SEC);
    }
    clock_t end = clock();
    printf("I have done the test\n");
    timerArray[testLengh] = (double)(end-begin) / (double)(CLOCKS_PER_SEC);
    
    for(int i = 0; i < testLengh+1;i++) {
        //printf("Printed: %lf\n", timerArray[i]);
        fprintf(f, "%lf\n", timerArray[i]);
    }
    printf("I have found: %d items...\n", itemsFound);
    printf("I have given you the test\n");
    fclose(f);
}
*/
void DoBenchmark_PutItemOut_Linked(int X) {
    FILE* f = fopen("BenchmarkFile_Linked_ItemOutPut.txt", "w");
    printf("I have created a file\n");
    //create Deque
    LinkedDeque_t myDeque = createDeque();
    //add Y in deque
    for(int i = 0; i<X; i++) {
        deque_add_front(&myDeque, (void*)i);
    }
    printf("I have added Y into deque");
    
    //Start Benchmark and add X
    clock_t begin = clock();
    int ItemsFound = 0;
    for(int o = 0; o<testLengh; o++) {
        for(int i = 0; i<X/testLengh; i++) {
            void* data = deque_pop_front(&myDeque);
            if(data != NULL) {
                ItemsFound++;
            }
        }
        clock_t zwischen = clock();
        timerArray[o] = (double)(zwischen-begin) / (double)(CLOCKS_PER_SEC);
        //printf("Zwischen = %d, Zwischen-Begin = %d\n",zwischen, (zwischen-begin));
    }
    clock_t end = clock();
    printf("I have done the test\n");
    timerArray[testLengh] = (double)(end-begin) / (double)(CLOCKS_PER_SEC);
    
    for(int i = 0; i < testLengh+1;i++) {
        fprintf(f, "%lf\n", timerArray[i]);
    }
    printf("I have found: %d items", ItemsFound);
    printf("I have given you the test\n");
    fclose(f);
}









void main() {
    //DoBenchmark_PutItemIn_Linked(0, 60000000);
    //DoBenchmark_PutItemIn_Array(0, 60000000);
    //DoBenchmark_PutItemIn_Block(0, 60000000);

    //DoBenchmark_PutOut_Block(60000000);
    //DoBenchmark_PutItemOut_Array(60000000);
    DoBenchmark_PutItemOut_Linked(60000000);

}
