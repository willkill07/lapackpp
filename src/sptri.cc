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
int64_t sptri(
    lapack::Uplo uplo, int64_t n,
    float* AP,
    int64_t const* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        lapack_int const* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int const* ipiv_ptr = (lapack_int const*) ipiv;
    #endif
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< float > work( (n) );

    ssptri_(
        &uplo_, &n_,
        AP,
        ipiv_ptr,
        &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t sptri(
    lapack::Uplo uplo, int64_t n,
    double* AP,
    int64_t const* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        lapack_int const* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int const* ipiv_ptr = (lapack_int const*) ipiv;
    #endif
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< double > work( (n) );

    dsptri_(
        &uplo_, &n_,
        AP,
        ipiv_ptr,
        &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t sptri(
    lapack::Uplo uplo, int64_t n,
    std::complex<float>* AP,
    int64_t const* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        lapack_int const* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int const* ipiv_ptr = (lapack_int const*) ipiv;
    #endif
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< std::complex<float> > work( (n) );

    csptri_(
        &uplo_, &n_,
        (lapack_complex_float*) AP,
        ipiv_ptr,
        (lapack_complex_float*) &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t sptri(
    lapack::Uplo uplo, int64_t n,
    std::complex<double>* AP,
    int64_t const* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        lapack_int const* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int const* ipiv_ptr = (lapack_int const*) ipiv;
    #endif
    lapack_int info_ = 0;

    // allocate workspace
    lapack::vector< std::complex<double> > work( (n) );

    zsptri_(
        &uplo_, &n_,
        (lapack_complex_double*) AP,
        ipiv_ptr,
        (lapack_complex_double*) &work[0], &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
