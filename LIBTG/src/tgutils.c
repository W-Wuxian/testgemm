#include "include/datatype.h"

void TGFill(tg_int_t pos, tg_scalar_t filler, tg_scalar_t *scalar) {
  scalar[pos] = filler;
}
void TGShow(tg_int_t pos, tg_scalar_t *scalar) {
  printf("%f ", (tg_scalar_t)scalar[pos]);
}

void TGAlloc(tg_mat_t *mat) {
  if (mat->val == NULL) {
    size_t valsize = (size_t)mat->ldnr * (size_t)mat->ldnc;
    mat->val = calloc(valsize, tg_size_of(mat->coeftype));
  }
}

void TGExit(tg_mat_t *mat) {
  if (mat->val != NULL) {
    free(mat->val);
    mat->val = NULL;
  }
}

int TGFillMat(tg_scalar_t val, tg_mat_t *mat) {
  int ierr = EXIT_SUCCESS;
  if (!mat) {
    return EXIT_FAILURE;
    if (!mat->val) {
      return EXIT_FAILURE;
    }
  }
  size_t size = mat->ldnr * mat->ldnc;
  for (size_t i = 0; i < size; i++) {
    TGFill(i, val, mat->val);
  }
  return ierr;
}

int TGFillMat2(tg_mat_t *mat) {
  int ierr = EXIT_SUCCESS;

  size_t i = 0, j = 0, offset = 0;
  size_t imax = (size_t)mat->ldnr;
  size_t jmax = (size_t)mat->ldnc;
  if (!mat) {
    return EXIT_FAILURE;
    if (!mat->val) {
      return EXIT_FAILURE;
    }
  }
  if (mat->rowcol_order == TGRowMajor) {
    offset = (size_t)mat->ldnc;
    printf("\toffset=%zu\n", offset);
    for (i = 0; i < imax; i++) {
      size_t k = offset * i;
      for (j = 0; j < jmax; j++) {
        printf("\ti=%zu\tj=%zu\tl=%zu\n", i, j, j + k);
        TGFill(j + k, (tg_scalar_t)(j + k), (tg_scalar_t *)mat->val);
      }
    }
  } else if (mat->rowcol_order == TGColMajor) {
    offset = mat->ldnr;
    printf("\toffset=%zu\n", offset);
    for (j = 0; j < jmax; j++) {
      size_t k = offset * j;
      for (i = 0; i < imax; i++) {
        printf("\tj=%zu\ti=%zu\tl=%zu\n", j, i, i + k);
        TGFill(i + k, (tg_scalar_t)(i + k), (tg_scalar_t *)mat->val);
      }
    }
  }
  return ierr;
}

int TGShowMat(tg_rectrange_t range, tg_mat_t *mat) {
  int ierr = EXIT_SUCCESS;
  size_t i = 0, j = 0, offset = 0;
  tg_int_t imin = range.nr1;
  tg_int_t jmin = range.nc1;
  tg_int_t imax = range.nr2;
  tg_int_t jmax = range.nc2;
  printf("RANGE\n");
  printf("%zu\t%zu\t%zu\t%zu\n", range.nr1, range.nr2, range.nc1, range.nc2);
  printf("%zu\t%zu\t%zu\t%zu\n", imin, imax, jmin, jmax);
  if (!mat) {
    return EXIT_FAILURE;
    if (!mat->val) {
      return EXIT_FAILURE;
    }
  }
  if (mat->rowcol_order == TGRowMajor) {
    offset = mat->ldnc;
    for (i = imin; i < imax; i++) {
      size_t k = offset * i;
      for (j = jmin; j < jmax; j++) {
        TGShow(j + k, (tg_scalar_t *)mat->val);
      }
      printf("\n");
    }
  } else if (mat->rowcol_order == TGColMajor) {
    offset = mat->ldnr;
    for (j = jmin; j < jmax; j++) {
      size_t k = offset * j;
      for (i = imin; i < imax; i++) {
        TGShow(i + k, (tg_scalar_t *)mat->val);
      }
      printf("\n");
    }
  }
  return ierr;
}

int FillMat(tg_int_t nrow, tg_int_t ncol, tg_scalar_t val, tg_scalar_t *Mat) {
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

int ShowMat(tg_int_t nrow, tg_int_t nr1, tg_int_t nr2, tg_int_t nc1,
            tg_int_t nc2, TYPE *Mat) {
  int ierr = EXIT_SUCCESS;
  tg_int_t i = 0;
  tg_int_t j = 0;
  if (!Mat) {
    return EXIT_FAILURE;
  }
  for (i = nr1; i < nr2; i++) {
    for (j = nc1; j < nc2; j++) {
      printf("%lf\t", Mat[i + j * nrow]);
    }
    printf("\n");
  }
  return ierr;
}

int GetDim(tg_int_t *m, tg_int_t *n, tg_int_t *k, tg_int_t *lda, tg_int_t *ldb,
           tg_int_t *ldc, int argc, char **argv) {
  int ierr = EXIT_SUCCESS;
  char *endPtr = NULL;
  if (argc != 7) {
    printf("Trying to Compute C = A*B + C\n");
    printf("Please rerun with:/t./exec m n k lda ldb ldc\n");
    printf("Where A is mxk inside ldaxlda; B is kxn inside ldbxldb; C is mxk "
           "inside ldcxldc\n");
    exit(ierr);
  } else {
    *m = strtol(argv[1], &endPtr, 10);
    *n = strtol(argv[2], &endPtr, 10);
    *k = strtol(argv[3], &endPtr, 10);
    *lda = strtol(argv[4], &endPtr, 10);
    *ldb = strtol(argv[5], &endPtr, 10);
    *ldc = strtol(argv[6], &endPtr, 10);
    printf("m = %ld\tn = %ld\tk = %ld\n", *m, *n, *k);
    printf("lda = %ld\tldb = %ld\tldc = %ld\n", *lda, *ldb, *ldc);
  }
  return ierr;
}