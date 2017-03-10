#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <liste.h>


/*
 * VARIABLE LOCALE
 */

unsigned long int liste_cpt = 0 ; 

/*
 * Methodes d'acces 
 */

/* Nombre d'elements */

extern 
int liste_nb_lire( liste_t * const liste )
{
  return(liste->nb );
} 

/* -- Acces individuel a un element */

extern 
void * liste_elem_lire( liste_t * const liste  , const int ind )
{
  if( (ind < 0) || (ind > liste_nb_lire(liste)-1 ) )
    {
      fprintf( stderr , "liste_elem_lire: mauvais indice d'element [%d] (devrait etre dans [%d..%d])\n",
	       ind , 0 , liste_nb_lire(liste)-1 );
      return(NULL);
    }

  return( liste->liste[ind] ) ;
}

/*
 * Tests 
 */

extern 
booleen_t liste_existe( liste_t * const liste )
{
  if( liste == NULL )
    {
      return(FAUX) ; 
     }
  else
    {
      return(VRAI) ; 
    }
}

extern 
booleen_t liste_vide( liste_t * const liste )
{
  if( liste->nb == 0 )
    {
      return(VRAI) ; 
    }
  else
    {
      return(FAUX) ; 
    }
}

/*
 * Methodes d'affectation 
 */


/* -- Acces individuel a un element */
extern 
err_t liste_elem_ecrire( liste_t * liste , 
			 void * const elem ,
			 const int ind )
			  
{

#ifdef _DEBUG_
  if( (ind < 0) || (ind > liste_nb_lire(liste) ) )
    {
      fprintf( stderr , "liste_elem_ecrire: mauvais indice d'element [%d] (devrait etre dans [%d..%d]\n",
	       ind , 0 , liste_nb_lire(liste) );
      return(ERR_LISTE_IND_ELEM);
    }
#endif
  liste-> affectation(liste -> liste[ind] , elem);
  /*liste->liste[ind] = elem ;*/
  return(OK) ;
}


/*
 * Creation d'une liste 
 */
extern
liste_t * liste_creer( const int nb, err_t(*detruire)(void **),err_t(*affectation)(void **, void *) )
{
  liste_t * liste ;
  
  if(( liste= malloc(sizeof(liste_t))) == NULL )
    {
      fprintf( stderr , "liste_creer: debordement memoire lors de la creation d'une liste\n");
      return((liste_t *)NULL);
    }
  liste->affectation = affectation;
  liste->detruire = detruire;
  liste->nb = nb ;
  liste->liste = (void**)NULL ;
  if( nb > 0 ) 
    {
      if( ( liste->liste = malloc( sizeof(void *) * nb ) ) == NULL ) 
	{
	  fprintf( stderr , "liste_creer: debordement memoire lors de la creation d'une liste\n");
	  free( liste ) ;
	  return((liste_t *)NULL);
	}
    }

  liste_cpt++ ; 

  return(liste);
}

/*
 * Destruction d'une liste 
 */

extern
err_t liste_detruire( liste_t ** liste, int taille_elem )
{
  int i;
  for(i = 0; i < (*liste) -> nb; i++){
	if(((*liste) -> liste[i]) != NULL){
		(*liste) -> detruire(((*liste) -> liste + i*taille_elem));
		free((*liste) -> liste + i * taille_elem);
	}
  }	
  free((*liste) -> liste);
  free(*liste);
  *liste = NULL;
  return(OK) ;
}


/*
 * Affichage d'une liste sur la sortie standard
 */

extern 
void liste_afficher( liste_t * const liste ,void (*afficher)(void *))
{
  int i;
  for(i=0; i < liste -> nb;i++){
	  afficher(liste-> liste[i]);
  }
}


/*
 * Tri Bulle
 */
static
err_t liste_trier_bulle( liste_t * liste){

  return(OK);
}




/*
 * Tri d'une liste 
 */
extern
err_t liste_trier( liste_t * liste )
{
  /*
   * A FAIRE 
   */

  return(OK) ; 
}
