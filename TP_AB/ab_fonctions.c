#include <ab_fonctions.h>

/*
 * Affichage des ancetres d'un noeud
 */

static booleen_t ab_ancetres_afficher_bis(const noeud_t * racine, noeud_t * n, void (*afficher)(const void *)){
	
	if(n != NULL){

		if(n == racine){
			afficher(n);
			return (VRAI);
		}
		else {
			
			return ab_ancetres_afficher_bis(racine->gauche, n, afficher) || ab_ancetres_afficher_bis(racine->droit, n, afficher);
		
		}

	}

	return (FAUX);
}

extern void ab_ancetres_afficher(const ab_t * arbre, noeud_t * noeud, void (*afficher)(const void *)){

	ab_ancetres_afficher_bis(arbre->racine, noeud, afficher);	
 
}

