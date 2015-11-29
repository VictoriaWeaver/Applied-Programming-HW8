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
  int lcv;        /* Loop counting variable */
  double *h;      /* The difference vector */
  double *alpha;  /* Alpha vector */
  double *p, *q, *r, *c;      /* The tridiagonal vectors */
  int N;
  
  N = splines->N;

  /* Size of h = N-1 */
  h = malloc(N * sizeof(double));

  if(NULL == h){
    fprintf(stderr, "Failed malloc: cspline_natural\n");
    return;
  }


  /* Generate the h (difference) vector: notes: hj = xj+1  -  xj*/
  for(lcv = 0; lcv < N; lcv++){

    h[lcv] = data->X[lcv+1] - data->X[lcv];

  }

	
  /* Find the alpha vector: notes: alphaj = 3((yj+1 - yj)  -  (yj - yj-1)) 
                                            -----------      ------------ , j= 1..N-1
                                                hj            hj -1 */
  alpha = malloc((N-1) * sizeof(double));

  if(NULL == alpha){
    fprintf(stderr, "Failed malloc: cspline_natural\n");
    return;
  }

  for(lcv = 1; lcv < N; lcv++){
    alpha[lcv-1] = 3.0 *(((data->Y[lcv+1] - data->Y[lcv])/(h[lcv])) - ((data->Y[lcv]-data->Y[lcv-1])/h[lcv-1]));
  }



    
  /* Generate the outside symmetric tri-diagonal matrix from h1 to hn-2  */
  p = malloc((N-2) * sizeof(double));
  q = malloc((N-1) * sizeof(double));
  r = malloc((N-2) * sizeof(double));

  if(NULL == p || NULL == q || NULL == r){
    fprintf(stderr, "Failed malloc: cspline_natural\n");
    return;
  }
  
  memcpy(p, &h[1], ((N-2) * sizeof(double)));
  memcpy(r, &h[1], ((N-2) * sizeof(double)));

  /* Generate the center diagonal of the symmetric tri-diagonal matrix 
        2(h0+h1)       0 to n-2 inclusive                                 */
  for(lcv = 0; lcv < N-1; lcv++){
    q[lcv] = 2.0 * (h[lcv] + h[lcv+1]);
  }
  
  c = malloc((N-1) * sizeof(double));

  if(NULL == c){
    fprintf(stderr, "Failed malloc: cspline_natural\n");
    return;
  }


  /* Use the general tri-diagonal solver to find spline value c */
  tridiagonal(p, q, r, c, alpha, N-1);
       
  /* Copy the solution of the tri-diagonal value c into the spline structure */
  memcpy(&(splines->c[1]), c, (N-2)*sizeof(double));

  /* Initial "c" condition, zero curvature at the end points */
  splines->c[0] = 0.0;
  splines->c[N-2] = 0.0;

  /* Solve for A, B, and D. */
  polySolve(splines, h, data);

  /* Free all the temporary vectors */
  free(h);
  free(alpha);
  free(p);
  free(q);
  free(r);
  free(c);

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
  int lcv;  /* Loop counting variable */
  int N;    /* The number of data points */
  double *h, *alpha;  /* The difference and alpha vector */
  double *p, *q, *r, *c;  /* tridiagonal vectors */


  N = (splines->N);

  /* Size of h = size of splines */
  h = malloc((N-1) * sizeof(double));
  

  if(NULL == h){
    fprintf(stderr, "Failed malloc: cspline_clamped\n");
    return;
  }

  /* Generate the h (difference) vector: notes: hj = xj+1  -  xj*/
  for(lcv = 0; lcv < N; lcv++){

    h[lcv] = data->X[lcv+1] - data->X[lcv];

  }
    
	/* Find the alpha vector 
        alpha0 = 3((y1 - y0) - y0') 
                   --------
                        h0                 */
  alpha = malloc((N+1) * sizeof(double));

  if(NULL == alpha){
    fprintf(stderr, "Failed malloc: cspline_clamped\n");
    return;
  }     

  alpha[0] = 3.0 * (((data->Y[1] - data->Y[0]) / h[0]) - data->y0);

    
  /* Find the alpha vector: notes: alphaj = 3((yj+1 - yj)  -  (yj - yj-1)) 
                                              -----------      ------------ , j= 1..N-1
                                                 hj            hj -1 */
  for(lcv = 1; lcv < N; lcv++){
    alpha[lcv] = 3.0 * (((data->Y[lcv+1] - data->Y[lcv]) / h[lcv]) + ((data->Y[lcv] - data->Y[lcv-1])/h[lcv-1]));
  }
    
  /*  alphan = 3(yn' - (yn - yn-1)  )
                         ----------
                           hn-1             */
  alpha[N] = 3.0 * (data->yn - (data->Y[N] - data->Y[N-1])/h[N-1]);

  p = malloc(N * sizeof(double));
  q = malloc((N+1) * sizeof(double));
  r = malloc(N * sizeof(double));
  c = malloc((N+1) * sizeof(double));

  if(NULL == p || NULL == q || NULL == r || NULL == c){
    fprintf(stderr, "Failed malloc: cspline_clamped\n");
    return;
  }

  /* Generate the outside symmetric tri-diagonal matrix */
  memcpy(p, h, (N * sizeof(double)));
  memcpy(r, h, (N * sizeof(double)));
   
  /* Generate the center diagonal of the symmetric tri-diagonal matrix */
  q[0] = 2.0 * h[0];

  for(lcv = 1; lcv < N; lcv++){
    q[lcv] = 2.0 * (h[lcv-1] + h[lcv]);
  }

  q[N-1] = 2 * h[N-1];
    
  /* Use the general tri-diagonal solver to find spline data c */
  tridiagonal(p, q, r, c, alpha, N);
    
  /* Copy the solution of the tri-diagonal value c into the spline structure */
  memcpy(splines->c, c, ((N+1) * sizeof(double)));

  /* Solve for A, B, and D. */
  polySolve(splines, h, data);

  /* Free all the temporary vectors */
  free(h);
  free(alpha);
  free(p);
  free(q);
  free(r);
  free(c);

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
	int lcv;  /* Loop counting variable */
  double *h, *alpha;  /* The difference and alpha vector */
  double *p, *q, *r, *c;  /* tridiagonal vectors */
  int N;      /* # of splines */

  N = splines->N;

  /* Size of h = size of splines */
  h = malloc(N * sizeof(double));

  if(NULL == h){
    fprintf(stderr, "Failed malloc: cspline_nak\n");
    return;
  }

  /* Generate the h (difference) vector: notes: hj = xj+1  -  xj*/
  for(lcv = 0; lcv < N; lcv++){

    h[lcv] = data->X[lcv+1] - data->X[lcv];

  }

	
  /* Find the alpha vector: notes: alphaj = 3((yj+1 - yj)  -  (yj - yj-1)) 
                                              -----------      ------------ , j= 1..N-1
                                                 hj            hj -1 */
  alpha = malloc((N-1) * sizeof(double));

  if(NULL == alpha){
    fprintf(stderr, "Failed malloc: cspline_nak\n");
    return;
  }

  for(lcv = 0; lcv < N-1; lcv++){
    alpha[lcv] = 3.0 * (((data->Y[lcv+1] - data->Y[lcv]) / h[lcv]) + ((data->Y[lcv] - data->Y[lcv-1])/h[lcv-1]));
  }
    
  /* Find the tri-diagonal matrix and solve for c */
  /* Generate the outside symmetric tri-diagonal matrix */
  p = malloc((N-2) * sizeof(double));
  q = malloc((N-1) * sizeof(double));
  r = malloc((N-2) * sizeof(double));
  c = malloc((N-1) * sizeof(double));

  if(NULL == p || NULL == q || NULL == r || NULL == c){
    fprintf(stderr, "Failed malloc: cspline_nak\n");
    return;
  }
  
  memcpy(&p[1], &h[2], (N-3) * sizeof(double));
  memcpy(r, &h[1], (N-3) * sizeof(double));

  /* Generate the extra bottom terms for knk 
         = h2 - hn-1**2/hn-2                 */
  r[N-3] = h[N-2] - ((h[N-1] * h[N-1]) / h[N-2]);
    
  /* Generate the top terms for knk 
         = h1 - h0**2/h1                  */
  p[0] = h[1] - ((h[0] * h[0]) / h[1]);

    
  /* Generate the center diagonal of the symmetric tri-diagonal matrix, with extra terms 
          =3h0 + 2h1 + (h0**2/h1                
           3hn-1 * 2hn-2 * hn-1**2/hn-2         */
  
  q[0] = (3.0 * h[0]) + (2.0 * h[1]) + (h[0] * h[0] / h[1]);

  for(lcv = 1; lcv < N-2; lcv++){
    q[lcv] = 2.0 * (h[lcv] + h[lcv+1]);
  }
  
  q[N-2] = (3.0 * h[N-1]) + (2.0 * h[N-2]) + (h[N-1] * h[N-1] / h[N-2]);    
    
  /* Use the general tri-diagonal solver, find spline value c, results returned in vector c */
  tridiagonal(p ,q, r, c, alpha, N-1);
    
  /* Set the C vector into the points 
                = 1 + h1/h0* c0 - h0/h1 * c1              */
 
 
  /* Copy the solution of the tri-diagonal value c into the spline structure */
  memcpy(splines->c, c, ((N-1) * sizeof(double)));
 
  /* Solve for A, B, and D. */
  polySolve(splines, h, data);

  /* Free all the temporary vectors */
  free(h);
  free(alpha);
  free(p);
  free(q);
  free(r);
  free(c);
 
}


/***************************************************************************************
 Evaluates a cubic spline at a give point 

 Where: double x         - Point at which splines should be evaluated
        CSplines *splines - Pointer to Spline Structure
 Returns: double - The value of spline at desired point x or NAN if not found
 Errors:  none
*****************************************************************************************/
double cspline_eval( double x, CSplines* splines){
  int lcv;  /* Loop counting variable */  
  double minBound;  /* Minimum x-value */
  double value;   /* The value of the evaluated spline */
  
  minBound = splines->X[0];

  if(x < minBound){
    fprintf(stderr, "ERROR: Minimum Bound\n");
    return NAN;
  }

  for(lcv = 0; lcv < (splines->N); lcv++){
    
    if(x >= splines->X[lcv] && x < splines->X[lcv+1]){
      break;
    }

    /* Note does not check for the last point, so the last spline will never be evaluated: NEEDS FIX */
    if(lcv == (splines->N)-1){
      fprintf(stderr, "ERROR: Maximum Bound\n");
      return NAN;
    }

  }

  value = (splines->a[lcv]) + (splines->b[lcv] * (x-splines->X[lcv]))
          + (splines->c[lcv] * ((x-splines->X[lcv])*(x-splines->X[lcv]))) 
          + (splines->d[lcv] * ((x-splines->X[lcv])*(x-splines->X[lcv])*(x-splines->X[lcv])));

  return value;
	
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
  double *d, *u, *l, *z;  /* Temporary vectors */
  int lcv;        /* Loop counting variable */

  d = malloc(N * sizeof(double));
  u = malloc((N-1) * sizeof(double));
  z = malloc(N * sizeof(double));
  l = malloc((N-1) * sizeof(double));

  if(NULL == d || NULL == u || NULL == z || NULL == l){
    fprintf(stderr, "Failed malloc: tridiagonal\n");
    return;
  }

  /* LU Factorization or Elimination, right from the notes */
  
  d[0] = q[0];
  u[0] = r[0];  
  l[0] = p[0] / d[0];

  for(lcv = 1; lcv < N-1; lcv++){
    
    d[lcv] = q[lcv] - (l[lcv-1]* r[lcv-1]);
    u[lcv] = r[lcv];
    l[lcv] = p[lcv] / d[lcv];

  }

  d[N-1] = q[N-1] - (l[N-2] * u[N-2]);

  /* Forward substitution: solving for z */
  z[0] = B[0];

  for(lcv = 1; lcv < N; lcv++){
    z[lcv] = B[lcv] - (l[lcv-1] * z[lcv-1]);
  }

  /* Back substitution: solving for x */
  x[N-1] = z[N-1] / d[N-1];
  
  for (lcv = N-2; lcv >= 0; lcv--){
    x[lcv] = (z[lcv] - (u[lcv] * x[lcv+1])) / d[lcv];
  }


  /* Free the temporary vectors */
  free(d);
  free(z);
  free(l);
  free(u);

  d = NULL;
  z = NULL;
  l = NULL;
  u = NULL;

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
  int lcv; /* Loop counting variable */

  for(lcv = 0; lcv < (splines->N)-1; lcv++){
    /*  aj = yj */
    splines->a[lcv] = points->Y[lcv];
       
    /*  b[j] = yj+1 - yj      cj+1 + 2cj
            ----------- -  ---------- hj
                 hj             3         */
    splines->b[lcv] = ((points->Y[lcv+1] - points->Y[lcv])/h[lcv]) - ((splines->c[lcv+1] + (2*splines->c[lcv])) * h[lcv] / 3.0);

    /* d[j] = cj+1 - cj
            -----------
                3hj        */
    splines->d[lcv] = (splines->c[lcv+1] - splines->c[lcv]) / (3.0 * h[lcv]);
  }
    
        
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
      fprintf(stdout, "%f %f %f %f %f %f\n", splines->X[lcv], splines->X[lcv+1],  
                splines->d[lcv], splines->c[lcv], splines->b[lcv], splines->a[lcv]);
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
  splines->a = malloc(N * sizeof(double));
  splines->b = malloc(N * sizeof(double));
  splines->c = malloc((N+1) * sizeof(double));
  splines->d = malloc(N * sizeof(double));
  splines->X = malloc((N+1) * sizeof(double));  /* Temporary until actual value is determined */

  /* Check for successful allocation */
   if((NULL == splines->a) || (NULL == splines->b) || (NULL == splines->c) || (NULL == splines->d) || (NULL == splines->X)){
      fprintf(stderr, "Failed malloc: s_alloc\n");
      return;
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
        int N          - The number of points required 
 Returns: nothing
 Errors:  prints an error message and exits 
*****************************************************************************************/
void p_alloc(Points *points, int N){
   /* Set the number of elements in the array */
   points->N = N;

   /* Allocate space for X and Y data */
   points->X = malloc(N * sizeof(double));
   points->Y = malloc(N * sizeof(double));

   /* Check for successful allocation */
   if((NULL == points->X) || (NULL == points->Y)){
      fprintf(stderr, "Failed malloc: p_alloc\n");
      return;
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
  points->yn = 0.0;
  
  /* Set the pointer to null in case of attempted future use */
  points = NULL;
}
