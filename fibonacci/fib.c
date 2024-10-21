#include <stdio.h>

int fibonaccirecur(int n);
int fibonacciiter(int n);

int main(void){
    int n = 100;
    printf("%d", fibonaccirecur(n));
    return 0;
}

int fibonaccirecur(int n){
    if(n == 0) return 0;
    else if (n == 1) return 1;
    return fibonaccirecur(n-1) + fibonaccirecur(n-2);  
}

int fibonacciiter(int n){
    int t, atual, ant, c;
    if(n <= 1) return 1;
    ant = 1;
    atual = 1;
    c = 2;
    while(c <= n){
        t = atual + ant;
        ant = atual;
        atual = t;
        c ++;
    }
    return t;
}