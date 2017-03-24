#include <stdio.h>

int factorielle(int n){
	int temp = 1;
	if(n == 1){
		return 1;
	}
	temp = n * factorielle(n - 1);
	printf("%i! -> res = %i\n",n,temp);
	return temp;
}

int main(){
	int res;

	res = factorielle(4);
	printf("Resultat : %i\n",res);
return 1;	
}
