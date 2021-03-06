# Applied-Programming-HW8

Piecewise Interpolation with Cubic Splines

Objective: To write a numerical interpolation module in C.  The module will consist of a header file, interp.h,
and a “code file”, called interp.c.  In this module (for now) you will implement functions for cubic spline
interpolation and evaluation for arbitrary sets of data points.

Makefile:
Run the command "make" to compile all the files for the splines.

For the valgrind portion to check for memory leaks, run the command "make valgrind".  All three methods of determining the splines will be run to check for memory leaks in each method.

To test the construction of the splines, run the command "make construct".  The data.txt file will be read in to calculate the splines for each of the three different methods.  The output of the program will be redirected to sparameters?.txt, where ?=1 is the natural method, ?=2 is the clamped method, and ?=3 is the not-a-knot method.

To test the portion of the program to evaluate points using differnt splines, run the command "make evaluate".  All three spline methods will be tested at six different points according to the splines calculated in the respective files sparameters?.txt.  The output of the program will be redirected to the files eresults?.txt, following the same naming pattern as before.

To generate a plot for the splines generated by the two methods natural and not-a-knot, run the command "make plots".  A png file will be generated containing both splines on one plot: splines.png.

To maintain clean directories, run the command "make clean" before recompiling or rerunning any of the previous commands.  This will avoid confusion between versions of files.
