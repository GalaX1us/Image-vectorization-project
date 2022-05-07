#ifndef _EPS_H_
#define _EPS_H_

#include "image.h"
#include "contour_image.h"
#include "simplification.h"

//écris l'entête d'un fichier eps
FILE* initialiser_eps(char *nom_f, int xmin, int ymin, int xmax, int ymax);

//Convertis un contour polygonal vers un fichier eps
void conversion_eps(Liste_Contour LC, char* nomSortie, Image I, char* option);

//ecris la fin d'un fichier eps
void fin_eps(FILE* f,char* option);

//Convertis un contour de Bezier 3 vers un fichier eps
void conversion_eps_bezier(Liste_Contour_Bezier LC, char* nomSortie, Image I, char* option);

#endif