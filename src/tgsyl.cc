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
int64_t tgsyl(
    lapack::Op trans, int64_t ijob, int64_t m, int64_t n,
    float const* A, int64_t lda,
    float const* B, int64_t ldb,
    float* C, int64_t ldc,
    float const* D, int64_t ldd,
    float const* E, int64_t lde,
    float* F, int64_t ldf,
    float* dif,
    float* scale )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(ijob) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldc) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldd) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lde) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldf) > std::numeric_limits<lapack_int>::max() );
    }
    char trans_ = to_char( trans );
    lapack_int ijob_ = (lapack_int) ijob;
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldc_ = (lapack_int) ldc;
    lapack_int ldd_ = (lapack_int) ldd;
    lapack_int lde_ = (lapack_int) lde;
    lapack_int ldf_ = (lapack_int) ldf;
    lapack_int info_ = 0;

    // query for workspace size
    float qry_work[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    stgsyl_(
        &trans_, &ijob_, &m_, &n_,
        A, &lda_,
        B, &ldb_,
        C, &ldc_,
        D, &ldd_,
        E, &lde_,
        F, &ldf_, dif, scale,
        qry_work, &ineg_one,
        qry_iwork, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< float > work( lwork_ );
    lapack::vector< lapack_int > iwork( (m+n+6) );

    stgsyl_(
        &trans_, &ijob_, &m_, &n_,
        A, &lda_,
        B, &ldb_,
        C, &ldc_,
        D, &ldd_,
        E, &lde_,
        F, &ldf_, dif, scale,
        &work[0], &lwork_,
        &iwork[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tgsyl(
    lapack::Op trans, int64_t ijob, int64_t m, int64_t n,
    double const* A, int64_t lda,
    double const* B, int64_t ldb,
    double* C, int64_t ldc,
    double const* D, int64_t ldd,
    double const* E, int64_t lde,
    double* F, int64_t ldf,
    double* dif,
    double* scale )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(ijob) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldc) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldd) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lde) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldf) > std::numeric_limits<lapack_int>::max() );
    }
    char trans_ = to_char( trans );
    lapack_int ijob_ = (lapack_int) ijob;
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldc_ = (lapack_int) ldc;
    lapack_int ldd_ = (lapack_int) ldd;
    lapack_int lde_ = (lapack_int) lde;
    lapack_int ldf_ = (lapack_int) ldf;
    lapack_int info_ = 0;

    // query for workspace size
    double qry_work[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    dtgsyl_(
        &trans_, &ijob_, &m_, &n_,
        A, &lda_,
        B, &ldb_,
        C, &ldc_,
        D, &ldd_,
        E, &lde_,
        F, &ldf_, dif, scale,
        qry_work, &ineg_one,
        qry_iwork, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< double > work( lwork_ );
    lapack::vector< lapack_int > iwork( (m+n+6) );

    dtgsyl_(
        &trans_, &ijob_, &m_, &n_,
        A, &lda_,
        B, &ldb_,
        C, &ldc_,
        D, &ldd_,
        E, &lde_,
        F, &ldf_, dif, scale,
        &work[0], &lwork_,
        &iwork[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tgsyl(
    lapack::Op trans, int64_t ijob, int64_t m, int64_t n,
    std::complex<float> const* A, int64_t lda,
    std::complex<float> const* B, int64_t ldb,
    std::complex<float>* C, int64_t ldc,
    std::complex<float> const* D, int64_t ldd,
    std::complex<float> const* E, int64_t lde,
    std::complex<float>* F, int64_t ldf,
    float* dif,
    float* scale )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(ijob) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldc) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldd) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lde) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldf) > std::numeric_limits<lapack_int>::max() );
    }
    char trans_ = to_char( trans );
    lapack_int ijob_ = (lapack_int) ijob;
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldc_ = (lapack_int) ldc;
    lapack_int ldd_ = (lapack_int) ldd;
    lapack_int lde_ = (lapack_int) lde;
    lapack_int ldf_ = (lapack_int) ldf;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    ctgsyl_(
        &trans_, &ijob_, &m_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) B, &ldb_,
        (lapack_complex_float*) C, &ldc_,
        (lapack_complex_float*) D, &ldd_,
        (lapack_complex_float*) E, &lde_,
        (lapack_complex_float*) F, &ldf_, dif, scale,
        (lapack_complex_float*) qry_work, &ineg_one,
        qry_iwork, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< std::complex<float> > work( lwork_ );
    lapack::vector< lapack_int > iwork( (m+n+2) );

    ctgsyl_(
        &trans_, &ijob_, &m_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) B, &ldb_,
        (lapack_complex_float*) C, &ldc_,
        (lapack_complex_float*) D, &ldd_,
        (lapack_complex_float*) E, &lde_,
        (lapack_complex_float*) F, &ldf_, dif, scale,
        (lapack_complex_float*) &work[0], &lwork_,
        &iwork[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tgsyl(
    lapack::Op trans, int64_t ijob, int64_t m, int64_t n,
    std::complex<double> const* A, int64_t lda,
    std::complex<double> const* B, int64_t ldb,
    std::complex<double>* C, int64_t ldc,
    std::complex<double> const* D, int64_t ldd,
    std::complex<double> const* E, int64_t lde,
    std::complex<double>* F, int64_t ldf,
    double* dif,
    double* scale )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(ijob) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldc) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldd) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lde) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldf) > std::numeric_limits<lapack_int>::max() );
    }
    char trans_ = to_char( trans );
    lapack_int ijob_ = (lapack_int) ijob;
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldb_ = (lapack_int) ldb;
    lapack_int ldc_ = (lapack_int) ldc;
    lapack_int ldd_ = (lapack_int) ldd;
    lapack_int lde_ = (lapack_int) lde;
    lapack_int ldf_ = (lapack_int) ldf;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    ztgsyl_(
        &trans_, &ijob_, &m_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) B, &ldb_,
        (lapack_complex_double*) C, &ldc_,
        (lapack_complex_double*) D, &ldd_,
        (lapack_complex_double*) E, &lde_,
        (lapack_complex_double*) F, &ldf_, dif, scale,
        (lapack_complex_double*) qry_work, &ineg_one,
        qry_iwork, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< std::complex<double> > work( lwork_ );
    lapack::vector< lapack_int > iwork( (m+n+2) );

    ztgsyl_(
        &trans_, &ijob_, &m_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) B, &ldb_,
        (lapack_complex_double*) C, &ldc_,
        (lapack_complex_double*) D, &ldd_,
        (lapack_complex_double*) E, &lde_,
        (lapack_complex_double*) F, &ldf_, dif, scale,
        (lapack_complex_double*) &work[0], &lwork_,
        &iwork[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
