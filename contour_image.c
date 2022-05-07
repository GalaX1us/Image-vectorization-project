#include <stdio.h>
#include <stdlib.h>
#include "contour_image.h"
#include "types_macros.h"
#include "simplification.h"
#include "eps.h" 

/* cette fonction trouve le pixel de départ pour determiné le point d'ou on va commencer*/
bool trouver_pixel_depart(double *x, double *y, Image I)
{
	UINT H = hauteur_image(I), L = largeur_image(I);

	for (UINT i = 1; i <= H; i++)
	{
		for (UINT j = 1; j <= L; j++)
		{
			if (get_pixel_image(I, j, i) == NOIR && get_pixel_image(I, j, i - 1) == BLANC)
			{
				*x = (double)j;
				*y = (double)i;
				return true;
			}
		}
	}
	return false;
}

Robot creer_robot(double x, double y, Orientation o)
{
	Robot r;
	r.o = o;
	r.x = x;
	r.y = y;

	return r;
}

void memoriser_position(Robot r)
{
	printf("(%.1f  %.1f)\n", r.x, r.y);
}

void avancer(Robot *r)
{
	switch (r->o)
	{
	case NORD:
		r->y--;
		break;
	case SUD:
		r->y++;
		break;
	case EST:
		r->x++;
		break;
	case OUEST:
		r->x--;
		break;
	default:
		ERREUR_FATALE("Probleme sur l'orientation")
		break;
	}
}

void droite(Robot *r)
{
	if (r->o == OUEST)
	{
		r->o = NORD;
	}
	else
	{
		r->o++;
	}
}

void gauche(Robot *r)
{
	if (r->o == NORD)
	{
		r->o = OUEST;
	}
	else
	{
		r->o--;
	}
}

void pixels_adjacents(Robot r, Image I, Pixel *pG, Pixel *pD)
{
	switch (r.o)
	{
	case NORD:
		*pG = get_pixel_image(I, r.x, r.y);
		*pD = get_pixel_image(I, r.x + 1, r.y);
		break;
	case SUD:
		*pG = get_pixel_image(I, r.x + 1, r.y + 1);
		*pD = get_pixel_image(I, r.x, r.y + 1);
		break;
	case EST:
		*pG = get_pixel_image(I, r.x + 1, r.y);
		*pD = get_pixel_image(I, r.x + 1, r.y + 1);
		break;
	case OUEST:
		*pG = get_pixel_image(I, r.x, r.y + 1);
		*pD = get_pixel_image(I, r.x, r.y);
		break;
	default:
		break;
	}
}

void nouvelle_orientation(Robot *r, Image I)
{
	Pixel pG, pD;
	pixels_adjacents(*r, I, &pG, &pD);

	if (pG == NOIR)
	{
		gauche(r);
	}
	else if (pD == BLANC)
	{
		droite(r);
	}
}

Contour ChercherContour(Image I, Image *mask, double x, double y)
{
	Robot R;
	Contour C = creer_liste_Point_vide();
	R = creer_robot(x, y, EST);
	do
	{
		//printf("%.1f,%.1f\n",R.x,R.y);
		ajouter_element_liste_Point(&C, creer_point(R.x, R.y));
		if (R.o == EST)
		{
			set_pixel_image(*mask, R.x + 1, R.y + 1, BLANC);
		}
		avancer(&R);
		nouvelle_orientation(&R, I);
	} while ((R.x != x) || (R.y != y) || (R.o != EST));

	ajouter_element_liste_Point(&C, creer_point(R.x, R.y));

	return C;
}

Liste_Contour ChercherPlusieurContour(Image I)
{
	Image Ma = creer_masque(I);
	Point Pd;
	Liste_Contour LC = creer_liste_Contour_vide();

	int nbC = 0;
	while (trouver_pixel_depart(&Pd.x, &Pd.y, Ma))
	{
		nbC++;
		Contour C = ChercherContour(I, &Ma, Pd.x-1, Pd.y-1);
		ajouter_element_liste_Contour(&LC,C);
	}

	return LC;
}



/* cr�er une cellule de liste avec l'�l�ment v
   renvoie le pointeur sur la cellule de liste cr��e
   la fonction s'arrete si la cr�ation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
	Cellule_Liste_Point *el;
	el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
	if (el == NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

Cellule_Liste_Contour *creer_element_liste_Contour(Liste_Point v)
{
	Cellule_Liste_Contour *el;
	el = (Cellule_Liste_Contour *)malloc(sizeof(Cellule_Liste_Contour));
	if (el == NULL)
	{
		fprintf(stderr, "creer_element_liste_Contour : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

/* cr�er une liste vide */
Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}

Liste_Contour creer_liste_Contour_vide()
{
	Liste_Contour L = {0, NULL, NULL};
	return L;
}

/* ajouter l'�l�ment e en fin de la liste L, renvoie la liste L modifi�e */
void ajouter_element_liste_Point(Liste_Point *L, Point e)
{
	Cellule_Liste_Point *el;

	el = creer_element_liste_Point(e);
	if (L->taille == 0)
	{
		/* premier �l�ment de la liste */
		L->first = L->last = el;
	}
	else
	{
		L->last->suiv = el;
		L->last = el;
	}
	L->taille++;
}

void ajouter_element_liste_Contour(Liste_Contour *L, Liste_Point e)
{
	Cellule_Liste_Contour *el;

	el = creer_element_liste_Contour(e);
	if (L->taille == 0)
	{
		/* premier �l�ment de la liste */
		L->first = L->last = el;
	}
	else
	{
		L->last->suiv = el;
		L->last = el;
	}
	L->taille++;
}

/* suppression de tous les �l�ments de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el = L.first;

	while (el)
	{
		Cellule_Liste_Point *suiv = el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL;
	L.taille = 0;
	return L;
}

Liste_Contour supprimer_liste_Contour(Liste_Contour L)
{
	Cellule_Liste_Contour *el = L.first;

	while (el)
	{
		supprimer_liste_Point(el->data);
		Cellule_Liste_Contour *suiv = el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL;
	L.taille = 0;
	return L;
}

/* concat�ne L2 � la suite de L1, renvoie la liste L1 modifi�e */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1.taille == 0)
		return L2;
	if (L2.taille == 0)
		return L1;

	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;		  /* le dernier �l�ment de L1 est celui de L2 */
	L1.taille += L2.taille;	  /* nouvelle taille pour L1 */
	return L1;
}
/* cr�er une s�quence de points sous forme d'un tableau de points
   � partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;

	/* taille de T = taille de L */
	T.taille = L.taille;

	/* allocation dynamique du tableau de Point */
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}

	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0;						   /* indice de l'�l�ment dans T.tab */
	Cellule_Liste_Point *el = L.first; /* pointeur sur l'�l�ment dans L */
	while (el)
	{
		T.tab[k] = el->data;
		k++;		   /* incr�menter k */
		el = el->suiv; /* passer � l'�lement suivant dans la liste chainee */
	}

	return T;
}

/* �crire le contour L � l'�cran
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acc�der aux �l�ments d'une
   s�quence de points par indice */
void ecrire_contour_ecran(Liste_Point L)
{
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);

	int k;
	int nP = TP.taille;

	printf("%d segments et %d points : [", nP - 1, nP);
	for (k = 0; k < nP; k++)
	{
		Point P = TP.tab[k]; /* r�cup�rer le point d'indice k */
		printf(" (%5.1f,%5.1f)", P.x, P.y);
	}
	printf("]\n");
}

UINT nombre_segments(Liste_Point LP)
{
	return LP.taille-1;
}


UINT nombre_segments_total(Liste_Contour LC)
{
	UINT nbST = 0;
	Cellule_Liste_Contour* cc = LC.first;
	while (cc!=NULL)
    {
		nbST+=nombre_segments(cc->data); 
        cc=cc->suiv;
    };
	return nbST;
}


UINT nombre_contours(Liste_Contour LC)
{
	return LC.taille;
}


void afficher_infos(Liste_Contour LC){
	printf("Nombre de contours : %d\n",nombre_contours(LC));
	printf("Nombre total de segments : %d\n",nombre_segments_total(LC));
}

void ecrire_contour_fichier(Liste_Contour LC, char* nomSortie)
{
	UINT nbC = nombre_contours(LC);
	FILE* f = fopen(nomSortie,"w");
	fprintf(f,"%d\n",nbC);
	Cellule_Liste_Contour* cc = LC.first;
	while (cc!=NULL)
    {
        Tableau_Point TP = sequence_points_liste_vers_tableau(cc->data);
		int t = TP.taille;
		fprintf(f, "\n");
		for (int i = 0; i < t; i++)
		{
		fprintf(f, "%.1f %.1f\n", TP.tab[i].x, TP.tab[i].y);
		}
		fprintf(f, "\n");
        cc=cc->suiv;
    };
	fclose(f);
}


void pbm_vers_eps(Image I, char *nomSortie, char* option)
{
	Liste_Contour LC = ChercherPlusieurContour(I);
	conversion_eps(LC,nomSortie,I,option);
	supprimer_liste_Contour(LC);
}
