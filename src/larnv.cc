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
/// @ingroup initialize
void larnv(
    int64_t idist,
    int64_t* iseed, int64_t n,
    float* X )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(idist) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int idist_ = (lapack_int) idist;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > iseed_( &iseed[0], &iseed[(4)] );
        lapack_int* iseed_ptr = &iseed_[0];
    #else
        lapack_int* iseed_ptr = (lapack_int*) iseed;
    #endif
    lapack_int n_ = (lapack_int) n;

    slarnv_(
        &idist_,
        iseed_ptr, &n_,
        X );
    #ifndef LAPACK_ILP64
        std::copy( iseed_.begin(), iseed_.end(), iseed );
    #endif
}

// -----------------------------------------------------------------------------
/// @ingroup initialize
void larnv(
    int64_t idist,
    int64_t* iseed, int64_t n,
    double* X )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(idist) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int idist_ = (lapack_int) idist;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > iseed_( &iseed[0], &iseed[(4)] );
        lapack_int* iseed_ptr = &iseed_[0];
    #else
        lapack_int* iseed_ptr = (lapack_int*) iseed;
    #endif
    lapack_int n_ = (lapack_int) n;

    dlarnv_(
        &idist_,
        iseed_ptr, &n_,
        X );
    #ifndef LAPACK_ILP64
        std::copy( iseed_.begin(), iseed_.end(), iseed );
    #endif
}

// -----------------------------------------------------------------------------
/// @ingroup initialize
void larnv(
    int64_t idist,
    int64_t* iseed, int64_t n,
    std::complex<float>* X )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(idist) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int idist_ = (lapack_int) idist;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > iseed_( &iseed[0], &iseed[(4)] );
        lapack_int* iseed_ptr = &iseed_[0];
    #else
        lapack_int* iseed_ptr = (lapack_int*) iseed;
    #endif
    lapack_int n_ = (lapack_int) n;

    clarnv_(
        &idist_,
        iseed_ptr, &n_,
        (lapack_complex_float*) X );
    #ifndef LAPACK_ILP64
        std::copy( iseed_.begin(), iseed_.end(), iseed );
    #endif
}

// -----------------------------------------------------------------------------
/// Returns a vector of n random complex numbers from a uniform or
/// normal distribution.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
///
/// @param[in] idist
///     The distribution of the random numbers:
///     - 1: real and imaginary parts each uniform (0,1)
///     - 2: real and imaginary parts each uniform (-1,1)
///     - 3: real and imaginary parts each normal (0,1)
///     - 4: uniformly distributed on the disc abs(z) < 1
///     - 5: uniformly distributed on the circle abs(z) = 1
///
/// @param[in,out] iseed
///     The vector iseed of length 4.
///     On entry, the seed of the random number generator; the array
///     elements must be between 0 and 4095, and iseed(4) must be
///     odd.
///     On exit, the seed is updated.
///
/// @param[in] n
///     The number of random numbers to be generated.
///
/// @param[out] X
///     The vector X of length n.
///     The generated random numbers.
///
// -----------------------------------------------------------------------------
/// @par Further Details
///
/// This routine calls the auxiliary routine `lapack::laruv` to generate random
/// real numbers from a uniform (0,1) distribution, in batches of up to
/// 128 using vectorisable code. The Box-Muller method is used to
/// transform numbers from a uniform to a normal distribution.
///
/// @ingroup initialize
void larnv(
    int64_t idist,
    int64_t* iseed, int64_t n,
    std::complex<double>* X )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(idist) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int idist_ = (lapack_int) idist;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > iseed_( &iseed[0], &iseed[(4)] );
        lapack_int* iseed_ptr = &iseed_[0];
    #else
        lapack_int* iseed_ptr = (lapack_int*) iseed;
    #endif
    lapack_int n_ = (lapack_int) n;

    zlarnv_(
        &idist_,
        iseed_ptr, &n_,
        (lapack_complex_double*) X );
    #ifndef LAPACK_ILP64
        std::copy( iseed_.begin(), iseed_.end(), iseed );
    #endif
}

}  // namespace lapack
