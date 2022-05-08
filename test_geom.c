#include <stdio.h>
#include <stdlib.h>

#include "geom2d.h"

int main(){

	Vecteur U,V;
	Point A,B;
	
	A = creer_point(1.0 , 4.0);
	B = creer_point(3.5 , -1.0);

	U = creer_vecteur(1.0 , 2.0);
	V = creer_vecteur(-1.0 , 2.0);
	
	printf("Point A : ");afficher_point(A);printf("\n");
	printf("Point B : ");afficher_point(B);printf("\n\n");

	printf("la somme des point A et B est : ");afficher_point(somme_point(A,B)); printf("\n");

    printf("la distance entre les points A et B est : %.1f",dist_points(A,B));printf("\n\n");

	printf("Vecteur U : ");afficher_vecteur(U);printf("\n");
	printf("Vecteur V : ");afficher_vecteur(V);printf("\n\n");

	printf("le vecteur créé à partir des points A et B est : ");afficher_vecteur(points_vers_vect(A,B)); printf("\n");
	
	printf("Le produit scalaire des vecteurs U et V est : %.1f \n", produit_scalaire(U,V));
    printf("Le produit du vecteur U par 2.0 est : ");afficher_vecteur(produit_vect_reel(U,2.0));printf("\n");
	printf("La norme du vecteur U est : %.1f \n",norme_vecteur(U));

return 0;
}