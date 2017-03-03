#ifndef _PERSONNE_H_
#define _PERSONNE_H_

#include <objet.h>
#include <individu.h>

/*
 * DEFINITION OBJET "INDIVIDU"  
 */

typedef struct personne_s 
{
  /*void (*afficher)(struct personne_s * elem);
  err_t (*detruire)(struct personne_s ** elem);
  */
  #include <attributs_individu.h>	
  char * adresse;
  char * ville;
} personne_t;


/*
 * VARIABLE LOCALE
 * declaration du compteur d'objets individu_t comme variable externe
 * pour compter les references sur ces objets 
 */

extern unsigned long int personne_cpt  ;

/* 
 * FONCTIONS
 */
extern personne_t * personne_creer(char * nom, char * prenom , char * adresse, char * ville ) ;
extern booleen_t personne_existe( personne_t * const personne ) ;

#endif
