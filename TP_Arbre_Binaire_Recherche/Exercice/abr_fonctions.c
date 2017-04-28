#include <abr_fonctions.h>

/*
 * Affichage des ancetres d'un noeud
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
                                                                                   
extern void abr_ancetres_afficher(const abr_t * arbre, noeud_t * noeud, void (*afficher)(const void *)){
                                                                                   
                                                                                   
                ab_ancetres_afficher_bis(arbre->racine, noeud, afficher, 0);       
                resetAffHauteur();                                                 
} 


/* 
 * Creation d'un arbre binaire de travail par dichotomie 
 * a partir d'une liste d'elements generiques
 */
/*
static
err_t abr_dicho_creer_bis( noeud_t * noeud , 
		       	   int rang,
			   liste_t * liste,
			   err_t (*fonction_affectation)( void * e1 , void * e2 ) )	
{ 
  if(rang == 0){
	  return (OK);
  }
  int rang1 = rang / 2;
  void * elem = NULL;
  elem = liste_elem_lire(liste,rang1);
  noeud = noeud_creer(elem,NULL,NULL,fonction_affectation);
  
  abr_dicho_creer_bis(noeud->droit,rang1/2 + rang1,liste,fonction_affectation);
  abr_dicho_creer_bis(noeud->gauche,rang1,liste,fonction_affectation);
  free(noeud);	
  return(OK) ; 
}



extern
err_t abr_dicho_creer( abr_t ** arbre , 
		       err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	
		       err_t (*fonction_destruction)( void * e) ,			
		       int (*fonction_comparaison) ( const void * e1 , const void * e2) ,
		       liste_t * liste )
{ 
  	(*arbre) = abr_creer(fonction_affectation,fonction_destruction,fonction_comparaison);
	int nb = liste_nb_lire(liste);
	printf("NB : %i\n",nb);
	return(abr_dicho_creer_bis((*arbre)->racine,nb,liste,(*arbre)->affecter));
}
*/

void abr_dicho_creer_bis(
				abr_t ** arbre, 
				int i,
				int j,
				liste_t * liste){

	if(i <= j){
		int milieu = (i + j) / 2;
		void * tmp = NULL;

		// Element à insérer dans l'arbre = milieu
		tmp = liste_elem_lire(liste, milieu);
		abr_inserer(*arbre, tmp);

		// On ajoute les valeurs à gauche de milieu
		abr_dicho_creer_bis(arbre, i, milieu - 1, liste);

		// On ajoute les valeurs à droite de milieu
		abr_dicho_creer_bis(arbre, milieu + 1, j, liste);

	}
}

extern err_t abr_dicho_creer(
				abr_t ** arbre,
				err_t (*fonction_affectation)(void * e1, void * e2),
				err_t (*fonction_destruction)(void * e),
				int   (*fonction_comparaison)(const void * e1, const void * e2),
				liste_t * liste)
{ 
	int taille = liste_nb_lire(liste);

	if(*arbre == NULL)
		*arbre = abr_creer(fonction_affectation, fonction_destruction, fonction_comparaison);
	

	abr_dicho_creer_bis(arbre, 0, taille - 1, liste);

	return OK;
}

