#include <stdio.h>

int fibo(int n){
	int temp;
	if(n == 1 || n == 0){
		return 1;
	}
	else{
		temp = (fibo(n - 2)+fibo(n - 1));
		printf("Pour n=%i -> res = %i\n",n,temp);
		return temp;
	}
}

int fibo_iter1(int n){
	int tab[n], i;
	tab[0] = 1;
	tab[1] = 1;
	for(i = 2; i < n; i++){
		tab[i] = tab[i -1] + tab[i -2];
	}
	return tab[i-1];
}

int fibo_iter2(int hauteur){
	int i,n,n1,n2;
	n2 = 1;
        n2 = 1;

	for(i = 0; i < hauteur; i++){
		n = n1 + n2;
		n2 = n1;
		n1 = n;
	}
	return n;
}



int main(){
	int res;
	res = fibo(5-1);
	printf("Resultat : %i\n",res);

	res = fibo_iter1(5);
	printf("Resultat : %i\n",res);

	res = fibo_iter2(5);
	printf("Resultat : %i\n",res);



	return 1;
}




