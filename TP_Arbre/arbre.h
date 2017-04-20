#ifndef ARBRE_H
#define ARBRE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR    1
#define NO_ERROR 0

// Print debugging
extern bool tree_printDebug;

/* ----------------- */
/* TYPES DEFINITIONS */
/* ----------------- */

typedef struct arbre_s{
	int numero;
	void * etiquette;
	struct arbre_s * gauche;
	struct arbre_s * droite;
	struct arbre_s * pere;
} arbre;



// Retourne le nombre d'un noeud
int noeud_numero_lire(arbre * a);

// Ecrit le nombre dans un noeud
void noeud_numero_ecrire(arbre * a, int numero);

// Retourn l'etiquette d'un noeud
void * noeud_etiquette_lire(arbre * a);

// Ecrit l'etiquette dans un noeud
void noeud_etiquette_ecrire(arbre * a, void * etiquette);

// Retourne la branche gauche d'un noeud
arbre * noeud_brancheGaucheLire(arbre * a);

// Retourne la branche droite d'un noeud
arbre * noeud_brancheDroiteLire(arbre * a);

// Ecrit sur la branche gauche d'un arbre
void noeud_brancheGaucheEcrire(arbre * a, arbre * gauche);

// Ecrit sur la branche droite d'un noeud
void noeud_brancheDroiteEcrire(arbre * a, arbre * droite);

// Retourne vrai si le noeud existe
bool noeud_existe(arbre * a);

// Retourne vrai si c'est une feuille 
bool noeud_feuille(arbre * a);

// Retourne vrai si c'est un pere 
bool noeud_est_pere(arbre * a);

// Cree un noeud
arbre * noeud_creer(int numero, void * etiquette, arbre * pere, arbre * gauche, arbre * droite);

//Affiche un noeud
void noeud_afficher(arbre * a, void (*etiquettePrint)(void *));


// Detruit un noeud
void noeud_detruire(arbre ** a);

// Detruit le noeud et ses enfants
void noeud_detruireRec(arbre ** a);

// Retourne le pointeur du noeud recherché par son numéro
arbre * noeud_numero_rechercher(arbre * a, int numero);

// Retourne le pointeur du noeud recherché 
arbre * noeud_rechercher(arbre * a, arbre * abis);

// Print a givent amount of space (for drawing the tree)
void printDepth(int depth);

// Affiche le noeud et ses enfants
void ab_print_enfant(arbre * a, void (*etiquettePrint)(void *), int depth);

// Affiche l'arbre
void ab_afficher(arbre * a, void (*etiquettePrint)(void *));

//Lit la racine de l'arbre
arbre * ab_racine_lire(arbre * a);

//Ecrit la racine de l'arbre
arbre * ab_racine_ecrire(void * etiquette, arbre * gauche, arbre * droite);

//Lit la taille d'un arbre
int ab_taille_lire(arbre * a);
	
//Retourne vrai si l'arbre existe
bool ab_existe(arbre * a);

//Retourn vrai si l'arbre vrai	
bool ab_vide(arbre * a);

/* ---------------------------------------- */
/* FUNCTIONS FOR PRINTING SOME LABELS TYPES */
/* ---------------------------------------- */

// Print a label that is an int
void label_printInt(void * e);

// Print a label that is a long
void label_printLong(void * e);

// Print a label that is a float
void label_printFloat(void * e);

// Print a label that is a double
void label_printDouble(void * e);

// Print a label that is a boolean
void label_printBool(void * e);

// Print a label that is a pointer
void label_printPointer(void * e);

// Print a label that is a char
void label_printChar(void * e);

// Print a label that is a string
void label_printString(void * e);


/* ---------------------- */
/* FUNCTIONS FOR COLORING */
/* ---------------------- */

#define TREE_COLOR_RED     "\x1b[31m"
#define TREE_COLOR_GREEN   "\x1b[32m"
#define TREE_COLOR_YELLOW  "\x1b[33m"
#define TREE_COLOR_BLUE    "\x1b[34m"
#define TREE_COLOR_MAGENTA "\x1b[35m"
#define TREE_COLOR_CYAN    "\x1b[36m"
#define TREE_COLOR_RESET   "\x1b[0m"

#endif
