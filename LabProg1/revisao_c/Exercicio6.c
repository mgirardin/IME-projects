#include <stdio.h>

int main(){
	int sup;
	int f_bef = 0, f_aft = 1;
	int aux = 0;

	printf("Digite o número de fibonacci desejado:\n");
	scanf("%d", &sup);
	if(sup>=0){
		for(int i = 0; i < sup; i++){
			aux = f_bef;
			f_bef = f_aft;
			f_aft = aux + f_aft;
		}
		printf("%d\n", f_bef);
	}
	else{
		printf("O número inserido deve ser maior ou igual a zero.\n");	
	}

	return 0;
}
