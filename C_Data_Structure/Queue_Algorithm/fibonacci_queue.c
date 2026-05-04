#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 5
typedef int Element;
#include "CircularQueue_lab.h"

int fibonacci(int n){

    if(n <= 1) return n;

    init_queue();
    enqueue(0);
    enqueue(1);
    for(int i = 2; i<= n; i++){
        int n1= dequeue();
        int n2 = peek();
        enqueue(n1+n2);
    }
    dequeue();
    return dequeue();
}

void main(){
    printf("피보나치 수열: ");
    
    for(int i = 0; i < 16; i++){
        printf("%d,",fibonacci(i));
    }
    printf("\n\n");
}