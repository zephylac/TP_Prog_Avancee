#include <stdlib.h>
#include <string.h>
#include <personne.h>
#include <individu.h>

/*
 * VARIABLE LOCALE
 */

unsigned long int personne_cpt = 0 ; 

/* 
 * FONCTIONS
 */

extern 
booleen_t personne_existe( personne_t * const personne )
{
  if( personne == NULL ) 
    return(FAUX) ;
  else
    return(VRAI) ; 
}

static 
err_t personne_detruire( personne_t ** personne ) 
{
   
   free((*personne) -> adresse);
   free((*personne) -> ville); 
   individu_detruire((individu_t**)personne);
   free((*personne));
   *personne = NULL;
   personne_cpt--;
   return(OK) ; 
  	
}

static
void personne_afficher( personne_t * const personne ) 
{

  printf( "{" ) ; 
  if(  personne_existe(personne) ) 
    {
	individu_afficher((individu_t*)personne);
    	printf("%s %s", personne-> adresse, personne -> ville);
    }
  printf( "}" ) ; 
}

static
char * copyString(char * string){
	char * stringBis = malloc(sizeof(char)*strlen(string)+1);
	strcpy(stringBis,string);
	return stringBis;
}

extern 
personne_t * personne_creer( char * nom, char * prenom, char * adresse, char * ville) 
{
  personne_cpt++;
  personne_t * personne = NULL;
  personne = (personne_t*)individu_creer(nom, prenom);
  
  personne = realloc(personne, sizeof(personne_t));
  personne -> adresse = copyString(adresse);
  personne -> ville = copyString(ville);

  personne -> afficher = (void (*)(objet_t *))personne_afficher;
  personne -> detruire = (err_t (*)(objet_t **))personne_detruire;
  return( personne ) ;
}
