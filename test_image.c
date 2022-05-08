#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"types_macros.h"
#include"image.h"

int main(int argc , char ** argv){
	Image I,J,NEG;

	I = lire_fichier_image("caractere2.pbm");
	ecrire_image(I);
	
	J = creer_image(9,9);
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			if(i==j){
				set_pixel_image(J,j,i,NOIR);
			}
		}
	}
	printf("\n");
	ecrire_image(J);
	printf("\n");
	
	NEG = negatif_image(J);
    ecrire_image(NEG);
	
	supprimer_image(&I);
	supprimer_image(&NEG);
	return 0;
}