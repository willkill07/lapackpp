// Copyright (c) 2017-2023, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "lapack.hh"
#include "lapack/fortran.h"
#include "NoConstructAllocator.hh"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup norm
float lantb(
    lapack::Norm norm, lapack::Uplo uplo, lapack::Diag diag, int64_t n, int64_t k,
    float const* AB, int64_t ldab )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldab) > std::numeric_limits<lapack_int>::max() );
    }
    char norm_ = to_char( norm );
    char uplo_ = to_char( uplo );
    char diag_ = to_char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int ldab_ = (lapack_int) ldab;

    // from docs
    int64_t lwork = (norm == Norm::Inf ? n : 1);

    // allocate workspace
    lapack::vector< float > work( max(1,lwork) );

    return slantb_(
        &norm_, &uplo_, &diag_, &n_, &k_,
        AB, &ldab_,
        &work[0]
    );
}

// -----------------------------------------------------------------------------
/// @ingroup norm
double lantb(
    lapack::Norm norm, lapack::Uplo uplo, lapack::Diag diag, int64_t n, int64_t k,
    double const* AB, int64_t ldab )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldab) > std::numeric_limits<lapack_int>::max() );
    }
    char norm_ = to_char( norm );
    char uplo_ = to_char( uplo );
    char diag_ = to_char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int ldab_ = (lapack_int) ldab;

    // from docs
    int64_t lwork = (norm == Norm::Inf ? n : 1);

    // allocate workspace
    lapack::vector< double > work( max(1,lwork) );

    return dlantb_(
        &norm_, &uplo_, &diag_, &n_, &k_,
        AB, &ldab_,
        &work[0]
    );
}

// -----------------------------------------------------------------------------
/// @ingroup norm
float lantb(
    lapack::Norm norm, lapack::Uplo uplo, lapack::Diag diag, int64_t n, int64_t k,
    std::complex<float> const* AB, int64_t ldab )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldab) > std::numeric_limits<lapack_int>::max() );
    }
    char norm_ = to_char( norm );
    char uplo_ = to_char( uplo );
    char diag_ = to_char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int ldab_ = (lapack_int) ldab;

    // from docs
    int64_t lwork = (norm == Norm::Inf ? n : 1);

    // allocate workspace
    lapack::vector< float > work( max(1,lwork) );

    return clantb_(
        &norm_, &uplo_, &diag_, &n_, &k_,
        (lapack_complex_float*) AB, &ldab_,
        &work[0]
    );
}

// -----------------------------------------------------------------------------
/// Returns the value of the one norm, Frobenius norm,
/// infinity norm, or the element of largest absolute value of an
/// n-by-n triangular band matrix A, with (k + 1) diagonals.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
///
/// @param[in] norm
///     The value to be returned:
///     - lapack::Norm::Max: max norm: max(abs(A(i,j))).
///                          Note this is not a consistent matrix norm.
///     - lapack::Norm::One: one norm: maximum column sum
///     - lapack::Norm::Inf: infinity norm: maximum row sum
///     - lapack::Norm::Fro: Frobenius norm: square root of sum of squares
///
/// @param[in] uplo
///     Whether the matrix A is upper or lower triangular.
///     - lapack::Uplo::Upper: Upper triangular
///     - lapack::Uplo::Lower: Lower triangular
///
/// @param[in] diag
///     Whether or not the matrix A is unit triangular.
///     - lapack::Diag::NonUnit: Non-unit triangular
///     - lapack::Diag::Unit: Unit triangular
///
/// @param[in] n
///     The order of the matrix A. n >= 0. When n = 0, returns zero.
///
/// @param[in] k
///     - If uplo = Upper, the number of super-diagonals of the matrix A;
///     - if uplo = Lower, the number of sub-diagonals of the matrix A
///     - k >= 0.
///
/// @param[in] AB
///     The n-by-n band matrix AB, stored in an ldab-by-n array.
///     The upper or lower triangular band matrix A, stored in the
///     first k+1 rows of AB. The j-th column of A is stored
///     in the j-th column of the array AB as follows:
///     - if uplo = Upper, AB(k+1+i-j,j) = A(i,j) for max(1,j-k) <= i <= j;
///     - if uplo = Lower, AB(1+i-j,j) = A(i,j) for j <= i <= min(n,j+k).
///     - Note that when diag = Unit, the elements of the array AB
///     corresponding to the diagonal elements of the matrix A are
///     not referenced, but are assumed to be one.
///
/// @param[in] ldab
///     The leading dimension of the array AB. ldab >= k+1.
///
/// @ingroup norm
double lantb(
    lapack::Norm norm, lapack::Uplo uplo, lapack::Diag diag, int64_t n, int64_t k,
    std::complex<double> const* AB, int64_t ldab )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldab) > std::numeric_limits<lapack_int>::max() );
    }
    char norm_ = to_char( norm );
    char uplo_ = to_char( uplo );
    char diag_ = to_char( diag );
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int ldab_ = (lapack_int) ldab;

    // from docs
    int64_t lwork = (norm == Norm::Inf ? n : 1);

    // allocate workspace
    lapack::vector< double > work( max(1,lwork) );

    return zlantb_(
        &norm_, &uplo_, &diag_, &n_, &k_,
        (lapack_complex_double*) AB, &ldab_,
        &work[0]
    );
}

}  // namespace lapack
