#include <stdlib.h>
#include <Rinternals.h>
#include <Rembedded.h>
#include <string.h>
/**
* Invokes the R command source(rfile), e.g. source("add.R")
*/
void source(const char *name)
{
  SEXP e;
 
  PROTECT(e = lang2(install("source"), mkString(name)));
  R_tryEval(e, R_GlobalEnv, NULL);
  UNPROTECT(1);
}

int main()
{
  // Intialize the embedded R environment.
  int r_argc = 2;
  char *r_argv[] = { "R", "--silent" };
  Rf_initEmbeddedR(r_argc, r_argv);

  
  //Create the C array
  double a[] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  int alen = 5;

  // Load the R function (source function defined above)
  source("add.R");

  printf("1. Vector exercise\n");
  printf("-------------------\n");
  // Allocate an R vector and copy the C array into it.
  SEXP arg;
  arg = PROTECT(allocVector(REALSXP, alen));
  //Note SEXP internals are hidden but the function REAL
  //provides access to the vector data
  memcpy(REAL(arg), a, alen * sizeof(double));
  printf("1. In C program\n");
  printf("C sending vector to R: ");
  for (int i=0; i<alen; i++){
    printf("%0.0f ",a[i]);
  }
  printf("\n\n");
  //Setup the call to the R function 
  SEXP add1_call;
  //The lang2 sets up a function with one parameter (lang2: the function with one parameter)
  //There are lang1, lang2, lang3, lang4, lang5 and lang6 for functions with 0 up to 5 arguments
  add1_call=PROTECT(lang2(install("add1"), arg));
 
   // Execute the function
   int errorOccurred;
   SEXP retval = R_tryEval(add1_call, R_GlobalEnv, &errorOccurred);

   if (!errorOccurred){
     double *val = REAL(retval);
     printf("3. In C program\n");
     printf("C received vector from R: ");
     for (int i = 0; i < LENGTH(retval); i++){
       printf("%0.0f ", val[i]);
     }
     printf("\n\n");
   }

   // Unprotect add1_call and arg, i.e. release for carbage collection 
   UNPROTECT(2);

   //----------------------------------
   printf("2. Matrix exercise, send column first data from C\n");
   printf("-------------------------------------------------\n");
   printf("Note the C matrix is in row first order,\n");
   printf("while R uses column first order.\n");
   //Create the C matrix
   const int x=5,y=6;
   double m[x][y];
   double num=1;
   for (int i=0; i < x; i++){
     for (int j=0; j < y; j++){
       m[i][j]=num;
       num++;
     }
   }
   printf("1. In C program\n");
   printf("C matrix\n");
   for (int i=0; i < x; i++){
     for (int j=0; j < y; j++){
       printf("%0.0f ", m[i][j]);
     }
     printf("\n");
   }
   //Allocate R matrix, copy the C matrix to it
   SEXP r_arg = PROTECT(allocMatrix(REALSXP, x, y));
   double* crm = REAL(r_arg);
   for (int i=0; i < x; i++){
     for (int j=0; j < y; j++){
       //REAL provides access to r_arg matrix data as double* vector crm.
       //We must explicitely index the crm vector as matrix
       //using column first order. Note that the indexing can be expanded
       //to N-dimensional matrix (https://en.wikipedia.org/wiki/Row-_and_column-major_order)
       crm[i+x*j]=m[i][j];
     }
   }

   printf("C matrix in contiguous memory\n");
   printf("(row first order):      ");
   double* v1=&m[0][0];
   for (int i=0; i < x*y; i++){
     printf("%0.0f ", v1[i]);
   }
   printf("\n");
   printf("C sending matrix to R\n");
   printf("(column first order):   ");  
   for (int i=0; i < x*y; i++){
     printf("%0.0f ", crm[i]);
   }
   printf("\n\n");
    
   //Setup the call to the R function 
   SEXP addm_call;
   addm_call=PROTECT(lang2(install("addm"), r_arg));
   
   // Execute the function
   int errorOccurred1;
   SEXP retval1 = R_tryEval(addm_call, R_GlobalEnv, &errorOccurred1);

   if (!errorOccurred1){
     double *m_val = REAL(retval1);
     printf("3. In C program\n");
     printf("C received matrix from R:\n");
     printf("Matrix in contiguous memory : ");
     for (int i=0; i < x*y; i++){
       printf("%0.0f ", crm[i]);
     }
     printf("\n");
     printf("Indexing matrix in column first order:\n");
     for (int i = 0; i < x; i++){
       for (int j = 0; j < y; j++){
	 //Note that we are indexing explicitely in column first order
	 printf("%0.0f ", m_val[i+x*j]);
       }
       printf("\n");
     }
     printf("\n");
   }

   //Realease for carbage collection
   UNPROTECT(2);

   printf("3. Matrix exercise,  match row-first data from C in R\n");
   printf("-----------------------------------------------------\n");
   printf("1. In C program\n");
   printf("C matrix\n");
   for (int i=0; i < x; i++){
     for (int j=0; j < y; j++){
       printf("%0.0f ", m[i][j]);
     }
     printf("\n");
   }
   //Allocate R matrix, copy the C matrix to it
   SEXP r_arg2 = PROTECT(allocMatrix(REALSXP, x, y));
   double* crm2 = REAL(r_arg2);
   for (int i=0; i < x; i++){
     for (int j=0; j < y; j++){
       //Note we have the view to r_arg2 data via crm2 as double* vector.
       //We index the crm2 vector explicitely as matrix, this time
       //arranging numbers in row first order. Note that the indexing can be expanded
       //to N-dimensional matrix (https://en.wikipedia.org/wiki/Row-_and_column-major_order)
       crm2[i*y+j]=m[i][j];
     }
   }
   printf("C sending matrix to R\n");
   printf("(row first order):   ");  
   for (int i=0; i < x*y; i++){
     printf("%0.0f ", crm2[i]);
   }
   printf("\n\n");

   //Setup the call to the R function 
   SEXP mrowfirst_call;
   mrowfirst_call=PROTECT(lang2(install("mrowfirst"), r_arg2));
   
   // Execute the function
   int errorOccurred2;
   R_tryEval(mrowfirst_call, R_GlobalEnv, &errorOccurred2);

   //Realease for carbage collection
   UNPROTECT(2);
   printf("\n");
   printf("4. 3D matrix exercise\n");
   printf("--------------------------\n");
   const int n=3;
   const int xdim=5;
   const int ydim=6;
   double m3[n][xdim][ydim];
   num=1.0;
   for (int i=0;i<n;i++){
     for (int j=0;j<xdim;j++){
       for (int k=0;k<ydim;k++){
	 m3[i][j][k]=num++;
       }
     }
   }
   printf("1. In C program\n");
   printf("Create 3D matrix\n");
   for (int i=0;i<n;i++){
     for (int j=0;j<xdim;j++){
       for (int k=0;k<ydim;k++){
	 printf("%0.0f ",m3[i][j][k]);
       }
       printf("\n");
     }
     printf("\n");
   }
   printf("3D matrix in contiguous memory\n");
   double *v3 = malloc(n*xdim*ydim*sizeof(double));
   v3=&m3[0][0][0];
   for (int i=0; i< n*xdim*ydim;i++){
     printf("%0.0f ", v3[i]);
   }
   printf("\n\n");
   // Allocate an R vector and copy the C array into it.
   SEXP r3_arg;
   int m3size = n*xdim*ydim;
   r3_arg = PROTECT(allocVector(REALSXP, m3size));
   double* cr3 = REAL(r3_arg);
   // Copy column first to R vector
   printf("Create vector in column first order in contiguous memory for R\n");
   for (int i=0;i<n;i++){
     for (int j=0;j<xdim;j++){
       for (int k=0;k<ydim;k++){
	 //This is how R sees 3D vector column first
	 cr3[i + j*n+k*n*xdim]=m3[i][j][k];
       }
     }
   }
   for (int i=0; i<n*xdim*ydim; i++){
     printf("%0.0f ", cr3[i]);
   }
   printf("\n\n");
   //Setup the call to the R function 
   SEXP m3d_call;
   m3d_call=PROTECT(lang2(install("matrix3d"), r3_arg));
   // Execute the function
   int errorOccurred4;
   R_tryEval(m3d_call, R_GlobalEnv, &errorOccurred4);
   UNPROTECT(2);
   printf("\nDone\n");
   // Release R environment
   Rf_endEmbeddedR(0);
 
   return 0;
}
