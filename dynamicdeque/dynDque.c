#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        deque->headBlockIndex = deque->headBlockIndex - distanceToMove;
        deque->tailBlockIndex = deque->tailBlockIndex - distanceToMove;
        return;
    }


    int newMapLenght = deque->mapLenght * 2;
    void*** newMap = malloc(sizeof(void*) * newMapLenght);
    int X = newMapLenght - deque->mapLenght;


    memcpy(&(newMap[X]), deque->map, deque->mapLenght*sizeof(void*));
    free(deque->map);
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
        deque->headBlockIndex = deque->headBlockIndex + distanceToMove;
        deque->tailBlockIndex = deque->tailBlockIndex + distanceToMove;
        return;
    }

    int newMapLenght = deque->mapLenght * 2;
    void*** newMap = malloc(sizeof(void*) * newMapLenght);

    memcpy(newMap, deque->map, deque->mapLenght*sizeof(void*));
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
        deque->headIndex = BLOCKSIZE - 1;
    }
    else {deque->headIndex--;}

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
        if(deque->tailBlockIndex == deque->mapLenght) {
            //map has to be resized...
            resizeMapTail(deque);
        }
        deque->tailBlockIndex--;
        deque->map[deque->tailBlockIndex] = malloc(sizeof(void*) * BLOCKSIZE);
        deque->tailIndex = 0;
    } 
    else {deque->tailIndex++;}

    deque->map[deque->tailBlockIndex][deque->tailIndex] = item;
    deque->elementCounter++;
}

void* deque_pop_front(ctrItems_t* deque) {
    if(deque->elementCounter == 0) {
        printf("Deque is empty!");
        return NULL;
    }
    
    void* ret = deque->map[deque->headBlockIndex][deque->headIndex];
    if(deque->headIndex == BLOCKSIZE - 1) {
        // have to jump back to earlyer block
        deque->headBlockIndex--;
        deque->headIndex = 0;
    }
    else{deque->headIndex--;}
    return ret;
}

void* deque_pop_back(ctrItems_t* deque) {
    if(deque->elementCounter == 0) {
        printf("Deque is empty!");
        return NULL;
    }
    
    void* ret = deque->map[deque->tailBlockIndex][deque->tailIndex];
    if(deque->tailIndex == 0){
        //have to jump back to previous block
        deque->tailBlockIndex++;
        deque->tailIndex = BLOCKSIZE - 1;
    }
    else{deque->tailIndex++;}
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
int main(void) {
    printf("Hello World!\n");

    ctrItems_t myDeque = {.elementCounter = 0};
    printf("0-Done\n");

    deque_add_front(&myDeque, (void*)1);
    printf("1-Done\n");
    deque_add_front(&myDeque, (void*)1);
    printf("2-Done\n");
    deque_add_front(&myDeque, (void*)1);
    printf("3-Done\n");
    deque_add_front(&myDeque, (void*)1);
    printf("4-Done\n");
    void* disp = deque_pop_front(&myDeque);
    printf("Popped: %d\n", (int)disp);



}