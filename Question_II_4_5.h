#ifndef _QUESTION_II_4_5
#define _QUESTION_II_4_5
#include "types.h"

void fonc_elipse(int taille_m, Vecteur *X, Vecteur *Y, Vecteur *U, Vecteur *V, Vecteur *t);
double erreur_ellipse(int taille_m);
double inte_simpson_elipse(Vecteur x, Vecteur y, Vecteur U, Vecteur V, Vecteur t);

#endif
