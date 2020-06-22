#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "initialisation.h"
#include "types.h"



Vecteur y_exact(Vecteur x)
{
/* Cette fonction permet d'allouer le tableau dynamique et d'initialiser tous les coefficients du vecteur en calculant notre fonction */
	int i;
	Vecteur tmp;

	tmp.NbrLig=x.NbrLig;
	tmp.coef = (double *)malloc(sizeof(double)*x.NbrLig);

	for(i=0;i<x.NbrLig;i++)
	{
		tmp.coef[i]=exp(-10*x.coef[i]);
	}

	return(tmp);
}


Matrice transpo(Matrice A)
{
/* Calcule de la transposee de A */
    int i;
    int j;
    Matrice tmp;

    /* Allocation memoire */
    tmp=InitMatriceZero(A.NbrCol,A.NbrLig);

    for (i=0;i<tmp.NbrLig;i++) {
        for (j=0; j<tmp.NbrCol;j++) {
                tmp.coef[i][j]=A.coef[j][i];
        }
    }
    return(tmp);
}

Matrice multipleM(Matrice A, Matrice B)
{
/* Cette fonction de structure permet de multiplier deux matrices ensemble, afin de réaliser M=tr(A)*A */
    int i,j,k;
    Matrice tmp;


    /* Gestion des erreurs */

    if(A.NbrCol!=B.NbrLig)
    {
    printf("Le nombre de colonne de la matriceA n'est pas egale aux nombres de ligne de la matriceB,vous n'pouvezpas continuer.\n");
    exit(0);

    }
    /* Allocation memoire de la matrice */
    tmp=InitMatriceZero(A.NbrLig,B.NbrCol);

    /* Calcul du produit des deux matrices */
     for (i=0; i<tmp.NbrLig; i++)
         for (j=0; j<tmp.NbrCol; j++)
             {
              tmp.coef[i][j]=0;
              for (k=0; k<A.NbrCol; k++)
                   tmp.coef[i][j] += A.coef[i][k]*B.coef[k][j];

          }
    /* renvoyer le resultat */

     return (tmp);
}


Vecteur multipleV(Matrice A, Vecteur y)
{
/* Cette fonction de structure permet de multiplier une matrice et un vecteur ensemble, afin de réaliser tr(A)*y */
    int i, j;
    Vecteur tmp;

    if(A.NbrCol!=y.NbrLig)
    {
    printf("Le nombre de colonne de la matrice 1 n'est pas egale aux nombres de ligne de la matrice 2,vous n'pouvezpas continuer.\n");
    exit(0);
    }

    tmp=InitVecteurZero(A.NbrLig);


    for (i=0; i<tmp.NbrLig; i++)
    {
        tmp.coef[i]=0.0;
        for (j=0; j<A.NbrCol; j++)
        {
            tmp.coef[i]=A.coef[i][j]*y.coef[j]+tmp.coef[i];
        }
    }

    return(tmp);
}



void factoriser_LU( Matrice *M, Matrice *U, Matrice *L ) {
/* on choisie de factoriser notre matrice avec la méthode LU, étant donné que nous voulons que le programme soit valable quelque soit la matrice du systeme */
	int i,j,k;
	double l;
	*U=InitMatriceZero(M->NbrLig,M->NbrCol);
	*L=InitMatriceZero(M->NbrLig,M->NbrCol);
	for (j=0;j<=(M->NbrLig)-1;j++) {
		
		for (i=0;i<=j;i++) {
			l=0.0;
			for (k=0;k<=i-1;k++) l += (L->coef[i][k])*(U->coef[k][j]);
			(U->coef[i][j]) = (M->coef[i][j]) - l;
		}
		L->coef[j][j] = 1;
		for (i=j+1;i<=(M->NbrCol)-1;i++) {
			l=0.0;
			for (k=0;k<=j-1;k++) l += (L->coef[i][k])*(U->coef[k][j]);
			(L->coef[i][j]) = ((M->coef[i][j]) - l)/(U->coef[j][j]);
		}
				
	}
	
}


Vecteur resol_trig_inf( Matrice L, Vecteur b) {
/* on réalise ici la descente afin de determiner y_reso tel que, Ly=b */
	int i,k;
	float l;
	Vecteur y_reso;
	y_reso=InitVecteurZero(L.NbrLig);
	for (i=0;i<L.NbrLig;i++) {
		l=0;
		for (k=0;k<=i-1;k++) l += L.coef[i][k]*y_reso.coef[k];
		y_reso.coef[i] = (b.coef[i] -l)/L.coef[i][i];
	}
	return(y_reso);
}

Vecteur resol_trig_sup( Matrice U, Vecteur y_reso) {
/* on realise la remontée afin de determiner a_reso tel que, Ua_reso=y_reso */
	int i,k;
	float l;
	Vecteur a_reso;
	a_reso=InitVecteurZero(U.NbrLig);
	FILE* fichier = NULL;

	fichier = (FILE *) fopen("Resolution_moindre.txt","w");
	if (fichier ==NULL) {
		printf("Impossible d'ouvrir le fichier Resolution_moindre.txt");
	}

	for (i=U.NbrLig-1;i>=0;i--) {
		l=0;
		for (k=i+1;k<y_reso.NbrLig;k++) l += U.coef[i][k]*a_reso.coef[k];
		a_reso.coef[i] = (y_reso.coef[i] -l)/U.coef[i][i];
		fprintf(fichier,"% 11.8e \n", a_reso.coef[i]);
		
	}
	fclose(fichier);
	return(a_reso);
}	


