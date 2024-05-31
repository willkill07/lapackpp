// Copyright (c) 2017-2023, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include <stdio.h>

#if defined(BLAS_HAVE_MKL) || defined(LAPACK_HAVE_MKL)
    #if (defined(BLAS_ILP64) || defined(LAPACK_ILP64)) && ! defined(MKL_ILP64)
        #define MKL_ILP64
    #endif
    #include <mkl_cblas.h>

#elif defined(BLAS_HAVE_ESSL) || defined(LAPACK_HAVE_ESSL)
    #if (defined(BLAS_ILP64) || defined(LAPACK_ILP64)) && ! defined(_ESV6464)
        #define _ESV6464
    #endif
    #include <essl.h>

#elif defined(BLAS_HAVE_ACCELERATE) || defined(LAPACK_HAVE_ACCELERATE)
    // On macOS, the official way to include cblas is via Accelerate.h.
    // Unfortunately with Xcode 10.3 and GNU g++ 9.3, that doesn't compile.
    // If we can find cblas.h, use it, otherwise use Accelerate.h.
    #if defined(BLAS_HAVE_ACCELERATE_CBLAS_H) || defined(LAPACK_HAVE_ACCELERATE_CBLAS_H)
        #include <cblas.h>
    #else
        #define ACCELERATE_NEW_LAPACK 1
        #include <Accelerate/Accelerate.h>
    #endif

#else
    #ifdef __cplusplus
        // Some ancient cblas.h don't include extern C. It's okay to nest.
        extern "C" {
        #include <cblas.h>
        }
    #else
        #include <cblas.h>
    #endif
#endif

int main()
{
    int n = 5;
    double x[] = { 1, 2, 3, 4, 5 };
    double y[] = { 5, 4, 3, 2, 1 };
    double result = cblas_ddot( n, x, 1, y, 1 );
    bool okay = (result == 35);
    printf( "%s\n", okay ? "ok" : "failed" );
    return ! okay;
}
