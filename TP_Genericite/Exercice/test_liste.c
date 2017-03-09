#define _POSIX_C_SOURCE 2

#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <individu.h>
#include <fraction.h>
#include <mystring.h>
#include <liste.h>


int
main(int argc, char * argv[]) 
{
  err_t noerr = OK; 
  individu_t ** individus = NULL  ; 
  fraction_t ** fractions = NULL  ;
  string_t ** strings = NULL  ; 

  liste_t * liste = NULL ; 
  int i = 0 ;
  int N = 0; 
  
  int c;
  int vflag = 0;
  
/* Traitement des arguments */ 

 while ((c = getopt(argc, argv, "v")) != -1)
    switch (c)
      {
      case 'v':
        vflag = 1;
        break;
      case '?':
        if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
      	return 1;
      default :
	abort();
      }  
  if(argc - optind == 1){
	 printf(" N = %s\n",argv[optind]);
  }
  printf("vflag = %d\n",vflag);





  individus = malloc( sizeof(individu_t *) * N )  ; 
  fractions = malloc( sizeof(fraction_t *) * N )  ;
  strings = malloc( sizeof(string_t *) * N )   ; 

  printf( "Debut du programme des test sur les listes de %d objets homogenes\n" , N ) ; 
  if(vflag == 1){
  	printf( "\nTest creation d'une liste de %d individus \n" , N ) ;
  }
  char prenom[128] ;
  char nom[128] ; 
  liste = liste_creer(N) ;  
  for( i=0 ; i<N ; i++ ) 
    {
      sprintf( nom , "nom_%d" , N-i ) ;
      sprintf( prenom , "prenom_%d" , N-i ) ;
      individus[i] = individu_creer( prenom , nom ) ; 
      liste_elem_ecrire( liste , individus[i] , i ) ;
    }
  
  if(vflag == 1){
  	printf( "Test affichage liste d'individus AVANT tri \n" ) ;
  	liste_afficher( liste , ' ' ) ; 
  	printf( "\n");

  	printf( "Test Tri de la liste des individus\n" );
  	liste_trier( liste  ) ;

  	printf( "Test affichage liste d'individus APRES tri\n" ) ;
  	liste_afficher( liste , ' ' ) ; 
  	printf( "\n");
 
  	printf( "Test destruction liste d'individus\n" ) ;
  }
  if( ( noerr = liste_detruire( &liste ) ) ){ 
  	printf("Sortie avec code erreur = %d\n" , noerr ) ;
  	return(noerr) ; 
  }
  if(vflag == 1){
	printf( "\nTest creation d'une liste de %d fractions \n" , N ) ;
  }
  liste = liste_creer(N) ;  
  for( i=0 ; i<N ; i++ ){
      	fractions[i] = fraction_creer( N-i , N-i+1 ) ; 
      	liste_elem_ecrire( liste , fractions[i] , i ) ;
  }
  if(vflag == 1){
  	printf( "Test affichage liste de fractions AVANT tri\n" ) ;
  	liste_afficher( liste , ' ' ) ; 
  	printf( "\n");

  	printf( "Test Tri de la liste des fractions\n" );
  	liste_trier( liste ) ;

  	printf( "Test affichage liste des fractions APRES tri\n" ) ;
  	liste_afficher( liste ,  ' ' ) ; 
  	printf( "\n");
 
  	printf( "Test destruction liste de fractions\n" ) ;
  }
  if( ( noerr = liste_detruire( &liste ) ) ) { 
  	printf("Sortie avec code erreur = %d\n" , noerr ) ;
      	return(noerr) ; 
  }
  if(vflag ==1){
  	printf( "\nTest creation d'une liste de %d strings \n" , N ) ;
  }
  char string[128] ;
  liste = liste_creer(N) ;  
  for( i=0 ; i<N ; i++ ){
      	sprintf( string , "string_%d" , N-i ) ; 
      	strings[i] = string_creer( string ) ; 
      	liste_elem_ecrire( liste , strings[i] , i ) ;
  }
  if(vflag == 1){
  	printf( "Test affichage liste de strings AVANT tri\n" ) ;
  	liste_afficher( liste ,  ' ' ) ; 
  	printf( "\n");
 
  	printf( "Test Tri de la liste des strings\n" );
  	liste_trier( liste  ) ;
  
  	printf( "Test affichage liste des strings APRES tri\n" ) ;
  	liste_afficher( liste ,  ' ' ) ; 
  	printf( "\n");
  
  	printf( "Test destruction liste de strings\n" ) ;
  }	
  if( ( noerr = liste_detruire( &liste  ) ) ){ 
  	printf("Sortie avec code erreur = %d\n" , noerr ) ;
  	return(noerr) ; 
  }
  free( individus ) ;
  free( fractions ) ;
  free( strings ) ; 
  printf( "\nFin du programme des test sur la liste d'objets homogenes\n" ) ; 
  printf( "Nombre de liste_t  = %lu\n" , liste_cpt ) ;

  return(0) ; 
}
