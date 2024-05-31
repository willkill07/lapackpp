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
int64_t geqp3(
    int64_t m, int64_t n,
    float* A, int64_t lda,
    int64_t* jpvt,
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
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > jpvt_( &jpvt[0], &jpvt[(n)] );
        lapack_int* jpvt_ptr = &jpvt_[0];
    #else
        lapack_int* jpvt_ptr = jpvt;
    #endif
    lapack_int info_ = 0;

    // query for workspace size
    float qry_work[1];
    lapack_int ineg_one = -1;
    sgeqp3_(
        &m_, &n_,
        A, &lda_,
        jpvt_ptr,
        tau,
        qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< float > work( lwork_ );

    sgeqp3_(
        &m_, &n_,
        A, &lda_,
        jpvt_ptr,
        tau,
        &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #ifndef LAPACK_ILP64
        std::copy( jpvt_.begin(), jpvt_.end(), jpvt );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
int64_t geqp3(
    int64_t m, int64_t n,
    double* A, int64_t lda,
    int64_t* jpvt,
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
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > jpvt_( &jpvt[0], &jpvt[(n)] );
        lapack_int* jpvt_ptr = &jpvt_[0];
    #else
        lapack_int* jpvt_ptr = jpvt;
    #endif
    lapack_int info_ = 0;

    // query for workspace size
    double qry_work[1];
    lapack_int ineg_one = -1;
    dgeqp3_(
        &m_, &n_,
        A, &lda_,
        jpvt_ptr,
        tau,
        qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< double > work( lwork_ );

    dgeqp3_(
        &m_, &n_,
        A, &lda_,
        jpvt_ptr,
        tau,
        &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #ifndef LAPACK_ILP64
        std::copy( jpvt_.begin(), jpvt_.end(), jpvt );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
int64_t geqp3(
    int64_t m, int64_t n,
    std::complex<float>* A, int64_t lda,
    int64_t* jpvt,
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
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > jpvt_( &jpvt[0], &jpvt[(n)] );
        lapack_int* jpvt_ptr = &jpvt_[0];
    #else
        lapack_int* jpvt_ptr = jpvt;
    #endif
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    float qry_rwork[1];
    lapack_int ineg_one = -1;
    cgeqp3_(
        &m_, &n_,
        (lapack_complex_float*) A, &lda_,
        jpvt_ptr,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) qry_work, &ineg_one,
        qry_rwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< std::complex<float> > work( lwork_ );
    lapack::vector< float > rwork( (2*n) );

    cgeqp3_(
        &m_, &n_,
        (lapack_complex_float*) A, &lda_,
        jpvt_ptr,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) &work[0], &lwork_,
        &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #ifndef LAPACK_ILP64
        std::copy( jpvt_.begin(), jpvt_.end(), jpvt );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
int64_t geqp3(
    int64_t m, int64_t n,
    std::complex<double>* A, int64_t lda,
    int64_t* jpvt,
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
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > jpvt_( &jpvt[0], &jpvt[(n)] );
        lapack_int* jpvt_ptr = &jpvt_[0];
    #else
        lapack_int* jpvt_ptr = jpvt;
    #endif
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    double qry_rwork[1];
    lapack_int ineg_one = -1;
    zgeqp3_(
        &m_, &n_,
        (lapack_complex_double*) A, &lda_,
        jpvt_ptr,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) qry_work, &ineg_one,
        qry_rwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< std::complex<double> > work( lwork_ );
    lapack::vector< double > rwork( (2*n) );

    zgeqp3_(
        &m_, &n_,
        (lapack_complex_double*) A, &lda_,
        jpvt_ptr,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) &work[0], &lwork_,
        &rwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #ifndef LAPACK_ILP64
        std::copy( jpvt_.begin(), jpvt_.end(), jpvt );
    #endif
    return info_;
}

}  // namespace lapack
