// Copyright (c) 2017-2023, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "lapack.hh"
#include "lapack/fortran.h"
#include "NoConstructAllocator.hh"

#if LAPACK_VERSION >= 30202  // >= v3.2.2

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t geqrfp(
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

    // query for workspace size
    float qry_work[1];
    lapack_int ineg_one = -1;
    sgeqrfp_(
        &m_, &n_,
        A, &lda_,
        tau,
        qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< float > work( lwork_ );

    sgeqrfp_(
        &m_, &n_,
        A, &lda_,
        tau,
        &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t geqrfp(
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

    // query for workspace size
    double qry_work[1];
    lapack_int ineg_one = -1;
    dgeqrfp_(
        &m_, &n_,
        A, &lda_,
        tau,
        qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< double > work( lwork_ );

    dgeqrfp_(
        &m_, &n_,
        A, &lda_,
        tau,
        &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t geqrfp(
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

    // query for workspace size
    std::complex<float> qry_work[1];
    lapack_int ineg_one = -1;
    cgeqrfp_(
        &m_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< std::complex<float> > work( lwork_ );

    cgeqrfp_(
        &m_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t geqrfp(
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

    // query for workspace size
    std::complex<double> qry_work[1];
    lapack_int ineg_one = -1;
    zgeqrfp_(
        &m_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< std::complex<double> > work( lwork_ );

    zgeqrfp_(
        &m_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack

#endif  // LAPACK >= v3.2.2
