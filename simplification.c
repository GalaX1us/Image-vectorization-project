#include "geom2d.h"
#include "image.h"
#include "types_macros.h"
#include "contour_image.h"
#include "simplification.h"
#include "math.h"

//Courbe de Bézier de degré 3
Cellule_Liste_Bezier3* creer_element_liste_Bezier3(Bezier3 v){
    Cellule_Liste_Bezier3 *el;
    el = (Cellule_Liste_Bezier3*)malloc(sizeof(Cellule_Liste_Bezier3));
    if (el == NULL){
        fprintf(stderr, "creer_element_liste_Bezier3 : allocation impossible\n");
        exit(-1);
    }

    el->data = v;
    el->suiv = NULL;
    return el;
}

Liste_Bezier3 creer_liste_Bezier3_vide(){
    Liste_Bezier3 L = {0, NULL, NULL};
    return L;
}

void ajouter_element_liste_Bezier3(Liste_Bezier3 *L, Bezier3 e){
    Cellule_Liste_Bezier3 *el;
    el = creer_element_liste_Bezier3(e);

    if(L->taille == 0){
        L->first = L->last = el;
    }
    else{
        L->last->suiv = el;
        L->last = el;
    }
    L->taille++;
}

Liste_Bezier3 supprimer_liste_Bezier3(Liste_Bezier3 L){
    Cellule_Liste_Bezier3 *el = L.first;

    while (el){
        Cellule_Liste_Bezier3 *suiv = el->suiv;
        free(el);
        el = suiv;
    }
    L.first = L.last = NULL;
    L.taille = 0;
    return L;
}

Liste_Bezier3 concatener_liste_Bezier3(Liste_Bezier3 L1, Liste_Bezier3 L2){
    if (L1.taille == 0) return L2;
    if (L2.taille == 0) return L1;

    L1.last->suiv = L2.first;
    L1.last = L2.last;
    L1.taille += L2.taille;
    return L1;
}

Tableau_Bezier3 sequence_bezier3_liste_vers_tableau(Liste_Bezier3 L){
    Tableau_Bezier3 T;

    T.taille = L.taille;
    T.tab = malloc(sizeof(Bezier3)*T.taille);

    if (T.tab == NULL){
        fprintf(stderr, "sequence_bezier3_liste_vers_tableau : allocation impossible");
        exit(-1);
    }

    int k = 0;
    Cellule_Liste_Bezier3 *el = L.first;
    while(el){
        T.tab[k] = el->data;
        k++;
        el = el->suiv;
    }

    return T;
}
// Gestion liste contour bezier

Cellule_Liste_Contour_Bezier *creer_element_liste_Contour_Bezier(Liste_Bezier3 v)
{
	Cellule_Liste_Contour_Bezier *el;
	el = (Cellule_Liste_Contour_Bezier *)malloc(sizeof(Cellule_Liste_Contour_Bezier));
	if (el == NULL)
	{
		fprintf(stderr, "creer_element_liste_Contour : allocation impossible\n");
		exit(-1);
	}
	el->data = v;
	el->suiv = NULL;
	return el;
}

Liste_Contour_Bezier creer_liste_Contour_Bezier_vide()
{
	Liste_Contour_Bezier L = {0, NULL, NULL};
	return L;
}

void ajouter_element_liste_Contour_Bezier(Liste_Contour_Bezier *L, Liste_Bezier3 e)
{
	Cellule_Liste_Contour_Bezier *el;

	el = creer_element_liste_Contour_Bezier(e);
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

// Simplification

Liste_Point simplification_segments_rec(Tableau_Point T, int p1, int p2, double d){
    double dmax = 0;
    double dj = 0;
    int k = p1;
    Liste_Point Liste = creer_liste_Point_vide();
    Liste_Point *L = &Liste;

    for (int j=p1+1; j<=p2; j++){
        dj = dist_point_segment(T.tab[j], T.tab[p1], T.tab[p2]);
        if (dmax < dj){
            dmax = dj;
            k = j;
        }
    }
    if (dmax <= d){
        ajouter_element_liste_Point(L, T.tab[p1]);
        ajouter_element_liste_Point(L, T.tab[p2]);   
    }
    else{

        Liste_Point L1 = simplification_segments_rec(T, p1, k, d);
        Liste_Point L2 = simplification_segments_rec(T, k, p2, d);

        if (L2.first) {
            Cellule_Liste_Point* first = L2.first;
            Cellule_Liste_Point* second = first->suiv;
            L2.first = second;
            free(first);
            L2.taille--;
        }
        Liste = concatener_liste_Point(L1,L2);
    }
    return Liste;
}

Liste_Contour simplification_segments(Liste_Contour T, double d){
    Liste_Contour Liste = creer_liste_Contour_vide();
    Cellule_Liste_Contour* C = T.first;
    while (C!=NULL)
    {
        Tableau_Point T = sequence_points_liste_vers_tableau(C->data);
        Liste_Point L = simplification_segments_rec(T,0,T.taille-1,d);
        ajouter_element_liste_Contour(&Liste,L);
        
        C = C->suiv;
    }
    return Liste;
}

Bezier2 approx_bezier2(Tableau_Point P, int j1, int j2){
    int n = j2-j1;
    Bezier2 B;      

    B.c0 = P.tab[j1];
    B.c2 = P.tab[j2];

    if (n == 1){
        B.c1 = somme_point(B.c0, B.c2);
        B.c1 = produit_point_reel(B.c1,0.5);
        return B;

    } else{
        double n_reel = (double)n;
        double alpha = (3.*n_reel)/(n_reel*n_reel -1.);
        double beta = (1.- (2.*n_reel))/(2.*(n_reel+1.));

        Point Cx = creer_point(0, 0);

        for(int i=1; i<n; i++){
            Cx = somme_point(Cx, P.tab[i+j1]);
        }
        B.c1 = somme_point(produit_point_reel(Cx,alpha), produit_point_reel(somme_point(B.c0, B.c2),beta));
        return B;
    }
}

Liste_Bezier3 simplification_douglas_peucker_bezier2_rec(Tableau_Point T, int j1, int j2, double d){
    Bezier2 B2 = approx_bezier2(T, j1, j2);
    
    int n = j2-j1;
    double dmax = 0;
    int k = j1;

    Liste_Bezier3 Liste = creer_liste_Bezier3_vide();
    
    for (int j=j1+1; j<=j2; j++){
        int i = j-j1;
        double ti = (double)i/(double)n;
        double dj = dist_point_bezier2(T.tab[j], B2, ti);
        if (dmax < dj){
            dmax = dj;
            k = j;
        }
    }
    
    if (dmax <= d){
        Bezier3 B3 = bezier2_to_bezier3(B2);
        ajouter_element_liste_Bezier3(&Liste, B3);
    }
    else{
        Liste = concatener_liste_Bezier3(simplification_douglas_peucker_bezier2_rec(T, j1, k, d), simplification_douglas_peucker_bezier2_rec(T, k, j2, d));
    }
    return Liste;
}

Liste_Contour_Bezier simplification_douglas_peucker_bezier2(Liste_Contour T, double d){
    Liste_Contour_Bezier Liste = creer_liste_Contour_Bezier_vide();
    Cellule_Liste_Contour* C = T.first;
    while (C!=NULL)
    {
        Tableau_Point T = sequence_points_liste_vers_tableau(C->data);
        Liste_Bezier3 L = simplification_douglas_peucker_bezier2_rec(T,0,T.taille-1,d);
        ajouter_element_liste_Contour_Bezier(&Liste,L);
        C = C->suiv;
    }
    return Liste;
}

double fonction_gamma(double k, double n){
    return ((6.*pow(k,4))-(8.*n*pow(k,3))+(6.*k*k)-(4.*n*k)+(pow(n,4))-(n*n));
}

Bezier3 approx_bezier3(Tableau_Point P, int j1, int j2){
    int n = j2-j1;

    if (n < 3 && n != 0){
        Bezier2 B2 = approx_bezier2(P, j1, j2);
        return bezier2_to_bezier3(B2);

    } else if (n >= 3){
        Bezier3 B3;

        B3.c0 = P.tab[j1];
        B3.c3 = P.tab[j2];

        double n_r = (double)n;
        double alpha = ((-15.*n_r*n_r*n_r)+(5.*n_r*n_r)+(2.*n_r)+4.)/(3.*(n_r+2.)*((3.*n_r*n_r)+1.));
        double beta = ((10.*n_r*n_r*n_r)-(15.*n_r*n_r)+n_r+2.)/(3.*(n_r+2.)*((3.*n_r*n_r)+1.));
        double lambda = (70.*n_r)/(3.*((n_r*n_r)-1.)*((n_r*n_r)- 4.)*((3.*n_r*n_r)+1.));
   
        Point C1tmp = creer_point(0, 0);
        Point C2tmp = creer_point(0, 0);

        for(int i=1; i<n; i++){
            C1tmp = somme_point(C1tmp, produit_point_reel(P.tab[i+j1],fonction_gamma(i, n_r)));
            C2tmp = somme_point(C2tmp, produit_point_reel(P.tab[i+j1],fonction_gamma(n_r-i, n_r)));
        }
        C1tmp = produit_point_reel(C1tmp,lambda);
        C2tmp = produit_point_reel(C2tmp,lambda);

        B3.c1 = somme_point(produit_point_reel(P.tab[j1],alpha), somme_point(produit_point_reel(P.tab[j2],beta), C1tmp));
        B3.c2 = somme_point(produit_point_reel(P.tab[j1],beta), somme_point(produit_point_reel(P.tab[j2],alpha), C2tmp));

        return B3; 
    }
    ERREUR_FATALE("n=0")
}

Liste_Bezier3 simplification_douglas_peucker_bezier3_rec(Tableau_Point T, int j1, int j2, double d){
    Bezier3 B3 = approx_bezier3(T, j1, j2);
    
    int n = j2-j1;
    double dmax = 0;
    int k = j1;

    Liste_Bezier3 Liste = creer_liste_Bezier3_vide();
    
    for (int j=j1+1; j<=j2; j++){
        int i = j-j1;
        double ti = (double)i/(double)n;
        double dj = dist_point_bezier3(T.tab[j], B3, ti);
        if (dmax < dj){
            dmax = dj;
            k = j;
        }
    }
    
    if (dmax <= d){
        ajouter_element_liste_Bezier3(&Liste, B3);
    }
    else{
        Liste = concatener_liste_Bezier3(simplification_douglas_peucker_bezier2_rec(T, j1, k, d), simplification_douglas_peucker_bezier2_rec(T, k, j2, d));
    }
    return Liste;
}

Liste_Contour_Bezier simplification_douglas_peucker_bezier3(Liste_Contour T, double d){
    Liste_Contour_Bezier Liste = creer_liste_Contour_Bezier_vide();
    Cellule_Liste_Contour* C = T.first;
    while (C!=NULL)
    {
        Tableau_Point T = sequence_points_liste_vers_tableau(C->data);
        Liste_Bezier3 L = simplification_douglas_peucker_bezier3_rec(T,0,T.taille-1,d);
        ajouter_element_liste_Contour_Bezier(&Liste,L);
        C = C->suiv;
    }
    return Liste;
}

UINT nombre_segments_bis(Liste_Bezier3 LP)
{
	return LP.taille;
}

UINT nombre_segments_total_bis(Liste_Contour_Bezier LC)
{
	UINT nbST = 0;
	Cellule_Liste_Contour_Bezier* cc = LC.first;
	while (cc!=NULL)
    {
		nbST+=nombre_segments_bis(cc->data); 
        cc=cc->suiv;
    };
	return nbST;
}


UINT nombre_contours_bis(Liste_Contour_Bezier LC)
{
	return LC.taille;
}

void afficher_infos_bis(Liste_Contour_Bezier LC){
	printf("Nombre de contours : %d\n",nombre_contours_bis(LC));
	printf("Nombre total de segments : %d\n",nombre_segments_total_bis(LC));
}
