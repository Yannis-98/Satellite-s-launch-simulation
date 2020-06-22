#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "types.h"

double fonc_u(double x, double y) { /* on utilise un formalise peremttant de ne pas mettre directement les formules a chaques fois, les erreurs sont donc evitees et l'algorithme est plus clair */
	double f;
	double M=5.972*pow(10,24);
	double G=6.674*pow(10,-11);
	
	f=-G*M*(x/(pow(x*x + y*y,3/2.0)));
return(f);
}


double fonc_v(double x, double y) { /* meme chose que fonc_u */
	double f;
	double M=5.972*pow(10,24);
	double G=6.674*pow(10,-11);
	
	f=-G*M*(y/(pow(x*x + y*y,3/2.0)));
return(f);
}

double app_S1(double h, double us1, double vs1, double x, double y, time_t *chrono, double *position) {
	time_t debut, fin, duree; /* on veut connaitre le temps d'execution de notre methode */
	debut=time(NULL);
	int NT=0; /* nombre de demie-tour (moitie)*/
	double t=0.0; 	/*temps initial */
	double tmp_u; /* on passe par une variable temporaire */
	double tmp_v;
	double tmp_x;
	double tmp_y;
	double norm=0.0; /* norme de notre vecteur */
	double n1=0.0; /* n1 et n2 sont les vecteurs tangentielles*/
	double n2=0.0;
	int s=0;

	/* Je n'utilise pas de tableau etant donnee que je ne connais pas la taille exacte de mes tableaux, car ces derniers dependent du nombre d'iteration de notre schema, je prefere alors le stocker */

	FILE* fichier = NULL;
	fichier = (FILE *) fopen("Schema1_Q1.txt","w");
	if (fichier ==NULL) {
		printf("Impossible d'ouvrir le fichier Schema1_Q1.txt");
	}

	 		
		while (NT<=5) { /* condition d'arret pour 5 tours */

			fprintf(fichier,"% 11.8e  % 11.8e  % 11.8e  % 11.8e  % 11.8e  % 11.8e \n", t,x, y,sqrt(x*x+y*y),us1, vs1); /*on stock nos points calcules */
			tmp_x=x;
			tmp_y=y;
			tmp_u=us1;
			tmp_v=vs1;
			
			x=x+h*tmp_u;
			y=y+h*tmp_v;
			us1=us1+h*fonc_u(tmp_x,tmp_y);
			vs1=vs1+h*fonc_v(tmp_x,tmp_y);

			if (tmp_x*x <0.0){ /* on repere quand notre satellite passe par l'axe y, on compte une moitiee de tour */
				NT=NT+1;
			}

			if ((NT==1) && (s==0)){ /*quand notre satellite atteint son perigee, on accelere afin de prendre l'orbite de transfert*/
				norm=sqrt(us1*us1+vs1*vs1);
				n1=us1/norm;
				n2=vs1/norm;
				us1=n1*10248.15689;
				s=1; /* indique que nous avons deja accelere une fois */
			}
			
			if ((NT==2) && (s==1)){
				norm=sqrt(us1*us1+vs1*vs1);/*quand notre satellite atteint son apogee, on accelere afin de rester dans notre orbite geostationnaire*/
				n1=us1/norm;
				n2=vs1/norm;
				us1=n1*3067.03;
				s=2; /* indique que nous avons accelere deux fois */
			}

			t=t+h;

		}
	fclose(fichier);
	*position=sqrt(x*x+y*y); /*on recupere la derniere position afin de la comparer avec la position theorique */
	fin=time(NULL);
	*chrono=fin-debut; /* temps d'execution de notre schema */
	return(t); /* renvoie le temps en seconde qu'a parcouru notre satelitte */
}
		
