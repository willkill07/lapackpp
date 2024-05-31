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
int64_t pteqr(
    lapack::Job compz, int64_t n,
    float* D,
    float* E,
    float* Z, int64_t ldz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldz) > std::numeric_limits<lapack_int>::max() );
    }
    char compz_ = to_char_comp( compz );
    lapack_int n_ = (lapack_int) n;
    lapack_int ldz_ = (lapack_int) ldz;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< float > work( (4*n) );

    spteqr_(
        &compz_, &n_,
        D,
        E,
        Z, &ldz_,
        &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pteqr(
    lapack::Job compz, int64_t n,
    double* D,
    double* E,
    double* Z, int64_t ldz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldz) > std::numeric_limits<lapack_int>::max() );
    }
    char compz_ = to_char_comp( compz );
    lapack_int n_ = (lapack_int) n;
    lapack_int ldz_ = (lapack_int) ldz;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< double > work( (4*n) );

    dpteqr_(
        &compz_, &n_,
        D,
        E,
        Z, &ldz_,
        &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pteqr(
    lapack::Job compz, int64_t n,
    float* D,
    float* E,
    std::complex<float>* Z, int64_t ldz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldz) > std::numeric_limits<lapack_int>::max() );
    }
    char compz_ = to_char_comp( compz );
    lapack_int n_ = (lapack_int) n;
    lapack_int ldz_ = (lapack_int) ldz;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< float > work( (4*n) );

    cpteqr_(
        &compz_, &n_,
        D,
        E,
        (lapack_complex_float*) Z, &ldz_,
        &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pteqr(
    lapack::Job compz, int64_t n,
    double* D,
    double* E,
    std::complex<double>* Z, int64_t ldz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldz) > std::numeric_limits<lapack_int>::max() );
    }
    char compz_ = to_char_comp( compz );
    lapack_int n_ = (lapack_int) n;
    lapack_int ldz_ = (lapack_int) ldz;
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< double > work( (4*n) );

    zpteqr_(
        &compz_, &n_,
        D,
        E,
        (lapack_complex_double*) Z, &ldz_,
        &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
