#include <stdio.h>
#include <stdlib.h>

#include "eps.h"
#include "image.h"
#include "contour_image.h"
#include "simplification.h"


void point_courant(FILE* f, Point A, Image I){
    fprintf(f, "\n%.1f %.1f moveto\n", A.x, I.H-A.y);
}

void tracer_segment(FILE *f, Point B, Image I){
    fprintf(f, "%.1f %.1f lineto\n",B.x, I.H-B.y);
}

void tracer_courbe_courant(FILE *f, Bezier3 B, Image I){
    fprintf(f, "%.1f %.1f moveto %.1f %.1f %.1f %.1f %.1f %.1f curveto\n",B.c0.x,I.H-B.c0.y,B.c1.x,I.H-B.c1.y,B.c2.x,I.H-B.c2.y,B.c3.x,I.H-B.c3.y);
}

void tracer_courbe(FILE *f, Bezier3 B, Image I){
    fprintf(f, "%.1f %.1f %.1f %.1f %.1f %.1f curveto\n",B.c1.x,I.H-B.c1.y,B.c2.x,I.H-B.c2.y,B.c3.x,I.H-B.c3.y);
}

FILE* initialiser_eps(char *nom_f, int xmin, int ymin, int xmax, int ymax){ 
    FILE *f = fopen(nom_f, "w");
    if (f == (FILE *)NULL){
        ERREUR_FATALE("initialiser_eps : ouverture du fichier sortie impossible\n");
    }
    
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: %d %d %d %d\n", xmin, ymin, xmax, ymax);
    fprintf(f, "0.0 setlinewidth\n");
    
    return f;
}

void ecrire_eps_point(FILE *f, Tableau_Point T, Image I){
    point_courant(f, T.tab[0],I);
    for (int i=0; i<T.taille; i++){
        tracer_segment(f, T.tab[i],I);
    }
}

void ecrire_eps_bezier(FILE *f, Tableau_Bezier3 T, Image I){
    tracer_courbe_courant(f, T.tab[0],I);
    for (int i=1; i<T.taille; i++){
        tracer_courbe(f, T.tab[i],I);
    }
}

void conversion_eps(Liste_Contour LC, char* nomSortie, Image I, char* option){
    FILE* E = initialiser_eps(nomSortie,0,0,I.L,I.H);
    Cellule_Liste_Contour* cc = LC.first;
    while (cc!=NULL)
    {
        Tableau_Point TP = sequence_points_liste_vers_tableau(cc->data);
        ecrire_eps_point(E,TP,I);
        cc=cc->suiv;
    }
    fin_eps(E,option);
}

void conversion_eps_bezier(Liste_Contour_Bezier LC, char* nomSortie, Image I, char* option){
    FILE* E = initialiser_eps(nomSortie,0,0,I.L,I.H);
    Cellule_Liste_Contour_Bezier* cc = LC.first;
    while (cc!=NULL)
    {
        Tableau_Bezier3 TP = sequence_bezier3_liste_vers_tableau(cc->data);
        ecrire_eps_bezier(E,TP,I);
        cc=cc->suiv;
    }
    fin_eps(E,option);
}

void fin_eps(FILE* f, char* option){
    fprintf(f, "%s\n",option);
    fprintf(f, "showpage");
    fclose(f);
}