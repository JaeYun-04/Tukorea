#include <stdio.h>
#include <stdlib.h>

static Element data[MAX_SIZE];
static int front = 0;
static int rear = 0;

void error(char* str) {
    printf("%s\n", str);
    exit(1);
}

void init_queue() {
    front = rear = 0;
}

int is_empty() {
    return front == rear;
}

int is_full() {
    return front == (rear + 1) % MAX_SIZE;
}


void enqueue(Element val) {
    if (is_full())
        error("Overflow Error!"); 
    rear = (rear + 1) % MAX_SIZE;
    data[rear] = val;
}

Element dequeue() {
    if (is_empty())
        error("Underflow Error!");
    front = (front + 1) % MAX_SIZE;
    return data[front];
}

Element peek() {
    if (is_empty())
        error("Underflow Error!");
    return data[(front + 1) % MAX_SIZE];
}

