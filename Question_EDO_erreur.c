
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "types.h"
#include "initialisation.h"


double f_dif(double x, double y) { /* afin de faciliter les calculs et de diminuer les erreurs, on utilisera cette fonction permettant de retrouver le formalisme */
	double f;
	f=-10*(y);
	return f;
}

Vecteur diff_S1(Vecteur x) {
	int i;
	double h;
	Vecteur ys1;
	FILE* fichier = NULL;
	fichier = (FILE *) fopen("Schema1_ys1.txt","w");
	if (fichier ==NULL) { /* securite à l'ouverture */
		printf("Impossible d'ouvrir le fichier Schema1_Q1.txt");
	}
	ys1=InitVecteurZero(x.NbrLig);
	ys1.coef[0]=1;
	 	for(i=0; i<x.NbrLig-1; i++) { /*on itere jusqu'a N non inclue*/
			h=x.coef[i+1]-x.coef[i];
			ys1.coef[i+1]=ys1.coef[i]+h*f_dif(x.coef[i], ys1.coef[i]);
			fprintf(fichier,"% 11.8e \n", ys1.coef[i]); /* on copie nos resultats dans une fichier afin de pouvoir les reutiliser plus tard */
		}
	fclose(fichier);
	return(ys1);
}


Vecteur diff_S2(Vecteur x) {
	int i;
	double h;
	Vecteur ys2;
	FILE* fichier = NULL;
	fichier = (FILE *) fopen("Schema2_ys2.txt","w");
	if (fichier ==NULL) {  /* securite à l'ouverture */
		printf("Impossible d'ouvrir le fichier Schema1_Q1.txt");
	}
	ys2=InitVecteurZero(x.NbrLig);
	ys2.coef[0]=1;
	 	for(i=0; i<x.NbrLig-1; i++) {
			h=x.coef[i+1]-x.coef[i];
			ys2.coef[i+1]=ys2.coef[i]+h*f_dif(x.coef[i], ys2.coef[i]+h*f_dif(x.coef[i], ys2.coef[i]));
			fprintf(fichier,"% 11.8e \n", ys2.coef[i]);/* on copie nos resultats dans une fichier afin de pouvoir les reutiliser plus tard */
		}
	fclose(fichier);
	return(ys2);
}


Vecteur diff_S3(Vecteur x) {
	int i;
	double h;
	Vecteur ys3;
	FILE* fichier = NULL;
	fichier = (FILE *) fopen("Schema3_ys3.txt","w");
	if (fichier ==NULL) {
		printf("Impossible d'ouvrir le fichier Schema1_Q1.txt");
	}
	ys3=InitVecteurZero(x.NbrLig);
	ys3.coef[0]=1;
	 	for(i=0; i<x.NbrLig-1; i++) {
			h=x.coef[i+1]-x.coef[i];
			ys3.coef[i+1]=ys3.coef[i]/(1+10*h);
			fprintf(fichier,"% 11.8e \n", ys3.coef[i]); /* on copie nos resultats dans une fichier afin de pouvoir les reutiliser plus tard */
		}
	fclose(fichier);
	return(ys3);
}

Vecteur diff_S4(Vecteur x) {
	int i;
	double h;
	Vecteur ys4;
	FILE* fichier = NULL;
	fichier = (FILE *) fopen("Schema4_ys4.txt","w");
	if (fichier ==NULL) {
		printf("Impossible d'ouvrir le fichier Schema1_Q1.txt");
	}
	ys4=InitVecteurZero(x.NbrLig);
	ys4.coef[0]=1;
	 	for(i=0; i<x.NbrLig-1; i++) {
			h=x.coef[i+1]-x.coef[i];
			ys4.coef[i+1]=(ys4.coef[i]+(h/2.0)*f_dif(x.coef[i], ys4.coef[i]))/(1+5*h);
			fprintf(fichier,"% 11.8e \n", ys4.coef[i]);		
		}
	fclose(fichier);
	return(ys4);
}


double Variance(Vecteur y, Vecteur ym, int N) { /* on calcule la variance */
	double err_quadr=0.0;
	int i;
	for(i=0; i<y.NbrLig-1; i++) {
		err_quadr=(1.0/(N))*pow((ym.coef[i]-y.coef[i]), 2) + err_quadr;
	}
	return(sqrt(err_quadr));
}
	



