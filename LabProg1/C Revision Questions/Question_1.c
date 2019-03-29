#include <stdio.h>

int main(){
	int sup;
	printf("Digite o limite superior desejado:\n");
	scanf("%d", &sup);
	printf("Os números pares até o limite são:\n");
	for(int i = 2; i < sup; i+=2){
		printf("%d ", i);
	}
	printf("\n");
	return 0;
}
