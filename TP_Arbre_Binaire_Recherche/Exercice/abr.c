#include <abr.h>

extern
noeud_t * abr_racine_lire( const abr_t * arbre ) 
{
  if(arbre->racine != NULL){                                                       
  	return (arbre->racine);                                            
  }                                                                                
  return(NULL) ; 
 
}

extern
err_t abr_racine_ecrire( abr_t * arbre , 
			noeud_t * racine ) 
{
  arbre->racine = racine;
  return(OK) ; 
}

extern
int abr_taille_lire( const abr_t * arbre ) 
{
  return (arbre->taille); 
}

extern
err_t abr_taille_incrementer( abr_t * arbre ) 
{
  arbre -> taille += 1; 
  return(OK);
}

extern
err_t abr_taille_decrementer( abr_t * arbre ) 
{
  arbre -> taille -= 1;	
  return(OK);
}


/*
 * Tests
 */

extern
booleen_t abr_existe(const abr_t * arbre )
{
  if( arbre == NULL ) 
    return(FAUX) ;
  else
    return(VRAI) ; 
}

extern
booleen_t abr_vide( const abr_t * arbre )
{
  if(arbre->racine != NULL){                                                       
	  return (FAUX);                                                           
  }                                                                                  
  return(VRAI) ; 
}

/*
 * Creation 
 */

extern
abr_t * abr_creer( err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	/*!< Fonction d'affectation d'un element */
		   err_t (*fonction_destruction)( void * e) ,			/*!< Fonction de destruction d'un element */
		   int (*fonction_comparaison) ( const void * e1 , const void * e2) )		/*!< Fonction de comparaison de 2 elements */
{
  abr_t * arbre = NULL ; 
                                                                                   
  arbre = malloc(sizeof(ab_t));                                                    
                                                                                   
  arbre->taille = 0;                                                               
  arbre->racine = NULL;                                                            
  arbre->affecter = fonction_affectation;                                          
  arbre->detruire= fonction_destruction;
  arbre->comparer=fonction_comparaison;   
  return(arbre) ; 
}


/*
 * Destruction 
 */

static err_t abr_detruire_bis( noeud_t ** noeud, err_t (*detruire) (void *)){    
        if(*noeud == NULL){                                                     
                return(OK);                                                     
        }                                                                       
        abr_detruire_bis(&((*noeud)->gauche),detruire);                          
        abr_detruire_bis(&((*noeud)->droit),detruire);                           
        noeud_detruire(noeud,detruire);                                         
        return(OK);                                                             
}                                                                               
                                                                                
extern                                                                          
err_t abr_detruire( abr_t ** arbre )                                              
{                                                                               
  if(*arbre != NULL){                                                           
          abr_detruire_bis(&((*arbre)->racine),(*arbre)->detruire);              
          free(*arbre);                                                         
          (*arbre) = NULL;                                                      
  }                                                                             
  return(OK) ;                                                                  
}   

/*
 * Affichage 
 */

#define MAX_HAUTEUR 100                                                         
extern void affHauteur (                                                        
    int hauteur,                                                                
    booleen_t leftMost,                                                         
    char * left,                                                                
    char * right,                                                               
    char * between,                                                             
    char * empty,                                                               
    booleen_t reset                                                             
) {                                                                             
    int i;                                                                      
    static booleen_t first = VRAI;                                              
    static booleen_t * tab = NULL;                                              
                                                                                
    if (reset) {                                                                
        first = VRAI;                                                           
        free(tab);                                                              
        tab = NULL;                                                             
        return ;                                                                
    }                                                                           
    if (first) {                                                                
        first = FAUX;                                                           
        tab = malloc(MAX_HAUTEUR * sizeof(booleen_t));                          
        for (i = 0; i < MAX_HAUTEUR; i++) tab[i] = FAUX;                        
    }                                                                           
    for(i = 0 ; i < hauteur-1 ; i++) {                                          
        if (tab[i])printf("%s", between);                                       
        else printf("%s", empty);                                               
    }                                                                           
    if (hauteur!=0) {                                                           
        if (leftMost) {                                                         
            printf ("%s", left);                                                
            tab[hauteur-1] = VRAI;                                              
        }                                                                       
        else {                                                                  
            printf ("%s", right);                                               
            tab[hauteur-1] = FAUX;                                              
        }                                                                       
    }                                                                           
}                                                                               
                                                                                
extern void resetAffHauteur () {                                                
            affHauteur(0,0,NULL,NULL,NULL,NULL,VRAI);                           
}

static void ab_afficher_prefixe (noeud_t * noeud, void (*afficher) (const void *), int hauteur, int aUnGauche)
{                                                                               
    if (noeud == NULL) return;                                                  
                                                                                
    affHauteur(hauteur, aUnGauche,"└── ","├── ","    ","|   ",FAUX);            
    afficher (noeud->etiquette);                                                
    printf ("\n");                                                              
    ab_afficher_prefixe (noeud->gauche, afficher, hauteur + 1, FAUX);           
    ab_afficher_prefixe (noeud->droit, afficher, hauteur + 1, noeud->gauche != NULL);
}                                                                               
                                                                                
static void ab_afficher_postfixe (noeud_t * noeud, void (*afficher) (const void *), int hauteur, int aUnGauche)
{                                                                               
    if (noeud == NULL) return;                                                  
                                                                                
    ab_afficher_postfixe (noeud->gauche, afficher, hauteur + 1, FAUX);          
    ab_afficher_postfixe (noeud->droit, afficher, hauteur + 1, noeud->gauche != NULL);
    affHauteur(hauteur, aUnGauche,"├── ","┌── ","    ","|   ",FAUX);            
                                                                                
    afficher (noeud->etiquette);                                                
    printf ("\n");                                                              
}                                                                               
                                                                                
static void ab_afficher_infixe (noeud_t * noeud, void (*afficher) (const void *), int hauteur, int aUnGauche)
{                                                                               
    if (noeud == NULL) return;                                                  
                                                                                
    ab_afficher_infixe (noeud->gauche, afficher, hauteur + 1, FAUX);            
    //affHauteur2(hauteur, aUnGauche);                                          
    affHauteur(hauteur, aUnGauche,"└── ","┌── ","    ","|   ",FAUX);            
    afficher (noeud->etiquette);                                                
    printf ("\n");                                                              
    ab_afficher_infixe (noeud->droit, afficher, hauteur + 1, noeud->gauche != NULL);
}                                                                               
                                                                                
extern                                                                          
void abr_afficher( const abr_t * arbre , void (*fonction_affichage)(const void *), ab_parcours_t parcours)
{                                                                               
        switch(parcours){                                                       
                case PREFIXE: ab_afficher_prefixe(arbre->racine, fonction_affichage, 0, 0);  break;
                case POSTFIXE: ab_afficher_postfixe(arbre->racine, fonction_affichage, 0, 0); break;
                case SYMETRIQUE: ab_afficher_infixe(arbre->racine, fonction_affichage, 0, 0); break;
                default: ab_afficher_prefixe(arbre->racine, fonction_affichage, 0, 0);  break;
        }                                                                       
        resetAffHauteur();                                                      
}

/*
 * Insertion d'une valeur dans un ABR
 */
extern
err_t abr_inserer( abr_t * arbre  ,
		   void * etiquette ) 
{
  noeud_t * noeud = NULL; 
  noeud = noeud_creer(etiquette, NULL, NULL,arbre->affecter);
  if(arbre->racine == NULL){
	arbre->racine = noeud; 
  	return(OK) ;
  }
  return(noeud_inserer(noeud,&(arbre->racine),arbre->comparer));
} 

/*
 * Suppression d'une valeur dans un ABR
 */

extern
err_t abr_supprimer( abr_t * arbre  ,
		   void * etiquette ) 
{
  if(arbre->racine == NULL){
  	return(OK) ;
  }
  return(noeud_supprimer(etiquette,&(arbre->racine),arbre->detruire,arbre->comparer));
}

/*
 * Chargement d'un arbre a partir d'un fichier 
 */

extern 
err_t abr_charger( abr_t ** arbre  ,						    /* Arbre Binaire d'elements a charger */
		   char *  nom_fichier ,					    /* Nom du fichier de chargement */
		   err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	    /* fonction d'affectation d'un element */ 
		   err_t (*fonction_destruction)(void * e) ,			    /* fonction de destruction d'un element */
		   int (*fonction_comparaison) ( const void * e1 , const void * e2) , /* fonction de comparasion de 2 etiquettes */
		   err_t (*fonction_chargement)(void *  e, FILE *  desc ) ) 	    /* Fonction de chargement d'un element */
{
  err_t noerr = OK ; 
  FILE * fd = NULL ; 
  void * etiquette = NULL ;
 
  /* Ouverture fichier en lecture */
  if( (fd = fopen( nom_fichier , "r" ) ) == NULL )
    {
      fprintf( stderr , "abr_charger: ouverture en lecture du fichier %s impossible\n" , 
	       nom_fichier ) ; 
      return(ERR_NOM_FICHIER) ;
    }

  /* Destruction de l'arbre si il existe deja */
  if( abr_existe( (*arbre) )  )
    {
      if( (noerr = abr_detruire( arbre ) ) )
	return(noerr) ; 
    }

  /* Creation de l'arbre */
  if( ( (*arbre) = abr_creer( fonction_affectation , 
			      fonction_destruction ,
			      fonction_comparaison ) ) == NULL )      
    return(ERR_DEB_MEMOIRE) ; 


  /* Lecture de la taille de l'arbre */
  int taille = 0 ; 
  if( fscanf( fd , "%d\n" , &taille ) != 1 )
    {
      /* Pas d'element a charger */
      return(OK)  ;
    }

  /* 
   * Chargement 
   */  
  while( ! feof(fd) )
    {
      /* 
       * Lecture 1 ligne :  <etiquette> 
       */
      
      if( (noerr = fonction_chargement( &etiquette , fd ) ) )
	{
	  if( feof(fd) )
	    continue ;
	  else
	    return(noerr) ; 
	}
	 
      /* 
       * Insertion de la valeur dans l'arbre 
       */
      
      if( ( noerr = abr_inserer( (*arbre) , etiquette ) ) )
	return(noerr ) ;
      
      if( ( noerr = fonction_destruction( &etiquette ) ) )
	return(noerr) ;
      
    }

  /* Fermeture */
  fclose(fd) ; 
  
  return(OK) ; 
}



/*
 * Sauvegarde d'un arbre dans un fichier 
 */


static 
err_t abr_sauver_bis( const noeud_t * racine , 
		     FILE * fd  ,						/* File descriptor du fichier de chargement */
		     err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) 	/* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ; 

  /* 
   * Sauvegarde du noeud racine 
   * Creation 1 ligne : <etiquette> 
   */
  
  if( ! noeud_existe( racine ) )
    return(OK) ; 
  
  if( (noerr = fonction_sauvegarde( noeud_etiquette_lire(racine) , 
				    fd ) ) )
    return(noerr) ; 

  fprintf( fd , "\n" ) ; 
      
  /* 
   * Sauvegarde des noeuds dans les sous arbres gauche et droit 
   */
  noeud_t * noeud_fg = noeud_sag_lire(racine) ;
  if( noeud_existe(noeud_fg) )
    {
      if( ( noerr = abr_sauver_bis( noeud_fg ,  fd , fonction_sauvegarde ) ) )
	return(noerr) ; 
    }
  
  noeud_t * noeud_fd = noeud_sad_lire(racine) ;
  if( noeud_existe(noeud_fd) )
    {
      if( ( noerr = abr_sauver_bis( noeud_fd ,  fd , fonction_sauvegarde ) ) )
	return(noerr) ; 
    }

  return(OK) ; 
}

extern 
err_t abr_sauver( const abr_t * arbre  ,						/* Arbre Binaire d'elements a charger */
		 char *  nom_fichier ,						/* Nom du fichier de chargement */
		 err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) 	/* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ; 
  FILE * fd = NULL ; 


  /* Ouverture fichier en ecriture */
  if( (fd = fopen( nom_fichier , "w" ) ) == NULL )
    {
      fprintf( stderr , "abr_sauver: ouverture en ecriture du fichier %s impossible\n" , 
	       nom_fichier ) ; 
      return(ERR_NOM_FICHIER) ;
    }

  /* test si arbre vide */
  if( !abr_existe( arbre )  )
    return(OK); 

  /* 
   * Sauvegarde
   */  

  /* Taille */
  fprintf( fd , "%d\n" , abr_taille_lire(arbre) ) ; 
  
  /* Elements */
  
  if( ( noerr = abr_sauver_bis(  abr_racine_lire(arbre) , fd  ,fonction_sauvegarde ) ) )
    return(noerr) ; 

  /* Fermeture */
  fclose(fd) ; 
  
  return(OK) ; 
}

/*
 * Recherche du pere d'un noeud dans un arbre 
 */

static noeud_t * ab_pere_rechercher_noeud(noeud_t * pere, const noeud_t * fils){      
        noeud_t * res = NULL;                                                   
        if(pere != NULL && fils != NULL){                                       
                if(fils == pere->gauche || fils == pere->droit){                
                        return pere;                                            
                }                                                               
                else{                                                           
                        if(pere->gauche != NULL){                               
                                res = ab_pere_rechercher_noeud(pere->gauche, fils);
                        }                                                       
                        if(res == NULL){                                        
                                res = ab_pere_rechercher_noeud(pere->droit, fils);
                        }                                                       
                        if(res != NULL){                                        
                                return res;                                     
                        }                                                       
                }                                                               
        }                                                                       
        return NULL;                                                            
}                                                                               
                                                                                
extern
noeud_t * abr_pere_rechercher( const abr_t * arbre , 
			      const noeud_t * noeud_fils )
{
	return(ab_pere_rechercher_noeud((arbre->racine), noeud_fils));          
}


/*
 * Recherche d'un element dans un arbre 
 */
extern
err_t abr_rechercher( noeud_t ** result , 
			  const abr_t * arbre , 
			  const void * etiquette)
{
  
  (*result) = NULL ;
  return(noeud_rechercher(result, arbre->racine, etiquette, arbre->comparer));
}
