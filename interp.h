/*
 ================================================================= 
 Header File for (Spline) Interpolation Module 
 Revised: JCCK. 11/18/2013
          R. Repka 11/10/2015 - Added NAN
 ================================================================= 
*/

#ifndef _INTERP_H_
#define _INTERP_H_

/* Data Types */
typedef struct
  {
   int     N;    /* Number of Elements in array         */
   double *a;    /* Pointer to Constant coefficients   	*/
   double *b;    /* Pointer to Linear coefficients      */
   double *c;    /* Pointer to Quadratic coefficients   */
   double *d;    /* Pointer to Cubic coefficients       */
   double *X;    /* Pointer interpolation interval  partition */
   } CSplines;

typedef struct
  {
   int     N;    /* Number of Elements in array  */
   double *X;    /* Pointer to X data            */
   double *Y;    /* Pointer to Y data            */
   double y0;    /* Derivative of first point */
   double yn;    /* Derivative of last point */
   int  Size;    /* Size of dynamic arrays       */
   int  Next;    /* Index to next point in array */
  } Points;

/* Define NAN if this compiler does not */ 
 #ifndef NAN
   #define NAN (0x7f38d30d9000)
#endif  
  
/* Function Prototypes, add more if needed */

extern void cspline_clamped( Points*, double, double, CSplines*);
extern void cspline_natural( Points*, CSplines* );
void cspline_nak( Points*, CSplines* );
extern double cspline_eval( double, CSplines* );
void polySolve(CSplines *splines, double *h, Points *points);
void printSplines(CSplines *splines);
void s_alloc(CSplines *splines, int N);
void s_free(CSplines *splines);
void p_alloc(Points *points, int N);
static void tridiagonal(double *p, double *q, double *r, double* x, double *B, int N);
void p_free(Points *points);

#endif /*  _INTERP_H_ */
