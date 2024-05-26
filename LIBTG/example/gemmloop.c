#include "datatype.h"

int main(int argc, char **argv) {
  int ierr = EXIT_SUCCESS;

  tg_scalar_t *A = NULL;
  tg_scalar_t *B = NULL;
  tg_scalar_t *C = NULL;

  tg_fixdbl_t Mem = 0.;
  const tg_scalar_t alpha = 1;
  const tg_scalar_t beta = 1;

  tg_int_t m = 0, n = 0, k = 0;
  tg_int_t lda = 0, ldb = 0, ldc = 0;

  printf("size of tg_scalar_t %zu double %zu float %zu\n", tg_size_of(ETYPE),
         tg_size_of(TGDouble), tg_size_of(TGFloat));
#if TYPE == tg_float_t
  printf("CASE TGFloat\n");
#elif TYPE == tg_double_t
  printf("CASE TGDouble\n");
#endif

  ierr = GetDim(&m, &n, &k, &lda, &ldb, &ldc, argc, argv);
  printf("%zu\n", SIZE_MAX);
  printf("m = %ld\tn = %ld\tk = %ld\n", m, n, k);
  printf("lda = %ld\tldb = %ld\tldc = %ld\n", lda, ldb, ldc);

  size_t Asize = m * k;
  size_t Bsize = k * n;
  size_t Csize = m * n;

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

  tg_mat_t matA = TGMATNULL();
  matA.nr = m;
  matA.nc = k;
  matA.ldnr = lda;
  matA.ldnc = lda;
  matA.rowcol_order = TGRowMajor;
  matA.coeftype = ETYPE;

  TGAlloc(&matA);
  ierr = TGFillMat2(&matA);

  tg_rectrange_t range = {.nr1 = 0, .nr2 = lda, .nc1 = 0, .nc2 = lda};
  ierr = TGShowMat(range, &matA);

  range = (tg_rectrange_t){
      .nr1 = min(2, m), .nr2 = min(5, m), .nc1 = min(2, k), .nc2 = min(5, k)};
  ierr = TGShowMat(range, &matA);

  TGExit(&matA);

  return ierr;
}