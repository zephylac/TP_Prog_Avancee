#define _POSIX_C_SOURCE 2

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <individu.h>
#include <fraction.h>
#include <mystring.h>
#include <liste.h>


/* OPTIONS VALIDES POUR LE PROGRAMME */
static struct option longopts[] = {
{"verbose", no_argument, 0, 'v'},
{"help", no_argument, 0, 'h'},
{"ajout", required_argument, 0, 'a'},
{"tri", required_argument, 0, 't'},
{"ordre",required_argument, 0, 'o'},
{0, 0, 0, 0}
};

static
void usage(){
	printf("Programme de test des listes homognènes\n");
	printf("Usage : test_liste [options] <nombre d'elements dans les listes>\n");
	printf("Options : \n");
	printf("   -h | --help 			  --> Aide\n");
	printf("   -v | --verbose                 --> Affiche les messages des traces\n");
	printf("   -a | --ajout < copie | ref >   --> Choix de la méthode d'ajout des éléments (référencement par défaut)\n");
	printf("   -t | --tri   < qsort | bulle > --> Choix de la méthode de tri à utiliser (qsort par défaut)\n");
	printf("   -o | --ordre < + | - >         --> Choix de l'ordre du tri (croissant par défaut)\n");
}


int
main(int argc, char * argv[]) 
{

  err_t noerr = OK; 
  individu_t ** individus = NULL  ; 
  fraction_t ** fractions = NULL  ;
  string_t ** strings = NULL  ; 

  liste_t * liste = NULL ; 
  int i = 0; 
  int N = 0; 
  
  int c;
  int vflag = 0;
  
  methode_elem_t methodeElem = referencement;
  methode_tri_t methodeTri = bulle_t;
  ordre_t ordreTri = croissant;

/* Traitement des arguments */ 

 while ((c = getopt_long(argc, argv, "vha:t:o:", longopts, NULL)) != -1){
    switch (c)
      {
      case 'v':
        vflag = 1;
        break;

      case 'h': 
	usage();
       	exit(0);

      case 'a':
	if(strcmp("ref", optarg) == 0)
		 methodeElem = referencement;
	else if(strcmp("copie", optarg) == 0)
		methodeElem = copie;
	else {
		printf("Erreur : Méthode de copie %s inconnue.\n\n", optarg);
		usage();
		exit(0);
	}
	break;
	
      case 't':
	if(strcmp("qsort", optarg) == 0)
		methodeTri = qsort_t;
	else if(strcmp("bulle", optarg) == 0)
		methodeTri = bulle_t;
	else {
		printf("Erreur : Méthode de tri %s inconnue.\n\n", optarg);
		usage();
		exit(0);
	}
	break; 
      
      case 'o':
	if(strcmp("+", optarg) == 0)
		ordreTri = croissant;
	else if(strcmp("-", optarg) == 0)
		ordreTri = decroissant;
	else {
		printf("Erreur : Méthode de tri %s inconnue.\n\n", optarg);
		usage();
		exit(0);
	}
	break;
      default : printf("Erreur : Option inconnue\n\n"); usage(); exit(0);
      }
  } 
  argc -= optind;
  argv += optind;

    
  if(argc == 1){
	/*N = atoi(argv[optind]);*/
	sscanf(argv[0],"%i",&N);
	if(N == 0){
		usage();
		exit(0);
	}
	else{
	printf(" N = %i\n",N);
	}
  }
  else{
	printf("Erreur : 1 argument attendu, %d passé(s).\n\n", argc);
	usage();
	exit(0);
  }  	
  
  printf("vflag = %d\n",vflag);


  err_t(*individu_methode_ajout)(void *, void *) = NULL;
  err_t(*fraction_methode_ajout)(void *, void *) = NULL; 
  err_t(*string_methode_ajout)(void *, void *)   = NULL;
  
  err_t(*individu_methode_detruire)(void *) = NULL;
  err_t(*fraction_methode_detruire)(void *) = NULL;
  err_t(*string_methode_detruire)(void *)   = NULL;

  if(methodeElem == referencement){
  	individu_methode_ajout = ind_rf;
	fraction_methode_ajout = frac_rf;
	string_methode_ajout   = str_rf;

	individu_methode_detruire = ind_eff;
	fraction_methode_detruire = frac_eff;
	string_methode_detruire   = str_eff;
  } 
  else {
	individu_methode_ajout = ind_cp;
	fraction_methode_ajout = frac_cp;
	string_methode_ajout   = str_cp;

	individu_methode_detruire = ind_det;
	fraction_methode_detruire = frac_det;
	string_methode_detruire   = str_det;
  }

  int (*individu_cmp)(const void *, const void *) = NULL;
  int (*fraction_cmp)(const void *, const void *) = NULL;
  int (*string_cmp)(const void *, const void *) = NULL; 

  if(ordreTri == decroissant){
	individu_cmp = ind_cmp_rev;
	fraction_cmp = frac_cmp_rev;
	string_cmp   = str_cmp_rev;
  }								
  else {
  	individu_cmp = ind_cmp;
	fraction_cmp = frac_cmp;
	string_cmp   = str_cmp;
  }

  individus = malloc( sizeof(individu_t *) * N )  ; 
  fractions = malloc( sizeof(fraction_t *) * N )  ;
  strings = malloc( sizeof(string_t *) * N )   ; 

  printf( "Debut du programme des test sur les listes de %d objets homogenes\n" , N ) ; 
  if(vflag == 1){
  	printf( "\nTest creation d'une liste de %d individus \n" , N ) ;
  }
  char prenom[128] ;
  char nom[128] ; 
  liste = liste_creer(N, individu_methode_detruire, individu_methode_ajout) ;  
  for( i=0 ; i<N ; i++ ) 
    {
      sprintf( nom , "nom_%d" , N-i ) ;
      sprintf( prenom , "prenom_%d" , N-i ) ;
      individus[i] = individu_creer( prenom , nom ) ; 
      liste_elem_ecrire( liste , individus[i] , i ) ;
    }
  
  if(vflag == 1){
  	printf( "Test affichage liste d'individus AVANT tri \n" ) ;
  	liste_afficher( liste , ind_aff ) ; 
  	printf( "\n");

  	printf( "Test Tri de la liste des individus\n" );
  	liste_trier( liste, individu_cmp, methodeTri) ;

  	printf( "Test affichage liste d'individus APRES tri\n" ) ;
  	liste_afficher( liste , ind_aff ) ; 
  	printf( "\n");
 
  	printf( "Test destruction liste d'individus\n" ) ;
  }
  if( ( noerr = liste_detruire( &liste ) ) ){ 
  	printf("Sortie avec code erreur = %d\n" , noerr ) ;
  	return(noerr) ; 
  }
  if(individus != NULL){
	for(i = 0 ; i < N ; i++){
		if(individus[i] != NULL) individu_detruire(&individus[i]);
	}
  }
  if(vflag == 1){
	printf( "\nTest creation d'une liste de %d fractions \n" , N ) ;
  }
  liste = liste_creer(N, fraction_methode_detruire, fraction_methode_ajout) ;  
  for( i=0 ; i<N ; i++ ){
      	fractions[i] = fraction_creer( N-i , N-i+1 ) ; 
      	liste_elem_ecrire( liste , fractions[i] , i ) ;
  }
  if(vflag == 1){
  	printf( "Test affichage liste de fractions AVANT tri\n" ) ;
  	liste_afficher( liste , frac_aff ) ; 
  	printf( "\n");

  	printf( "Test Tri de la liste des fractions\n" );
  	liste_trier( liste, fraction_cmp, methodeTri ) ;

  	printf( "Test affichage liste des fractions APRES tri\n" ) ;
  	liste_afficher( liste ,  frac_aff ) ; 
  	printf( "\n");
 
  	printf( "Test destruction liste de fractions\n" ) ;
  }
  if( ( noerr = liste_detruire( &liste ) ) ) { 
  	printf("Sortie avec code erreur = %d\n" , noerr ) ;
      	return(noerr) ; 
  }
  if(fractions != NULL){
	for(i = 0 ; i < N ; i++){
		if(fractions[i] != NULL) fraction_detruire(&fractions[i]);
	}
  }
  if(vflag ==1){
  	printf( "\nTest creation d'une liste de %d strings \n" , N ) ;
  }
  char string[128] ;
  liste = liste_creer(N, string_methode_detruire, string_methode_ajout) ;  
  for( i=0 ; i<N ; i++ ){
      	sprintf( string , "string_%d" , N-i ) ; 
      	strings[i] = string_creer( string ) ; 
      	liste_elem_ecrire( liste , strings[i] , i ) ;
  }
  if(vflag == 1){
  	printf( "Test affichage liste de strings AVANT tri\n" ) ;
  	liste_afficher( liste , str_aff) ; 
  	printf( "\n");
 
  	printf( "Test Tri de la liste des strings\n" );
  	liste_trier( liste, string_cmp, methodeTri) ;
  
  	printf( "Test affichage liste des strings APRES tri\n" ) ;
  	liste_afficher( liste , str_aff) ; 
  	printf( "\n");
  
  	printf( "Test destruction liste de strings\n" ) ;
  }	
  if( ( noerr = liste_detruire( &liste ) ) ){ 
  	printf("Sortie avec code erreur = %d\n" , noerr ) ;
  	return(noerr) ; 
  }
  if(strings != NULL){
	for(i = 0 ; i < N ; i++){
		if(strings[i] != NULL) string_detruire(&strings[i]);
	}
  }
  free( individus ) ;
  free( fractions ) ;
  free( strings ) ; 
  printf( "\nFin du programme des test sur la liste d'objets homogenes\n" ) ; 
  printf( "Nombre de liste_t  = %lu\n" , liste_cpt ) ;

  return(0) ; 
}
