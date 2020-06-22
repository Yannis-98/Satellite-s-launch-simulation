#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "initialisation.h"
#include "types.h"

double f_moindre(Vecteur a, double x) {
	int i; /*on utlise cette fonction afin de faciliter les futurs calculs */
	double tmp;
	tmp=0.0;
	for (i=0; i<a.NbrLig; i++) {
		tmp=tmp+(a.coef[i]*pow(x, i));
	}
	return(tmp);
}

Vecteur fonc_moindre_carre(Vecteur a, Vecteur x) {
	int i;
	int j;
	Vecteur tmp;
	tmp=InitVecteurZero(x.NbrLig);
	for(i=0; i<x.NbrLig; i++) {
		tmp.coef[i]=0;
		for(j=0; j<a.NbrLig; j++) {
			tmp.coef[i]=a.coef[j]*pow(x.coef[i],j) + tmp.coef[i];
		}
	}
	return(tmp);
}

double inte_trapeze(Vecteur y, Vecteur x) { /* calcul de notre integrale via la fonction theorique*/
	int i;
	double s=0;
	for(i=0; i<x.NbrLig-1; i++) {
		s=s+(y.coef[i]+y.coef[i+1])*(x.coef[i+1]-x.coef[i])/2;
	}
	return(s);
}

double inte_trapeze_m(Vecteur a, Vecteur x) { /* calcul de notre integrale via la fonction approchee*/
	int i;
	double h;
	double y1;
	double y2;
	double s=0;
	s=0.0;
	h=(x.coef[x.NbrLig-1]-x.coef[0])/(x.NbrLig-1);
	for (i=0; i<x.NbrLig; i++) {
		y1=f_moindre(a, x.coef[i]);
		y2=f_moindre(a, x.coef[i+1]);
		s=s+(h/2)*(y1+y2);
	}
	return(s);
}

