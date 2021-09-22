#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int BLOCKSIZE = 256;
int INITIAL_SIZE = 64; 

//  [Index Block]
//       [0]
//       [1]    head = front
//       [2]     ||
//       [3]    tail = back
//       [4] 
//       [5]

//todo:
// what happens when I push front and remove back indefenetily (would wonder up and always reserve new storrage)

typedef struct ctrItems {
    void*** map;
    int mapLenght;
    int headBlockIndex;
    int headIndex;
    int tailBlockIndex;
    int tailIndex;
    int elementCounter;
} ctrItems_t;

ctrItems_t initDeque() {
    ctrItems_t deque;
    deque.map = malloc(sizeof(void*) * INITIAL_SIZE);
    deque.mapLenght = INITIAL_SIZE;
    deque.elementCounter = 0;
    return deque;
}

void resizeMapHead(ctrItems_t* deque) {
    int currentFill = deque->tailBlockIndex - deque->headBlockIndex;
    if(1.0*currentFill/deque->mapLenght < 0.3) {
        // dont need new size of map... just reposition it
        int centerMap = deque->mapLenght/2;
        int distanceToMove = centerMap - deque->headBlockIndex;
        memmove(&(deque->map[centerMap]), &(deque->map[deque->headBlockIndex]), (currentFill*sizeof(void*)) );
        deque->headBlockIndex = deque->headBlockIndex + distanceToMove;
        deque->tailBlockIndex = deque->tailBlockIndex + distanceToMove;
        return;
    }

    int newMapLenght = deque->mapLenght * 2;
    void*** newMap = malloc(sizeof(void*) * newMapLenght);
    if(newMap == NULL) {
        printf("Could not allocate %f memory!\n", sizeof(void*) * newMapLenght);
        return;
    }
        
    int X = newMapLenght - deque->mapLenght;
    memcpy(&(newMap[X]), deque->map, deque->mapLenght*sizeof(void*));
    free(deque->map);
    //printf("I have free'd\n");
    deque->map = newMap;
    deque->mapLenght = newMapLenght;
    deque->tailBlockIndex = deque->tailBlockIndex + X;
    deque->headBlockIndex = deque->headBlockIndex + X;
}

void resizeMapTail(ctrItems_t* deque) {
    int currentFill = deque->tailBlockIndex - deque->headBlockIndex;
    if(1.0*currentFill/deque->mapLenght < 0.3) {
        // dont need new size of map... just reposition it
        int centerMap = deque->mapLenght/2;
        int distanceToMove = deque->tailBlockIndex - centerMap;
        memmove(&(deque->map[centerMap-distanceToMove]), &(deque->map[deque->headBlockIndex]), (currentFill*sizeof(void*)) );
        deque->headBlockIndex = deque->headBlockIndex - distanceToMove;
        deque->tailBlockIndex = deque->tailBlockIndex - distanceToMove;
        return;
    }

    int newMapLenght = deque->mapLenght * 2;
    void*** newMap = malloc(sizeof(void*) * newMapLenght);
    if(newMap == NULL) {
        printf("Could not allocate %f memorey!\n", sizeof(void*) * newMapLenght);
        return;
    }

    memcpy(&(newMap[0]), deque->map, deque->mapLenght*sizeof(void*));
    free(deque->map);
    deque->map = newMap;
    deque->mapLenght = newMapLenght;
    
}

void deque_add_front(ctrItems_t* deque, void* item) {
    if(deque->elementCounter == 0) {
        deque->map[deque->mapLenght/2] = malloc(sizeof(void*) * BLOCKSIZE);
        deque->headBlockIndex = deque->mapLenght/2;
        deque->tailBlockIndex = deque->mapLenght/2;
        deque->headIndex = BLOCKSIZE/2;
        deque->tailIndex = BLOCKSIZE/2;

        deque->map[deque->headBlockIndex][deque->headIndex] = item;
        deque->elementCounter++;
        return;
    }

    if(deque->headIndex == 0) {
        //new block has to be created...
        if(deque->headBlockIndex == 0) {
            //map has to be resized...
            resizeMapHead(deque);            
        }
        deque->headBlockIndex--;
        deque->map[deque->headBlockIndex] = malloc(sizeof(void*) * BLOCKSIZE);
        if(deque->map[deque->headBlockIndex] == NULL) {
            printf("Could not allocate a new Block\n");
            return;
        }
        deque->headIndex = BLOCKSIZE - 1;
    }
    else {deque->headIndex--;}

    //printf("HeadBlockIndex %d\n", deque->headBlockIndex);
    //printf("HeadIndex: %d\n", deque->headIndex);

    deque->map[deque->headBlockIndex][deque->headIndex] = item;
    deque->elementCounter++;
}

void deque_add_back(ctrItems_t* deque, void* item) {
    if(deque->elementCounter == 0) {
        deque->map[deque->mapLenght/2] = malloc(sizeof(void*) * BLOCKSIZE);
        deque->headBlockIndex = deque->mapLenght/2;
        deque->tailBlockIndex = deque->mapLenght/2;
        deque->headIndex = BLOCKSIZE/2;
        deque->tailIndex = BLOCKSIZE/2;

        deque->map[deque->tailBlockIndex][deque->tailIndex] = item;
        deque->elementCounter++;
        return;
    }
    
    if(deque->tailIndex == BLOCKSIZE - 1) {
        // new block has to be created
        if(deque->tailBlockIndex == deque->mapLenght-1) {
            //map has to be resized...
            resizeMapTail(deque);
        }
        deque->tailBlockIndex++;
        deque->map[deque->tailBlockIndex] = malloc(sizeof(void*) * BLOCKSIZE);
        if(deque->map[deque->tailBlockIndex] == NULL) {
            printf("Could not allocate a new Block\n");
            return;
        }
        deque->tailIndex = 0;
    } 
    else {deque->tailIndex++;}

    deque->map[deque->tailBlockIndex][deque->tailIndex] = item;
    deque->elementCounter++;
}

void* deque_pop_front(ctrItems_t* deque) {
    if(deque->elementCounter == 0) {
        printf("Deque is empty!\n");
        return NULL;
    }
    
    void* ret = deque->map[deque->headBlockIndex][deque->headIndex];
    if(deque->headIndex == BLOCKSIZE - 1) {
        // have to jump back to earlyer block
        deque->headBlockIndex++;
        deque->headIndex = 0;
    }
    else{deque->headIndex++;}
    
    deque->elementCounter--;
    
    return ret;
}

void* deque_pop_back(ctrItems_t* deque) {
    if(deque->elementCounter == 0) {
        printf("Deque is empty!\n");
        return NULL;
    }
    
    void* ret = deque->map[deque->tailBlockIndex][deque->tailIndex];
    if(deque->tailIndex == 0){
        //have to jump back to previous block
        deque->tailBlockIndex--;
        deque->tailIndex = BLOCKSIZE - 1;
    }
    else{deque->tailIndex--;}
    deque->elementCounter--;
    return ret;
}

void* deque_look_front(ctrItems_t* deque) {
    return deque->map[deque->headBlockIndex][deque->headIndex];
}

void* deque_look_back(ctrItems_t* deque) {
    return deque->map[deque->tailBlockIndex][deque->tailIndex];
}

int deque_count(ctrItems_t* deque) {
    return deque->elementCounter;
}

int secondText(void) {
    int TESTNUMBER = 1000000;
    ctrItems_t mydeque = initDeque();
    printf("I test with %d iterations\n", TESTNUMBER);

    for(int i = 0; i < TESTNUMBER; i++) {
        deque_add_front(&mydeque, (void*)i);
        deque_add_back(&mydeque, (void*)i);
    }
    printf("%d Map Elemente\n", mydeque.mapLenght);
    printf("%d Elemente in que\n", mydeque.elementCounter);

    int goal = mydeque.elementCounter;
    
    for(int x = 0; x < goal; x++) {
        (int)deque_pop_front(&mydeque);
        //printf("Counter %d\n", x);
    }
    printf("%d Map Elemente\n", mydeque.mapLenght);
    printf("%d Elemente in que\n", mydeque.elementCounter);

    printf("Done\n");
}


int initialTest(void) {
    printf("Hello World!\n");

    ctrItems_t myDeque = initDeque();

    deque_add_front(&myDeque, (void*)123);
   
    deque_add_front(&myDeque, (void*)234);
   
    deque_add_front(&myDeque, (void*)345);
    
    deque_add_front(&myDeque, (void*)456);


    printf("Lenght: %d\n", myDeque.elementCounter);
    printf("HeadIndex: %d, TailIndex %d\n", myDeque.headIndex, myDeque.tailIndex);
    void* disp = deque_pop_back(&myDeque);
    printf("Popped: %d\n", (int)disp);
    disp = deque_pop_front(&myDeque);
    printf("Popped: %d\n", (int)disp);
    disp = deque_pop_front(&myDeque);
    printf("Popped: %d\n", (int)disp);
    disp = deque_pop_front(&myDeque);
    printf("Popped: %d\n", (int)disp);
    disp = deque_pop_front(&myDeque);
    printf("Popped: %d\n", (int)disp);

    printf("Lenght: %d\n", myDeque.elementCounter);
    printf("HeadIndex: %d, TailIndex %d\n", myDeque.headIndex, myDeque.tailIndex);
}

int TESTLENGH = 100000000;
void Benchmark() {
    ctrItems_t myDeque = initDeque();
    clock_t begin = clock();
    for(int i = 0; i < TESTLENGH; i++) {
        deque_add_front(&myDeque, (void*)i);
    }
    clock_t end = clock();
    double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("Execution time: %f in sec\n", time_spent);
}



int main(void) {
    Benchmark();
}