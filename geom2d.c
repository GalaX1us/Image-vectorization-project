#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "geom2d.h"

/* cree le point de coordonnées x,y */
Point creer_point(double x , double y){
	Point P = {x,y};
	return P;
}

/* somme P1 + P2 */
Point somme_point(Point P1 , Point P2){
	return creer_point(P1.x + P2.x , P1.y + P2.y);
}

Point produit_point_reel(Point P1 , double d){
	return creer_point(P1.x*d, P1.y*d);
}

/* distance entre deux points */
double dist_points(Point P1 , Point P2){
	return sqrt(pow((P2.x-P1.x),2)+pow((P2.y-P1.y),2));
}

/* Affiche le point */
void afficher_point(Point P){
	printf("(%.1f ,%.1f)", P.x , P.y);
}

/* cree un veceur a partir de x et y */
Vecteur creer_vecteur(double x , double y){
	Vecteur V;
	V.x=x;
	V.y=y;
	return V;
}

Vecteur vect_bipoint(Point A , Point B){
	Vecteur V = {B.x - A.x, B.y - A.y};
	return V;
}

/* vecteur correspondant aux points A et B */
Vecteur points_vers_vect(Point A , Point B){
	Vecteur V = {B.x-A.x,B.y-A.y};
	return V;
}

/* produit d'un vecteur et d'un réel */
Vecteur produit_vect_reel(Vecteur V, double r){
	V.x=r*(V.x);
	V.y=r*(V.y);
	return V;
}

/* retourne la norme d'un vecteur */
double norme_vecteur(Vecteur V){
	return sqrt((V.x * V.x)+(V.y * V.y));
}

/* produit scalaire de v1 et v2 */
double produit_scalaire(Vecteur V1 , Vecteur V2){
	return V1.x*V2.x + V1.y*V2.y;
}

/*Somme de deux vecteurs*/
Vecteur somme_vecteur(Vecteur V1, Vecteur V2){
	Vecteur V;
	V.x = V1.x + V2.x;
	V.y = V1.y + V2.y;
	return V;
}

void afficher_vecteur(Vecteur V){
	printf("(%.1f ,%.1f)", V.x , V.y);
}

double dist_point_segment(Point P, Point A, Point B){
    if (A.x==B.x && A.y==B.y){
        return norme_vecteur(vect_bipoint(A,P));
    }
    double lambda;
    Vecteur AP,AB;
    AP=vect_bipoint(P,A);
    AB=vect_bipoint(B,A);
    lambda=(produit_scalaire(AP,AB))/(produit_scalaire(AB,AB));

    Point Q,minusA = {-A.x,-A.y};
    Point BminusA=somme_point(B,minusA);
    Point lambdaAB = {(BminusA.x)*lambda,(BminusA.y)*lambda};
    Q=somme_point(A,lambdaAB);

    if(lambda<0){
        return norme_vecteur(vect_bipoint(A,P));
    }
    else if(lambda<=1){
        return norme_vecteur(vect_bipoint(Q,P));
    }
    else{
        return norme_vecteur(vect_bipoint(B,P));
    }
}

Point bezier2_C(Bezier2 po, double t) {
    Point p0 = produit_point_reel(po.c0, pow(1 - t, 2));
    Point p1 = produit_point_reel(po.c1, 2 * t * (1 - t));
    Point p2 = produit_point_reel(po.c2, t * t);

    return somme_point(p0, somme_point(p1, p2));
}

Point bezier3_C(Bezier3 po, double t) {
    Point p0 = produit_point_reel(po.c0, pow(1 - t, 3));
    Point p1 = produit_point_reel(po.c1, 3 * t * pow(1 - t, 2));
    Point p2 = produit_point_reel(po.c2, 3 * t * t * (1 - t));
    Point p3 = produit_point_reel(po.c3, t * t * t);

    return somme_point(p0, somme_point(p1, somme_point(p2, p3)));
}


Bezier3 bezier2_to_bezier3(Bezier2 po) {
    return (Bezier3) {
        po.c0,
        somme_point(produit_point_reel(po.c1,2./3.),produit_point_reel(po.c0,1./3.)),
        somme_point(produit_point_reel(po.c1,2./3.),produit_point_reel(po.c2,1./3.)),
        po.c2,
    };
}

double dist_point_bezier2(Point P, Bezier2 B, double t){
    Point C = bezier2_C(B, t);
    return dist_points(P, C);
}

double dist_point_bezier3(Point P, Bezier3 B, double t){
    Point C = bezier3_C(B, t);
    return dist_points(P, C);
}
