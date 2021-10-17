#include <stdio.h>
#define MAX 15
//update
typedef struct deque {
    int front, back;
    void* array[MAX];
} deque_t; 

void deque_add_front(void*, deque_t*);              // adds an element to the front
void deque_add_back(void*, deque_t*);               // adds an element to the back
void* deque_del_front(deque_t*);                    // deletes an element from the front (and returns the element)
void* deque_del_back(deque_t*);                     // deletes an element from the back (and returns the element)
void deque_display_int(deque_t*);                   // displays the deque
int deque_count(deque_t*);                          // counts the amount of elements in the que
void* deque_look_front(deque_t*);                   // returns the front element       
void* deque_look_back(deque_t*);                    // retunrs the back element

void main() {
    deque_t myTestingQue = {.front = -1};

    printf("\nCreate Deque and add first item into it:");
    deque_add_back((void*)1,&myTestingQue);
    deque_display_int(&myTestingQue);

    printf("\nNow, lets add a few more objects both to the front and back");
    deque_add_front((void*)2,&myTestingQue);
    deque_add_back((void*)3,&myTestingQue);
    deque_add_front((void*)4,&myTestingQue);

    deque_display_int(&myTestingQue); // more elements

    deque_add_back((void*)5,&myTestingQue);
    deque_add_front((void*)6,&myTestingQue);
    deque_add_back((void*)7,&myTestingQue);
    deque_add_front((void*)8,&myTestingQue);

    deque_display_int(&myTestingQue); // more elements

    deque_add_back((void*)9,&myTestingQue);
    deque_add_front((void*)10,&myTestingQue);
    deque_add_back((void*)11,&myTestingQue);
    deque_add_front((void*)12,&myTestingQue);

    deque_display_int(&myTestingQue); // more elements

    deque_add_back((void*)13,&myTestingQue);
    deque_add_front((void*)14,&myTestingQue);
    deque_add_back((void*)15,&myTestingQue);
    deque_add_front((void*)16,&myTestingQue);

    printf("Now The Deque is full, the last item ('16') could not have been added...");
    deque_display_int(&myTestingQue);

    printf("\nNow, lets remove some from the back to see how it behaves...");
    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);

    deque_display_int(&myTestingQue);

    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);

    deque_display_int(&myTestingQue);

    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);

    deque_display_int(&myTestingQue);

    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);
    deque_del_back(&myTestingQue);
    printf("Now, we've emptied the que, just by deleating from tha back...");    
    deque_display_int(&myTestingQue);

    printf("\nNow, lets add some again :D");
    deque_add_front((void*)1,&myTestingQue);
    deque_display_int(&myTestingQue);
    deque_add_front((void*)2,&myTestingQue);
    deque_display_int(&myTestingQue);
    deque_add_front((void*)3,&myTestingQue);
    deque_display_int(&myTestingQue);
    deque_add_front((void*)4,&myTestingQue);
    deque_display_int(&myTestingQue);
    
    printf("\n");
}

void deque_add_front(void* value, deque_t* myQue){
    if(myQue->front == -1) {                        // check if my frontpointer is undefined
        myQue->front = myQue->back = 0;             // if so, I set on position 0
        myQue->array[myQue->front] = value;         // and place the object I tried to save in the initial position
        return;                                     // returns the function
    }
    if(myQue->front + 1 % MAX == myQue->back) {     // if, when I try the front pointer + 1 % MAX == back pointer, then my deque is full
        printf("\nThe Deque is full!\n");
        return;
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
    if(myQue->front == -1){                         // check if my frontpointer is undefined
        myQue->front = myQue->back = 0;             // if so, then set position 0
        myQue->array[myQue->front] = value;         // and place the object I tried to save in the initial position
        return;                                     // returns the function
    }

    if(myQue->front + 1 % MAX == myQue->back) {     // if, when I try the front pointer + 1 % MAX == back pointer, then my deque is full
        printf("\nThe Deque is full!\n");
        return;
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
        printf("\nThe Deque is empty!\n");          // if not, state error to the user
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
    void* toDel;
    if(myQue->front == -1){                         // check if the front pointer is defined
        printf("\nThe Deque is empty!\n");          // if not, state error to the user
        return 0;                                   // returns the function
    }
    toDel = myQue->array[myQue->back];              // gets the date which is to be deleted
    myQue->array[myQue->back] = NULL;               // pointles display operation -> you just have to move the pointer

    if(myQue->front == myQue->back) {               // checks if both pointer point to the same position
        myQue->front = myQue->back = -1;            // if so, this is the last entry, resets pointer to undefined
    }   else{                                       // of the pointers are difrent
        myQue->back++;                              // increment the back pointer
        if(myQue->back == MAX){                     // if the pointer overflows
            myQue->back = 0;                        // set pointer to 0;
        }
    }
    return toDel;                                   // returns the function with the deleted value
}

void deque_display_int(deque_t* myQue) {            
    printf("\nArray Front: ");                            // Prints the beginning of the que
    for(int i = 0; i < MAX; i++){                   // loop through the que
        printf(" %d", myQue->array[i]);             // prints the position of the que
        if(myQue->array[i] == myQue->array[myQue->front] ){
            printf("F");
        }
        if(myQue->array[i] == myQue->array[myQue->back] ){
            printf("B");
        }

    }   
    printf(" :Array Back\n");                             // prints the end of the list

    //todo display wo der pointer ist


}

int deque_count(deque_t* myQue) {
    int c = 0;                                      // declaration of counting variable
    for(int i = 0; i < MAX; i++){                   // loop through que
        if(myQue->array[i] != NULL){                // check if entry in que is an entry or is empty
            c++;                                    // if so, increase counting variable
        }
    }
    return c;                                       // returns function with the counting variable
}

void* deque_look_front(deque_t* myQue) {
    if(myQue->front == -1){                         // check if the front pointer is defined
        printf("\nThe Deque is empty!\n");          // if not, state error to the user
        return 0;                                   // returns the function
    }
    return myQue->array[myQue->front];              // returns the function with the front element
}

void* deque_look_back(deque_t* myQue) {
    if(myQue->front == -1){                         // check if the front pointer is defined
        printf("\nThe Deque is empty!\n");          // if not, state error to the user
        return 0;                                   // returns the function
    }
    return myQue->array[myQue->back];               // returns the function with the back element
}