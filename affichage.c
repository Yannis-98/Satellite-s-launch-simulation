#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "types.h"


void AfficheVecteur(char *msg,Vecteur V) /*cette fonction permet d'afficher nos differents vecteurs */
{
    int i;

    printf("Affichage du vecteur %s\n \n",msg);
    for(i=0;i<V.NbrLig;i++)
    {
        printf("%s[%3d]= % 11.8e\n",msg,i+1,V.coef[i]);
    }
	printf("\n-------------------------------------------------------------- \n");
}

void AfficheMatrice(char *msg,Matrice V) /*cette fonction permet d'afficher nos differentes matrices */
{
    int i;
    int j;

    printf("Affichage de la matrice %s\n \n",msg);
    for(i=0;i<V.NbrLig;i++)
    {
        for(j=0;j<V.NbrCol;j++)
        {
            printf("%s[%3d,%3d]= % 11.8e\t",msg,i+1,j+1,V.coef[i][j]);
        }
        printf("\n");
    }
    
	printf("\n-------------------------------------------------------------- \n");
}
