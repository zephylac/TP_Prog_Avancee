#ifndef _LISTE_SDD_H_
#define _LISTE_SDD_H_

#include <commun.h>
#include <objet.h>


#define LISTE_NULL NULL
#define LISTE_ID_NULL -1


typedef struct liste_s
{
  int nb ;		/* Nombre d'objets dans la liste  */
  objet_t ** liste ;	/* liste  des objets */
} liste_t ;

typedef struct liste_objet_s
{
  int (*liste_nb_lire)(struct liste_objet_s *);
  objet_t * (*liste_elem_lire)(struct liste_objet_s *, const int);
  booleen_t (*liste_vide)(struct liste_objet_s *);
  err_t (*liste_elem_ecrire)(struct liste_objet_s *, objet_t *, const int);
  err_t (*liste_detruire) (struct liste_objet_s **);
  void (*liste_afficher)(struct liste_objet_s *, const char);

  int nb ;		/* Nombre d'objets dans la liste  */
  objet_t ** liste ;	/* liste  des objets */
} liste_objet_t ;



#endif
