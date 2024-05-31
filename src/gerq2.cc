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
/// @ingroup gerqf
int64_t gerq2(
    int64_t m, int64_t n,
    float* A, int64_t lda,
    float* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< float > work( (m) );

    sgerq2_(
        &m_, &n_,
        A, &lda_,
        tau,
        &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gerqf
int64_t gerq2(
    int64_t m, int64_t n,
    double* A, int64_t lda,
    double* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< double > work( (m) );

    dgerq2_(
        &m_, &n_,
        A, &lda_,
        tau,
        &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gerqf
int64_t gerq2(
    int64_t m, int64_t n,
    std::complex<float>* A, int64_t lda,
    std::complex<float>* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< std::complex<float> > work( (m) );

    cgerq2_(
        &m_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Computes an RQ factorization of an m-by-n matrix A:
/// $A = R Q$.
///
/// This is the unblocked Level 2 BLAS version of the algorithm.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
///
/// @param[in] m
///     The number of rows of the matrix A. m >= 0.
///
/// @param[in] n
///     The number of columns of the matrix A. n >= 0.
///
/// @param[in,out] A
///     The m-by-n matrix A, stored in an lda-by-n array.
///     On entry, the m-by-n matrix A.
///     On exit:
///     - if m <= n, the upper triangle of the subarray
///     A(1:m,n-m+1:n) contains the m-by-m upper triangular matrix R;
///
///     - if m >= n, the elements on and above the (m-n)-th subdiagonal
///     contain the m-by-n upper trapezoidal matrix R.
///
///     - The remaining elements, with the array tau, represent the
///     unitary matrix Q as a product of min(m,n) elementary
///     reflectors (see Further Details).
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= max(1,m).
///
/// @param[out] tau
///     The vector tau of length min(m,n).
///     The scalar factors of the elementary reflectors (see Further
///     Details).
///
/// @return = 0: successful exit
///
// -----------------------------------------------------------------------------
/// @par Further Details
///
/// The matrix Q is represented as a product of elementary reflectors
/// \[
///     Q = H(1)^H H(2)^H \dots H(k)^H, \text{ where } k = \min(m,n).
/// \]
///
/// Each H(i) has the form
/// \[
///     H(i) = I - \tau v v^H
/// \]
///
/// where $\tau$ is a scalar, and v is a vector with
/// v(n-k+i+1:n) = 0 and v(n-k+i) = 1; conj(v(1:n-k+i-1)) is stored on
/// exit in A(m-k+i,1:n-k+i-1), and $\tau$ in tau(i).
///
/// @ingroup gerqf
int64_t gerq2(
    int64_t m, int64_t n,
    std::complex<double>* A, int64_t lda,
    std::complex<double>* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< std::complex<double> > work( (m) );

    zgerq2_(
        &m_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
