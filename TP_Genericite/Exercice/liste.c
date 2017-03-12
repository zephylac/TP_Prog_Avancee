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
  liste-> affectation(&(liste -> liste[ind]) , elem);
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
		(*liste) -> detruire(&((*liste) -> liste[i]));
		(*liste) -> liste[i] = NULL;
	}
  }	
  free((*liste) -> liste);
  free(*liste);
  liste_cpt--;
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
 * Inverse l'ordre d'un tableau
 */
static
void inverserTab(liste_t * liste){
  int i, j;
  void ** temp = NULL;
  for( i = 0,j = liste -> nb - 1; i < liste -> nb / 2; i++, j--){
  	temp = liste->liste[i];
	liste->liste[i] = liste->liste[j];
	liste->liste[j] = temp;
  }
}

/*
 * Tri bulle
 */
static
err_t liste_trier_bulle( liste_t * liste,ordre_t ordre, int (*comparer)(const void *, const void *))
{
  int i, j, test;
  void * temp = NULL;
  int triee = 0;
  int taille = liste -> nb;
  for(i = 0; i < taille - 1; i++){
  	triee = 1;
	for(j = 0; j < taille - i - 1 ; j++){
		if(ordre == croissant){
			test = comparer(&(liste->liste[j]), &(liste->liste[j+1]));
		}
		else{
			test = comparer(&(liste->liste[j+1]), &(liste->liste[j]));
		}
		if(test > 0 ){
				triee = 0;
			 	temp = liste -> liste[j];
				liste -> liste[j] = liste -> liste[j + 1];
				liste -> liste[j + 1] = temp;
		}
	}
	if (triee) return(OK);
  }
  return(OK);
}

/*
 * Tri quicksort
 */
static
err_t liste_trier_qsort( liste_t * liste,ordre_t ordre, int (*comparer)(const void *, const void * )){
  qsort(liste -> liste, liste -> nb, sizeof(liste->liste[0]),comparer);
  if (ordre == decroissant){
  	inverserTab(liste);	
  }
  return(OK);
}


/*
 * Tri d'une liste
 */

extern 
err_t liste_trier( liste_t * liste, ordre_t ordre, int (*comparer)(const void *, const void *), methode_tri_t tri){
  
  switch(tri){
  		case qsort_t: liste_trier_qsort(liste, ordre, comparer); break;
  		case bulle_t: liste_trier_bulle(liste, ordre, comparer); break;
  		default: printf("Erreur tri non existant\n");
  }	
  return(OK);
}

