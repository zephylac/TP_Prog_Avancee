#include <stdlib.h>
#include <string.h>
#include <mystring.h>


/*
 * VARIABLE LOCALE
 */

unsigned long int string_cpt = 0 ; 

/* 
 * FONCTIONS
 */

/*
 * Test existance 
 */
extern 
booleen_t string_existe( string_t * const string )
{
  if( string == NULL ) 
    return(FAUX) ;
  else
    return(VRAI) ; 
}

/*
 * Destruction 
 */
extern
err_t string_detruire( string_t ** string ) 
{

  /* Liberation attributs */
  free( (*string)->string ) ; 
  /* Liberation memoire de l'objet */
  free( (*string) ) ;
  /* Pour eviter les pointeurs fous */
  (*string) = NULL ; 

  string_cpt-- ; 

  return(OK) ; 
}
/*
 * Effacement 
 */

err_t string_effacer( string_t ** string ) 
{
  /* 
   * l'Objet n'est pas detruit 
   */

  /* 
   * Sa reference est effacee 
   */
  
  (*string) = NULL ; 

  string_cpt-- ; 

  return(OK) ; 
}

/*
 * Affichage
 */

extern
void string_afficher( string_t * const string ) 
{

  printf( "{" ) ; 
  if(  string_existe(string) ) 
    {
      printf( "%s" , string->string) ;
    }
  printf( "}" ) ; 
}

/*
 * Creation 
 */

extern 
string_t * string_creer( char * const chaine ) 
{
  string_t * string = NULL ; 

  /* Creation place memoire objet string */
  if( ( string = malloc(sizeof(string_t)) ) == NULL )
    {
      fprintf( stderr , "string_creer: debordement memoire lors de la creation d'un objet de type string_t (%lu demandes)\n", 
	       (unsigned long int)sizeof(string_t) ) ;
      return((string_t *)NULL);
    }

  /* Affectation attributs specifiques */
  if( ( string->string = malloc(sizeof(char)*strlen(chaine)+1) ) == NULL )
    {
      fprintf( stderr , "string_creer: debordement memoire lors de la creation d'un objet de type string_t (%lu demandes)\n", 
	       (unsigned long int)strlen(chaine)+1 ) ;
      return((string_t *)NULL);
    }
  strcpy( string->string , chaine ) ;

  string_cpt++ ; 

  return( string ) ;
}

/*
 * Comparaison
 */

extern
int string_comparer( const string_t * const str1 , const string_t * const str2 )
{
  return(strcmp( str1->string , str2->string) ) ;
}

/*
 * Affectation d'une string par reference 
 */

extern
err_t string_referencer( string_t ** str_cible ,  string_t * str_source )
{
  (*str_cible) = str_source ; 
  return(OK) ; 
}

/*
 * Affectation d'un string par copie 
 */

extern
err_t string_copier( string_t ** str_cible ,  string_t * str_source )
{
  err_t noerr = OK ; 

  if( string_existe( (*str_cible) ) )
    {
      if( ( noerr = string_detruire( str_cible ) ) )
	return(noerr) ;
    }

  if( ! string_existe( str_source ) )
    return(OK) ; 

  if( ( (*str_cible) = string_creer( str_source->string ) ) )
    return(ERR_DEB_MEMOIRE) ; 

  return(OK) ; 
}

extern
err_t str_det(void ** str){
	return string_detruire((string_t**)str);
}

extern
void str_aff(void * const str){
	string_afficher((string_t*)str);
}

extern
err_t str_cp(void ** str1, void * str2){
	return string_copier((string_t**)str1, (string_t*)str2);
}

extern
err_t str_rf(void ** str1, void * str2){
	return string_referencer((string_t**)str1, (string_t*)str2);
}

extern
int str_cmp(const void * str1, const void * str2){
	return string_comparer(*(string_t**)str1, *(string_t**)str2);
}
