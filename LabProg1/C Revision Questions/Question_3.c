#include <stdio.h>

int main(){
	FILE *fptr;
	int number, count = 0;
	int sum =0, prod = 1;
	fptr = fopen("textfile.txt", "r"); 
	if(fptr == NULL){
		printf("Arquivo não encontrado.\n");
		return 1;
	}
	
	while(fscanf(fptr,"%d", &number) != EOF){

		if(count%2==0) prod *= number;
		else sum += number;
		count += 1;		
	}
	printf("Produto dos pares: %d\n", prod);
	printf("Soma dos ímpares: %d\n", sum);

	fclose(fptr);
	return 0;
}
