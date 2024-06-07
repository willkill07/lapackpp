// Copyright (c) 2017-2023, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "lapack.hh"
#include "lapack/fortran.h"
#include "NoConstructAllocator.hh"

#if LAPACK_VERSION >= 30700  // >= 3.7

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup hesv
int64_t hesv_rk(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    std::complex<float>* A, int64_t lda,
    std::complex<float>* E,
    int64_t* ipiv,
    std::complex<float>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(nrhs) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int nrhs_ = (lapack_int) nrhs;
    lapack_int lda_ = (lapack_int) lda;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        lapack::vector< lapack_int > ipiv_( (n) );
        lapack_int* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int* ipiv_ptr = (lapack_int*) ipiv;
    #endif
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    lapack_int ineg_one = -1;
    chesv_rk_(
        &uplo_, &n_, &nrhs_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) E,
        ipiv_ptr,
        (lapack_complex_float*) B, &ldb_,
        (lapack_complex_float*) qry_work, &ineg_one, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< std::complex<float> > work( lwork_ );

    chesv_rk_(
        &uplo_, &n_, &nrhs_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) E,
        ipiv_ptr,
        (lapack_complex_float*) B, &ldb_,
        (lapack_complex_float*) &work[0], &lwork_, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    #ifndef LAPACK_ILP64
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
/// Computes the solution to a system of linear equations
/// \[
///     A X = B,
/// \]
/// where A is an n-by-n Hermitian matrix and X and B are n-by-nrhs matrices.
///
/// The bounded Bunch-Kaufman (rook) diagonal pivoting method is used
/// to factor A as
///     $A = P U D U^H P^T,$ if uplo = Upper, or
///     $A = P L D L^H P^T,$ if uplo = Lower,
/// where U (or L) is unit upper (or lower) triangular matrix,
/// $U^H$ (or $L^H$) is the conjugate of U (or L), P is a permutation
/// matrix, $P^T$ is the transpose of P, and D is Hermitian and block
/// diagonal with 1-by-1 and 2-by-2 diagonal blocks.
///
/// `lapack::hetrf_rk` is called to compute the factorization of a
/// Hermitian matrix. The factored form of A is then used to solve
/// the system of equations $A X = B$ by calling `lapack::hetrs_rk`.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
/// For real matrices, this is an alias for `lapack::sysv_rk`.
/// For complex symmetric matrices, see `lapack::sysv_rk`.
///
/// @param[in] uplo
///     Whether the upper or lower triangular part of the
///     Hermitian matrix A is stored:
///     - lapack::Uplo::Upper: Upper triangle of A is stored;
///     - lapack::Uplo::Lower: Lower triangle of A is stored.
///
/// @param[in] n
///     The number of linear equations, i.e., the order of the
///     matrix A. n >= 0.
///
/// @param[in] nrhs
///     The number of right hand sides, i.e., the number of columns
///     of the matrix B. nrhs >= 0.
///
/// @param[in,out] A
///     The n-by-n matrix A, stored in an lda-by-n array.
///     - On entry, the Hermitian matrix A.
///       - If uplo = Upper: the leading n-by-n upper triangular part
///       of A contains the upper triangular part of the matrix A,
///       and the strictly lower triangular part of A is not
///       referenced.
///
///       - If uplo = Lower: the leading n-by-n lower triangular part
///       of A contains the lower triangular part of the matrix A,
///       and the strictly upper triangular part of A is not
///       referenced.
///
///     - On successful exit, diagonal of the block diagonal
///     matrix D and factors U or L as computed by `lapack::hetrf_rk`:
///       - ONLY diagonal elements of the Hermitian block diagonal
///         matrix D on the diagonal of A, i.e. D(k,k) = A(k,k);
///         (superdiagonal (or subdiagonal) elements of D
///         are stored on exit in array E), and
///       - If uplo = Upper: factor U in the superdiagonal part of A.
///       - If uplo = Lower: factor L in the subdiagonal part of A.
///
///     - For more info see the description of `lapack::hetrf_rk`.
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= max(1,n).
///
/// @param[out] E
///     The vector E of length n.
///     On exit, contains the output computed by the factorization
///     routine `lapack::hetrf_rk`, i.e. the superdiagonal (or subdiagonal)
///     elements of the Hermitian block diagonal matrix D
///     with 1-by-1 or 2-by-2 diagonal blocks, where
///     - If uplo = Upper: E(i) = D(i-1,i), i=2:n, E(1) is set to 0;
///     - If uplo = Lower: E(i) = D(i+1,i), i=1:n-1, E(n) is set to 0.
///
///     - Note: For 1-by-1 diagonal block D(k), where
///     1 <= k <= n, the element E(k) is set to 0 in both
///     uplo = Upper or uplo = Lower cases.
///
///     - For more info see the description of `lapack::hetrf_rk`.
///
/// @param[out] ipiv
///     The vector ipiv of length n.
///     Details of the interchanges and the block structure of D,
///     as determined by `lapack::hetrf_rk`.
///     For more info see the description of `lapack::hetrf_rk`.
///
/// @param[in,out] B
///     The n-by-nrhs matrix B, stored in an ldb-by-nrhs array.
///     On entry, the n-by-nrhs right hand side matrix B.
///     On successful exit, the n-by-nrhs solution matrix X.
///
/// @param[in] ldb
///     The leading dimension of the array B. ldb >= max(1,n).
///
/// @return = 0: successful exit
/// @return > 0: If return value = k, the matrix A is singular, because:
///     If uplo = Upper: column k in the upper
///     triangular part of A contains all zeros.
///     If uplo = Lower: column k in the lower
///     triangular part of A contains all zeros.
///
///     Therefore D(k,k) is exactly zero, and superdiagonal
///     elements of column k of U (or subdiagonal elements of
///     column k of L ) are all zeros. The factorization has
///     been completed, but the block diagonal matrix D is
///     exactly singular, and division by zero will occur if
///     it is used to solve a system of equations.
///
///     NOTE: info only stores the first occurrence of
///     a singularity, any subsequent occurrence of singularity
///     is not stored in info even though the factorization
///     always completes.
///
/// @ingroup hesv
int64_t hesv_rk(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    std::complex<double>* A, int64_t lda,
    std::complex<double>* E,
    int64_t* ipiv,
    std::complex<double>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(nrhs) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int nrhs_ = (lapack_int) nrhs;
    lapack_int lda_ = (lapack_int) lda;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        lapack::vector< lapack_int > ipiv_( (n) );
        lapack_int* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int* ipiv_ptr = (lapack_int*) ipiv;
    #endif
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    lapack_int ineg_one = -1;
    zhesv_rk_(
        &uplo_, &n_, &nrhs_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) E,
        ipiv_ptr,
        (lapack_complex_double*) B, &ldb_,
        (lapack_complex_double*) qry_work, &ineg_one, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< std::complex<double> > work( lwork_ );

    zhesv_rk_(
        &uplo_, &n_, &nrhs_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) E,
        ipiv_ptr,
        (lapack_complex_double*) B, &ldb_,
        (lapack_complex_double*) &work[0], &lwork_, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    #ifndef LAPACK_ILP64
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

}  // namespace lapack

#endif  // LAPACK >= 3.7
