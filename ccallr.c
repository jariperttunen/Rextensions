#include <stdlib.h>
#include <string.h>
#include <Rinternals.h>
#include <Rembedded.h>

void source(const char *name)
{
  SEXP e;
 
  PROTECT(e = lang2(install("source"), mkString(name)));
  R_tryEval(e, R_GlobalEnv, NULL);
  UNPROTECT(1);
}

double* callprebas(double site_info[], int n_model_trees,double init_var[][])
{
  int site_info_length=12;
  int init_var_cols = 7;
   // Intialize the embedded R environment.
  int r_argc = 2;
  char *r_argv[] = { "R", "--silent" };
  Rf_initEmbeddedR(r_argc, r_argv);

  // Allocate an R vector corresponding to site_info and copy the site_info (C array) into it.
  //Length of the site_info vector
  
  SEXP arg_v = PROTECT(allocVector(REALSXP, site_info_length));
  //Note SEXP internals are hidden but the function REAL
  //provides access to the vector data
  memcpy(REAL(arg), site_info, site_info_length*sizeof(double));

  //Allocate an R matrix corresponding to initVar copy the initVar (C matrix into it)
  SEXP arg_m = PROTECT(allocMatrix(REALSXP, n_model_trees, init_var_cols));
  double* c_arg_m = REAL(r_arg)
  for (int i=0; i < n_model_trees; i++){
    for (int j=0; j < init_var_cols; j++){
      //REAL provides access to r_arg matrix data as double* vector crm.
      //We must explicitely index the crm vector as matrix
      //using column first order. Note that the indexing can be expanded
      //to N-dimensional matrix (https://en.wikipedia.org/wiki/Row-_and_column-major_order)
      c_arg_m[i+x*j]=initVar[i][j];
    }
  }

  
