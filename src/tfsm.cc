// Copyright (c) 2017-2023, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "lapack.hh"
#include "lapack/fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
void tfsm(
    lapack::Op transr, lapack::Side side, lapack::Uplo uplo, lapack::Op trans, lapack::Diag diag, int64_t m, int64_t n, float alpha,
    float const* A,
    float* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = to_char( transr );
    char side_ = to_char( side );
    char uplo_ = to_char( uplo );
    char trans_ = to_char( trans );
    char diag_ = to_char( diag );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int ldb_ = (lapack_int) ldb;

    stfsm_(
        &transr_, &side_, &uplo_, &trans_, &diag_, &m_, &n_, &alpha,
        A,
        B, &ldb_
    );
}

// -----------------------------------------------------------------------------
void tfsm(
    lapack::Op transr, lapack::Side side, lapack::Uplo uplo, lapack::Op trans, lapack::Diag diag, int64_t m, int64_t n, double alpha,
    double const* A,
    double* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = to_char( transr );
    char side_ = to_char( side );
    char uplo_ = to_char( uplo );
    char trans_ = to_char( trans );
    char diag_ = to_char( diag );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int ldb_ = (lapack_int) ldb;

    dtfsm_(
        &transr_, &side_, &uplo_, &trans_, &diag_, &m_, &n_, &alpha,
        A,
        B, &ldb_
    );
}

// -----------------------------------------------------------------------------
void tfsm(
    lapack::Op transr, lapack::Side side, lapack::Uplo uplo, lapack::Op trans, lapack::Diag diag, int64_t m, int64_t n, std::complex<float> alpha,
    std::complex<float> const* A,
    std::complex<float>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = to_char( transr );
    char side_ = to_char( side );
    char uplo_ = to_char( uplo );
    char trans_ = to_char( trans );
    char diag_ = to_char( diag );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int ldb_ = (lapack_int) ldb;

    ctfsm_(
        &transr_, &side_, &uplo_, &trans_, &diag_, &m_, &n_,
        (lapack_complex_float*) &alpha,
        (lapack_complex_float*) A,
        (lapack_complex_float*) B, &ldb_
    );
}

// -----------------------------------------------------------------------------
void tfsm(
    lapack::Op transr, lapack::Side side, lapack::Uplo uplo, lapack::Op trans, lapack::Diag diag, int64_t m, int64_t n, std::complex<double> alpha,
    std::complex<double> const* A,
    std::complex<double>* B, int64_t ldb )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldb) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = to_char( transr );
    char side_ = to_char( side );
    char uplo_ = to_char( uplo );
    char trans_ = to_char( trans );
    char diag_ = to_char( diag );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int ldb_ = (lapack_int) ldb;

    ztfsm_(
        &transr_, &side_, &uplo_, &trans_, &diag_, &m_, &n_,
        (lapack_complex_double*) &alpha,
        (lapack_complex_double*) A,
        (lapack_complex_double*) B, &ldb_
    );
}

}  // namespace lapack
