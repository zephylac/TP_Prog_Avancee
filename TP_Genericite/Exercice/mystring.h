#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <commun.h>

/*
 * DEFINITION OBJET "STRING"  
 */

typedef struct string_s 
{
  char * string ;
} string_t ;

/*
 * VARIABLE LOCALE
 * declaration du compteur d'objets string_t comme variable externe
 * pour compter les references sur ces objets 
 */

extern unsigned long int string_cpt  ;

/* 
 * FONCTIONS
 */
/* Creation */
extern string_t * string_creer(char * const chaine ) ;
/* Test existance */
extern booleen_t string_existe( string_t * const string ) ;
/* Destructions */
extern err_t string_detruire( string_t ** string ) ;
/* Effacements */
extern err_t string_effacer( string_t ** string ) ;
/* Affichages */
extern void string_afficher( string_t * const string ) ;
/* Comparaisons */
extern int string_comparer( const string_t * const str1 , const string_t * const str2 ) ;
/* Referencements */
extern err_t string_referencer( string_t ** str_cible ,  string_t * str_source ) ;
/* Copies */
extern err_t string_copier( string_t ** str_cible ,  string_t * str_source ) ; 

extern void str_aff(void * const str);
extern err_t str_det(void ** str);
extern err_t str_cp(void ** str1, void * str2);
extern err_t str_rf(void ** str1, void * str2);
extern int str_cmp(const void * str1, const void * str2);
#endif
