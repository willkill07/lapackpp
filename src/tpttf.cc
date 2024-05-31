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
int64_t tpttf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    float const* AP,
    float* ARF )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = to_char( transr );
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    stpttf_(
        &transr_, &uplo_, &n_,
        AP,
        ARF, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tpttf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    double const* AP,
    double* ARF )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = to_char( transr );
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    dtpttf_(
        &transr_, &uplo_, &n_,
        AP,
        ARF, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tpttf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    std::complex<float> const* AP,
    std::complex<float>* ARF )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = to_char( transr );
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    ctpttf_(
        &transr_, &uplo_, &n_,
        (lapack_complex_float*) AP,
        (lapack_complex_float*) ARF, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tpttf(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    std::complex<double> const* AP,
    std::complex<double>* ARF )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char transr_ = to_char( transr );
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    ztpttf_(
        &transr_, &uplo_, &n_,
        (lapack_complex_double*) AP,
        (lapack_complex_double*) ARF, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
