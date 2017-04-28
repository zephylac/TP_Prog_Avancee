#include <avl.h>


 static
 err_t rotation_gauche(noeud_t ** noeud)
{
  if(*noeud != NULL){
  	noeud_t * nouveau = (*noeud)->droit;
	nouveau->gauche = *noeud;
	(*noeud)->droit = nouveau->gauche;
	*noeud = nouveau;

  }
  return OK;
} 

static
err_t rotation_droite(noeud_t ** noeud)
{
  if(*noeud != NULL){
  	noeud_t * nouveau = (*noeud)->gauche;
	nouveau->droit = *noeud;
	(*noeud)->gauche = nouveau->droit;
	*noeud = nouveau;
  }
  return OK;
}

static
err_t rotation_gauche_droite(noeud_t ** noeud)
{
  rotation_gauche(&((*noeud)->gauche));
  rotation_droite(noeud);
  return OK;
}

static
err_t rotation_droite_gauche(noeud_t ** noeud)
{
  rotation_droite(&((*noeud)->droit));
  rotation_gauche(noeud);
  return OK;
}

static
int avl_desequilibre(noeud_t * noeud)
{
  if(noeud == NULL) return 0;
  return (noeud_hauteur(noeud->gauche,0) - noeud_hauteur(noeud->droit,0));
}


static
void avl_equilibrer_bis(noeud_t ** noeud)
{
  if(*noeud != NULL && ((*noeud)->gauche != NULL || (*noeud)->droit != NULL))
  {
  	int res = avl_desequilibre(*noeud);
	if(res == 2)
	{
		int gauche = avl_desequilibre((*noeud)->gauche);
		if(gauche == 1 || gauche == 0) rotation_droite(noeud);
		else if(gauche == -1) rotation_gauche_droite(noeud);
	}
	else if(res == -2)
	{
		int droite = avl_desequilibre((*noeud)->droit);
		if(droite == 1) rotation_droite_gauche(noeud);
		if(droite == -1 || droite == 0) rotation_gauche_droite(noeud);
	}
	avl_equilibrer(&((*noeud)->gauche);
	avl_equilibrer(&((*noeud)->droit);
  }
}

extern
err_t avl_equilibrer(avl_t * arbre)
{
	avl_equilibrer_bis(&(arbre->racien));
	return OK;
}
	
extern
noeud_t * avl_racine_lire( const avl_t * arbre ) 
{
  return(abr_racine_lire(arbre )) ; 
}

extern
err_t avl_racine_ecrire( avl_t * arbre , 
			noeud_t * racine ) 
{
  return(abr_racine_ecrire( arbre , racine )) ; 
}

extern
int avl_taille_lire( const avl_t * arbre ) 
{
  return(abr_taille_lire(arbre ) ) ; 
}

extern
err_t avl_taille_incrementer( avl_t * arbre ) 
{
  return(abr_taille_incrementer(arbre ) ) ; 
}

extern
err_t avl_taille_decrementer( avl_t * arbre ) 
{
return(abr_taille_decrementer(arbre)) ; 
}


/*
 * Tests
 */

extern
booleen_t avl_existe( const avl_t * arbre )
{
return(abr_existe(arbre)) ; 
}

extern
booleen_t avl_vide( const avl_t * arbre )
{
return(abr_vide(arbre)) ; 
}

/*
 * Creation 
 */

extern
avl_t * avl_creer( err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	/*!< Fonction d'affectation d'un element */
		   err_t (*fonction_destruction)( void * e) ,			/*!< Fonction de destruction d'un element */
		   int (*fonction_comparaison) ( const void * e1 , const void * e2) )		/*!< Fonction de comparaison de 2 elements */
{
  return(abr_creer( fonction_affectation ,
		    fonction_destruction,
		    fonction_comparaison ) ); 
}


/*
 * Destruction 
 */

extern 
err_t avl_detruire( avl_t ** arbre ) 
{
 return(abr_detruire(arbre)) ; 
}

/*
 * Affichage 
 */


extern 
void avl_afficher( const avl_t * arbre , 
		   void (*fonction_affichage)(const void *) ,
		   const ab_parcours_t parcours ) 
{
  return(abr_afficher( arbre , 
		       fonction_affichage ,
		       parcours )) ; 
}


/*
 * Insertion d'une valeur dans un AVL
 */

extern
err_t avl_inserer( avl_t * arbre  ,
		   void * etiquette ) 
{
  return(abr_inserer( arbre  ,
		      etiquette ) ) ; 
}

/*
 * Suppression d'une valeur dans un AVL
 */

extern 
booleen_t avl_supprimer( avl_t * arbre ,
			 void * etiquette ) 
{
  return(abr_supprimer(arbre , etiquette ) ) ; 
  
} 

/*
 * Chargement d'un arbre a partir d'un fichier 
 */

extern 
err_t avl_charger( avl_t ** arbre  ,						    /* Arbre Binaire d'elements a charger */
		   char *  nom_fichier ,					    /* Nom du fichier de chargement */
		   err_t (*fonction_affectation)( void * e1 , void * e2 ) ,	    /* fonction d'affectation d'un element */ 
		   err_t (*fonction_destruction)(void * e) ,			    /* fonction de destruction d'un element */
		   int (*fonction_comparaison) ( const void * e1 , const void * e2) , /* fonction de comparasion de 2 etiquettes */
		   err_t (*fonction_chargement)(void *  e, FILE *  desc ) ) 	    /* Fonction de chargement d'un element */
{
 return(abr_charger( arbre  ,	
		     nom_fichier ,
		     fonction_affectation ,
		     fonction_destruction ,
		     fonction_comparaison ,
		     fonction_chargement )) ; 
}

/*
 * Sauvegarde d'un arbre dans un fichier 
 */

extern 
err_t avl_sauver( const avl_t * arbre  ,						/* Arbre Binaire d'elements a charger */
		  char *  nom_fichier ,						/* Nom du fichier de chargement */
		  err_t (*fonction_sauvegarde)(void *  e, FILE *  desc ) ) 	/* Fonction de sauvegarde d'un element */
{
 return(abr_sauver( arbre  ,
		    nom_fichier ,
		    fonction_sauvegarde) )  ;
}

/*
 * Recherche du pere d'un noeud dans un arbre 
 */



extern
noeud_t * avl_pere_rechercher( const avl_t * arbre , 
			      const noeud_t * noeud_fils )
{
return(abr_pere_rechercher( arbre , 
			    noeud_fils )) ; 
}


/*
 * Recherche d'un element dans un arbre 
 */

extern
booleen_t avl_rechercher( noeud_t ** result , 
			  const avl_t * arbre , 
			  const void * etiquette )
{
  return(abr_rechercher( result , 
			 arbre , 
			 etiquette )) ; 
}
