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
    printf("Tests unitaires Bezier 2 :\n");
    printf("==========================\n");
    printf("\nTest cas n = 1 : \n");
    Liste_Point L = creer_liste_Point_vide();
    Point A = creer_point(0.,0.);
    Point B = creer_point(0.,2.);
    ajouter_element_liste_Point(&L,A);
    ajouter_element_liste_Point(&L,B);
    printf("P0 = (%.1f,%.1f), P1 = (%.1f,%.1f)\n",A.x,A.y,B.x,B.y);
    Tableau_Point T = sequence_points_liste_vers_tableau(L);
    Bezier2 B2 = approx_bezier2(T,0,T.taille-1);
    printf("C0 = (%.1f,%.1f), C1 = (%.1f,%.1f), C2 = (%.1f,%.1f)\n",B2.c0.x,B2.c0.y,B2.c1.x,B2.c1.y,B2.c2.x,B2.c2.y);
    printf("\n");

    //Test 2

    int n = 10;
    Point Q0 = creer_point(4.,4.);
    Point Q1 = creer_point(3.,3.);
    Point Q2 = creer_point(5.,5.);

    Bezier2 B2_2;

    B2_2.c0 = Q0;
    B2_2.c1 = Q1;
    B2_2.c2 = Q2;

    printf("Test cas n = 10 : \n");
    printf("Avant : C0 = (%.1f,%.1f), C1 = (%.1f,%.1f), C2 = (%.1f,%.1f)\n",B2_2.c0.x,B2_2.c0.y,B2_2.c1.x,B2_2.c1.y,B2_2.c2.x,B2_2.c2.y);

    L = supprimer_liste_Point(L);

    for (int i = 0; i <= n; i++){
        ajouter_element_liste_Point(&L,bezier2_C(B2_2,(double)i/(double)n));
    }

    Tableau_Point T_2 = sequence_points_liste_vers_tableau(L);
    Bezier2 B2_3 = approx_bezier2(T_2,0,T_2.taille-1);

    printf("Après : C0 = (%.1f,%.1f), C1 = (%.1f,%.1f), C2 = (%.1f,%.1f)\n",B2_3.c0.x,B2_3.c0.y,B2_3.c1.x,B2_3.c1.y,B2_3.c2.x,B2_3.c2.y);

    L = supprimer_liste_Point(L);
    ajouter_element_liste_Point(&L,creer_point(0,0));
    ajouter_element_liste_Point(&L,creer_point(1,0));
    ajouter_element_liste_Point(&L,creer_point(1,1));
    ajouter_element_liste_Point(&L,creer_point(1,2));
    ajouter_element_liste_Point(&L,creer_point(2,2));
    ajouter_element_liste_Point(&L,creer_point(3,2));
    ajouter_element_liste_Point(&L,creer_point(3,3));
    ajouter_element_liste_Point(&L,creer_point(4,3));
    ajouter_element_liste_Point(&L,creer_point(5,3));
    
    Tableau_Point T_3 = sequence_points_liste_vers_tableau(L);
    Bezier2 B2_4 = approx_bezier2(T_3,0,T_3.taille-1);

    printf("\nTest du cours avec 9 points :\n");
    printf("C1 = %.5f,%.5f\n",B2_4.c1.x,B2_4.c1.y);
    
 
    for (int i = 0; i < T_3.taille; i++)
    {
        printf("Distance entre le point %d (%.1f,%.1f) et la courbe est : %.3f\n",i,T_3.tab[i].x,T_3.tab[i].y,dist_point_bezier2(T_3.tab[i],B2_4,(double)i/(double)(T_3.taille-1)));
    }
    return 0;
};