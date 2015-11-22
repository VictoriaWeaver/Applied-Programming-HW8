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
        double *q - pointer to the top other outer vector - part of U
        double *r - pointer to the center vector          - part of U
        double* x - resulting solution vector, x returned, the logical "c"
        double *B - pointer to value matrix - alpha
        int N     - Number of elements
  Returns: nothing
  Errors:  prints an error and exits
*****************************************************************************************/
void tridiagonal(double *p, double *q, double *r, double* x, double *B, int N){
 
    
    /* LU Factorization or Elimination, right from the notes */
 
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
  
}

/***************************************************************************************
 Allocates space for the splines
 
 Where: CSplines *Splines - Pointer to Spline Structure to allocate    
        int N             - The number of splines required 
 Returns: nothing
 Errors:  prints an error message and exits 
*****************************************************************************************/
void s_alloc(CSplines *splines, int N){

}

/***************************************************************************************
 Frees the spline 
 
 Where: CSplines *Splines - Pointer to Spline Structure to free    
 Returns: nothing
 Errors:  none
*****************************************************************************************/
void s_free(CSplines *splines){
 
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
  free(points->Y);
  
  /* Set the derivatives to 0.0 */
  points->y0 = 0.0;
  points->yn = 0.0
  
  /* Set the pointer to null in case of attempted future use */
  points = NULL;
}
