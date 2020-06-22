#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "Question_II_2.h"
#include "types.h"

double app_S2(double h, double us1, double vs1, double x, double y, time_t *chrono2, double *position) {
	time_t debut,fin; /* on suit le meme procede que pour le premier schema, seule la methode de resolution va changer */
	debut=time(NULL);	
	double t=0.0;
	double tmp_u;
	double tmp_v;
	double tmp_x;
	double tmp_y;
	int NT=0;
	double norm=0.0;
	double n1=0.0;
	double n2=0.0;
	int s=0;
	int c=0;
	int taille_m=0;

	FILE* fichier = NULL;
	fichier = (FILE *) fopen("Schema2_Q2.txt","w");
	if (fichier ==NULL) {
		printf("Impossible d'ouvrir le fichier Schema2_Q2.txt");
	}
	FILE* fichier2 = NULL;
	fichier2 = (FILE *) fopen("./T_X_Y_U_V.txt","w");
	if (fichier2 ==NULL) {
		printf("Impossible d'ouvrir le fichier T_X_Y_U_V.txt");
	}


	 		
		while (NT<=5) { /* condition d arret de 5 moities de tours */
			
			fprintf(fichier,"% 11.8e  % 11.8e  % 11.8e  % 11.8e  % 11.8e \n", t,x, y,us1, vs1); /* on stock toute la trajectoire */
			tmp_x=x;
			tmp_y=y;
			tmp_u=us1;
			tmp_v=vs1;

			x=x+(h/2.0)*(us1+(us1+h*fonc_u(x,y)));
			y=y+(h/2.0)*(vs1+(vs1+h*fonc_v(x,y)));

			us1=us1+(h/2.0)*(fonc_u(tmp_x,tmp_y)+fonc_u(tmp_x+h*tmp_u,tmp_y+h*tmp_v));
			vs1=vs1+(h/2.0)*(fonc_v(tmp_x,tmp_y)+fonc_v(tmp_x+h*tmp_u,tmp_y+h*tmp_v));
			
			if (tmp_x*x <0.0){
				NT=NT+1;
			}
			if ((NT==1) && (s==0)){
				norm=sqrt(us1*us1+vs1*vs1);
				n1=us1/norm;
				n2=vs1/norm;
				us1=n1*10248.15689;
				s=1;
				c=1; /*indique que nous sommes dans l'orbite de transfert */
			}
			
			if (c==1) { /*cette condition permet de recuperer seulement la trajectoire de l'orbite de transfert */
				fprintf(fichier2,"% 11.8e  % 11.8e  % 11.8e  % 11.8e  % 11.8e\n",t,x, y,us1,vs1); /*on stock dans une fichier l'orbite de transfert */
				taille_m=taille_m+1; /*on recupere combien de fois on passe dans cette condition */
			}			
				
			if ((NT==2) && (s==1)){
				norm=sqrt(us1*us1+vs1*vs1); 
				n1=us1/norm;
				n2=vs1/norm;
				us1=n1*3067.03;
				s=2;
				c=0; /*indique que nous ne sommes plus dans l'orbite de transfert */
			}

			
			t=t+h;
			
			
		}
	fclose(fichier);
	fclose(fichier2);
	*position=sqrt(x*x+y*y);
	fin=time(NULL);
	*chrono2=fin-debut;
	return(taille_m); /* on retourne la taille des vecteurs de notre orbite de transfert */
	
}

