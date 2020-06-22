#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "Question2.h"
#include "initialisation.h"
#include "types.h"


double inte_simpson(Vecteur y, Vecteur x) {
	int i;
	double s=0;
	double res;
	
	double h;
	h=(x.coef[x.NbrLig-1]-x.coef[0])/(x.NbrLig-1);
/* Notre intervalle est impair */
	for (i=0; i<x.NbrLig-2; i=i+2) {
		s=s+(y.coef[i] + 4*y.coef[i+1]+y.coef[i+2]);
	}
/* Dans le cas d'intervalle impair*/
	if ((x.NbrLig-1 %2)!=0) {
		s=s+((h/2)*(y.coef[x.NbrLig-2]*y.coef[x.NbrLig-1]));
	}


	res=(h/3)*s;
	
	
	return(res);
}




double inte_simpson_m(Vecteur a, Vecteur x){ /* on adapte notre fonction au fait que l'on utilise notre fonction approchee */
	int i; 
	double s;
	double y1;
	double y2;
	double ym;
	double h;
	s=0.0;
	h=(x.coef[x.NbrLig-1]-x.coef[0])/(x.NbrLig-1)/2;
	for (i=0; i<x.NbrLig-1; i++) {
		y1=f_moindre(a, x.coef[i]);
		y2=f_moindre(a, x.coef[i+1]);
		ym=f_moindre(a, (x.coef[i]+x.coef[i+1])/2);
		s=s+(h/3)*(y1+4*ym+y2);
	}
	return(s);
}


double inte_gauss(Vecteur a, Vecteur x) {
/* methode de gauss à 3 points pour ym */
	int i;
	int j;
        int n;
	double s;
	double s_f;
	double w[3]={0.5555555556, 0.8888888889, 0.5555555556};
	double xsi[3]={-0.7745966692, 0.0, 0.7745966692}; 
	double tmp;

	double y;
	s=0.0;
	tmp=0.0;
	
	n=3;

	for(i=0; i<x.NbrLig-1; i++) {
		s=0.0;
		/*for (j=0; j<=3; j++) {*/
		for (j=0; j<=n-1; j++) {
			y=f_moindre(a, ((x.coef[i+1]+x.coef[i])/2) + ((x.coef[i+1]-x.coef[i])/2)*xsi[j]);
			s=s+w[j]*y;
		}

		tmp=tmp+s*((x.coef[i+1]-x.coef[i])/2);
	}
	
	return(tmp);
}
	

