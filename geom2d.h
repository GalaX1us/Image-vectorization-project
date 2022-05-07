#ifndef _GEOM2D_H_
#define _GEOM2D_H_

typedef struct Point_S {
	double x,y;
}Point;

typedef struct Vecteur_S {
	double x,y; 
}Vecteur;

typedef struct Segment_{
    Point A,B;
} Segment;

typedef struct Bezier2_ {
    Point c0, c1, c2;
} Bezier2;


typedef struct Bezier3_ {
    Point c0, c1, c2, c3;
} Bezier3;

/* cree le point de coordonnées x,y */
Point creer_point(double x , double y);

/* somme P1 + P2 */
Point somme_point(Point P1 , Point P2);

/* produit des coordonnées d'un point par un réel */
Point produit_point_reel(Point P1 , double d);

/* affiche la distance entre deux points */
double dist_points(Point P1 , Point P2);

/* affiche les informations du point */
void afficher_point(Point P);

/* cree un veceur a partir de x et y */
Vecteur creer_vecteur(double x , double y);

Vecteur vect_bipoint(Point A , Point B);

/* vecteur correspondant aux points A et B */
Vecteur points_vers_vect(Point A , Point B);

/* miliplication de vecteur */
Vecteur produit_vect_reel(Vecteur V, double r);

/* retourne la norme d'un vecteur */
double norme_vecteur(Vecteur V);

/* produit vectoriel de v1 et v2 */
double produit_scalaire(Vecteur V1 , Vecteur V2);

/* somme deux vecteurs */
Vecteur somme_vecteur(Vecteur V1, Vecteur V2);

/* affiche les informations du vecteur */
void afficher_vecteur(Vecteur V);

//renvoie la distanvce en un point et un segment
double dist_point_segment(Point P,Point A, Point B);

//convertis une courbe de bezier 2 en bezier 3
Bezier3 bezier2_to_bezier3(Bezier2 po);

// renvoie la distance entre le point et la courbe de bezier 2 en t
double dist_point_bezier2(Point P, Bezier2 B, double t);

// renvoie la distance entre le point et la courbe de bezier 3 en t
double dist_point_bezier3(Point P, Bezier3 B, double t);

// Calcul le point correspondant à la courbe de bezier 2 évaluée en t
Point bezier2_C(Bezier2 po, double t);

// Calcul le point correspondant à la courbe de bezier 2 évaluée en t
Point bezier3_C(Bezier3 po, double t);

#endif /* _GEOM2D_H_ */