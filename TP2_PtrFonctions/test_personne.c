#include <stdio.h>
#include <individu.h>
#include <personne.h>
int
main() 
{
  /* err_t noerr = OK; */
  personne_t * personne = NULL ; 

  printf( "Debut du programme des test sur les objets de type personne_t\n" ) ; 

  printf( "Test d'existence sur un personne_t inexistant\n" ) ;
  ( personne_existe(personne) ? printf("-->KO\n") : printf ("-->OK\n") )  ;

  printf(" Création d'une personne : \n");
  personne = personne_creer("Rogers", "Water", "7 rue de l'info","Le mans");
  
  printf( "Test affichage personne\n" ) ;  
/*  personne -> afficher((objet_t*)personne);*/
  printf( "\n");

  printf( "Test d'existence sur une personne_t existant\n" ) ;
  ( personne_existe(personne) ? printf("-->OK\n") : printf ("-->KO\n") )  ;
  
  printf( "Test destruction indiv_1\n" ) ;
  personne -> detruire((objet_t**)&personne);
  ( personne_existe(personne) ? printf("-->KO\n") : printf ("-->OK\n") )  ;

  printf( "Fin du programme des test sur les objets de type personne_t\n" ) ; 
  
  printf( "Nombre de individu_t  = %lu\n" , personne_cpt ) ;

  return(0) ; 
}
