#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "Question_II_2.h"
#include "initialisation.h"
#include "types.h"

/* ces fonctions sont calculées analytiquement via un développement venant de la jacobienne du système, et ensuite de Cramer */
double det(double A1, double A2, double B1, double B2) {
	double s;
	s=A1*B2-A2*B1; /*calcul du determinant, matrice de dim2 */
	return(s);
}

double f_g1(double  x, double u, double X, double Y, double d_t) {
	double s;
	s=X-x-d_t*u-(d_t*d_t)*fonc_u(X, Y);
	return (s);
}

double f_dg1x(double X, double Y, double d_t) {
	double s;
	double M=5.972e24;
	double G=6.674e-11;
	s=1+(d_t*d_t)*G*M*(-2*X*X+Y*Y)/pow((X*X+Y*Y),5.0/2);
	return (s);
}

double f_dg1y(double X, double Y, double d_t) {
	double s;
	double M=5.972e24;
	double G=6.674e-11;
	s=-d_t*d_t*G*M*(X*Y)/pow((X*X+Y*Y), 5.0/2);
	return (s);
}

double f_g2(double  y, double v, double X, double Y, double d_t) {
	double s;
	s=Y-y-d_t*v-(d_t*d_t)*fonc_v(X,Y);
	return (s);
}


double f_dg2x(double X, double Y, double d_t) {
	double s;
	double M=5.972e24;
	double G=6.674e-11;
	s=-d_t*d_t*G*M*(X*Y)/pow((X*X+Y*Y), 5.0/2);
	return (s);
}

double f_dg2y(double X, double Y, double d_t) {
	double s;
	double M=5.972e24;
	double G=6.674e-11;
	s=1+(d_t*d_t)*G*M*(-2*Y*Y+X*X)/pow((X*X+Y*Y),5.0/2);	
	return (s);
}

void Newton(double xn, double yn, double un, double vn, double d_t, double *xnp1, double *ynp1) {
	double eps=1e-12; /* critère d'arret */

	double x;
	double y;
	double g1;
	double g2;
	double dg1x;
	double dg1y;
	double dg2x;
	double dg2y;
	double DeltaX;
	double DeltaY;

	x=xn; /* stockage de nos valeurs d'entrees */
	y=yn;
	
	do
	{
		g1=-f_g1(xn,un,x,y,d_t); /* vient de la jacobienne, trouvé analytiqement */
		g2=-f_g2(yn,vn,x,y,d_t);
		dg1x=f_dg1x(x,y,d_t);
		dg1y=f_dg1y(x,y,d_t);
		dg2x=f_dg2x(x,y,d_t);
		dg2y=f_dg2y(x,y,d_t);

		DeltaX=det(g1,g2,dg2x,dg2y)/det(dg1x,dg1y,dg2x,dg2y);
		DeltaY=det(dg1x,dg1y,g1,g2)/det(dg1x,dg1y,dg2x,dg2y);

		x=x+DeltaX;
		y=y+DeltaY;
	}
	while ((fabs(DeltaX) > eps*fabs(xn)) && (fabs(DeltaY) > eps*fabs(yn))); /* quand DeltaX et DeltaY proche de 0 */


	*xnp1=x;
	*ynp1=y;

}
	
double app_S3(double d_t, double us1, double vs1, double x1, double y1, time_t *chrono3, double *position) {
	time_t debut, fin;
	debut=time(NULL);	
	int NT=0;
	double t=0.0; 	
	double xn, xnp1;
	double yn, ynp1;
	double un, unp1;
	double vn, vnp1;
	double norm=0.0;
	double n1=0.0;
	double n2=0.0;
	int s=0;
	
	

	FILE* fichier = NULL;
	fichier = (FILE *) fopen("Schema3_Q4.txt","w"); /*stockage de nos valeurs*/
	if (fichier ==NULL) {
		printf("Impossible d'ouvrir le fichier Schema3_Q4.txt");
	}

	 	xn=x1;
		yn=y1;
		un=us1;
		vn=vs1;
	
		while (NT<=5) { /* condition d'arret pour 2.5 tours */

			fprintf(fichier,"% 11.8e  % 11.8e  % 11.8e  % 11.8e  % 11.8e  % 11.8e \n", t,xn, yn,sqrt(xn*xn+yn*yn),un, vn);

			Newton(xn, yn, un, vn, d_t, &xnp1, &ynp1); /* calcul des racines */
			
			unp1=un+d_t*fonc_u(xnp1,ynp1); /* réalisation de notre schéma aprés avoir trouvé nos xnp1 et ynp1 via Newton */
			vnp1=vn+d_t*fonc_v(xnp1,ynp1);

			if (xn*xnp1 <0.0){
				NT=NT+1;
			}

			if ((NT==1) && (s==0)){ /* meme demarche que les autres schemas */
				norm=sqrt(unp1*unp1+vnp1*vnp1);
				n1=unp1/norm;
				n2=vnp1/norm;
				unp1=n1*10248.15689;
				s=1;
			}
			
			if ((NT==2) && (s==1)){
				norm=sqrt(unp1*unp1+vnp1*vnp1);
				n1=unp1/norm;
				n2=vnp1/norm;
				unp1=n1*3067.03;
				s=2;
			}

			xn=xnp1;
			yn=ynp1;
			un=unp1;
			vn=vnp1;
			
			t=t+d_t;

		}
	fclose(fichier);
	*position=sqrt(xn*xn+yn*yn);
	fin=time(NULL);
	*chrono3=fin-debut; /* temps d'execution */
	return(t);/* durée des 2.5 tours */
}	


