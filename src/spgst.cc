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
int64_t spgst(
    int64_t itype, lapack::Uplo uplo, int64_t n,
    float* AP,
    float const* BP )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(itype) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int itype_ = (lapack_int) itype;
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    sspgst_(
        &itype_, &uplo_, &n_,
        AP,
        BP, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t spgst(
    int64_t itype, lapack::Uplo uplo, int64_t n,
    double* AP,
    double const* BP )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(itype) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
    }
    lapack_int itype_ = (lapack_int) itype;
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int info_ = 0;

    dspgst_(
        &itype_, &uplo_, &n_,
        AP,
        BP, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
