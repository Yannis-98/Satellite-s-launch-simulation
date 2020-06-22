#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "initialisation.h"
#include "types.h"


double erreur_quadr(Vecteur y, Vecteur ym, int N) { /* on calcul l'erreur quadratique moyen */
	double err_quadr=0.0;
	int i;
	for(i=0; i<y.NbrLig-1; i++) {
		err_quadr=pow((ym.coef[i]-y.coef[i]), 2) + err_quadr;
	}
	return(err_quadr);
}
