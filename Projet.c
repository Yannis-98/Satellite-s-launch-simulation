#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "initialisation.h"
#include "affichage.h"
#include "Question1.h"
#include "Question2.h"
#include "Question3.h"
#include "Question4.h"
#include "Question5.h"
#include "Question_EDO_erreur.h"
#include "Question_II_2.h"
#include "Question_II_3.h"
#include "Question_II_4_5.h"
#include "Question_II_6.h"
#include "types.h"



int main()
{
/*--------Initialisation pour la question 1----------------- */
    	Vecteur x;	/* declaration de notre vecteur xi */
    	Vecteur y;	/* declaration de notre vecteur y_exact */
    	Matrice A;	/* matrice correspondant aux coefficiants */
    	Matrice At;	/* transposée de A */
    	Matrice M;	/* resultat de M=tr(A)*A */
    	Vecteur b;	/*resultat de b=tr(A)*y */
    	Matrice U;	/* resolution du LU */
    	Matrice L;
	Vecteur y_reso;	/* y_m */
	Vecteur a_reso;	/*coefficiant du moindre carree */


/*--------Initialisation pour la question 2----------------- */

	double trapeze_f;
	Vecteur y_moindre;
	double trapeze_moindre;

/*--------Initialisation pour la question 3----------------- */

	double simps_moindre;
	double gauss_moindre;

/*--------Initialisation pour la question 4----------------- */

	double I_exact;
	double I_simps;
	double I_gauss;
	double err_quadr;

/*--------Initialisation pour la question 6----------------- */
	Vecteur ys1;
/*--------Initialisation pour la question 7----------------- */
	Vecteur ys2;
/*--------Initialisation pour la question 8----------------- */
	Vecteur ys3;
/*--------Initialisation pour la question 9----------------- */
	Vecteur ys4;
/*--------Initialisation pour la question 10----------------- */
	double err_quadrS1;
	double err_quadrS2;
	double err_quadrS3;
	double err_quadrS4;
	

/*--------Initialisation pour l'application----------------- */

	double us1;	/* vitesse suivant x */
	double vs1;	/*vitesse suivant y */
	double x_t;	/* position suivant x */
	double y_t;	/* position suivant y */
	double temps_S1;
	double temps_S3;
	time_t chrono1, chrono2, chrono3;

    	int N;
    	int m;
	double h;		/* pas (ici de temps) */
	double Alti_3=36000000; /*Distance apogée et centre de la Terre */
	double Rayon=6371000;  /*Rayon de la Terre */
	double Alti_1=200000;	/*Rayon de la premiere orbite */
	double Arret;
	Arret=Rayon+Alti_3;	/* Distance théorique au rayon de la Terre pour l'orbite geostationnaire */
	us1=-7788.203; /* vitesse trouvée via la 3è loi de Kepler */
	vs1=0;
	x_t=0;
	y_t=Alti_1+Rayon;
	double position;	/* position du satellite */

	int taille_m;		/* Nombre d'element d'un vecteur */
	

	Vecteur X;		/* vitesses et positions durant l'ellipse de transfert */
	Vecteur Y;
	Vecteur U_e;
	Vecteur V_e;
	Vecteur t_e;

	double err;

	double W;	/* travail durant l'orbite de transfert */
	
	

	
	do {
		printf("Veuiller entrer la valeur du nombre d'intervalle N\n");
		scanf("%d", &N);
	
	}
	while (N<0);
	do {
		printf("Veuiller entrer la valeur de l'ordre de la methode d'approximation m compris entre 1 et 10\n");
		scanf("%d", &m);
	}
	while ((m<1)||(m>10));


/*------------------Question 1-------------------- */
	printf("\n\n-----------------Question I_1------------------------------ \n\n");

/* on réalise notre approximation au sens des moindres carres, en utilisant la formule suivante : (tr(A)*A)*x=tr(A)*y */

	x=InitVecteurZero(N);

    /*AfficheVecteur("x",x);*/

    x=InitVecteur(0.0,3.0,N);

    /*AfficheVecteur("x",x);*/

    y=y_exact(x);

    /*AfficheVecteur("y",y);*/

    A=InitMatrice(m,x);

    /*AfficheMatrice("A",A);*/

    At=transpo(A);
    /*AfficheMatrice("transpo A",At);*/

    M=multipleM(At,A);
    /*AfficheMatrice("Matrice M",M);*/
  
    b=multipleV(At,y);

    AfficheVecteur("Vecteur b",b);
 
    factoriser_LU( &M, &U, &L );
	
	/*AfficheMatrice("Matrice U",U);*/
	/*AfficheMatrice("Matrice L",L);*/  

	y_reso=resol_trig_inf( L, b);
	printf("Vecteur y_reso, tel que L*y_reso=b : \n");
	AfficheVecteur("Vecteur y_reso",y_reso);
	
	a_reso=resol_trig_sup( U, y_reso);
	printf("Vecteur a_reso, tel que U*a_reso=y_reso : \n");
	AfficheVecteur("Vecteur a_reso",a_reso);


/* ------------------Question 2----------------------*/
	printf("\n\n-----------------Question I_2------------------------------ \n\n");
	trapeze_f=inte_trapeze(y,x); /* on calcule ici l'integrale avec la methode trapeze */
	printf("L'integrale de la fonction y=exp(-10x) d'apres la methode des trapezes : \n % 11.8e \n\n", trapeze_f);

	y_moindre = fonc_moindre_carre(a_reso, x); /* on calcule la fonction y_m */
	/*AfficheVecteur("Vecteur y_moindre",y_moindre);*/

	trapeze_moindre=inte_trapeze_m(a_reso ,x); /*on realise l'integrale avec la methode trapeze sur la fonction moindre caree y_m */
	printf("L'integrale de la fonction moindre carree d'apres la methode des trapezes : \n % 11.8e \n", trapeze_moindre);
	



/* ------------------Question 3----------------------*/
	printf("\n\n-----------------Question I_3------------------------------ \n\n");

	simps_moindre=inte_simpson_m(a_reso ,x); /* on calcule l'integrale de notre fonction approchee avec la methode simpson */
	printf("L'integrale de la fonction moindre carree d'apres la methode de simpson : \n % 11.8e \n\n", simps_moindre);

	gauss_moindre=inte_gauss(a_reso, x); /* on calcule l'integrale de notre fonction approchee avec la methode de gauss */
	printf("L'integrale de la fonction moindre carree d'apres la methode de Gauss : \n % 11.8e \n", gauss_moindre);
	


/* ------------------Question 4----------------------*/
	/* on compare les integrales entre elles, on en deduit l'integrale la plus precise */
	printf("\n\n-----------------Question I_4------------------------------ \n\n");
	I_gauss=gauss_moindre;
	I_simps=simps_moindre;
	I_exact=(1/10.0)*(1-exp(-30));
	comparaison_int(I_simps, I_gauss, I_exact);


/* ------------------Question 5----------------------*/
	printf("\n\n-----------------Question I_5------------------------------ \n\n");	
	err_quadr=erreur_quadr(y, y_moindre, N); /* on trouve l'erreur quadratique de notre methode */
	printf("l'erreur quadratique est de : \n % 11.8e\n",err_quadr);
	

/* ------------------Question 6----------------------*/
	printf("\n\n-----------------Question I_6------------------------------ \n\n");
	ys1=diff_S1(x); /*Calcul de l'EDO avec la methode Euler explicite */
	printf("la solution avec le schema 1 est stockee dans le fichier 'Schema1_ys1.txt' \n");

/* ------------------Question 7----------------------*/
	printf("\n\n-----------------Question I_7------------------------------ \n\n");
	ys2=diff_S2(x); /*Calcul de l'EDO avec la methode Runge-Kutta explicite */
	printf("la solution avec le schema 2 est stockee dans le fichier 'Schema2_ys2.txt' \n");

/* ------------------Question 8----------------------*/
	printf("\n\n-----------------Question I_8------------------------------ \n\n");
	ys3=diff_S3(x); /*Calcul de l'EDO avec la methode Euler implicit */
	printf("la solution avec le schema 3 est stockee dans le fichier 'Schema3_ys3.txt' \n");

/* ------------------Question 9----------------------*/
	printf("\n\n-----------------Question I_9------------------------------ \n\n");
	ys4=diff_S4(x); /*Calcul de l'EDO avec la methode Runge-Kutta semi-explicite */
	printf("la solution avec le schema 4 est stockee dans le fichier 'Schema4_ys4.txt' \n");
	

/* ------------------Question 10----------------------*/
	printf("\n\n-----------------Question I_10------------------------------ \n\n");
	/* Calcul des variances */
	err_quadrS1=Variance(y, ys1, N);
	printf("La Variance du schema 1 est de : \n % 11.8e\n",err_quadrS1);
	printf("\n");

	err_quadrS2=Variance(y, ys2, N);
	printf("La Variance du schema 2 est de : \n % 11.8e\n",err_quadrS2);
	printf("\n");

	err_quadrS3=Variance(y, ys3, N);
	printf("La Variance du schema 3 est de : \n % 11.8e\n",err_quadrS3);
	printf("\n");

	err_quadrS4=Variance(y, ys4, N);
	printf("La Variance du schema 4 est de : \n % 11.8e\n",err_quadrS4);

/*----------------------Application-----------------------------------------------------*/

/* ------------------Question 2----------------------*/
	printf("\n\n-----------------Question II_2------------------------------ \n\n");

	/*on realise le calcul de nos differentiels couplés avec la methode d'Euler explicite*/


	printf("Afin de realiser le schema 1, quel pas de temps (t) desirez vous? \n");
	scanf("%lf", &h);

	temps_S1=app_S1( h, us1, vs1, x_t, y_t, &chrono1, &position);
	printf("La hauteur h= % 11.8e m est atteinte avec le schema 1, le satellite realise 2.5 tours en %f heures\n \n",position, temps_S1/3600.0);
	printf("L'erreur relatif a la valeur theorique P=% 11.8e m est de %e %% \n", Arret, 100*(abs(Arret-position))/Arret);
	printf("\nLe temps d'execution du schema 1 est de %ld s\n",chrono1);



/* ------------------Question 3----------------------*/
	printf("\n\n-----------------Question II_3------------------------------ \n\n");

	/*on realise le calcul de nos differentiels couplés avec la methode de Runge-Kutta explicite*/
	
	printf("Afin de realiser le schema 2, quel pas de temps (t) desirez vous?\n");
	scanf("%lf", &h);
	taille_m=app_S2( h, us1, vs1, x_t, y_t, &chrono2, &position);
	printf("\nLa hauteur h= % 11.8e m est atteinte avec le schema 2\n",position);
	printf("L'erreur relatif a la valeur theorique P=% 11.8e m est de %e %% \n", Arret, 100*(abs(Arret-position))/Arret);
	printf("Le temps d'execution du schema 2 est de %ld s\n",chrono2);
	

/* ------------------Question 4----------------------*/
	printf("\n\n-----------------Question II_4------------------------------ \n\n");

	/*on mesure l'erreur quadratique entre l'equation d'une ellipse parfaite et nos points calculés à l'aide de la question 2*/

	fonc_elipse(taille_m, &X, &Y, &U_e, &V_e, &t_e);
	err=erreur_ellipse(taille_m);
	printf("L'erreur au sens des moindres carrees avec l'ellipse est de %11.8e \n", err);


/* ------------------Question 5----------------------*/

	printf("\n\n-----------------Question II_5------------------------------ \n\n");

	/*On calcul ici le travail sur l'orbite de transfert qui est elliptique */

	W=inte_simpson_elipse(X, Y, U_e, V_e, t_e);
	printf("Le travail par unite de masse durant l'orbite de transfert vaut W=% 11.8e J/kg\n", W);	

/* ------------------Question 6----------------------*/
	printf("\n\n-----------------Question II_6------------------------------ \n\n");

	/*on realise le calcul de nos differentiels couplés avec la methode d'Euler implicite en commançant par résoudre avec la methode de Newton-Raphton*/

	printf("Afin de realiser le schema 3, quel pas de temps (t) desirez vous?\n");
	scanf("%lf", &h);
	temps_S3=app_S3(h, us1, vs1, x_t, y_t, &chrono3, &position);
	printf("\nLa hauteur h= % 11.8e m est atteinte avec le schema 3, le satellite realise 2.5 tours en %f heures\n",position, (temps_S3/3600));
	printf("L'erreur relatif a la valeur theorique P=% 11.8e m est de %e %% \n", Arret, 100*(abs(Arret-position))/Arret);
	printf("Le temps d'execution du schema 3 est de %ld s\n",chrono3);



    return(0);

}
