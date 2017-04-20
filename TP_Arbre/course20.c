#include "arbre.h"
#include "course20.h"

int max(int a, int b){
	if(a > b){
		return a;
	}
	return b;
}

int min(int a, int b){
	if(a > b){
		return b;
	}
	return a;
}

int humain_joue(int course){
	int a;
	int b;
	int c;
	if(20 - course <= 3)
		return -1;
	
	a = ordi_joue(course + 1);
	b = ordi_joue(course + 2);
	c = ordi_joue(course + 3);
	
	return min( min(a,b),c);
}

int ordi_joue(int course){
	int a;
	int b;
	int c;
	if(20 - course <= 3)
		return 1;
	
	a = humain_joue(course + 1);
	b = humain_joue(course + 2);
	c = humain_joue(course + 3);
	
	return(max( max(a,b),c));
}

int min_max(int course){
	int a;
	int b;
	int c;

	if(20 - course <= 3)
		return 20-course;
	
	a = humain_joue(course + 1);
	b = humain_joue(course + 2);
	c = humain_joue(course + 3);
	
	return max(1,max(max(a,b),c));
}



int tourJoueur(){
	int n = 0;
	while(n > 3 || n < 1){
		printf("Sélectionner un chiffre entre 1 et 3 : ");
		scanf("%i",&n);
	}
	printf("Le joueur joue %i ",n);
	return n;
}

int tourOrdi(int course){
	int n;
	if(course > 16){
		n = 20 - course;
	}
	else{
		n = min_max(course);
	}
	printf("L'ordinateur joue %i ",n);
	return n;
}

int main(){
	int tour;
	int total = 0;
	while(1){
		/* Joueur */
		tour = 0;
		total += tourJoueur();
		printf("Total : %i\n",total);

		if(total == 20){
			break;
		}
		

		/* Ordinateur */

		tour = 1;
		total += tourOrdi(total);
		printf("Total : %i\n",total);

		if(total == 20){
			break;
		}
	}

	if(tour){
		printf("L'ordinateur gagne\n");
	}
	else{
		printf("Le joueur gagne\n");
	}
	return 1;
}

