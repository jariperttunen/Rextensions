# R extensions
Three examples demonstrate techniques to call R functions from C with R's C library API. 
They also highlight row-major (row-first) vs. column-major (column-first) matrix storage organization
in C and R respectively.

The first example creates one vector in C, passes on the vector data to R function that
makes vector addition in R style and returns the result vector back to C.

The second example creates one matrix in C, sends the matrix data as column-first to R function
that performs matrix addition in R style and returns the result matrix back to C. 

The third example creates one matrix in C, sends the matrix data as row-first to R function
that creates R matrix filled by rows to acquire the same view with the original C matrix
for correct indexing in R.

The datatype for the vector and the matrices used is *double*. 

## Usage

The R runtime system requires R_HOME environment variable. 
In macOS type (Terminal command line):

	export R_HOME=/Library/Frameworks/R.framework/Resources
	
R_HOME denotes the R installation location. To compile the exercise:

	cc -o rcall -g -I$R_HOME/include -L$R_HOME/lib -lR -lRblas rcall.c
	
To run the exercise:
	
	./rcall

The series of steps in Linux are similar, for example:

	export R_HOME=/usr/lib64/R/
 	cc -o rcall -g -I/usr/include/R -L$R_HOME/lib -lR -lRblas rcall.c
	./rcall

See *rcall.c* and *add.R* for details.

## Litterature

1. [How to call R function from C]( https://pabercrombie.com/wordpress/2014/05/how-to-call-an-r-function-from-c/)
  - Based on this example. Extended the example to *double* datatype and for matrices.
  
2. [Writing R extensions](https://cran.r-project.org/doc/manuals/R-exts.html)
  - *Must read, especially the chapter 5.9 Handling R objects in C*!
  - Official guide to R extensions including required functions and  datatypes used in this *Rextensions* exercise.
