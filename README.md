# R extensions
Three examples demonstrate techniques to call R functions from C
with R's C library API, a.k.a. *R extensions*. They also highlight row-major (row-first) 
vs. column-major (column-first) matrix storage layout in C and R respectively.

The first example creates one vector in C, passes on the vector data to R function that
makes vector addition in R style and returns the result vector back to C.

The second example creates one matrix in C, sends the matrix data as *column-first* to R function
that performs matrix addition in R style and returns the result matrix back to C. 

The third example uses the C matrix from the second example, sends the matrix data 
as *row-first* to R function that creates R matrix filled by rows to acquire the same view 
with the original C matrix for correct indexing in R.

The datatype for the vector and the matrices used is *double*. See *rcall.c* and *add.R* for details.

Note that albeit the C prgram *rcall.c* is compiled the calls to R functions in R extension always 
proceed via R interpreter. 

## Usage

The R runtime system requires R_HOME environment variable. 
In macOS type (Terminal command line):

	export R_HOME=/Library/Frameworks/R.framework/Resources
	
R_HOME denotes the R installation location. To compile the examples:

	cc -o rcall -g -I$R_HOME/include -L$R_HOME/lib -lR -lRblas rcall.c
	
To run the examples:
	
	./rcall

Linux is similar, for example:

	export R_HOME=/usr/lib64/R/
 	cc -o rcall -g -I/usr/include/R -L$R_HOME/lib -lR -lRblas rcall.c
	./rcall

## Litterature

1. [How to call R function from C]( https://pabercrombie.com/wordpress/2014/05/how-to-call-an-r-function-from-c/)
  - Based on this example. Extended the example to *double* datatype and for matrices.
  
2. [Writing R extensions](https://cran.r-project.org/doc/manuals/R-exts.html)
  - *Must read! Especially the chapter 5.9 Handling R objects in C*.
  - Official guide to R extensions including required functions and  datatypes used in these *Rextensions* examples.
