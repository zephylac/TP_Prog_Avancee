#include <stdio.h>

int nb_chiffre(int n, int test){
	if(n - test > 0){
		return 1 + nb_chiffre(n, test * 10);
	}
	return 0;
}

int main(){
	int res = 0;
	res = nb_chiffre(1789,1);
	printf("Resultat : %i\n",res);
	return 1;
}
