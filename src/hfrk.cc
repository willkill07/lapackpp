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
void hfrk(
    lapack::Op transr, lapack::Uplo uplo, lapack::Op trans, int64_t n, int64_t k, float alpha,
    std::complex<float> const* A, int64_t lda, float beta,
    std::complex<float>* C )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = to_char( transr );
    char uplo_ = to_char( uplo );
    char trans_ = to_char( trans );
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int lda_ = (lapack_int) lda;

    chfrk_(
        &transr_, &uplo_, &trans_, &n_, &k_, &alpha,
        (lapack_complex_float*) A, &lda_, &beta,
        (lapack_complex_float*) C
    );
}

// -----------------------------------------------------------------------------
void hfrk(
    lapack::Op transr, lapack::Uplo uplo, lapack::Op trans, int64_t n, int64_t k, double alpha,
    std::complex<double> const* A, int64_t lda, double beta,
    std::complex<double>* C )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = to_char( transr );
    char uplo_ = to_char( uplo );
    char trans_ = to_char( trans );
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int lda_ = (lapack_int) lda;

    zhfrk_(
        &transr_, &uplo_, &trans_, &n_, &k_, &alpha,
        (lapack_complex_double*) A, &lda_, &beta,
        (lapack_complex_double*) C
    );
}

}  // namespace lapack
