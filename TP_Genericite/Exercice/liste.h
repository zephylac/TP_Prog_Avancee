#ifndef _LISTE_H_
#define _LISTE_H_

#include <commun.h>

#define LISTE_NULL NULL
#define LISTE_ID_NULL -1

typedef enum {
	qsort_t,
       	bulle_t
} methode_tri_t;

typedef enum {
	croissant,
       	decroissant
} ordre_t;

typedef enum {
	referencement,
       	copie
} methode_elem_t;

typedef struct liste_s
{
  int nb ;		/* Nombre d'objets dans la liste  */
  void ** liste ;	/* liste  des objets */
  err_t (*detruire)(void *);
  err_t (*affectation)(void *, void *);
} liste_t ;

extern unsigned long int liste_cpt  ;

/*
 * FONCTIONS
 */

/*!
 * \name Methodes d'acces 
 * @{
 */

/*! Acces au nombre d'objets */
extern int liste_nb_lire( liste_t * const liste );

/*! Acces a un objets de la liste */
extern void * liste_elem_lire( liste_t * const liste , const int ind );

/*!
 * @}
 * \name Tests 
 * @{
 */

/*! Teste si la liste existe */
extern booleen_t liste_existe( liste_t * const liste) ; 

/*! Teste si la liste est vide (aucun &eacute;l&eacute;ment dedans) */
extern booleen_t liste_vide( liste_t * const liste) ; 

/*!
 * @}
 * \name Methodes d'affectations 
 * @{
 */

/*! Affectation d'un objet */
extern err_t liste_elem_ecrire( liste_t * liste, 
				void * const elem ,
				const int ind ) ;

/*!
 * @}
 * \name Primitives
 * @{
 */

/*!
 * Creation d'une liste 
 */
extern liste_t * liste_creer( const int nb,err_t(*detruire)(void *), err_t(*affectation)(void *, void *));

/*!
 * Destruction d'une liste 
 */

extern err_t liste_detruire( liste_t ** liste) ; 


/*! 
 * \name Affichage
 * @{
 */

/*!
 * Affichage d'une liste sur la sortie standard
 */

extern void liste_afficher( liste_t * const liste , void(*afficher)(void *) );

/*!
 * @}
 */


/*!
 * tri d'une liste 
 */
extern err_t liste_trier( liste_t * liste, int (*comparer)(const void *, const void *), methode_tri_t tri);

/*! @} */
#endif
