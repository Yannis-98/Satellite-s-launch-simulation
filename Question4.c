#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "initialisation.h"
#include "types.h"

void comparaison_int(double I_simps, double I_gauss, double I_exact) {
	double tmp1;
	double tmp2;
	
	/* calcule de l'ecart relatif entre simpson et exacte*/
	tmp1=(I_simps-I_exact)/I_exact;
	tmp1=fabs(tmp1);
	printf("L'ecart relatif entre la methode de Simpson et l'integrale exacte est de : \n");
	printf("% 11.8e d'ou une erreur de % 11.8e %% \n", tmp1, tmp1*100);

	/* calcule de l'ecart relatif entre gauss et exacte*/
	tmp2=(I_gauss-I_exact)/I_exact;
	tmp2=fabs(tmp2);
	printf("\nL'ecart relatif entre la methode de Gauss et l'integrale exacte est de :\n");
	printf("% 11.8e d'ou une erreur de % 11.8e %% \n", tmp2, tmp2*100);
	
	printf("\n");
	if(tmp2<tmp1) {
		printf("La methode de Gauss est plus precise");
	}
	if(tmp2>tmp1) {
		printf("La methode de Simpson est plus precise");
	}
	if(tmp2==tmp1) {
		printf("Les deux methodes sont aussi precises");
	}
}
