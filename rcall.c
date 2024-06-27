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

  printf("1. Vector Exercise\n");
  printf("-------------------\n");
  // Allocate an R vector and copy the C array into it.
  SEXP arg;
  arg = PROTECT(allocVector(REALSXP, alen));
  memcpy(REAL(arg), a, alen * sizeof(double));

  //Setup the call to the R function 
  SEXP add1_call;
  add1_call=PROTECT(lang2(install("add1"), arg));
 
   // Execute the function
   int errorOccurred;
   SEXP retval = R_tryEval(add1_call, R_GlobalEnv, &errorOccurred);

   if (!errorOccurred){
     double *val = REAL(retval);
     
     printf("C received from R: ");
     for (int i = 0; i < LENGTH(retval); i++){
       printf("%0.0f ", val[i]);
     }
     printf("\n\n");
   }

   // Unprotect add1_call and arg, i.e. release for carbage collection 
   UNPROTECT(2);

   //---------------------------------
   printf("2. Matrix Exercise\n");
   printf("------------------\n");
   printf("Note the C matrix in row first order,\n");
   printf("while R uses column first order.\n\n");
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

   //Allocate R matrix, copy the C matrix to it
   SEXP r_arg = PROTECT(allocMatrix(REALSXP, x, y));
   double* crm = REAL(r_arg);
   for (int i=0; i < x; i++){
     for (int j=0; j < y; j++){
       //Note we have the vector view to r_arg via crm as double*.
       //We must manually index the crm as matrix.
       //Note we explicitly arrange numbers in column first order
       crm[i+x*j]=m[i][j];
     }
   }

   printf("C matrix in memory\n");
   printf("(row first order):      ");
   double* v1=&m[0][0];
   for (int i=0; i < x*y; i++){
     printf("%0.0f ", v1[i]);
   }
   printf("\n");
   printf("C sending data to R\n");
   printf("(column first order):   ");  
   for (int i=0; i < x*y; i++){
     printf("%0.0f ", crm[i]);
   }
   printf("\n");
    
   //Setup the call to the R function 
   SEXP addm_call;
   addm_call=PROTECT(lang2(install("addm"), r_arg));
   
   // Execute the function
   int errorOccurred1;
   SEXP retval1 = R_tryEval(addm_call, R_GlobalEnv, &errorOccurred1);

   if (!errorOccurred1){
     double *m_val = REAL(retval1);
     
     printf("C received from R:\n");
     printf("Matrix in memory : ");
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
   // Release R environment
   Rf_endEmbeddedR(0);

   return 0;
}
