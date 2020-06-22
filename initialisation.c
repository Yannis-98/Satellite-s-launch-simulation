#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "types.h"

Vecteur InitVecteurZero(int Ni)
{
/* Cette fonction permet d'allouer le tableau dynamique et d'initialiser tous les coefficients de la matrice */
	int i;
	Vecteur tmp;

	tmp.NbrLig=Ni;
	tmp.coef = (double *)malloc(sizeof(double)*Ni);

	for(i=0;i<Ni;i++)
	{
		tmp.coef[i]=0.0;
	}

	
	return(tmp);
}

Matrice InitMatriceZero(int Ni, int Nj)
{
/* Cette fonction permet d'allouer le tableau dynamique et d'initialiser tous les coefficients de la matrice */
	int i;
	int j;
	Matrice tmp;

	tmp.NbrLig=Ni;
	tmp.NbrCol=Nj;

/* Allocation memoire */
	tmp.coef = (double **)malloc(sizeof(double)*Ni);
	for(i=0;i<Ni;i++)
	{
		tmp.coef[i]=(double *)malloc(sizeof(double)*Nj);
	}

/* Mise a zero des coefficients */
	for(i=0;i<Ni;i++)
	{
		for(j=0;j<Nj;j++)
		{
			tmp.coef[i][j]=0.0;
		}
	}
	
	

	return(tmp);
}

Vecteur InitVecteur(double a, double b, int Ni)
{
/* Cette fonction permet d'allouer le tableau dynamique et d'initialiser tous les coefficients de la matrice */
	int i;
	Vecteur tmp;

	tmp.NbrLig=Ni;

	tmp=InitVecteurZero(tmp.NbrLig);

	for(i=0;i<Ni;i++)
	{
		tmp.coef[i]=a+i*(b-a)/(Ni-1);
	}

	return(tmp);
}

Matrice InitMatrice(int m, Vecteur x)
{
    int i;
    int j;
    Matrice tmp;

    tmp.NbrLig = x.NbrLig;
    tmp.NbrCol = m;

    /* Allocation memoire */
	tmp.coef = (double **)malloc(sizeof(double)*x.NbrLig);
	for(i=0;i<x.NbrLig;i++)
	{
		tmp.coef[i]=(double *)malloc(sizeof(double)*x.NbrLig);
	}

    for(i=0;i<x.NbrLig;i++) /* initialisation à 0 */
	{
		for(j=0;j<m;j++)
        {
            tmp.coef[i][j]=pow(x.coef[i],j);
        }
	}

	return(tmp);

}


