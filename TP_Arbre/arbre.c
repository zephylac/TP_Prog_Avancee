#include "arbre.h"

// Default value for debug.
bool arbre_printDebug = false;


// Retourne le nombre d'un noeud
int noeud_numero_lire(arbre * a){
	if(a != NULL)
		return a->numero;
	return ERROR;
}

// Ecrit le nombre dans un noeud
void noeud_numero_ecrire(arbre * a, int numero){
	if(a != NULL)
		a->nb = numero;
}

// Retourn l'etiquette d'un noeud
void * noeud_etiquette_lire(arbre * a){
	if(a != NULL)
		return a->etiquette;
	return NULL;
}

// Ecrit l'etiquette dans un noeud
void noeud_etiquette_ecrire(arbre * a, void * etiquette){
	if(a != NULL)
		a->etiquette = etiquette;
}

// Retourne la branche gauche d'un noeud
arbre * noeud_brancheGaucheLire(arbre * a){
	if(a != NULL)
		return a->gauche;
	return NULL;
}

// Retourne la branche droite d'un noeud
arbre * noeud_brancheDroiteLire(arbre * a){
	if(a != NULL)
		return a->droite;
	return NULL;
}

// Ecrit sur la branche gauche d'un arbre
void noeud_brancheGaucheEcrire(arbre * a, arbre * gauche){
	if(a != NULL)
		a->gauche = gauche;
}

// Ecrit sur la branche droite d'un noeud
void noeud_brancheDroiteEcrire(arbre * a, arbre * droite){
	if(a != NULL)
		a->droite = droite;
}

// Retourne vrai si le noeud existe
bool noeud_existe(arbre * a){
	return a != NULL;
}

// Retourne vrai si c'est une feuille 
bool noeud_feuille(arbre * a){
	return a != NULL && a->gauche == NULL && a->droite == NULL;
}

// Retourne vrai si c'est un pere 
bool noeud_est_pere(arbre * a){
	return !noeud_feuille(a);
}

// Cree un noeud
arbre * noeud_creer(int numero, void * etiquette, arbre * pere, arbre * gauche, arbre * droite){
	arbre * a = malloc(sizeof(arbre));

	a->numero 	= numero;
	a->etiquette  	= etiquette;
	a->pere 	= pere;
	a->gauche 	= gauche;
	a->droite  	= droite;

	return a;
}
/*
// Mis a jour des noeuds
void arbre_MAJArbre(arbre * a){
	if(a != NULL){
		if(a->gauche != NULL){
			a->gauche->pere = a;
			arbre_MAJArbre(a->gauche);
		}
		if(a->droite != NULL){
			a->droite->pere = a;
			arbre_MAJArbre(a->droite);
		}
	}
}
*/
//Affiche un noeud
void noeud_afficher(arbre * a, void (*etiquettePrint)(void *),){
	if(*a != NULL){
		printf("Numero    : %i\n",a->numero);
		etiquettePrintf(a->etiquette);
		printf("Pere 	  : %i\n",a->pere);
		
	}
}

// Detruit un noeud
void noeud_detruire(arbre ** a){
	if(*a != NULL)
		free(*a);
	*a = NULL;
}

// Detruit le noeud et ses enfants
void noeud_detruireRec(arbre ** a){
	if(*a != NULL){
		noeud_detruireRec(&((*a)->gauche));
		noeud_detruireRec((&((*a)->droite));
		noeud_detruire((a);
	}
}

// Retourne le pointeur du noeud recherché par son numéro
arbre * noeud_numero_rechercher(arbre * a, int numero){
	arbre * gauche, * droite;

	if(a != NULL){
		if(a->numero == numero)
			return a;

		gauche  = noeud_numero_rechercher(a->gauche, numero);
		droite = tree_numberSearch(a->droite, numero);

		if(gauche != NULL)
			return gauche;
		return droite;
	}
	return NULL;
}


// Retourne le pointeur du noeud recherché 
arbre * noeud_rechercher(arbre * a, arbre * abis){
	arbre * gauche, * droite;

	if(a != NULL){
		if(a->numero == abis->numero)
			if(a->pere == abis->pere)
				if(a->gauche == abis->gauche)
					if(a->droite == abis->droite)
						if(a->etiquette == abis->etiquette)
							return a;
	return NULL
}



// Print a givent amount of space (for drawing the tree)
void printDepth(int depth){
	int i;
	printf("%s", TREE_COLOR_YELLOW);
	for(i = 0 ; i < depth ; i++)
		printf("│   ");
}

// Affiche le noeud et ses enfants
void ab_print_enfant(arbre * a, void (*etiquettePrint)(void *), int depth){
	if(a != NULL){
		printf("%s", TREE_COLOR_RESET);
		etiquettePrint(a->etiquette);
		printf("%s", TREE_COLOR_RESET);

		if(arbre_printDebug){
			printf(" | {n°: %s%i%s} - {@: %s%p%s} - {father: %s%p%s} - {left: %s%p%s | right: %s%p%s}", 
							TREE_COLOR_BLUE, 
							a->numero,
							TREE_COLOR_RESET,
							TREE_COLOR_BLUE,
							a, 
							TREE_COLOR_RESET,
							TREE_COLOR_BLUE,
							a->pere,
							TREE_COLOR_RESET,
							TREE_COLOR_BLUE,
							a->gauche,
							TREE_COLOR_RESET,
							TREE_COLOR_BLUE,
							a->droite,
							TREE_COLOR_RESET);
		}

		// Affiche l'enfant de gauche
		if(a->gauche != NULL){
			printf("\n");
			printDepth(depth);

			if(a->droite != NULL)
				printf("├");
			else
				printf("└");

			printf("── ");
			ab_print_enfant(a->gauche, etiquetteAff, depth + 1);
		}


		// Affiche l'enfant de droite
		if(a->droite != NULL){
			printf("\n");
			printDepth(depth);
			printf("└── ");
			ab_print_enfant(a->droite, etiquettePrint, depth + 1);
		}
	}
}

//Lit la racine de l'arbre
arbre * ab_racine_lire(arbre * a){
	if(a->pere != NULL){
		ab_racine_lire(a->pere);
	}
	else{
		return(a);
	}
}

//Ecrit la racine de l'arbre
arbre * ab_racine_ecrire(void * etiquette, arbre * gauche, arbre * droite){
	arbre * a = malloc(sizeof(arbre));

	a->numero 	= 0;
	a->etiquette  	= etiquette;
	a->pere 	= NULL;
	a->gauche 	= gauche;
	a->droite  	= droite;

	return a;
}

//Lit la taille d'un arbre
ab_taille_lire(arbre * a){
	if(a->gauche == NULL && a->droite == NULL){
		return 0;
	}
	else{
		return 1 + ab_taille_lire(a->gauche) + ab_taille_lire(a->droite)
	}
}

//Retourne vrai si l'arbre existe
bool ab_existe(arbre * a){
	return a != NULL;
}

bool ab_vide(arbre * a){
	a = ab_racine_lire(a);
	if(a->gauche == NULL && a->droite == NULL){
		return 0;
	}
	else{
		return 1;
	}
}

// Affiche l'arbre
void ab_afficher(arbre * a, void (*etiquettePrint)(void *)){
	ab_print_enfant(t, etiquettePrint, 0);
	printf("\n");
}



/* ---------------------------------------- */
/* FUNCTIONS FOR PRINTING SOME LABELS TYPES */
/* ---------------------------------------- */

// Print a label that is an int
void label_printInt(void * e){
	int * i = e;
	printf("%i", *i);
}

// Print a label that is a long
void label_printLong(void * e){
	long * l = e;
	printf("%li", *l);
}

// Print a label that is a float
void label_printFloat(void * e){
	float * f = e;
	printf("%f", *f);
}

// Print a label that is a double
void label_printDouble(void * e){
	double * d = e;
	printf("%f", *d);
}

// Print a label that is a boolean
void label_printBool(void * e){
	bool * b = e;
	printf("%i", *b);
}

// Print a label that is a pointer
void label_printPointer(void * e){

	printf("%p", e);
}

// Print a label that is a char
void label_printChar(void * e){
	char * c = e;
	printf("%c", *c);
}

// Print a label that is a string
void label_printString(void * e){
	char * str = e;
	printf("%s", str);
}
