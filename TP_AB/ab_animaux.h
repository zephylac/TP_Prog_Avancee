#ifndef _AB_ANIMAUX_H_
#define _AB_ANIMAUX_H_
/*
 * Definition Arbre Binaire des animaux
 */

#include <ab.h>
#include <mystring.h>

/*
 * Affichage 
 */

extern void ab_animaux_afficher( const ab_t * arbre , 
				 void (*fonction_affichage)(const void *)) ;

/*
 * Reconnaissance 
 */

extern void ab_animaux_reconnaitre( ab_t * arbre , 
				    noeud_t * noeud,
				    noeud_t * pere,
				    err_t (*fonction_affectation)(void * , void *) ,
				    void (*fonction_affichage)(const void *)) ;
#endif
