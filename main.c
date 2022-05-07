#include <stdio.h>
#include <string.h>

#include "geom2d.h"
#include "image.h"
#include "contour_image.h"
#include "eps.h"
#include "simplification.h"

void erreur()
{
    fprintf(stderr, "Erreur : ./main -i <fichier.pbm> <dist seuil> <degree simplification> infos sur l'image apres simplification\n");
    fprintf(stderr, "         ./main -ia <fichier.pbm> infos sur l'image avant simplification\n");
    fprintf(stderr, "         ./main -e <fichier.pbm> <dist seuil> <option : fill/stroke> <degree simplification> pour convertir l'image simplifie en fichier EPS\n");
    exit(1);
}

int main(int argc, char *argv[])
{
    int option = -1;
    int degree = -1;
    if (argc == 5 && strcmp(argv[1], "-i") == 0 )
    {
        option = 1;
        if (strcmp(argv[4],"1")==0){
            degree=1;
        }else if(strcmp(argv[4],"2")==0){
            degree=2;
        }else if(strcmp(argv[4],"3")==0){
            degree=3;
        }else{
            erreur();
        }
    }
    else if (argc == 3 && strcmp(argv[1], "-ia") == 0 )
    {
        Image I = lire_fichier_image(argv[2]);
        Liste_Contour LC = ChercherPlusieurContour(I);
        afficher_infos(LC);
        return 0;
    }
    else if (argc == 6 && strcmp(argv[1], "-e") == 0  && (strcmp(argv[4], "fill") == 0 || strcmp(argv[4], "stroke") == 0))
    {
        option = 2;
        if (strcmp(argv[5],"1")==0){
            degree=1;
        }else if(strcmp(argv[5],"2")==0){
            degree=2;
        }else if(strcmp(argv[5],"3")==0){
            degree=3;
        }else{
            erreur();
        }
    }else
    {
        erreur();
    }

    char nomSortieEps[50];
    char nomSortie[50];
    strcpy(nomSortie,argv[2]);
    nomSortie[strlen(nomSortie) - 4] = '\0';

    Image I = lire_fichier_image(argv[2]);
    Liste_Contour LC = ChercherPlusieurContour(I);

    Liste_Contour Simp = creer_liste_Contour_vide(); 
    Liste_Contour_Bezier Simp_Bez = creer_liste_Contour_Bezier_vide();
    
    double seuil = atof(argv[3]);

    switch (degree)
    {
    case 1:
        Simp = simplification_segments(LC,seuil);
        break;
    case 2:
        Simp_Bez = simplification_douglas_peucker_bezier2(LC,seuil);
        break;
    case 3:
        Simp_Bez = simplification_douglas_peucker_bezier3(LC,seuil);
        break;
    default:
        break;
    }
    
    
    switch (option)
    {
    case 1:
        switch (degree)
        {
        case 1:
            afficher_infos(Simp);
            break;
        case 2: case 3:
            afficher_infos_bis(Simp_Bez);
            break;
        default:
            break;
        }
        break;
    case 2:
        
        strcpy(nomSortieEps, nomSortie);
        strcat(nomSortieEps, ".eps");
        printf("Conversion de %s vers %s\n",argv[2],nomSortieEps);

        switch (degree)
        {
        case 1:
            conversion_eps(Simp,nomSortieEps,I,argv[4]);
            break;
        case 2: case 3:
            conversion_eps_bezier(Simp_Bez,nomSortieEps,I,argv[4]);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    
    supprimer_liste_Contour(LC);
    supprimer_image(&I);
    return 0;
}