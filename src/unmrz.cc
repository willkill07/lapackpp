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
int64_t unmrz(
    lapack::Side side, lapack::Op trans, int64_t m, int64_t n, int64_t k, int64_t l,
    std::complex<float> const* A, int64_t lda,
    std::complex<float> const* tau,
    std::complex<float>* C, int64_t ldc )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(l) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldc) > std::numeric_limits<lapack_int>::max() );
    }
    char side_ = to_char( side );
    char trans_ = to_char( trans );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int l_ = (lapack_int) l;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldc_ = (lapack_int) ldc;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    lapack_int ineg_one = -1;
    cunmrz_(
        &side_, &trans_, &m_, &n_, &k_, &l_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) C, &ldc_,
        (lapack_complex_float*) qry_work, &ineg_one, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< std::complex<float> > work( lwork_ );

    cunmrz_(
        &side_, &trans_, &m_, &n_, &k_, &l_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) C, &ldc_,
        (lapack_complex_float*) &work[0], &lwork_, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t unmrz(
    lapack::Side side, lapack::Op trans, int64_t m, int64_t n, int64_t k, int64_t l,
    std::complex<double> const* A, int64_t lda,
    std::complex<double> const* tau,
    std::complex<double>* C, int64_t ldc )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(l) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldc) > std::numeric_limits<lapack_int>::max() );
    }
    char side_ = to_char( side );
    char trans_ = to_char( trans );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int l_ = (lapack_int) l;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldc_ = (lapack_int) ldc;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    lapack_int ineg_one = -1;
    zunmrz_(
        &side_, &trans_, &m_, &n_, &k_, &l_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) C, &ldc_,
        (lapack_complex_double*) qry_work, &ineg_one, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    lapack::vector< std::complex<double> > work( lwork_ );

    zunmrz_(
        &side_, &trans_, &m_, &n_, &k_, &l_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) C, &ldc_,
        (lapack_complex_double*) &work[0], &lwork_, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
