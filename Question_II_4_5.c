#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "initialisation.h"
#include "Question_II_2.h"
#include "types.h"


void fonc_elipse(int taille_m, Vecteur *X, Vecteur *Y, Vecteur *U, Vecteur *V, Vecteur *t) {
	double Ttmp,Xtmp,Ytmp,Utmp, Vtmp; /* on initialise de nouveaux vecteurs permettant de recuperer les valeurs de nos variables de l'orbite de transfert */
	int i;
	FILE* fichier2 = NULL;
	
	*t=InitVecteurZero(taille_m);
	*X=InitVecteurZero(taille_m);
	*Y=InitVecteurZero(taille_m);
	*U=InitVecteurZero(taille_m);
	*V=InitVecteurZero(taille_m);

	fichier2 = (FILE *) fopen("./T_X_Y_U_V.txt","r"); /*on ouvre en mode lecture */
	if (fichier2 ==NULL) {
		printf("Impossible d'ouvrir le fichier T_X_Y_U_V.txt");
		exit;
	}

	for(i=0; i<taille_m; i++) {
		fscanf(fichier2,"%lf %lf %lf %lf %lf",&Ttmp,&Xtmp,&Ytmp, &Utmp, &Vtmp);
		t->coef[i]= Ttmp;	
		X->coef[i]= Xtmp;
		Y->coef[i]= Ytmp;
		U->coef[i]= Utmp;
		V->coef[i]= Vtmp;
		
	}
	fclose(fichier2);
}
		
	
double erreur_ellipse(int taille_m) { 
	double Alti_3=36000000;
	double Rayon=6371000;
	double Alti_1=200000;
	
	double a=((Rayon+Alti_1)+Alti_3)/2.0;
	double c=a-(Alti_1+Rayon);
	double b=sqrt(a*a-c*c);
	int i;
	double x;
	double xc=0;
	double y;
	double yc=c;
	double t;
	double reste=0.0;	
	double diff=0.0;
	FILE* fichier2 = NULL;

	fichier2 = (FILE *) fopen("./T_X_Y_U_V.txt","r");	
	if (fichier2 ==NULL) {
		printf("Impossible d'ouvrir le fichier T_X_Y_U_V.txt");
		exit;
	}

	for(i=0; i<taille_m; i++) {
		fscanf(fichier2,"%lf %lf %lf", &t, &x, &y);
		reste=(x-xc)*(x-xc)/(a*a) + (y-yc)*(y-yc)/(b*b); /* le reste doit etre  egale à 1 si notre trajectoire est une ellipse parfaite */

		diff=pow((reste-1),2)+diff; /* le chiffre 1 est le resultat pour une ellipse parfaite etant donnee que (x-xc)*(x-xc)/(a*a) + (y-yc)*(y-yc)/(b*b) = 1 */
		
	}
	return(diff);
}

double inte_simpson_elipse(Vecteur x, Vecteur y, Vecteur U, Vecteur V, Vecteur t){
	/* calcul du travail de la force via la formule dW=F.dV */
	int i;
	double s; 
	double tmp1;
	double tmp2;
	double tmp_m;
	double h;
	s=0.0;
	h=(t.coef[t.NbrLig-1]-t.coef[0])/(t.NbrLig-1);

	for (i=0; i<t.NbrLig-2; i=i+2) {
		tmp1=fonc_u(x.coef[i], y.coef[i])*U.coef[i]+fonc_v(x.coef[i], y.coef[i])*V.coef[i];
		tmp2=fonc_u(x.coef[i+1], y.coef[i+1])*U.coef[i+1]+fonc_v(x.coef[i+1], y.coef[i+1])*V.coef[i+1];
		tmp_m=fonc_u(x.coef[i+2], y.coef[i+2])*U.coef[i+2]+fonc_v(x.coef[i+2], y.coef[i+2])*V.coef[i+2];
		s=s+(h/3)*(tmp1+4*tmp_m+tmp2);
	}
	return(s);
}
	


