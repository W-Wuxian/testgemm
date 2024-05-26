#ifndef _datatype_h_
#define _datatype_h_

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int32_t tg_int32_t;
typedef int64_t tg_int64_t;
typedef uint32_t tg_uint32_t;
typedef uint64_t tg_uint64_t;

typedef double tg_fixdbl_t;
typedef float tg_fixflt_t;

typedef double tg_double_t;
typedef float tg_float_t;

/**
 * Compiler numbers (Extracted form PaRSEC project)
 **/
#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
/* Windows and non-Intel compiler */
#include <complex>
typedef std::complex<float> tg_complex32_t;
typedef std::complex<double> tg_complex64_t;
#else
typedef float _Complex tg_complex32_t;
typedef double _Complex tg_complex64_t;
#endif

#if !defined(__cplusplus) && defined(HAVE_COMPLES_H)
#include <complex.h>
#else

#ifdef __cplusplus
extern "C" {
#endif

/**
 * These declaration will not clash with C++ provides because
 * the names in C++ are name-mangled.
 */

extern double cabs(tg_complex64_t z);
extern double creal(tg_complex64_t z);
extern double cimag(tg_complex64_t z);

extern float cabsf(tg_complex32_t z);
extern float crealf(tg_complex32_t z);
extern float cimagf(tg_complex32_t z);

extern tg_complex64_t conj(tg_complex64_t z);
extern tg_complex64_t csqrt(tg_complex64_t z);

extern tg_complex32_t conjf(tg_complex32_t z);
extern tg_complex32_t csqrtf(tg_complex32_t z);

#ifdef __cplusplus
}
#endif

#endif /* HAVE_COMPLEX_H */

#ifndef TYPE
#define TYPE other
#endif

#if TYPE == float
#undef TYPE
#define TYPE tg_float_t
#define ETYPE TGFloat
typedef tg_float_t tg_scalar_t;
#elif TYPE == double
#undef TYPE
#define TYPE tg_double_t
#define ETYPE TGDouble
typedef tg_double_t tg_scalar_t;
#elif TYPE == cx32
#undef TYPE
#define TYPE tg_complex32_t
#define ETYPE TGComplex32
typedef tg_complex32_t tg_scalar_t;
#elif TYPE == cx64
#undef TYPE
#define TYPE tg_complex64_t
#define ETYPE TGComplex64
typedef tg_complex64_t tg_scalar_t;
#else
#error Undefined TYPE not supported
exit(EXIT_SUCCESS);
#endif // TYPE

#ifndef ITYPE
#define ITYPE I32
#endif

#if ITYPE == I32
#undef ITYPE
#define ITYPE tg_int32_t
typedef tg_int32_t tg_int_t;
typedef tg_uint32_t tg_uint_t;
#elif ITYPE == I64
#undef ITYPE
#define ITYPE tg_int64_t
typedef tg_int64_t tg_int_t;
typedef tg_uint64_t tg_uint_t;
#else
#error Undefined ITYPE not supported
exit(EXIT_SUCCESS);
#endif // TYPE

#define max(a, b) (((a) < (b)) ? (b) : (a))
#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef enum tg_rc_major_order_e {
  TGRowMajor, /**< Row major order >*/
  TGColMajor  /**< Col major order >*/
} tg_rc_major_order_t;

typedef enum tg_coeftype_e {
  TGFloat = 2,
  TGDouble = 3,
  TGComplex32 = 4,
  TGComplex64 = 5
} tg_coeftype_t;

struct tg_rectrange_s;
typedef struct tg_rectrange_s {
  tg_int_t nr1;
  tg_int_t nr2;
  tg_int_t nc1;
  tg_int_t nc2;
} tg_rectrange_t;

struct tg_mat_s;
typedef struct tg_mat_s {
  tg_rc_major_order_t rowcol_order;
  tg_coeftype_t coeftype;
  tg_int_t nr;
  tg_int_t nc;
  tg_int_t ldnr;
  tg_int_t ldnc;
  void *val;
} tg_mat_t;

#define TGMATNULL()                                                            \
  {                                                                            \
    .rowcol_order = TGColMajor, .coeftype = TGDouble, .nr = 0, .nc = 0,        \
    .ldnr = 0, .ldnc = 0, .val = NULL                                          \
  }

struct tg_submat_s;
typedef struct tg_submat_s {
  tg_rectrange_t rectrange;
  tg_mat_t *mat;
} tg_submat_t;

static inline size_t tg_size_of(tg_coeftype_t type) {
  switch (type) {
  case TGFloat:
    return sizeof(float);
  case TGDouble:
    return sizeof(double);
  case TGComplex32:
    return 2 * sizeof(float);
  case TGComplex64:
    return 2 * sizeof(double);
  default:
    fprintf(stderr, "tg_size_of: invalid type parameter\n");
    assert(0);
    return sizeof(double);
  }
}

#endif /* _datatype_h_ */