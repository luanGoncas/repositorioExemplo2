#include <stdlib.h>
#include <stdio.h>

//Recursive mode of Fibonacci sequence

int fibonacciRec(int n){
	if(n < 2){
		return n;
	}else{
		return fibonacciRec(n - 1) + fibonacciRec(n - 2);
	}
}

//Iterative mode of Fibonacci sequence

int fibonacciIte(int n){
	int i = 1, j = 0, t;
	for(int k = 0; k < n - 1; k++){
		t = i + j;
		i = j;
		j = t;
	}
	return j;
}

//Divide and conquer mode of Fibonacci sequence

int fibonacciDiv(int n){
	if(n <= 0){
		return 0;
	}
	int i = n - 1;
	int a = 1, b = 0, c = 0, d = 1;
	while(i > 0){
		if(i % 2 == 0){
			a = d*b + c*a;
			b = d*(b + a) + c*b;
			c = c*c + d*d;
			d = d*(2*c + d);
		}
		i = i/2;
	}
	return a + b;
}

int main(){
	int n;

	printf("Digite um numero ");
	scanf("%d", &n);

	printf("Fibonacci recursivo:  %d\n", fibonacciRec(n));
	printf("Fibonacci iterativo: %d\n", fibonacciIte(n));
	printf("Fibonacci divisao e conquista: %d\n", fibonacciDiv(n));

	return 0;
}