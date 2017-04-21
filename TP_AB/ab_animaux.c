#include <ab_animaux.h>
#include <string.h>
#define MAX_NAME_SZ 256
/*
 * Affichage 
 */

static
void ab_animaux_afficher_bis(const noeud_t * noeud, void (*afficher)(const void *),int profondeur, int position )
{

if(noeud != NULL) {
	int i;

          for( i = 0; i < profondeur; i++ )
                 printf("|-----");
          switch(position){
                  case 0:
                          printf("[] ");
                          break;
                  case 1:
                          printf("[oui] ");
                          break;
                  case 2:
                          printf("[non] ");
                          break;
            default:
                    break;
          }
          afficher( noeud->etiquette );
          printf("\n");

  }

  if( noeud->gauche != NULL ){
            ab_animaux_afficher_bis( noeud->gauche, afficher, profondeur+1, 1 );
  }
  if( noeud->droit != NULL ){
            ab_animaux_afficher_bis( noeud->droit, afficher, profondeur+1, 2 );
  }
}

extern 
void ab_animaux_afficher( const ab_t * arbre , 
			  void (*fonction_affichage)(const void *)) 
{
	ab_animaux_afficher_bis(arbre->racine, fonction_affichage, 0, 0); 
}

/*
 * Reconnaissance 
 */

extern 
void ab_animaux_reconnaitre( ab_t * arbre , 
			     noeud_t * noeud,
			     noeud_t * pere,
			     err_t (*fonction_affectation)(void * , void *) ,
			     void (*fonction_affichage)(const void *)) 
{
	
	string_t * rep = NULL;
	string_t * ques = NULL;
	noeud_t * noeud2;
	int taille;
	booleen_t test = FAUX;
	

	if(noeud == NULL){
		char *name = malloc (MAX_NAME_SZ);
		char *name1 = malloc (MAX_NAME_SZ);

		if (name == NULL || name1 == NULL) {
        		printf ("No memory\n");
        		return ;
    		}

		noeud_afficher(pere,string_string_afficher_cb);
		printf("Je donne ma langue au chat.\nQuelle est la réponse ? ");
		fgets (name, MAX_NAME_SZ, stdin);

    		if ((strlen(name)>0) && (name[strlen (name) - 1] == '\n'))
        		name[strlen (name) - 1] = '\0';
		
		rep = string_creer(name);

		printf("Donnez une question dont la réponse est oui pour \"%s\" et non pour \"",name);
		noeud_afficher(pere,fonction_affichage);
		printf("\" : ");
		
		fgets (name1, MAX_NAME_SZ, stdin);

    		if ((strlen(name1)>0) && (name1[strlen (name1) - 1] == '\n'))
        		name1[strlen (name1) - 1] = '\0';
		
		ques = string_creer(name1);

		taille = ab_taille_lire(arbre);
		noeud2 = noeud_creer(taille + 1,pere->etiquette,NULL,NULL,string_copier_cb);
		ab_taille_incrementer(arbre);
		noeud_sad_ecrire(pere,noeud2);
		noeud_etiquette_ecrire(pere, ques, string_copier_cb);
	        if(ques != NULL) string_detruire(&ques);	
		free (name);

		taille = ab_taille_lire(arbre);
		noeud2 = noeud_creer(taille + 1,rep,NULL,NULL, string_copier_cb);
		ab_taille_incrementer(arbre);
		noeud_sag_ecrire(pere,noeud2);
		if(rep != NULL) string_detruire(&rep);
		free (name1);
	}
	else{

		noeud_afficher(noeud,string_string_afficher_cb);
		printf("\n");
		test = OuiNon_saisir("Reponse : ") ;       
		if(test){
			if(noeud->gauche == NULL){
				printf("J'ai trouvee, programme fini\n");
				return ;
			}
			else{
				ab_animaux_reconnaitre(arbre,noeud->gauche,noeud,fonction_affectation,string_string_afficher_cb);
		
			}
		}	
		else{
			ab_animaux_reconnaitre(arbre,noeud->droit,noeud,fonction_affectation,string_string_afficher_cb);
		}
	}
}
