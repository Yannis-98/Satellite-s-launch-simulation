#ifndef _QUESTION1
#define _QUESTION1

#include "types.h"

Vecteur y_exact(Vecteur x);
Matrice transpo(Matrice A);
Matrice multipleM(Matrice A, Matrice B);
Vecteur multipleV(Matrice A, Vecteur y);
void factoriser_LU( Matrice *M, Matrice *U, Matrice *L );
Vecteur resol_trig_inf( Matrice L, Vecteur b);
Vecteur resol_trig_sup( Matrice U, Vecteur y_reso);

#endif
