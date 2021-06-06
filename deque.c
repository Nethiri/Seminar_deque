#include <stdio.h>
#define MAX 10

typedef struct deque {
    int front, back;
    void* array[MAX];
} deque_t;

void deque_add_front(void*, deque_t*);
void deque_add_back(void*, deque_t*);
void* deque_del_front(deque_t*);
void* deque_del_back();
void deque_display();
int deque_count();



void main() {

}

void deque_add_front(void* value, deque_t* myQue){
    if(myQue->front + 1 % MAX == myQue->back) {     // if, when I try the front pointer + 1 % MAX == back pointer, then my deque is full
        printf("The Deque is full!\n");
        return;
    }

    if(myQue->front == -1) {                        // check if my frontpointer is undefined
        myQue->front = myQue->back = 0;             // if so, I set on position 0
        myQue->array[myQue->front] = value;         // and place the object I tried to save in the initial position
        return;                                     // returns the function
    }
    
    if((myQue->front + 1) % MAX){                   // if the front pointer is somewhere in the array (not causing an overflow)
        myQue->front++;                             // add to the front pointer + 1 
        myQue->array[myQue->front] = value;         // place data at the new front pointers position
    }   else {                                      // if the front pointer is at the end of the array (causing an overflow)
        myQue->front = 0;                           // brint front pointer to the beginning of the array
        myQue->array[myQue->front] = value;         // place data at the new front pointers position
    }
    return;                                         // returns the function
}

void deque_add_back(void* value, deque_t* myQue){
    if(myQue->front + 1 % MAX == myQue->back) {     // if, when I try the front pointer + 1 % MAX == back pointer, then my deque is full
        printf("The Deque is full!\n");
        return;
    }

    if(myQue->front == -1){                         // check if my frontpointer is undefined
        myQue->front = myQue->back = 0;             // if so, then set position 0
        myQue->array[myQue->front] = value;         // and place the object I tried to save in the initial position
        return;                                     // returns the function
    }

    if((myQue->back - 1) % MAX == -1){              // checks if my back pointer under?flows
        myQue->back = MAX - 1;                      // if so, set the backpointer to the last position
        myQue->array[myQue->back] = value;          // place data at the last position
    }   else{                                       // if the back pointer does not produce an overflow
        myQue->back--;                              // decrement backpointer by 1
        myQue->array[myQue->back] = value;          // place data ath the new back pointer position
    }
    return;                                         // returns the function
}

void* deque_del_front(deque_t* myQue) {
    void* toDel;
    if(myQue->front == -1){                         // check if the front pointer is defined
        printf("The Deque is empty!\n");            // if not, state error to the user
        return 0;                                   // returns the function
    }
    toDel = myQue->array[myQue->front];             // gets the data which is to be deleted
    myQue->array[myQue->front] = NULL;              // pointles display operation -> you just have to move the pointer

    if(myQue->front == myQue->back) {               // checks if both pointer point to the same position
        myQue->front = myQue->back = -1;            // if so, this is the last entry, resets pointer to undefined
    }   else{                                       // if the pointers are difrent
        myQue->front--;                             // decrement front pointer
        if(myQue->front == -1) {                    // if front pointer underflows
            myQue->front = MAX -1;                  // set front pointer to MAX - 1;
        }  
    }
    return toDel;                                   // returns the function with the deleted value
}

void* deque_del_back(deque_t* myQue) {
    
}


