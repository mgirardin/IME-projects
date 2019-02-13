#include <stdio.h>
#include <stdlib.h>

int swap(int *a, int *b){
	int aux = *a;
	*a = *b;
	*b = aux;
	return 0;
}

int bubble(int* array, int length){
	for(int i = 0; i < length; i++){
		for(int j = 0; j < length-1-i; j++){
			if(array[j]>array[j+1]) swap(array+j, array+j+1); 		
		}	
	}
	return 0;
}
	
int main(){
	int length, *array;
	printf("Entre com o número de termos:\n");
	scanf("%d", &length);
	array = malloc(length * sizeof(int));
	if (array == NULL){
		printf("Memória insuficiente.\n");
		return 1;	
	}
	printf("Entre com os termos:\n");
	for(int i = 0; i < length; i++){
		scanf("%d", &array[i]);
	}
	bubble(array, length);
	printf("Sequência ordenada:\n");
	for(int i = 0; i < length; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
	free(array);
	return 0;
}
