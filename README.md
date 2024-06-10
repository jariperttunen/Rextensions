# R extensions
Demonstrating calling R functions from C. Two examples are available,
one for vectors and one for matrices.

The two examples create one vector and one matrix respectively as data, 
pass the data to R functions that make vector and matrix addition 
in R style and return the results to C. The datatype for the vector 
and the matrix used is *double*.

## Usage

To set-up R environment (macOS Terminal command line):

	export R_HOME=/Library/Frameworks/R.framework/Resources
	export LD_LIBRARY_PATH=/Library/Frameworks/R.framework/Resources/lib
	
To compile the excercise:

	cc -o rcall -g -I$R_HOME/include -L$R_HOME/lib -lR -lRblas rcall.c
	
To run the exercise:
	
	./rcall

The set-up and compilation is for macOS. Linux is similar, for example:

	export R_HOME=/usr/lib64/R/
	export LD_LIBRAY_PATH=/usr/lib64/R/lib
 	cc -o rcall -g -I/usr/include/R -L$R_HOME/lib -lR -lRblas rcall.c
	./rcall
 
## Litterature

1. [How to call R function from C]( https://pabercrombie.com/wordpress/2014/05/how-to-call-an-r-function-from-c/)
  - Based on this example. Extended the example to *double* datatype and for matrices.
  
2. [Writing R exensions](https://cran.r-project.org/doc/manuals/R-exts.html#Handling-R-objects-in-C)
  - Must read! Official guide to R extensions including required 
    functions and  datatypes used in the exercise.
