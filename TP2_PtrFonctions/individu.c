#include <stdlib.h>
#include <string.h>
#include <individu.h>


/*
 * VARIABLE LOCALE
 */

unsigned long int individu_cpt = 0 ; 

/* 
 * FONCTIONS
 */

extern 
booleen_t individu_existe( individu_t * const individu )
{
  if( individu == NULL ) 
    return(FAUX) ;
  else
    return(VRAI) ; 
}

static 
err_t individu_detruire( individu_t ** individu ) 
{
   if((*individu) -> nom != NULL)
   	free((*individu) -> nom);
   
   if((*individu) -> prenom != NULL)
	free((*individu) -> prenom);
   
   if((*individu) != NULL)
	free(*individu);
   
   *individu = NULL;
   individu_cpt--;
   return(OK) ; 
  	
}

static
void individu_afficher( individu_t * const individu ) 
{

  printf( "{" ) ; 
  if(  individu_existe(individu) ) 
    {
      printf( "%s %s" , individu->prenom , individu->nom ) ;
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
individu_t * individu_creer( char * const prenom , char * const nom ) 
{
  individu_cpt++;
  individu_t * individu = malloc(sizeof(individu_t));
  individu -> nom = copyString(nom);
  individu -> prenom = copyString(prenom);
  individu -> afficher = (void (*)(objet_t *))individu_afficher;
  individu -> detruire = (err_t (*)(objet_t **))individu_detruire;
  return( individu ) ;
}
