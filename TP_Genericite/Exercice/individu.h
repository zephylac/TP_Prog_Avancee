#ifndef _INDIVIDU_H_
#define _INDIVIDU_H_

/*
 * DEFINITION OBJET "INDIVIDU"  
 */

#include <commun.h>

typedef struct individu_s 
{
  char * nom ;
  char * prenom ;
} individu_t ;

/*
 * VARIABLE LOCALE
 * declaration du compteur d'objets individu_t comme variable externe
 * pour compter les references sur ces objets 
 */

extern unsigned long int individu_cpt  ;

/* 
 * FONCTIONS
 */

extern individu_t * individu_creer(char * const prenom , char * const nom ) ;

extern booleen_t individu_existe( individu_t * const individu ) ;

extern err_t individu_detruire( individu_t ** individu ) ;
extern err_t individu_effacer( individu_t ** individu ) ;

extern void individu_afficher( individu_t * const individu ) ;

extern int individu_comparer( const individu_t * const ind1 , const individu_t * const ind2 ) ;

extern err_t individu_referencer( individu_t ** ind_cible ,  individu_t * ind_source ) ;
extern err_t individu_copier( individu_t ** ind_cible ,  individu_t * ind_source ) ; 

extern err_t ind_eff(void * ind);
extern err_t ind_det(void * ind);
extern void ind_aff(void * const ind);
extern err_t ind_cp(void * ind1, void * ind2);
extern err_t ind_rf(void * ind1, void * ind2);
extern int ind_cmp(const void * ind1, const void * ind2);
extern int ind_cmp_rev(const void * ind1, const void * ind2);

#endif
