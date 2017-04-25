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



extern
err_t abr_dicho_creer( abr_t ** arbre , 
		       err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	
		       err_t (*fonction_destruction)( void * e) ,			
		       int (*fonction_comparaison) ( const void * e1 , const void * e2) ,
		       liste_t * liste )
{ 
  booleen_t fin = FAUX;
  int nb = liste_nb_lire(liste);
  int rang1 = nb / 2;
  int rang2 = nb/ 2;
  abr_inserer(arbre,liste_elem_lire(liste,rang1));
  while (!fin){
  	if(r
	rang1 = rang1/2;
  	abr_inserer(arbre,liste_elem_lire(liste,rang1));
  	
	rang2 = rang2 + rang2/2;
	abr_inserer(arbre,liste_elem_lire(liste,rang2));
	
  return(OK) ; 
}

