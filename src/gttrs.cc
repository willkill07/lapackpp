#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup gtsv_computational
int64_t gttrs(
    lapack::Op trans, int64_t n, int64_t nrhs,
    float const* DL,
    float const* D,
    float const* DU,
    float const* DU2,
    int64_t const* ipiv,
    float* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    char trans_ = op2char( trans );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int const* ipiv_ptr = &ipiv_[0];
    #else
        blas_int const* ipiv_ptr = ipiv_;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int info_ = 0;

    LAPACK_sgttrs( &trans_, &n_, &nrhs_, DL, D, DU, DU2, ipiv_ptr, B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gtsv_computational
int64_t gttrs(
    lapack::Op trans, int64_t n, int64_t nrhs,
    double const* DL,
    double const* D,
    double const* DU,
    double const* DU2,
    int64_t const* ipiv,
    double* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    char trans_ = op2char( trans );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int const* ipiv_ptr = &ipiv_[0];
    #else
        blas_int const* ipiv_ptr = ipiv_;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int info_ = 0;

    LAPACK_dgttrs( &trans_, &n_, &nrhs_, DL, D, DU, DU2, ipiv_ptr, B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gtsv_computational
int64_t gttrs(
    lapack::Op trans, int64_t n, int64_t nrhs,
    std::complex<float> const* DL,
    std::complex<float> const* D,
    std::complex<float> const* DU,
    std::complex<float> const* DU2,
    int64_t const* ipiv,
    std::complex<float>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    char trans_ = op2char( trans );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int const* ipiv_ptr = &ipiv_[0];
    #else
        blas_int const* ipiv_ptr = ipiv_;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int info_ = 0;

    LAPACK_cgttrs( &trans_, &n_, &nrhs_, DL, D, DU, DU2, ipiv_ptr, B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Solves one of the systems of equations
///     \f$ A   X = B, \f$
///     \f$ A^T X = B, \f$ or
///     \f$ A^H X = B, \f$
/// with a tridiagonal matrix A using the LU factorization computed
/// by `lapack::gttrf`.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
///
/// @param[in] trans
///     Specifies the form of the system of equations.
///     - lapack::Op::NoTrans:   \f$ A   X = B \f$ (No transpose)
///     - lapack::Op::Trans:     \f$ A^T X = B \f$ (Transpose)
///     - lapack::Op::ConjTrans: \f$ A^H X = B \f$ (Conjugate transpose)
///
/// @param[in] n
///     The order of the matrix A.
///
/// @param[in] nrhs
///     The number of right hand sides, i.e., the number of columns
///     of the matrix B. nrhs >= 0.
///
/// @param[in] DL
///     The vector DL of length n-1.
///     The (n-1) multipliers that define the matrix L from the
///     LU factorization of A.
///
/// @param[in] D
///     The vector D of length n.
///     The n diagonal elements of the upper triangular matrix U from
///     the LU factorization of A.
///
/// @param[in] DU
///     The vector DU of length n-1.
///     The (n-1) elements of the first super-diagonal of U.
///
/// @param[in] DU2
///     The vector DU2 of length n-2.
///     The (n-2) elements of the second super-diagonal of U.
///
/// @param[in] ipiv
///     The vector ipiv of length n.
///     The pivot indices; for 1 <= i <= n, row i of the matrix was
///     interchanged with row ipiv(i). ipiv(i) will always be either
///     i or i+1; ipiv(i) = i indicates a row interchange was not
///     required.
///
/// @param[in,out] B
///     The n-by-nrhs matrix B, stored in an ldb-by-nrhs array.
///     On entry, the matrix of right hand side vectors B.
///     On exit, B is overwritten by the solution vectors X.
///
/// @param[in] ldb
///     The leading dimension of the array B. ldb >= max(1,n).
///
/// @retval = 0: successful exit
///
/// @ingroup gtsv_computational
int64_t gttrs(
    lapack::Op trans, int64_t n, int64_t nrhs,
    std::complex<double> const* DL,
    std::complex<double> const* D,
    std::complex<double> const* DU,
    std::complex<double> const* DU2,
    int64_t const* ipiv,
    std::complex<double>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    char trans_ = op2char( trans );
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        blas_int const* ipiv_ptr = &ipiv_[0];
    #else
        blas_int const* ipiv_ptr = ipiv_;
    #endif
    blas_int ldb_ = (blas_int) ldb;
    blas_int info_ = 0;

    LAPACK_zgttrs( &trans_, &n_, &nrhs_, DL, D, DU, DU2, ipiv_ptr, B, &ldb_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
