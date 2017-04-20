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
			     err_t (*fonction_affectation)(void * , void *) ,
			     void (*fonction_affichage)(const void *)) 
{
	char reponse[3];
	char reponse1[50];
	char question[50];
	noeud_t * noeud1;
	noeud_t * noeud2;
	int taille;

	if(noeud == NULL){
		noeud1 = ab_pere_rechercher(arbre, noeud);
		printf("Je donne ma langue au chat.\nQuelle est la réponse ? ");
		scanf("%s",reponse1);
		printf("Donnez une question dont la réponse est oui pour \"%s\" et non pour \"%s\" : ",reponse1,noeud1->etiquette);
		scanf("%s",question);
		taille = ab_taille_lire(arbre);
		noeud2 = noeud_creer(taille + 1,noeud1->etiquette,NULL,NULL,string_copier_cb);
		ab_taille_incrementer(arbre);
		noeud_sad_ecrire(noeud1,noeud2);
		
		noeud_etiquette_ecrire(noeud1, question, string_copier_cb);

		taille = ab_taille_lire(arbre);
		noeud2 = noeud_creer(taille + 1,reponse1,NULL,NULL, string_copier_cb);
		ab_taille_incrementer(arbre);
		noeud_sag_ecrire(noeud1,noeud2);

	}
	else{

		noeud_afficher(noeud,string_string_afficher_cb);
		printf("\nRéponse : ");
		scanf("%s",reponse);

		/*while((strcmp("oui",reponse)) != 0 && (strcmp("non",reponse)) != 0){
			printf("Réponse : oui/non\n");
			scanf("%s",reponse);
		}*/
		if(strcmp("oui",reponse) == 0){
			ab_animaux_reconnaitre(arbre,noeud->gauche,fonction_affectation,string_string_afficher_cb);
		}
		if(strcmp("non",reponse) == 0){
			ab_animaux_reconnaitre(arbre,noeud->droit,fonction_affectation,string_string_afficher_cb);
		}
	}
}
