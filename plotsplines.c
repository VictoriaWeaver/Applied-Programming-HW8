/***********************************************************************************
 Purpose : Show how to call gnuplot from C to generate plots (via a pipe)
 Requires: curve.txt (text file name with data for plots)
           gnuplot   (tested with version 4.4 )
           pipes     (Not ANSI C but POSIX compliant; tested under GNU/Linux)
 Side effects: a png figure called splines.png
 Author  : Juan C. Cockburn Nov 2014
 Revised : October 28, 2014
 Warning : popen is not part of standard C; expect warnings if using -ansi !

 To view the png figure use "display" (do not forget to set your X11 terminal first)
 ***************************************************************************/
#include <stdio.h>

int main(void) 
{
/* Declare variables */
  FILE *pipe; /* pipe is a pointer to a a pipe process */

  printf(" ----------------------------------------------------------\n");
  printf(" Example: Draw figures from C using pipes and gnuplot      \n");
  printf(" ----------------------------------------------------------\n");

/* Open pipe to communicate with gnuplot */
  if( (pipe = (FILE *) popen("gnuplot -persist","w")) == NULL ) 
  {
    fprintf(stderr,"Unable to open pipe to gnuplot\n");
    return -1;
  }
    
/* Send gnuplot commands through pipe, note the end f line \n character */
#if 0
  /* gnuplot: send output to X11 terminal with desired font */
  fprintf(pipe,"set terminal x11 font 'Vera.ttf'\n");
#endif
  /* gnuplot: send output to png file with desired font */
  fprintf(pipe,"set terminal png enhanced font 'DejaVuSans.ttf'\n"); 
  fprintf(pipe,"set output 'splines.png' \n"); 

  /* gnuplot: set title, labels, legend  and line styles */
  fprintf(pipe,"set title 'Cubic spline interpolation result '\n");
  fprintf(pipe,"set xlabel 'x'\n");
  fprintf(pipe,"set ylabel 'f(x)'\n");
  fprintf(pipe,"set style data lines\n"); /* draw lines between data pts  */
  fprintf(pipe,"set xrange [-2:5]\n");		/* set x range		  */ 
  /* read data file with (x,y) points */
  fprintf(pipe,"plot 'plotPoints.txt' using 1:2 lt 1 lw 2 t 'cubic spline nat','plotPoints.txt' using 3:4 lt 1 lw 2 t 'cubic spline nak' \n");

/* Close pipe */
  pclose(pipe);

  return 0 ;
}
