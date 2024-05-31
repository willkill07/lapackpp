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
int64_t pstrf(
    lapack::Uplo uplo, int64_t n,
    float* A, int64_t lda,
    int64_t* piv,
    int64_t* rank, float tol )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        lapack::vector< lapack_int > piv_( (n) );
        lapack_int* piv_ptr = &piv_[0];
    #else
        lapack_int* piv_ptr = piv;
    #endif
    lapack_int rank_ = (lapack_int) *rank;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< float > work( (2*n) );

    spstrf_(
        &uplo_, &n_,
        A, &lda_,
        piv_ptr, &rank_, &tol,
        &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    #ifndef LAPACK_ILP64
        std::copy( piv_.begin(), piv_.end(), piv );
    #endif
    *rank = rank_;
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pstrf(
    lapack::Uplo uplo, int64_t n,
    double* A, int64_t lda,
    int64_t* piv,
    int64_t* rank, double tol )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        lapack::vector< lapack_int > piv_( (n) );
        lapack_int* piv_ptr = &piv_[0];
    #else
        lapack_int* piv_ptr = piv;
    #endif
    lapack_int rank_ = (lapack_int) *rank;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< double > work( (2*n) );

    dpstrf_(
        &uplo_, &n_,
        A, &lda_,
        piv_ptr, &rank_, &tol,
        &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    #ifndef LAPACK_ILP64
        std::copy( piv_.begin(), piv_.end(), piv );
    #endif
    *rank = rank_;
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pstrf(
    lapack::Uplo uplo, int64_t n,
    std::complex<float>* A, int64_t lda,
    int64_t* piv,
    int64_t* rank, float tol )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        lapack::vector< lapack_int > piv_( (n) );
        lapack_int* piv_ptr = &piv_[0];
    #else
        lapack_int* piv_ptr = piv;
    #endif
    lapack_int rank_ = (lapack_int) *rank;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< float > work( (2*n) );

    cpstrf_(
        &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        piv_ptr, &rank_, &tol,
        &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    #ifndef LAPACK_ILP64
        std::copy( piv_.begin(), piv_.end(), piv );
    #endif
    *rank = rank_;
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pstrf(
    lapack::Uplo uplo, int64_t n,
    std::complex<double>* A, int64_t lda,
    int64_t* piv,
    int64_t* rank, double tol )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        lapack::vector< lapack_int > piv_( (n) );
        lapack_int* piv_ptr = &piv_[0];
    #else
        lapack_int* piv_ptr = piv;
    #endif
    lapack_int rank_ = (lapack_int) *rank;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< double > work( (2*n) );

    zpstrf_(
        &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        piv_ptr, &rank_, &tol,
        &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    #ifndef LAPACK_ILP64
        std::copy( piv_.begin(), piv_.end(), piv );
    #endif
    *rank = rank_;
    return info_;
}

}  // namespace lapack
