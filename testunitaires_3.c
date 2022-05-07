#include <stdio.h>
#include <string.h>

#include "geom2d.h"
#include "image.h"
#include "contour_image.h"
#include "eps.h"
#include "simplification.h"

int main(int argc, char *argv[])
{
    printf("==========================\n");
    printf("Tests unitaires Bezier 3 :\n");
    printf("==========================\n");    

    printf("\nTest cas n = 1 : \n");
    Liste_Point L = creer_liste_Point_vide();
    Point A = creer_point(0.,0.);
    Point B = creer_point(0.,2.);
    ajouter_element_liste_Point(&L,A);
    ajouter_element_liste_Point(&L,B);
    printf("P0 = (%.1f,%.1f), P1 = (%.1f,%.1f)\n",A.x,A.y,B.x,B.y);
    Tableau_Point T = sequence_points_liste_vers_tableau(L);
    Bezier3 B3 = approx_bezier3(T,0,T.taille-1);
    printf("C0 = (%.1f,%.1f), C1 = (%.1f,%.1f), C2 = (%.1f,%.1f), C3 = (%.1f,%.1f)\n",B3.c0.x,B3.c0.y,B3.c1.x,B3.c1.y,B3.c2.x,B3.c2.y,B3.c3.x,B3.c3.y);
    Point C1M = produit_point_reel(somme_point(produit_point_reel(A,2.),B),1./3.);
    Point C2M = produit_point_reel(somme_point(produit_point_reel(B,2.),A),1./3.);
    printf("Calcul à la main : C0 = (%.1f,%.1f), C1 = (%.1f,%.1f), C2 = (%.1f,%.1f), C3 = (%.1f,%.1f)\n",A.x,A.y,C1M.x,C1M.y,C2M.x,C2M.y,B.x,B.y);

    printf("\nTest cas n = 2 : \n");
    Liste_Point L2 = creer_liste_Point_vide();
    Point P0 = creer_point(1.,0.);
    Point P1 = creer_point(2.,1.);
    Point P2 = creer_point(3.,0.);
    ajouter_element_liste_Point(&L2,P0);
    ajouter_element_liste_Point(&L2,P1);
    ajouter_element_liste_Point(&L2,P2);
    printf("P0 = (%.1f,%.1f), P1 = (%.1f,%.1f), P2 = (%.1f,%.1f)\n",P0.x,P0.y,P1.x,P1.y,P2.x,P2.y);
    Tableau_Point T2 = sequence_points_liste_vers_tableau(L2);
    Bezier3 B3_2 = approx_bezier3(T2,0,T2.taille-1);

    printf("C0 = (%.1f,%.1f), C1 = (%.1f,%.1f), C2 = (%.1f,%.1f), C3 = (%.1f,%.1f)\n",B3_2.c0.x,B3_2.c0.y,B3_2.c1.x,B3_2.c1.y,B3_2.c2.x,B3_2.c2.y,B3_2.c3.x,B3_2.c3.y);
    Point C1M_2 = produit_point_reel(somme_point(produit_point_reel(P1,4.),produit_point_reel(P2,-1.)),1./3.);
    Point C2M_2 = produit_point_reel(somme_point(produit_point_reel(P1,4.),produit_point_reel(P0,-1.)),1./3.);
    printf("Calcul à la main :\nC0 = (%.1f,%.1f), C1 = (%.1f,%.1f), C2 = (%.1f,%.1f), C3 = (%.1f,%.1f)\n",P0.x,P0.y,C1M_2.x,C1M_2.y,C2M_2.x,C2M_2.y,P2.x,P2.y);

    int n = 10;
    Point Q0 = creer_point(0.,0.);
    Point Q1 = creer_point(1.,1.);
    Point Q2 = creer_point(1.,2.);
    Point Q3 = creer_point(0.,3.);

    Bezier3 B3_3;

    B3_3.c0 = Q0;
    B3_3.c1 = Q1;
    B3_3.c2 = Q2;
    B3_3.c3 = Q3;

    printf("\nTest cas n = 10 : \n");
    printf("Avant : C0 = (%.1f,%.1f), C1 = (%.1f,%.1f), C2 = (%.1f,%.1f), C3 = C2 = (%.1f,%.1f)\n",B3_3.c0.x,B3_3.c0.y,B3_3.c1.x,B3_3.c1.y,B3_3.c2.x,B3_3.c2.y,B3_3.c3.x,B3_3.c3.y);

    Liste_Point L3 = creer_liste_Point_vide();
    
    for (int i = 0; i <= n; i++){
        ajouter_element_liste_Point(&L3,bezier3_C(B3_3,(double)i/(double)n));
    }

    Tableau_Point T_3 = sequence_points_liste_vers_tableau(L3);
    Bezier3 B3_4 = approx_bezier3(T_3,0,T_3.taille-1);

    printf("Après : C0 = (%.1f,%.1f), C1 = (%.1f,%.1f), C2 = (%.1f,%.1f), C3 = (%.1f,%.1f)\n",B3_4.c0.x,B3_4.c0.y,B3_4.c1.x,B3_4.c1.y,B3_4.c2.x,B3_4.c2.y,B3_4.c3.x,B3_4.c3.y);
    Liste_Point L4 = creer_liste_Point_vide();

    ajouter_element_liste_Point(&L4,creer_point(0.,0.));
    ajouter_element_liste_Point(&L4,creer_point(1.,0.));
    ajouter_element_liste_Point(&L4,creer_point(1.,1.));
    ajouter_element_liste_Point(&L4,creer_point(1.,2.));
    ajouter_element_liste_Point(&L4,creer_point(2.,2.));
    ajouter_element_liste_Point(&L4,creer_point(3.,2.));
    ajouter_element_liste_Point(&L4,creer_point(3.,3.));
    ajouter_element_liste_Point(&L4,creer_point(4.,3.));
    ajouter_element_liste_Point(&L4,creer_point(5.,3.));
    
    Tableau_Point T_4 = sequence_points_liste_vers_tableau(L4);
    Bezier3 B3_5 = approx_bezier3(T_4,0,T_4.taille-1);

    printf("\nTest du cours avec 9 points :\n");
    printf("C1 = (%.5f,%.5f), C2 = (%.5f,%.5f)\n",B3_5.c1.x,B3_5.c1.y,B3_5.c2.x,B3_5.c2.y);
    
 
    for (int i = 0; i < T_4.taille; i++)
    {
        printf("Distance entre le point %d (%.1f,%.1f) et la courbe est : %.3f\n",i,T_4.tab[i].x,T_4.tab[i].y,dist_point_bezier3(T_4.tab[i],B3_5,(double)i/(double)(T_4.taille-1)));
    }

    return 0;
};