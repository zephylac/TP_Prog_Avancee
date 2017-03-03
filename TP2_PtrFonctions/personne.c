#include <stdlib.h>
#include <string.h>
#include <personne.h>


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
   free((*personne) -> prenom);
   free((*personne) -> nom);
   free((*personne) -> adresse);
   free((*personne) -> ville);
   (*personne) -> adresse = NULL;
   (*personne) -> nom = NULL;
   (*personne) -> prenom = NULL;
   (*personne) -> ville = NULL;
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
    ((individu_t*)personne) -> afficher((objet_t*)personne);
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
  personne_t * personne = malloc(sizeof(personne_t));
  personne -> nom = copyString(nom);
  personne -> prenom = copyString(prenom);
  personne -> adresse = copyString(adresse);
  personne -> ville = copyString(ville);

  personne -> detruire = (void (*)(objet_t *))personne_detruire;
  personne -> afficher = (err_t (*)(objet_t **))personne_afficher;
  return( personne ) ;
}
