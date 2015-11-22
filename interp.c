/*******************************************************************
* interp.c - student file
*
* Finds splines from given points with different interpolation methods.
*
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interp.h"




/***************************************************************************************
 Finds the coefficients of the natural cubic spline for a given set of data points
 Zero 2nd derivatives at end-points)
		so’’   (xo) = 0  
        sn-1’’ (xn) = 0
	    set to zero curvature at endpoints

 Where: Points   *Data	-   Pointer to Data Points array
        CSplines *Splines - Pointer to Spline Structure, data returned here 
                            Splines Coefficients of Cubic Spline Interpolants 
 Returns: nothing    
 Errors:  prints an message and exits 
*****************************************************************************************/
void cspline_natural(Points* data, CSplines* splines){

	
    /* Generate the h (difference) vector: notes: hj = xj+1  -  xj*/
 
	
    /* Find the alpha vector: notes: alphaj = 3(yj+1 - yj  - yj - yj-1)     j=1..n-1
                                              ---------------------------
                                                    hj         hj       */
 
    
    /* Generate the outside symmetric tri-diagonal matrix from h1 to hn-2  */
  
    
    /* Generate the center diagonal of the symmetric tri-diagonal matrix 
        2(h0+h1)       0 to n-2 inclusive                                 */
 
    
    /* Use the general tri-diagonal solver to find spline value c */
 
    
    /* Initial "c" condition, zero curvature at the end points */
 
    
    /* Copy the solution of the tri-diagonal value c into the spline structure */
 
    
    /* Solve for A, B, and D. */
 
}


/***************************************************************************************
 Finds the coefficients of the clamped cubic spline for a given set of data points
         (Prescribed 1st derivatives at end-points)
		so’ (xo) =  f ’ (x0 )  
        s’ (xn)  = f ’ (xn )
	    clamp end-points at prescribed angles
        
 Where Points *Data	     - Pointer to Data Points array
       double fpa	     - derivative of function at x=a
       double fpb	     - derivative of function at x=b
       CSplines *Splines - Pointer to Spline Structure, data returned here 
                            Splines Coefficients of Cubic Spline Interpolants      
 Returns: Nothing
 Errors:  none
*****************************************************************************************/
void cspline_clamped( Points* data, double fpa, double fpb, CSplines* splines){

	
    /* Generate the h vector: notes: hj = xj+1  -  xj*/
 
    
	/* Find the alpha vector 
        alpha0 = 3(y1 - y0) - y0' 
                 -------------
                     h0                 */

    
    /* Find the alpha vector: notes: alphaj = 3(yj+1 - yj  - yj - yj-1)      j=1...n-1
                                              --------------------------    
                                                    hj         hj       */
  
    
    /*  alphan = 3(yn' - (yn - yn-1)  )
                          ----------
                              hn-1             */


    /* Generate the outside symmetric tri-diagonal matrix */

    
    /* Generate the center diagonal of the symmetric tri-diagonal matrix */

    
    /* Use the general tri-diagonal solver to find spline data c */
 
    
    /* Copy the solution of the tri-diagonal value c into the spline structure */
 
}


/***************************************************************************************
 Finds the coefficients of the not-a-knot cubic spline for a given set of data points
        Not-a-Knot (Continuous 3rd derivatives at x1 and xn-1)
	 	so’’’ (x1) = sn-1’’’ (xn-1) 

 Where Points *Data	     - Pointer to Data Points array
       CSplines *Splines - Pointer to Spline Structure, data returned here 
                            Splines Coefficients of Cubic Spline Interpolants      
 Returns: Nothing
 Errors:  none
***************************************************************************************/
void cspline_nak( Points* data, CSplines* splines ){

    
	/* Find the h vector: notes: hj = xj+1  -  xj*/

	
    /* Find the alpha vector: notes: alphaj = 3(yj+1 - yj  - yj - yj-1)  
                                               -----------   ------------  j= 1..N-1
                                                    hj         hj       */
 
    
    /* Find the tri-diagonal matrix and solve for c */
    /* Generate the outside symmetric tri-diagonal matrix */
  
    
    /* Generate the extra bottom terms for knk 
           = h2 - hn-1**2/hn-2                 */

    
    /* Generate the top terms for knk 
           = h1 - h0**2/h1                  */

    
    /* Generate the center diagonal of the symmetric tri-diagonal matrix, with extra terms 
            =3h0 + 2h1 + (h0**2/h1              */
  
    
    /*       3hn-1 * 2hn-2 * hn-1**2/hn-2         */
 
    
     /* Use the general tri-diagonal solver, find spline value c, results returned in vector c */

    
    /* Set the C vector into the points 
                  = 1 + h1/h0* c0 - h0/h1 * c1              */
 
 
    /* Copy the solution of the tri-diagonal value c into the spline structure */
 
 
    /* Solve for A, B, and D. */
 
}


/***************************************************************************************
 Evaluates a cubic spline at a give point 

 Where: double x         - Point at which splines should be evaluated
        CSplines *plines - Pointer to Spline Structure
 Returns: double - The value of spline at desired point x or NAN if not fount
 Errors:  none
*****************************************************************************************/
double cspline_eval( double x, CSplines* splines){
 
    
	
}


/***************************************************************************************
 Solves the tridiagonal matrix (3 vectors really) into the array x
             Uses:  Ax=B,  LU factorization:  Lz = B, Ux=z
 
 Where: double *p - pointer to the bottom outer vector - part of L
        double *r - pointer to the top other outer vector - part of U
        double *q - pointer to the center vector          - part of U
        double* x - resulting solution vector, x returned, the logical "c"
        double *B - pointer to value matrix - alpha
        int N     - Number of elements
  Returns: nothing
  Errors:  prints an error and exits
*****************************************************************************************/
void tridiagonal(double *p, double *q, double *r, double* x, double *B, int N){
  double *d, *l, *z;  /* Temporary vectors */
  int lcv;        /* Loop counting variable */

  d = malloc(N * sizeof(double));
  z = malloc((N-1) * sizeof(double));
  l = malloc((N-1) * sizeof(double));

  if(NULL == d || NULL == z || NULL == l){
    fprintf(stderr, "Failed malloc: tridiagonal\n");
  }

  /* LU Factorization or Elimination, right from the notes */
  
  d[0] = q[0];  
  l[0] = p[0] / d[0];

  for(lcv = 1; lcv < N-1; lcv++){
    
    d[lcv] = q[lcv] - (l[lcv-1]* r[lcv-1]]);
    l[lcv] = p[lcv] / d[lcv];

  }
  d[N-1] = q[N-1] - (l[N-2]] * r[n-2]]);

  /* Forward substitution: solving for z */
  z[0] = B[0];

  for(lcv = 1; lcv < N; lcv++){
    z[lcv] = B[lcv] - (l[lcv-1] * z[lcv-1]);
  }

  /* Back substitution: solving for x */
  x[N-1] = z[N-1] / d[N-1];
  
  for (lcv = N-2; lcv >= 0; lcv--){
    x[lcv] = (z[lcv] - x[lcv+1]) / d[lcv];
  }

  /* Free the temporary vectors */
  free(d);
  free(z);
  free(l);

  d = NULL;
  z = NULL;
  l = NULL;

}


/***************************************************************************************
 Finds the A, B, D, and X poly values using the following
        aj = yj
        bj = yj+1 - yj      cj+1 + 2cj
            ----------- -  ---------- hj
                hj             3
        cj = passed in from tridiagional solution
        dj = cj+1 - cj
            -----------
                3h
  
 Where: CSplines *Splines - Pointer to Spline Structure, data returned here    
        double *h         - difference vector: e.g. hj = xj+1  -  xj*
        Points *points	  - Pointer to Data Points array                            
 Returns: nothing
 Errors:  none 
*****************************************************************************************/
void polySolve(CSplines *splines, double *h, Points *points){
        /*  aj = yj */
       
        
        /*  b[j] = yj+1 - yj      cj+1 + 2cj
                  ----------- -  ---------- hj
                       hj             3         */
         
        /* d[j] = cj+1 - cj
                -----------
                     3h        */
        
        /* Copy the associated points */
   
}


/***************************************************************************************
 Prints the splines to standard out 
            of the form:  X0 X1 d c b a
 
 Where: CSplines *Splines - Pointer to Spline Structure to print                          
 Returns: nothing
 Errors:  none 
*****************************************************************************************/
void printSplines(CSplines *splines){
    int lcv;  /* Loop counting variable */

    for(lcv = 0; lcv < (splines->N); lcv++){

      /* Temporary fix for the last point where there is no X1 value (out of bounds) */
      if(lcv == splines->N - 1){
        fprintf(stdout, "%g X1 %g %g %g %g\n", splines->X[lcv], splines->d[lcv],    \ 
                splines->c[lcv], splines->b[lcv], splines->a[lcv]);
      }
      else{
        fprintf(stdout, "%g %g %g %g %g %g\n", splines->X[lcv], splines->X[lcv+1],  \
                splines->d[lcv], splines->c[lcv], splines->b[lcv], splines->a[lcv]);
      }

    }
}

/***************************************************************************************
 Allocates space for the splines
 
 Where: CSplines *Splines - Pointer to Spline Structure to allocate    
        int N             - The number of splines required 
 Returns: nothing
 Errors:  prints an error message and exits 
*****************************************************************************************/
void s_alloc(CSplines *splines, int N){
  /* Set the number of splines */
  splines->N = N;

  /* Allocate space for the coefficients and the partition */
  splines->a = malloc(N * sizeof(doulbe));
  splines->b = malloc(N * sizeof(doulbe));
  splines->c = malloc(N * sizeof(doulbe));
  splines->d = malloc(N * sizeof(doulbe));
  splines->X = malloc(N * sizeof(doulbe));  /* Temporary until actual value is determined */

  /* Check for successful allocation */
   if((NULL == a) || (NULL == b) || (NULL == c) || (NULL == d) || (NULL == X)){
      fprintf(stderr, "Failed malloc: s_alloc\n");
   }

}

/***************************************************************************************
 Frees the spline 
 
 Where: CSplines *Splines - Pointer to Spline Structure to free    
 Returns: nothing
 Errors:  none
*****************************************************************************************/
void s_free(CSplines *splines){
  /* Set the size to 0 */
  splines->N = 0;

  /* Free the space for the coefficients and the partition*/
  free(splines->a);
  splines->a = NULL;

  free(splines->b);
  
  free(splines->c);
  splines->c = NULL;
  
  free(splines->d);
  splines->d = NULL;
  
  free(splines->X);
  splines->X = NULL;
  
  /* Set the pointer to NULL in case of attempted future use */
  splines = NULL;
 
}

/***************************************************************************************
 Allocates space to hold the points 
 
 Where: Points *points - Pointer to Points Structure to allocate    
        int N          - The number of splines required 
 Returns: nothing
 Errors:  prints an error message and exits 
*****************************************************************************************/
void p_alloc(Points *points, int N){
 /* typedef struct
  {
   int     N;    /* Number of Elements in array  *
   double *X;    /* Pointer to X data            *
   double *Y;    /* Pointer to Y data            *
   double y0;    /* Derivative of first point *
   double yn;    /* Derivative of last point *
  } Points;*/

   /* Set the number of elements in the array */
   points->N = N;

   /* Allocate space for X and Y data */
   points->X = malloc(N * sizeof(double));
   points->Y = malloc(N * sizeof(double));

   /* Check for successful allocation */
   if((NULL == X) || (NULL == Y)){
      fprintf(stderr, "Failed malloc: p_alloc\n");
   }

   /* Set the derivatives of the first and last points */
   /* Temporarily set to 0.0 */
   points->y0 = 0.0;
   points->yn = 0.0;


}

/***************************************************************************************
 Frees the values in the points structure
 
 Where: Points *points - Pointer to Points Structure to free    
 Returns: nothing
 Errors:  none 
*****************************************************************************************/
void p_free(Points *points){
  /* Set the size to 0 */
  points->N = 0;

  /* Free the X and Y data sets */
  free(points->X);
  points->X = NULL;

  free(points->Y);
  points->Y = NULL;

  /* Set the derivatives to 0.0 */
  points->y0 = 0.0;
  points->yn = 0.0
  
  /* Set the pointer to null in case of attempted future use */
  points = NULL;
}
