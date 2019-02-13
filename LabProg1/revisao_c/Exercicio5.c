#include <stdio.h>

int fibonacci(int n){
	if(n==0){
		return 0;	
	}
	else if (n==1 || n==2){
		return 1;	
	}
	return fibonacci(n-1)+fibonacci(n-2);
}

int main(){
	int n;
	printf("Digite o número de fibonacci desejado:\n");
	scanf("%d", &n);
	int fib = fibonacci(n);
	printf("%d\n", fib);
	return 0;
}
