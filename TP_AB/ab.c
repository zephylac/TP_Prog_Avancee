#include <ab.h>

extern
noeud_t * ab_racine_lire( const ab_t * arbre ) 
{
  if(arbre->racine != NULL){
		return (arbre->racine);
  }
  return(NULL) ; 
}

extern
err_t ab_racine_ecrire( ab_t * arbre , 
			noeud_t * racine ) 
{
  arbre->racine = racine;
  return(OK) ; 
}

extern
int ab_taille_lire( const ab_t * arbre ) 
{
  return (arbre->taille);
}

extern
err_t ab_taille_incrementer( ab_t * arbre ) 
{
  arbre -> taille += 1;
  return(OK);
}


/*
 * Tests
 */

extern
booleen_t ab_existe( const ab_t * arbre )
{
  return arbre != NULL; 
}

extern
booleen_t ab_vide( const ab_t * arbre )
{
  if(arbre->racine->gauche == NULL && arbre->racine->droit == NULL){
  	  return (VRAI);
  }
  return(FAUX);
}

/*
 * Creation 
 */

extern
ab_t * ab_creer( err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	/*!< Fonction d'affectation d'un element */
		 err_t (*fonction_destruction)( void * e)  )			/*!< Fonction de destruction d'un element */
{
  ab_t * arbre = NULL ; 

  arbre = malloc(sizeof(ab_t));
  
  arbre->taille = 0;
  arbre->racine = NULL;
  arbre->affecter = fonction_affectation;
  arbre->detruire= fonction_destruction;
 
  return(arbre) ; 
}


/*
 * Destruction 
 */

extern 
err_t ab_detruire( ab_t ** arbre ) 
{
  if(*arbre != NULL){                                                           
        (*arbre)->detruire(arbre);	                             
        (*arbre) = NULL;                                       
  }                                                                             
  return(OK) ; 
}

/*
 * Affichage d'un arbre selon 
 * --> Adaptez cette fonction pour qu'elle puisse afficher l'arbre dans un parcours soit 
 * - infixe
 * - postfixe
 * - symetrique 
 */


// Print a givent amount of space (for drawing the tree)
void affHauteur(int hauteur){
	int i;
	for(i = 0 ; i < hauteur ; i++)
		printf("│   ");
}

// Affiche le noeud et ses enfants
static void ab_print_enfant_inf(noeud_t * noeud, void (*afficher)(const void *), int hauteur){
	if(noeud != NULL){
		afficher(noeud->etiquette);

		// Affiche l'enfant de gauche
		if(noeud->gauche != NULL){
			printf("\n");
			affHauteur(hauteur);

			if(noeud->droit != NULL)
				printf("├");
			else
				printf("└");

			printf("── ");
			ab_print_enfant(noeud->gauche, afficher, hauteur + 1);
		}


		// Affiche l'enfant de droite
		if(noeud->droit != NULL){
			printf("\n");
			affHauteur(hauteur);
			printf("└── ");
			ab_print_enfant(noeud->droit, afficher, hauteur + 1);
		}
	}
}

static void ab_print_enfant_post(noeud_t * noeud, void (*afficher)(const void *), int hauteur){
	if(noeud != NULL){
		afficher(noeud->etiquette);

		// Affiche l'enfant de gauche
		if(noeud->gauche != NULL){
			printf("\n");
			affHauteur(hauteur);

			if(noeud->droit != NULL)
				printf("├");
			else
				printf("└");

			printf("── ");
			ab_print_enfant(noeud->gauche, afficher, hauteur + 1);
		}


		// Affiche l'enfant de droite
		if(noeud->droit != NULL){
			printf("\n");
			affHauteur(hauteur);
			printf("└── ");
			ab_print_enfant(noeud->droit, afficher, hauteur + 1);
		}
	}
}

static void ab_print_enfant_sym(noeud_t * noeud, void (*afficher)(const void *), int hauteur){
	if(noeud != NULL){
		afficher(noeud->etiquette);

		// Affiche l'enfant de gauche
		if(noeud->gauche != NULL){
			printf("\n");
			affHauteur(hauteur);

			if(noeud->droit != NULL)
				printf("├");
			else
				printf("└");

			printf("── ");
			ab_print_enfant(noeud->gauche, afficher, hauteur + 1);
		}


		// Affiche l'enfant de droite
		if(noeud->droit != NULL){
			printf("\n");
			affHauteur(hauteur);
			printf("└── ");
			ab_print_enfant(noeud->droit, afficher, hauteur + 1);
		}
	}
}

 extern 
void ab_afficher( const ab_t * arbre , 
		  void (*fonction_affichage)(const void *)) 
{
  	ab_print_enfant(arbre->racine, fonction_affichage, 0);
	printf("\n");
}


/*
 * Chargement d'un arbre a partir d'un fichier 
 */

extern 
err_t ab_charger( ab_t ** arbre  ,						/* Arbre Binaire d'elements a charger */
		  char *  nom_fichier ,						/* Nom du fichier de chargement */
		  err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	/* fonction d'affectation d'un element */ 
		  err_t (*fonction_destruction)(void * e) ,			/* fonction de destruction d'un element */
		  err_t (*fonction_chargement)(void *  e, FILE *  desc ) ) 	/* Fonction de chargement d'un element */
{
  err_t noerr = OK ; 
  FILE * fd = NULL ; 
  void * etiquette = NULL ;
  noeud_t * noeud = NULL ; 
  noeud_t * noeud_fg = NULL ;   
  noeud_t * noeud_fd = NULL ; 

  int num_noeud = -1 ;
  int num_fg    = -1 ; 
  int num_fd    = -1 ;
    


  /* Initialisation du resultat */
  (*arbre) = NULL ; 

  /* Ouverture fichier en lecture */
  if( (fd = fopen( nom_fichier , "r" ) ) == NULL )
    {
      fprintf( stderr , "ab_charger: ouverture en lecture du fichier %s impossible\n" , 
	       nom_fichier ) ; 
      return(ERR_NOM_FICHIER) ;
    }

  /* Destruction de l'arbre si il existe deja */
  if( ab_existe( (*arbre) )  )
    {
      if( (noerr = ab_detruire( arbre ) ) )
	return(noerr) ; 
    }

  /* Creation de l'arbre */
  if( ( (*arbre) = ab_creer( fonction_affectation , 
			     fonction_destruction ) ) == NULL )      
    return(ERR_DEB_MEMOIRE) ; 

  /* 
   * Chargement 
   */  
  while( ! feof(fd) )
    {
      /* 
       * Lecture 1 ligne : num_noeud num_fils_gauche num_fils_droit <etiquette> 
       */
      
      /* -- Lecture num_noeud num_fils_gauche num_fils_droit */
      if( fscanf( fd , "%d%d%d" , &num_noeud , &num_fg , &num_fd ) != 3 ) 
	{
	  if( feof(fd) )
	    continue ;
	  else
	    return( ERR_SCANF ) ; 
	}
      
      /* -- Lecture etiquette */
      if( (noerr = fonction_chargement( &etiquette , fd ) ) )
	return(noerr) ; 
      
      /* Recherche noeud */
      noeud = NULL ; 
      if( noeud_numero_rechercher( &noeud , 
				   ab_racine_lire((*arbre)) ,
				   num_noeud ) )
	{
	  /* Noeud existant --> affectation etiquette */
	  if( ( noerr = noeud_etiquette_ecrire( noeud , etiquette , fonction_affectation ) ) )
	    return(noerr) ; 
	}
      else
	{
	  /* Noeud inexistant --> creation + affectation etiquette ( racine ) */

	  if( ab_taille_lire((*arbre)) != 0 )
	    {
	      printf("ab_charger: Erreur : Creation de la racine lorsque la taille de l'arbre > 0 (%d)\n", 
		     ab_taille_lire((*arbre)) ) ;
	      printf("           Noeud invoque: [#%d fg:%d fd:%d]" , num_noeud , num_fg , num_fd );
	      
	      return(ERR_ARBRE_NOEUD) ; 
	    }

	  if( ( noerr = ab_taille_incrementer((*arbre)) ) )
	    return(noerr) ; 
	  
	  if( ( noeud = noeud_creer( num_noeud, 
				     etiquette , NULL , NULL , 
				     fonction_affectation ) ) == NULL )
	    return(ERR_DEB_MEMOIRE) ;

	  if( (noerr = ab_racine_ecrire( (*arbre) , noeud ) ) )
	    return(noerr) ; 
	}
      
      /* 
       * Sous arbre gauche 
       */
      if( num_fg != -1 ) 
	{
	  /* Recherche fils gauche */
	  if( noeud_numero_rechercher( &noeud_fg , 
				       ab_racine_lire((*arbre)) ,
				       num_fg ) )
	    {
	      /* Noeud existant --> erreur , on ne devrait pas l'avoir deja rencontre dans le fichier */
	      printf("ab_charger: Erreur : lors de la creation du noeud %d (fils gauche de %d) : %d est deja cree\n", 
		     num_fg , num_noeud , num_fg ) ;
	      return(ERR_ARBRE_NOEUD) ; 	    
	    }
	  else
	    {
	      /* Noeud inexistant --> creation */
	      ab_taille_incrementer((*arbre)) ;
	      if( ( noeud_fg = noeud_creer( num_fg , 
					    NULL , NULL , NULL , 
					    fonction_affectation ) ) == NULL )
		return(ERR_DEB_MEMOIRE) ;
	    }
	  
	  /* Rattachement au noeud */
	  if( ( noerr = noeud_sag_ecrire( noeud , noeud_fg ) ) )
	    return(noerr) ; 
	}

      /* 
       * Sous arbre droit 
       */
      if( num_fd != -1 ) 
	{
	  /* Recherche fils droit */
	  if( noeud_numero_rechercher( &noeud_fd , 
				       ab_racine_lire((*arbre)) ,
				       num_fd ) )
	    {
	      /* Noeud existant --> erreur */
	      printf("ab_charger: Erreur : lors de la creation du noeud %d (fils droit de %d) : %d est deja cree\n", 
		     num_fd , num_noeud , num_fd ) ;
	      return(ERR_ARBRE_NOEUD) ; 
	    }
	  else
	    {
	      /* Noeud inexistant --> creation */
	      ab_taille_incrementer((*arbre)) ;
	      if( ( noeud_fd = noeud_creer( num_fd , 
					    NULL , NULL , NULL , 
					    fonction_affectation ) ) == NULL )
		return(ERR_DEB_MEMOIRE) ;
	    }
	  
	  /* Rattachement au noeud */
	  if( ( noerr = noeud_sad_ecrire( noeud , noeud_fd ) ) )
	    return(noerr) ; 
	}
  
    }
  /* Fermeture */
  fclose(fd) ; 
  
  return(OK) ; 
}



/*
 * Sauvegarde d'un arbre dans un fichier 
 */


static 
err_t ab_sauver_bis( const noeud_t * racine , 
		     FILE * fd  ,						/* File descriptor du fichier de chargement */
		     err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) 	/* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ; 
  int num_noeud = -1 ; 
  int num_fg = -1 ; 
  int num_fd = -1 ; 

  /* 
   * Sauvegarde du noeud racine 
   * Creation 1 ligne : num_noeud num_fils_gauche num_fils_droit <etiquette> 
   */
  
  /* --- Ecriture des numeros de noeud */
  if( ! noeud_existe( racine ) )
    return(OK) ; 

  num_noeud = noeud_numero_lire(racine) ; 

  noeud_t * noeud_fg = noeud_sag_lire(racine) ;
  noeud_t * noeud_fd = noeud_sad_lire(racine) ;

  if( noeud_existe(noeud_fg) )
    num_fg = noeud_numero_lire(noeud_fg)  ;

  if( noeud_existe(noeud_fd) )
    num_fd = noeud_numero_lire(noeud_fd)  ;

  fprintf( fd , "%d %d %d " , num_noeud , num_fg , num_fd ) ;
  
  /* -- Ecriture etiquette */
  if( (noerr = fonction_sauvegarde( noeud_etiquette_lire(racine) , 
				    fd ) ) )
    return(noerr) ; 

  fprintf( fd , "\n" ) ; 
      
  /* 
   * Sauvegarde des noeuds dans les sous arbres gauche et droit 
   */
  if( noeud_existe(noeud_fg) )
    {
      if( ( noerr = ab_sauver_bis( noeud_fg ,  fd , fonction_sauvegarde ) ) )
	return(noerr) ; 
    }
  
  if( noeud_existe(noeud_fd) )
    {
      if( ( noerr = ab_sauver_bis( noeud_fd ,  fd , fonction_sauvegarde ) ) )
	return(noerr) ; 
    }

  return(OK) ; 
}

extern 
err_t ab_sauver( const ab_t * arbre  ,						/* Arbre Binaire d'elements a charger */
		 char *  nom_fichier ,						/* Nom du fichier de chargement */
		 err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) 	/* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ; 
  FILE * fd = NULL ; 


  /* Ouverture fichier en ecriture */
  if( (fd = fopen( nom_fichier , "w" ) ) == NULL )
    {
      fprintf( stderr , "ab_sauver: ouverture en ecriture du fichier %s impossible\n" , 
	       nom_fichier ) ; 
      return(ERR_NOM_FICHIER) ;
    }

  /* test si arbre vide */
  if( !ab_existe( arbre )  )
    return(OK); 

  /* 
   * Sauvegarde
   */  
  
  if( ( noerr = ab_sauver_bis(  ab_racine_lire(arbre) , fd  ,fonction_sauvegarde ) ) )
    return(noerr) ; 

  /* Fermeture */
  fclose(fd) ; 
  
  return(OK) ; 
}

/*
 * Recherche du pere d'un noeud dans un arbre 
 */

extern
noeud_t * ab_pere_rechercher( const ab_t * arbre , 
			      const noeud_t * noeud_fils )
{
  /***********
   * A FAIRE *
   ***********/
  return(NULL);
}

