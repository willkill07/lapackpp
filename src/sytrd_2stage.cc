// Copyright (c) 2017-2023, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "lapack.hh"
#include "lapack/fortran.h"
#include "NoConstructAllocator.hh"

#if LAPACK_VERSION >= 30700  // >= v3.7

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup heev_computational
int64_t sytrd_2stage(
    lapack::Job jobz, lapack::Uplo uplo, int64_t n,
    float* A, int64_t lda,
    float* D,
    float* E,
    float* tau,
    float* hous2, int64_t lhous2 )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lhous2) > std::numeric_limits<lapack_int>::max() );
    }
    char jobz_ = to_char( jobz );
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int lhous2_ = (lapack_int) lhous2;
    lapack_int info_ = 0;

    // query for workspace size
    float qry_work[1];
    lapack_int ineg_one = -1;
    ssytrd_2stage_(
        &jobz_, &uplo_, &n_,
        A, &lda_,
        D,
        E,
        tau,
        hous2, &lhous2_,
        qry_work, &ineg_one, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< float > work( lwork_ );

    ssytrd_2stage_(
        &jobz_, &uplo_, &n_,
        A, &lda_,
        D,
        E,
        tau,
        hous2, &lhous2_,
        &work[0], &lwork_, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @see lapack::hetrd_2stage
/// @ingroup heev_computational
int64_t sytrd_2stage(
    lapack::Job jobz, lapack::Uplo uplo, int64_t n,
    double* A, int64_t lda,
    double* D,
    double* E,
    double* tau,
    double* hous2, int64_t lhous2 )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lhous2) > std::numeric_limits<lapack_int>::max() );
    }
    char jobz_ = to_char( jobz );
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int lhous2_ = (lapack_int) lhous2;
    lapack_int info_ = 0;

    // query for workspace size
    double qry_work[1];
    lapack_int ineg_one = -1;
    dsytrd_2stage_(
        &jobz_, &uplo_, &n_,
        A, &lda_,
        D,
        E,
        tau,
        hous2, &lhous2_,
        qry_work, &ineg_one, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< double > work( lwork_ );

    dsytrd_2stage_(
        &jobz_, &uplo_, &n_,
        A, &lda_,
        D,
        E,
        tau,
        hous2, &lhous2_,
        &work[0], &lwork_, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack

#endif  // LAPACK >= v3.7
