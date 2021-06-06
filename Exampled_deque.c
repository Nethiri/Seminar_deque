#include <math.h>
#include <stdio.h>

#define MAX 10

void deque_add_front(int *, int, int *, int *); //element added at the front
void deque_add_back(int *, int, int *, int *); //element added at the rear
int deque_del_front(int *, int *, int *); //element deleted at the front
int deque_del_back(int *, int *, int *);  //element deleted at the rear
void deque_display(int *); //displays the deque
int deque_count(int *); //counts the elements of the list



void main() {
    int arr[MAX];
    int front, back, i, n;
    front = back = -1;                      //first inizilize the elements front and rear as unknown
    for(i = 0; i < MAX; i++) {
        arr[i] = 0;                         // placing 0 into the array at each position to have it defined...
    }

    
    deque_add_back(arr, 1, &front, &back);
    //deque_add_front(arr, 2, &front, &back);
    deque_add_back(arr, 3, &front, &back);
    //deque_add_front(arr, 4, &front, &back);
    deque_add_back(arr, 5, &front, &back);
    //deque_add_front(arr, 6, &front, &back);
    deque_add_back(arr, 7, &front, &back);
    //deque_add_front(arr, 8, &front, &back);


    printf("Elements in the Deque: ");
    deque_display(arr);



}

void deque_add_front(int *array, int toadd, int *pfront, int *pback) {
    int i, o, p;
    if(*pfront == 0 && *pback == MAX - 1){  // checks if front and backpointer are in position 0 and MAX - 1
        printf("The Deque is full\n");
        return;
    }

    if(*pfront == -1) {                     // if front / rear are undefined, set a position and begin a list
        *pfront = *pback = 0;               // sets front / rear pointer to 0
        array[*pfront] = toadd;             // sets at the position of front pointer the newly to add item
        return;                             // returns the function
    }

    if(*pfront != MAX - 1){                 // if the front pointer is pointint to anything but the last possible position
        i = deque_count(array);             // count through the array
        o = *pback + 1;                     // add to the rearpointer 1
        for(p = 1; p <= i; p++){            // count through the array
            array[o] = array[o-1];          // re-order the array, beginning with the rear pointer one to the left
            o--;
        }
        array[o] = toadd;                   // adds the new item to the front position
        *pfront = o;                        // sets the front pointer
        (*pback)++;                 
    }   else{                               // if the previous statement is incorrect
        (*pfront)--;                        // adds the element to add at the position of the front pointer (minus 1)
        array[*pfront] = toadd;
    }
}

void deque_add_back(int *array, int toadd, int *pfront, int *pback) {
    int i, o;
    if(*pfront == 0 && *pback == MAX - 1){  // checks if front and backpointer are in position 0 and MAX - 1
        printf("The Deque is full\n");
        return;
    }

    if(*pfront == -1) {                     // if the front pointer is undefined, set a position and begin a list
        *pback = *pfront = 0;               // defines front and rear pointer               
        array[*pback] = toadd;              // places the item to add in the position of the rear pointer
        return;                             
    }

    if(*pback == MAX -1) {
        i = *pfront - 1;
        for(o = *pfront - 1; o < *pback; o++){
            i = o;
            if(i == MAX - 1){
                array[i] = 0;
            }   else {
                array[i] = array[o + 1];
            }
            (*pback)--;
            (*pfront)--;
        }
        (*pback)++;
        array[*pback] = toadd;
    }
}

int deque_del_front(int *array, int *pfront, int *pback) {
    int toDel;
    if(*pfront == -1) {
        printf("The Deque is empty!\n");
        return 0;
    }

    toDel = array[*pfront];
    array[*pfront] = 0;
    
    if(*pfront == *pback){
        *pfront = *pback = -1;
    } else {
        (*pfront)++;
    }
    return toDel;
}

int deque_del_rear(int *array, int *pfront, int *pback) {
    int toDel;
    if(*pfront == -1){
        printf("The Deque is empty!\n");
        return 0;
    }

    toDel = array[*pback];
    array[*pback] = 0;
    (*pback)--;
    if(*pback == -1){
        *pfront = -1;
    }
    return toDel;
}

void deque_display(int *array) {
    int i;
    printf("Front: ");
    for(i = 0; i < MAX; i++){
        printf(" %d", array[i]);
    }
    printf(" :rear");
}

int deque_count(int *array) {
    int c = 0;
    int i;
    for(i = 0; i<MAX; i++){
        if(array[i] != 0){
            c++;
        }
    }
    return c;
}

