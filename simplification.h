#ifndef _SIMPLIFICATION_H_
#define _SIMPLIFICATION_H_

#include "image.h"
#include "geom2d.h"
#include "contour_image.h"

// Courbes de Bezier de degré 3

typedef struct Cellule_Liste_Bezier3_{
    Bezier3 data;
    struct Cellule_Liste_Bezier3_ *suiv;
} Cellule_Liste_Bezier3;

typedef struct Liste_Bezier3_{
    unsigned int taille;
    Cellule_Liste_Bezier3 *first;
    Cellule_Liste_Bezier3 *last;
} Liste_Bezier3;

typedef struct Tableau_Bezier3_{
    unsigned int taille;
    Bezier3 *tab;
} Tableau_Bezier3;

typedef struct Cellule_Liste_Contour_Bezier_
{
	Liste_Bezier3 data;    /* donn�e de l'�l�ment de liste */
	struct Cellule_Liste_Contour_Bezier_* suiv; /* pointeur sur l'�l�ment suivant */
} Cellule_Liste_Contour_Bezier;

typedef struct Liste_Contour_Bezier_
{
	unsigned int taille;        /* nombre d'�l�ments dans la liste */
	Cellule_Liste_Contour_Bezier *first; /* pointeur sur le premier �l�ment de la liste */
	Cellule_Liste_Contour_Bezier *last;  /* pointeur sur le dernier �l�ment de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Contour_Bezier;

//Fonction simplifiant un contours avec des courbes de bezier 01
Liste_Contour simplification_segments(Liste_Contour T, double d);

//Fonction approximant une liste de points en une courbe de bezier 2
Bezier2 approx_bezier2(Tableau_Point P, int j1, int j2);

//Fonction approximant une liste de points en une courbe de bezier 2
Bezier3 approx_bezier3(Tableau_Point P, int j1, int j2);

//Fonction qui convertis une liste chainée en un tableau
Tableau_Bezier3 sequence_bezier3_liste_vers_tableau(Liste_Bezier3 L);

//Fonction simplifiant un contours avec des courbes de bezier 2
Liste_Contour_Bezier simplification_douglas_peucker_bezier2(Liste_Contour T, double d);

//Fonction simplifiant un contours avec des courbes de bezier 3
Liste_Contour_Bezier simplification_douglas_peucker_bezier3(Liste_Contour T, double d);

Liste_Contour_Bezier creer_liste_Contour_Bezier_vide();

//affiche les infos d'une image après simplification par bezier 2 ou 3
void afficher_infos_bis(Liste_Contour_Bezier LC);

//ecrit le contours d'une image simplfiee par des courbes de bezier dans un fichier
void ecrire_contour_bezier_fichier(Liste_Contour_Bezier LC, char* nomSortie);

#endif /* _SIMPLIFICATION_H_ */
