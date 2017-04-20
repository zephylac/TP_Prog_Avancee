#include <ab_animaux.h>
#include <string.h>
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
	char chaine[50];
	char chaine2[50];

	string_t * rep;
	string_t * ques;
	noeud_t * noeud2;
	int taille;
	booleen_t test = FAUX;

	if(noeud == NULL){
		noeud_afficher(pere,string_string_afficher_cb);
		printf("Je donne ma langue au chat.\nQuelle est la réponse ? ");
		scanf("%s",chaine);
		rep = string_creer(chaine);
		
		printf("Donnez une question dont la réponse est oui pour \"%s\" et non pour \"",chaine);
		noeud_afficher(pere,fonction_affichage);
		printf("\" : ");
		scanf("%s",chaine2);
		ques = string_creer(chaine2);

		taille = ab_taille_lire(arbre);
		noeud2 = noeud_creer(taille + 1,pere->etiquette,NULL,NULL,string_copier_cb);
		ab_taille_incrementer(arbre);
		noeud_sad_ecrire(pere,noeud2);
		
		noeud_etiquette_ecrire(pere, ques, string_copier_cb);

		taille = ab_taille_lire(arbre);
		noeud2 = noeud_creer(taille + 1,rep,NULL,NULL, string_copier_cb);
		ab_taille_incrementer(arbre);
		noeud_sag_ecrire(pere,noeud2);

	}
	else{

		noeud_afficher(noeud,string_string_afficher_cb);
		printf("\n");
		test = OuiNon_saisir("Reponse : ") ;       
		if(test){
			ab_animaux_reconnaitre(arbre,noeud->gauche,noeud,fonction_affectation,string_string_afficher_cb);
		}
		else{
			ab_animaux_reconnaitre(arbre,noeud->droit,noeud,fonction_affectation,string_string_afficher_cb);
		}
	}
}
