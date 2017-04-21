#include <ab_fonctions.h>

/*
 *  * Affichage des ancetres d'un noeud
 */

static booleen_t ab_ancetres_afficher_bis(noeud_t * racine, noeud_t * noeud, void (*afficher)(const void *), int hauteur){
		if(racine == NULL || noeud == NULL || racine == noeud) return FAUX;
		if(racine->gauche == noeud || racine->droit == noeud){
			printf("\n");
			affHauteur(hauteur, VRAI,"┌── ","    ","    ","    ",FAUX);	
			afficher(racine->etiquette);
			return VRAI;
		}
		if(ab_ancetres_afficher_bis(racine->gauche, noeud, afficher, hauteur+1)){
			printf("\n");
			affHauteur(hauteur, VRAI,"┌── ","    ","    ","    ",FAUX);	
			afficher(racine->etiquette);
			return VRAI;
		}
		if(ab_ancetres_afficher_bis(racine->droit, noeud, afficher, hauteur+1)){
			printf("\n");
			affHauteur(hauteur, VRAI,"┌── ","    ","    ","    ",FAUX);	
			afficher(racine->etiquette);
			return VRAI;
		}
		return (FAUX);
}

extern void ab_ancetres_afficher(const ab_t * arbre, noeud_t * noeud, void (*afficher)(const void *)){

		
		ab_ancetres_afficher_bis(arbre->racine, noeud, afficher, 0);	
		resetAffHauteur();		 
}
