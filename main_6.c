#include <stdio.h>
#include <string.h>

#include "geom2d.h"
#include "image.h"
#include "contour_image.h"
#include "eps.h"
#include "simplification.h"

void erreur()
{
    fprintf(stderr, "Erreur : ./main -d <x1 x2> <xA yA> <xB yB> distance entre P1 et [AB]\n");
    fprintf(stderr, "         ./main -i <fichier.pbm> <dist seuil> infos sur l'image apres simplification\n");
    fprintf(stderr, "         ./main -ia <fichier.pbm> infos sur l'image avant simplification\n");
    fprintf(stderr, "         ./main -f <fichier.pbm> <dist seuil> pour écrire les contours de l'image simplfie dans un fichier\n");
    fprintf(stderr, "         ./main -e <fichier.pbm> <dist seuil> <option : fill/stroke> pour convertir l'image simplifie en fichier EPS\n");
    exit(1);
}

int main(int argc, char *argv[])
{
    int option = -1;
    if (argc == 8 && strcmp(argv[1], "-d") == 0 )
    {
        Point P = creer_point(atof(argv[2]),atof(argv[3]));
        Point A = creer_point(atof(argv[4]),atof(argv[5]));
        Point B = creer_point(atof(argv[6]),atof(argv[7]));
        printf("La distance entre le point <%.1f,%.1f> et le segment [<%.1f,%.1f>,<%.1f,%.1f>] est : %.3f\n",P.x,P.y,A.x,A.y,B.x,B.y,dist_point_segment(P,A,B));
        return 0;
    }
    else if (argc == 4 && strcmp(argv[1], "-i") == 0 )
    {
        option = 4;
    }
    else if (argc == 3 && strcmp(argv[1], "-ia") == 0 )
    {
        Image I = lire_fichier_image(argv[2]);
        Liste_Contour LC = ChercherPlusieurContour(I);
        afficher_infos(LC);
        return 0;
    }
    else if (argc == 4 && strcmp(argv[1], "-f") == 0 )
    {
        option = 2;
    }
    else if (argc == 5 && strcmp(argv[1], "-e") == 0  && (strcmp(argv[4], "fill") == 0 || strcmp(argv[4], "stroke") == 0))
    {
       option=3;
    }
    else
    {
        erreur();
    }

    Image I = lire_fichier_image(argv[2]);
    char nomSortie[50];
    strcpy(nomSortie,argv[2]);
    nomSortie[strlen(nomSortie) - 4] = '\0';
    Liste_Contour LC = ChercherPlusieurContour(I);
    double seuil = atof(argv[3]);
    Liste_Contour Simp = simplification_segments(LC,seuil);
    
    char nomSortieContour[50];
    char nomSortieEps[50];

    switch (option)
    {
    case 4:
        afficher_infos(Simp);
        break;
    case 2:
        
        strcpy(nomSortieContour, nomSortie);
        strcat(nomSortieContour, "_contours.txt");
        printf("Conversion de %s vers %s\n",argv[2],nomSortieContour);
        ecrire_contour_fichier(Simp,nomSortieContour);
        break;
    case 3:
        
        strcpy(nomSortieEps, nomSortie);
        strcat(nomSortieEps, ".eps");
        printf("Conversion de %s vers %s\n",argv[2],nomSortieEps);
        conversion_eps(Simp,nomSortieEps,I,argv[4]);
        break;
    default:
        break;
    }
    
    supprimer_liste_Contour(LC);
    supprimer_image(&I);
    return 0;
}