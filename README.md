# R Extensions

Four examples demonstrate techniques to call R functions from C
with *C libraries for R API*[^api], a.k.a. *R Extensions*. They also highlight row-major (row-first) 
vs. column-major (column-first) matrix storage layout in C and R respectively.

The first example creates one vector in C, passes on the vector data to R function that
makes vector addition in R style and returns the result vector back to C.

The second example creates one matrix in C, sends the matrix data as *column-first* to R function
that performs matrix addition in R style and returns the result matrix back to C. 

The third example uses the C matrix from the second example, sends the matrix data 
as *row-first* to R function that creates R matrix filled by rows to acquire the same view 
with the original C matrix for correct indexing in R.

The fourth example creates a 3D matrix in C, rearranges the default row first layout in C 
to column first into a *vector* and passes the vector to R function. The R function receives the vector 
and creates 3D matrix with `array` type. After that matrix addition in R style is executed and 
the modified 3D matrix is returned to C. The C program sees the returned 3D matrix as a *vector* and
prints out the vector content in contiguous memory first and then indexing the content as column first.
The column first indexing allows the vector content to be inserted in a 3D matrix in C as row first. 

Although in the examples the C code snippets organise the matrices row or columns first the R `matrix` and
`array` types have option to read data row or column first. But when passing the data one must be aware 
of the storage layout ordering. The datatype for the vectors and the matrices used is *double*. 
See *rcall.c* and *add.R* for details.

Note that even though in R Extensions C programs are compiled the calls to R functions are nevertheless
always  executed by the R interpreter implemented in and accessible from the C libraries API for R. 

## Usage

The R runtime system requires R_HOME environment variable[^rhome]. 
In macOS type (Terminal command line):

	export R_HOME=/Library/Frameworks/R.framework/Resources
	
R_HOME denotes the R installation location. To compile the examples with C libraries API for R:

	cc -o rcall -g -I$R_HOME/include -L$R_HOME/lib -lR -lRblas rcall.c
	
To run the examples (make sure R_HOME is set):
	
	./rcall

Linux is similar, for example:

	export R_HOME=/usr/lib64/R/
 	cc -o rcall -g -I/usr/include/R -L$R_HOME/lib -lR -lRblas rcall.c
	./rcall

## The SEXP data structure
R  Extensions  provides  SEXP data  structure[^sexp]  that  abstracts
all built-in datatypes  in  R, building  blocks  of  R objects  (arithmetic  types,
vectors, matrices,  lists and  the like).  For  the R  Extensions user
SEXP  models an  R  variable  bound to  a  value. *It is the SEXP variables
that are used in information exchange between C and R*. The  implementation
details of  SEXP are  hidden from  the user but  the internals  can be
queried with the API for SEXP. A common use case is to access the R object data.
 
## Litterature

1. [How to call R function from C]( https://pabercrombie.com/wordpress/2014/05/how-to-call-an-r-function-from-c/)
  - Based on this example. Extended the example to *double* datatype and for matrices.
  
2. [Writing R Extensions](https://cran.r-project.org/doc/manuals/R-exts.html)
  - *Must read! Especially the chapter 5.9 Handling R objects in C*.
  - Official guide to R Extensions including documentation for 
    functions and  datatypes used in the R Extensions examples.
3. [R Internals](https://cran.r-project.org/doc/manuals/r-devel/R-ints.html)
  - Technical document of the implementation of R, meant for the R development team.
  - Chapter 1.1 is devoted to the SEXP data structure.
    
[^api]: **A**pplication **P**rogramming **I**nterface.
[^rhome]: Set R_HOME permanently in the shell (zsh,bash etc.) configuration file.
[^sexp]: To be precise SEXP  is a  C pointer to a SEXPREC structure but the API is
         for SEXP.
