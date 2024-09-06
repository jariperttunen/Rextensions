#include <stdlib.h>
#include <string.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <Rembedded.h>

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

  source("rlist.r");
  SEXP ls_call;
  //The lang2 sets up a function with one parameter.
  //There are lang1, lang2, lang3, lang4, lang5 and lang6 for functions with 0 up to 5 arguments
  ls_call=PROTECT(lang1(install("rlist")));
  // Execute the function
   int errorOccurred;
   SEXP ls_val = R_tryEval(ls_call, R_GlobalEnv, &errorOccurred);
   if (isList(ls_val)){
     printf("Returned a list\n");
   }
   else if (isVector(ls_val)){
     printf("Return value was  a vector\n");
   }
   else{
     printf("Return value type unknown\n");
   }
   double ls_length = XLENGTH(ls_val);
   printf("Vector length %f0.0\n",ls_length);
   //Although vector type is true, VECTOR_ELT can only be applied to a list.
   //So ls_val is a list as a return value.
   SEXP ls_m = VECTOR_ELT(ls_val,0);
   SEXP dims = GET_DIM(ls_m);
   if (isVector(dims)){
     printf("Matrix dimensions\n");
     printf("Length %td\n",XLENGTH(dims));
     long r = INTEGER(dims)[0];
     long c = INTEGER(dims)[1];
     printf("Rows %ld Columns %ld\n",r,c); 
   }
   double ls_length1 = XLENGTH(ls_m);
   printf("Vector length %f0.0\n",ls_length1);
   UNPROTECT(1);
}
