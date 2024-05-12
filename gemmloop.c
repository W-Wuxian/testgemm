#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TYPE
#define TYPE float
#endif

#define max(a, b) (((a) < (b)) ? (b) : (a))
#define min(a, b) (((a) < (b)) ? (a) : (b))

int GetDim(long *m, long *n, long *k, int argc, char **argv) {
  int ierr = EXIT_SUCCESS;
  char *endPtr = NULL;
  if (argc != 4) {
    printf("Trying to Compute C = A*B + C\n");
    printf("Please rerun with:/t./exec m n k\n");
    printf("Where A is mxk; B is kxn; C is mxk\n");
    exit(ierr);
  } else {
    *m = strtol(argv[1], &endPtr, 10);
    *n = strtol(argv[2], &endPtr, 10);
    *k = strtol(argv[3], &endPtr, 10);
    printf("m = %ld\tn = %ld\tk = %ld\n", *m, *n, *k);
  }
  return ierr;
}

int FillMat(long nrow, long ncol, TYPE val, TYPE *Mat) {
  int ierr = EXIT_SUCCESS;
  if (!Mat) {
    return EXIT_FAILURE;
  }
  size_t size = nrow * ncol;
  for (size_t i = 0; i < size; i++) {
    Mat[i] = val;
  }
  return ierr;
}

int ShowMat(long nrow, long nr1, long nr2, long nc1, long nc2, TYPE *Mat) {
  int ierr = EXIT_SUCCESS;
  if (!Mat) {
    return EXIT_FAILURE;
  }
  for (long i = nr1; i < nr2; i++) {
    for (long j = nc1; j < nc2; j++) {
      // printf("%ld\t", i + j * nrow);
      printf("%lf\t", Mat[i + j * nrow]);
    }
    printf("\n");
  }
  return ierr;
}

int main(int argc, char **argv) {
  int ierr = EXIT_SUCCESS;

  TYPE *A = NULL;
  TYPE *B = NULL;
  TYPE *C = NULL;

  double Mem = 0.;
  const TYPE alpha = 1;
  const TYPE beta = 1;

  long m = 0, n = 0, k = 0;
  long lda = 0, ldb = 0, ldc = 0;
  size_t Asize = m * k;
  size_t Bsize = k * n;
  size_t Csize = m * n;

  ierr = GetDim(&m, &n, &k, argc, argv);
  printf("m = %ld\tn = %ld\tk = %ld\n", m, n, k);

  A = (TYPE *)calloc(Asize, sizeof(TYPE));
  B = (TYPE *)calloc(Bsize, sizeof(TYPE));
  C = (TYPE *)calloc(Csize, sizeof(TYPE));

  ierr = FillMat(m, k, 1., A);
  ierr = FillMat(m, k, 2., B);
  ierr = FillMat(m, k, 3., C);

  ierr = ShowMat(m, max(0, 2), min(5, m), max(0, 2), min(5, k), A);

  free(A);
  free(B);
  free(C);
  A = NULL;
  B = NULL;
  C = NULL;

  return ierr;
}