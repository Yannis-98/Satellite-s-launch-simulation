#ifndef _QUESTION_II_6
#define _QUESTION_II_6
#include "types.h"



double det(double A1, double A2, double B1, double B2);
double f_g1(double  x, double u, double X, double Y, double d_t);
double f_dg1x(double X, double Y, double d_t);
double f_dg1y(double X, double Y, double d_t);
double f_g2(double  y, double v, double X, double Y, double d_t);
double f_dg2x(double X, double Y, double d_t);
double f_dg2y(double X, double Y, double d_t);
void Newton(double xn, double yn, double un, double vn, double d_t, double *xnp1, double *ynp1);
double app_S3(double d_t, double us1, double vs1, double x1, double y1, time_t *chrono3, double *position);

#endif
