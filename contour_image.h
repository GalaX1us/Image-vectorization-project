#ifndef _CONTOUR_IMAGE_H_
#define _CONTOUR_IMAGE_H_

#include "image.h"
#include "geom2d.h"


typedef enum {NORD, EST, SUD, OUEST} Orientation;

typedef struct Robot_{
  Orientation o;
  double x,y;
}Robot;

/*---- le type cellule de liste de point ----*/
typedef struct Cellule_Liste_Point_
{
	Point data; 
	   /* donnee de l'element de liste */
	struct Cellule_Liste_Point_* suiv; /* pointeur sur l'element suivant */
} Cellule_Liste_Point;



/*---- le type liste de point ----*/
typedef struct Liste_Point_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Point *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Point *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Point;

typedef struct Cellule_Liste_Contour_
{
	Liste_Point data;    /* donnee de l'element de liste */
	struct Cellule_Liste_Contour_* suiv; /* pointeur sur l'�l�ment suivant */
} Cellule_Liste_Contour;

typedef struct Liste_Contour_
{
	unsigned int taille;        /* nombre d'elements dans la liste */
	Cellule_Liste_Contour *first; /* pointeur sur le premier element de la liste */
	Cellule_Liste_Contour *last;  /* pointeur sur le dernier element de la liste */
	                       /* first = last = NULL et taille = 0 <=> liste vide */
} Liste_Contour;

typedef Liste_Point Contour; /* type Contour = type Liste_Point */

/*---- le type tableau de point ----*/
typedef struct Tableau_Point_
{
	unsigned int taille; /* nombre d'�l�ments dans le tableau */
	Point *tab;          /* (pointeur vers) le tableau des �l�ments */
} Tableau_Point;

/* Affiche les positions du robots au fur et a mesure */
void memoriser_position(Robot r);

/* cherche et renvoie le pixel de départ */
bool trouver_pixel_depart(double *x,double *y, Image I); 

/*crée et intialise un robot*/
Robot creer_robot(double x,double y,Orientation o);

/*Fait avancer le robot*/
void avancer(Robot *r);

/* Tourne le robot a droite */
void droite(Robot *r);

/* Tourne le robot a gauche */
void gauche(Robot *r);

/* donne les pixels devant à gauche/droite du robot */
void pixels_adjacents(Robot r, Image I, Pixel *pG, Pixel *pD);

/* trouve la nouvelle orientation du robot */
void nouvelle_orientation(Robot *r, Image I);

//cherche un contour d'une image
Contour ChercherContour(Image I, Image *mask, double x, double y);

//cherche tous les contours d'une image
Liste_Contour ChercherPlusieurContour(Image I);

//crée une cellule contenant un points
Cellule_Liste_Point *creer_element_liste_Point(Point v);

//crée une liste de points vide
Liste_Point creer_liste_Point_vide();

//Ajoute un point à une liste de points
void ajouter_element_liste_Point(Liste_Point *L, Point e);

//Vide une liste de points
Liste_Point supprimer_liste_Point(Liste_Point L);

//créer une liste de contours vide
Liste_Contour creer_liste_Contour_vide();

//Creer une cellule pour mettre un nouveau contour
Cellule_Liste_Contour *creer_element_liste_Contour(Liste_Point v);

//Ajoute un contour à une liste de contours
void ajouter_element_liste_Contour(Liste_Contour *L, Liste_Point e);

//Vide une liste de points
Liste_Contour supprimer_liste_Contour(Liste_Contour L);

//concatene deux liste de points
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2);

//Convertis une liste chainée en un tableau
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L);

//renvoie le nombre de segments d'une partie des contours de l'image
UINT nombre_segments(Liste_Point LP);

//renvoie le nombre de segment total dans tous les contours d'une image
UINT nombre_segments_total(Liste_Contour LC);

//renvoie le nombre de contours
UINT nombre_contours(Liste_Contour LC);

//affiche les information d'un contour à l'écran
void afficher_infos(Liste_Contour LC);

//écris le contour d'une image dans un fichier
void ecrire_contour_fichier(Liste_Contour LC, char* nomSortie);


#endif /* _CONTOUR_IMAGE_H_ */
