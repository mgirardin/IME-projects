#include <stdio.h>
#include <stack>
using namespace std;

#define NOT_VALID "Essa movimentação não é válida!\n\n"
#define VALID "Movimentação realizada!\n\n"
#define CONGRATS "Parabéns, você ganhou!\n"

//Prints the 3 tower structures
int layout(stack<int> a, stack<int> b, stack<int> c, int size){
	int size_a = a.size(), size_b = b.size(), size_c = c.size();
	int tmp_a, tmp_b, tmp_c;
	int i, j;
	for(i = 0; i < size+1; i++){
		printf("\t\t\t\t");
		if(size_a + i >= size+1){
			tmp_a = a.top();
			a.pop();
			for(j = 0; j<tmp_a; j++){
				printf("\b");			
			}
			for(j = 0; j<tmp_a; j++){
				printf("-");			
			}
			printf("|");	
			for(j = 0; j<tmp_a; j++){
				printf("-");			
			}
			printf("\t\t");
		}	
		else{
			printf("|");
			printf("\t\t");
		}

		if(size_b + i >= size+1){
			tmp_b = b.top();
			b.pop();
			for(j = 0; j<tmp_b; j++){
				printf("\b");			
			}
			for(j = 0; j<tmp_b; j++){
				printf("-");			
			}
			printf("|");	
			for(j = 0; j<tmp_b; j++){
				printf("-");			
			}
			printf("\t\t");
		}	
		else{
			printf("|");
			printf("\t\t");
		}	
		if(size_c + i >= size+1){
			tmp_c = c.top();
			c.pop();
			for(j = 0; j<tmp_c; j++){
				printf("\b");			
			}
			for(j = 0; j<tmp_c; j++){
				printf("-");			
			}
			printf("|");	
			for(j = 0; j<tmp_c; j++){
				printf("-");			
			}
		}	
		else{
			printf("|");
		}
		printf("\n");
	}
	return 0;
}
//Pops the top element from stack a and pushes it to stack b if allowed
bool swap_top(stack<int>& a, stack<int>& b){
	int tmp = (a.empty() ? 0 : a.top()), tmp2 = (b.empty() ? 0 : b.top());
	
	if (!tmp){
		return false;	
	}
	else if(b.empty() || tmp < tmp2){
		a.pop();
		b.push(tmp);
		return true;		
	}
	else return false;
}
int main(){
	int tout, tin, done = 0, chose = 0;
	stack<int> first, second, third;
	int size;
	while(chose == 0){
		printf("Escolha o número de peças do seu jogo (até 6 peças):\n");
		scanf("%d", &size);
		if (size>=1 && size<=6){
			chose = 1;		
		}
		else printf("Você não pode escolher esse número!\n");
	}
	
	for(int i=size; i>=1; i--){
		first.push(i);	
	}

	while(!done){
		printf("\n");
		layout(first, second, third, size);
		printf("Digite a sua movimentação:\n");
		scanf(" %d %d", &tout, &tin);

		if(tin==tout || tin>3 || tout>3 || tin<1 || tout<1){	
			printf(NOT_VALID);
		}
		else if(tout == 1){
			if (tin == 2){
				if(!swap_top(first, second)){
					printf(NOT_VALID);
				}
				else{
					printf(VALID);
				}
			}
			else if (tin == 3){
				if(!swap_top(first, third)){
					printf(NOT_VALID);
				}
				else{
					printf(VALID);
				}
			}		
		}
		else if(tout == 2){
			if (tin == 3){
				if(!swap_top(second, third)){
					printf(NOT_VALID);
				}
				else{
					printf(VALID);
				}
			}
			else if(tin ==1) {
				if(!swap_top(second, first)){
					printf(NOT_VALID);
				}
				else{
					printf(VALID);
				}
			}		
		}
		else{
			if (tin == 1){
				if(!swap_top(third, first)){
					printf(NOT_VALID);
				}
				else{
					printf(VALID);
				}
			}
			else if (tin == 2){
				if(!swap_top(third, second)){
					printf(NOT_VALID);
				}
				else{
					printf(VALID);
				}
			}
					
		}

		if(first.empty() && (second.empty() || third.empty())){
			done = 1;		
		}
	}
	layout(first, second, third, size);
	printf(CONGRATS);
	return 0;
}
