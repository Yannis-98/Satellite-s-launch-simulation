#ifndef _TYPES
#define _TYPES


typedef struct Matrice Matrice;
struct Matrice
{
    /* Ici, on cree une structure pour manipuler une matrice */
    int NbrLig; /* Nombre de ligne de la matrice */
    int NbrCol; /* Nombre de colonne de la matrice */
    double **coef; /* Tableau dynamique representant les coeficient de la matrice */
};

typedef struct Vecteur Vecteur;
struct Vecteur /* structure de vecteur afin de faciliter la manipulation*/
{
    int NbrLig;
    double *coef;
};

#endif
