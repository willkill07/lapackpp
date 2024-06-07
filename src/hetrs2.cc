// Copyright (c) 2017-2023, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "lapack.hh"
#include "lapack/fortran.h"
#include "NoConstructAllocator.hh"

#if LAPACK_VERSION >= 30300  // >= 3.3

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup hesv_computational
int64_t hetrs2(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    std::complex<float> const* A, int64_t lda,
    int64_t const* ipiv,
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
        std::vector< lapack_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        lapack_int const* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int const* ipiv_ptr = (lapack_int const*) ipiv;
    #endif
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< std::complex<float> > work( (n) );

    chetrs2_(
        &uplo_, &n_, &nrhs_,
        (lapack_complex_float*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_float*) B, &ldb_,
        (lapack_complex_float*) &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Solves a system of linear equations $A X = B$ with a
/// Hermitian matrix A using the factorization $A = U D U^H$ or
/// $A = L D L^H$ computed by `lapack::hetrf` and converted by `lapack::syconv`.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
/// For real matrices, this in an alias for `lapack::sytrs2`.
/// For complex symmetric matrices, see `lapack::sytrs2`.
///
/// @see hetrs
///
/// @param[in] uplo
///     Whether the details of the factorization are stored
///     as an upper or lower triangular matrix.
///     - lapack::Uplo::Upper: Upper triangular, form is $A = U D U^H;$
///     - lapack::Uplo::Lower: Lower triangular, form is $A = L D L^H.$
///
/// @param[in] n
///     The order of the matrix A. n >= 0.
///
/// @param[in] nrhs
///     The number of right hand sides, i.e., the number of columns
///     of the matrix B. nrhs >= 0.
///
/// @param[in] A
///     The n-by-n matrix A, stored in an lda-by-n array.
///     The block diagonal matrix D and the multipliers used to
///     obtain the factor U or L as computed by `lapack::hetrf`.
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= max(1,n).
///
/// @param[in] ipiv
///     The vector ipiv of length n.
///     Details of the interchanges and the block structure of D
///     as determined by `lapack::hetrf`.
///
/// @param[in,out] B
///     The n-by-nrhs matrix B, stored in an ldb-by-nrhs array.
///     On entry, the right hand side matrix B.
///     On exit, the solution matrix X.
///
/// @param[in] ldb
///     The leading dimension of the array B. ldb >= max(1,n).
///
/// @return = 0: successful exit
///
/// @ingroup hesv_computational
int64_t hetrs2(
    lapack::Uplo uplo, int64_t n, int64_t nrhs,
    std::complex<double> const* A, int64_t lda,
    int64_t const* ipiv,
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
        std::vector< lapack_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        lapack_int const* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int const* ipiv_ptr = (lapack_int const*) ipiv;
    #endif
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< std::complex<double> > work( (n) );

    zhetrs2_(
        &uplo_, &n_, &nrhs_,
        (lapack_complex_double*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_double*) B, &ldb_,
        (lapack_complex_double*) &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack

#endif  // LAPACK >= 3.3.0
