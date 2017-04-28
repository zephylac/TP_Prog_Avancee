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
static err_t abr_dicho_creer_bis (noeud_t ** noeud,
    				int rang,
    				void ** liste,
    				err_t (*fonction_affectation) (void * e1, void * e2))
{
    if (rang == 0) return OK;
    int milieu = rang/2;
    (*noeud) = noeud_creer (liste[milieu], NULL, NULL, fonction_affectation);
    abr_dicho_creer_bis (&((*noeud) -> gauche), milieu, liste , fonction_affectation);
    abr_dicho_creer_bis (&((*noeud) -> droit), rang - milieu - 1, liste + milieu + 1,fonction_affectation);
    
    return OK;	
}

extern err_t abr_dicho_creer(
				abr_t ** arbre,
				err_t (*fonction_affectation)(void * e1, void * e2),
				err_t (*fonction_destruction)(void * e),
				int   (*fonction_comparaison)(const void * e1, const void * e2),
				liste_t * liste)
{ 
	int taille = liste_nb_lire(liste);

	*arbre = abr_creer(fonction_affectation, fonction_destruction, fonction_comparaison);
	

	/*abr_dicho_creer_bis(arbre, 0, taille - 1, liste);*/

	return(abr_dicho_creer_bis(&((*arbre)->racine),taille,liste->liste,fonction_affectation));
}
