#include <stdio.h>

int print_even(int sup){
	printf("%d ", (sup%2==0) ? sup-2 : sup-1);
	if(sup>4) return print_even(sup-2);
	else return 0;
}

int main(){
	int sup;
	printf("Digite o limite superior desejado:\n");
	scanf("%d", &sup);
	print_even(sup);
	printf("\n");
	return 0;
}
