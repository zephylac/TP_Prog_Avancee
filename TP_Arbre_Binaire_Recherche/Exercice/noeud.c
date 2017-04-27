#include <noeud.h>

/* Etiquette */                                                                 
                                                                                
extern                                                                          
void * noeud_etiquette_lire( const noeud_t * noeud )                            
{                                                                               
  if(noeud != NULL)                                                             
          return noeud->etiquette;                                              
  return NULL;                                                                     
  return(NULL) ;                                                                   
}                                                                                  
                                                                                   
extern                                                                             
err_t noeud_etiquette_ecrire( noeud_t * noeud ,                                    
                              void * etiquette ,                                   
                              err_t (*affecter)( void * e1 , void * e2 ) )         
{                                                                                  
  if(noeud != NULL)                                                                
          affecter(&(noeud->etiquette), etiquette);                                
  return(OK) ;                                                                     
}                                                                                  
                                                                                   
/* Sous arbre gauche */                                                            
                                                                                   
extern                                                                             
noeud_t * noeud_sag_lire( const noeud_t * noeud )                                  
{                                                                                  
  if(noeud != NULL)                                                                
          return noeud->gauche;                                                    
  return(NULL) ;                                                                   
}                                                                                  
                                                                                   
extern                                                                             
err_t noeud_sag_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_gauche )           
{                                                                                  
  if(noeud != NULL)                                                                
                noeud->gauche = sous_arbre_gauche;                                 
  return(OK) ;                                                                     
}                                                                                  
                                                                                   
/* Sous arbre droit */                                                             
                                                                                   
extern                                                                             
noeud_t * noeud_sad_lire( const noeud_t * noeud )                                  
{                                                                                  
  if(noeud != NULL)                                                                
                return noeud->droit;                                               
  return(NULL) ;                                                                   
}                                                                                  
                                                                                   
extern                                                                             
err_t noeud_sad_ecrire( noeud_t * noeud ,  noeud_t * sous_arbre_droit )            
{                                                                                  
  if(noeud != NULL)                                                                
                noeud->droit = sous_arbre_droit;                                   
  return(OK) ;                                                                     
}                                                                                  
                                                                                   
/*                                                                                 
 * Existance ?                                                                     
 */                                                                                
                                                                                   
booleen_t                                                                          
noeud_existe( const noeud_t * noeud )                                           
{                                                                               
if(noeud == NULL)                                                               
        return(FAUX);                                                           
return(VRAI);                                                                   
  /*return noeud != NULL;*/                                                     
}                     

/*                                                                              
 * Feuille ?                                                                    
 */                                                                             
extern                                                                          
booleen_t noeud_feuille( const noeud_t * noeud )                                
{                                                                               
  return noeud != NULL && noeud->gauche == NULL && noeud->droit == NULL;        
}                                                                               
                                                                                
/*                                                                              
 * Parents ?                                                                    
 */                                                                             
                                                                                
extern                                                                          
booleen_t noeud_est_pere( const noeud_t * noeud_pere ,                          
                          const noeud_t * noeud_fils )                          
{                                                                               
  if(noeud_pere->gauche == noeud_fils || noeud_pere->droit == noeud_fils)       
          return(VRAI);                                                         
  else{                                                                         
          return(FAUX) ;                                                        
  }                                                                             
}                                                                               
                                                                                
/*                                                                              
 * Creation                                                                     
 */                                                                             
                                                                                
extern                                                                          
noeud_t * noeud_creer( void * etiquette ,                                       
                       noeud_t * sous_arbre_gauche ,                            
                       noeud_t * sous_arbre_droit ,                             
                       err_t (*affecter)( void * e1 , void * e2 ) )             
{                                                                               
  noeud_t * noeud = NULL ;                                                      
                                                                                
  noeud = malloc(sizeof(noeud_t));                                              
                                                                                
        noeud->etiquette = NULL;                                                
        affecter(&(noeud->etiquette), etiquette);                               
        noeud->gauche   = sous_arbre_gauche;                                    
        noeud->droit    = sous_arbre_droit;                                     
                                                                                
  return( noeud ) ;                                                             
}                                                                               
                                                                                
/*                                                                              
 * Destruction                                                                  
 */                                                                             
                                                                                
extern                                                                          
err_t noeud_detruire( noeud_t ** noeud ,                                        
                      err_t (*detruire)( void * e) )                            
{                                                                               
  detruire(&((*noeud)->etiquette));                                   
  free((*noeud));                                                     
  (*noeud) = NULL;                                                    
  return(OK) ;                                                                  
}          

/*                                                                              
 * Affichage                                                                    
 */                                                                             
                                                                                
extern                                                                          
void noeud_afficher( const noeud_t * noeud ,                                    
                     void (*afficher)(const void *) )                           
{                                                                               
  if(noeud != NULL){                                                            
                /*printf("Numero    : %i\n",noeud->numero);*/                   
                afficher(noeud->etiquette);                                     
  }                                                                             
}                                                                               
/*
 * Recherche noeud min/max
 */
noeud_t * noeud_min_max(noeud_t * noeud){
	if(noeud->droit == NULL){
		return noeud;
	}
	else{
		return(noeud_min_max(noeud->droit));
	}
	return NULL;
}


extern int noeud_nb_fils(noeud_t * noeud){
	int res = -1;
	if(noeud != NULL){
		res++;
		if(noeud->gauche != NULL)
			res++;
		if(noeud->droit  != NULL)
			res++;
	}
	return res;
}
/*
 * Sauvegarde dans un fichier 
 */

extern 
err_t noeud_fd_sauver( noeud_t * noeud  ,	                  /* Noeud a sauvegarder */
		       FILE * fd , 		                  /* Descripteur fichier  */
		       err_t (*sauver)( void * e, FILE *  desc) ) /* Fonction de sauvegarde d'un element */
{
  err_t noerr = OK ;

  if( ! noeud_existe( noeud ) ) 
    return(OK) ; 

  if( ( noerr = sauver( noeud->etiquette , fd ) ) )
   return(noerr) ; 

 return(OK) ; 
}

/*
 * Recherches d'un noeud dans un arbre 
 */

extern
booleen_t noeud_rechercher( noeud_t ** result ,			 /* Resultat: @ du noeud trouve */  
			    noeud_t * racine  ,	         /* Racine de l'arbre de recherche */
			    const void * etiquette  ,		 /* Valeur a rechercher dans l'arbre */
			    int (*comparer)(const void * n1 , const void * n2) ) /* Fonction de comparaison des etiquettes */
{
  if(racine == NULL) return(FAUX);                                                 
  int cmp = comparer(etiquette, racine->etiquette);                                 
  if(cmp < 0) return(noeud_rechercher(result,racine->gauche, etiquette, comparer));   
  if(cmp > 0) return(noeud_rechercher(result,racine->droit, etiquette, comparer));       
  if(cmp == 0){                                                                    
        *result = racine;                                                           
        return(VRAI);                                                              
  } 
  return(FAUX);
}

/*
 * Insertion d'un noeud dans un ABR (aux feuilles)
 * Le noeud doit etre cree avec son etiquette
 */

extern
err_t noeud_inserer( noeud_t * noeud ,			          /* @ du noeud a inserer */  
		     noeud_t ** racine  ,	                  /* Racine de l'arbre de recherche */
		     int (*comparer)(const void * n1 , const void * n2))     /* Fonction de comparaison des etiquettes */
{
  int cmp = comparer(noeud->etiquette, (*racine)->etiquette);                                     
                                                                                   
  if(cmp ==0) return(-1);                                                          
  if(cmp < 0){                                                                     
        if((*racine)->gauche == NULL){                                                
                noeud_sag_ecrire((*racine),noeud);                                    
                return(OK);                                                        
        }                                                                          
        else                                                                       
        {                                                                          
        return(noeud_inserer(noeud,&((*racine)->gauche),comparer));            
        }                                                                          
  }                                                                                
  if( cmp > 0)                                                                     
  {                                                                                
        if((*racine)->droit == NULL){                                                 
                noeud_sad_ecrire((*racine),noeud);                                    
                return(OK);                                                        
        }                                                                          
        else                                                                       
        {                                                                          
        return(noeud_inserer(noeud,&((*racine)->droit),comparer));             
        }                                                                          
  }
  return(OK)  ;
}


/*
 * Suppression d'un noeud dans un ABR
 * Renvoie VRAI si le noeud existait dans l'arbre 
 *         FAUX sinon 
 */

extern
booleen_t noeud_supprimer( void * etiquette ,			 /* valeur a supprimer de l'arbre */ 
			   noeud_t ** racine  ,	                  /* Racine de l'arbre de recherche */
			   err_t (*detruire)( void * e ) , /* Fonction de destruction des etiquettes */
			   int (*comparer)(const void * n1 , const void * n2) ) 
{
  if((*racine) == NULL)                                                               
  {                                                                                
        return(OK);                                                                
  }                                                                                
  int cmp = comparer(etiquette, (*racine)->etiquette);                                     
  if(cmp ==0){
	 int nbFils = noeud_nb_fils(*racine);
         if(nbFils == 0)
         	return noeud_detruire(racine, detruire);

         if(nbFils == 1){

                noeud_t * tmp = (*racine)->gauche;
                if(tmp == NULL)
                	tmp = (*racine)->droit;
                if(tmp == NULL)
                        printf("Erreur, y'a une erreur.\n");

                noeud_t * tmp2 = *racine;
                (*racine)->gauche = NULL;
                (*racine)->droit  = NULL;
                noeud_detruire(&tmp2, detruire);
                *racine = tmp;
                return VRAI;
         }
	if(nbFils == 2){
		noeud_t * max = noeud_min_max((*racine)->gauche);
		void * tmp           = (*racine)->etiquette;
		(*racine)->etiquette = max->etiquette;
		max->etiquette       = tmp;
		noeud_supprimer(etiquette, &((*racine)->gauche), affecter, detruire, comparer);
		return VRAI;
	}
	return FAUX;  
  }                                                                                
  if(cmp < 0)                                                                      
  {                                                                                
        return(noeud_supprimer(etiquette,&((*racine)->gauche),detruire,comparer));         
  }                                                                                
    if( cmp > 0)                                                                   
  {                                                                                
        return(noeud_supprimer(etiquette,&((*racine)->droit),detruire,comparer));          
  }                                                                                
  return(FAUX) ;
}


