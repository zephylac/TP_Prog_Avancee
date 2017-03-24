#include <stdio.h>

/*	while(mot[ind1] == ' ' && ind1 < ind2){
		ind1++;
	}
	while(mot[ind2] == ' '&& ind2 > ind1){
		ind2--;
	}
*/


int palin(char * mot, int ind1, int ind2){
	if(ind1 < ind2){
		if(mot[ind1] == mot[ind2]){
			return palin(mot,(ind1++),(ind2--));
		}
		else{
			return 0;
		}
	}
	else{
		return 1;
	}	
	
}



int palin_iter(char * mot, int taille){
	int res = 1;
	int i,j;
	for(i = 0, j= taille -1 ; i < j;i++, j--){
		while(mot[i] == ' '){
			i++;
		}
		while(mot[j] == ' '){
			j--;
		}
		if(mot[i] == mot[j]){
			res = res * 1;
		}
		else{
			res = res * 0;
		}
	}
	return res;
}



int main(){
	int res;
	
	res = palin("ABCBA",0,5-1);
	( res ? printf("Palindrome\n") : printf ("Pas Palindrome\n") )  ;

	res = palin("ESOPERESTEETSEREPOSE",0,20-1);
	( res ? printf("Palindrome\n") : printf ("Pas Palindrome\n") )  ;


	res = palin("ESOPE RESTE ET SE REPOSE",0,24-1);
	( res ? printf("Palindrome\n") : printf ("Pas Palindrome\n") )  ;

	return 1;
}

