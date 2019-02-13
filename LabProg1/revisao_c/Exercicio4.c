#include <stdio.h>

int main(){
	FILE *fptr;
	int number, count_m = 0, count_f = 0;
	int sum_m = 0, sum_f = 0;
	char c;
	fptr = fopen("textfile.txt", "r"); 
	if(fptr == NULL){
		printf("Arquivo não encontrado.\n");
		return 1;
	}
	
	while(fscanf(fptr,"%c %d\n", &c ,&number) != EOF){
		printf("%c %d\n", c, number);
		if(c == 'M'){
			count_m++;
			sum_m += number;	
		}
		else{
			count_f++;
			sum_f += number;
		}		
	}
	if((float)sum_m/count_m < (float)sum_f/count_f){
		printf("F %.1f\n", (float)sum_f/count_f);
	}
	else{
		printf("M %.1f\n", (float)sum_m/count_m);	
	}

	fclose(fptr);
	return 0;
}
