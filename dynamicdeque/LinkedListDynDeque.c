#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 0  head 
// 1   ||
// 2   ||
// 3  tail 
// 4


typedef struct DequeItem{
    struct DequeItem* previous;
    void* data;
    struct DequeItem* next;
} DequeItem_t;

typedef struct LinkedDeque{
    DequeItem_t* head;
    DequeItem_t* tail;
    int elementCount;
} LinkedDeque_t;

LinkedDeque_t createDeque() {
    LinkedDeque_t deque;
    deque.elementCount = 0;
    deque.head = NULL;
    deque.tail = NULL;
    return deque;
}

void Deque_add_front(LinkedDeque_t* deque, void* item) {
    //construct a new head
    DequeItem_t* newHead = malloc(sizeof(DequeItem_t));
    newHead->data = item;
    newHead->next = deque->head;
    newHead->previous = NULL;
    //set old head
    if(deque->head == NULL) {
       deque->head = newHead; 
       deque->tail = newHead;
       deque->elementCount++;
    }
    else{
        deque->head->previous = newHead;
        deque->head = newHead;
        deque->elementCount++;
    }
    
}

void Deque_add_back(LinkedDeque_t* deque, void* item) {
    //construct a new tail
    DequeItem_t* newTail = malloc(sizeof(DequeItem_t));
    newTail->data = item;
    newTail->next = NULL;
    newTail->previous = deque->tail;
    //set old tail
    if(deque->tail == NULL) {
        deque->head = newTail;
        deque->tail = newTail;
        deque->elementCount++;
    }
    else{
        deque->tail->next = newTail;
        deque->tail = newTail;
        deque->elementCount++;
    }
}

void* Deque_pop_front(LinkedDeque_t* deque) {
    if(deque->elementCount == 0) {
        printf("Deque is Empty!");
        return NULL;
    }
    void* ret = deque->head->data;
    
    DequeItem_t* newHead = deque->head->next;
    free(deque->head);
    deque->head = newHead;  
    deque->elementCount--;
    return ret;
}

void* Deque_pop_back(LinkedDeque_t* deque) {
    if(deque->elementCount == 0) {
        printf("Deque is Empty!");
        return NULL;
    }
    void* ret = deque->tail->data;
    DequeItem_t* newTail = deque->tail->previous;
    free(deque->tail);
    deque->tail = newTail; 
    deque->elementCount--;
    return ret;
}

void testFunktion() {
    LinkedDeque_t myDeque = createDeque();
    Deque_add_front(&myDeque, (void*)1);
    Deque_add_front(&myDeque, (void*)2);
    Deque_add_front(&myDeque, (void*)3);
    Deque_add_front(&myDeque, (void*)4);    
    printf("Popped: %d\n", Deque_pop_back(&myDeque));
    printf("Popped: %d\n", Deque_pop_back(&myDeque));
    printf("Popped: %d\n", Deque_pop_back(&myDeque));
    printf("Popped: %d\n", Deque_pop_back(&myDeque));

    printf("Done\n");
}

int TESTLENGH = 10000000;
void Benchmark() {
    LinkedDeque_t myDeque = createDeque();
    clock_t begin = clock();
    for(int i = 0; i < TESTLENGH; i++) {
        Deque_add_front(&myDeque, (void*)i);
    }
    clock_t end = clock();
    double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("Execution time: %f in sec\n", time_spent);
}

int main(void) {
    Benchmark();
}