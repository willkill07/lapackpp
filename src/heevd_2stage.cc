// Copyright (c) 2017-2023, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "lapack.hh"
#include "lapack/fortran.h"
#include "NoConstructAllocator.hh"

#if LAPACK_VERSION >= 30700  // >= 3.7

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup heev
int64_t heevd_2stage(
    lapack::Job jobz, lapack::Uplo uplo, int64_t n,
    std::complex<float>* A, int64_t lda,
    float* W )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char jobz_ = to_char( jobz );
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    float qry_rwork[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    cheevd_2stage_(
        &jobz_, &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        W,
        (lapack_complex_float*) qry_work, &ineg_one,
        qry_rwork, &ineg_one,
        qry_iwork, &ineg_one, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);
    lapack_int lrwork_ = real(qry_rwork[0]);
    lapack_int liwork_ = real(qry_iwork[0]);

    // allocate workspace
    lapack::vector< std::complex<float> > work( lwork_ );
    lapack::vector< float > rwork( lrwork_ );
    lapack::vector< lapack_int > iwork( liwork_ );

    cheevd_2stage_(
        &jobz_, &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        W,
        (lapack_complex_float*) &work[0], &lwork_,
        &rwork[0], &lrwork_,
        &iwork[0], &liwork_, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Computes all eigenvalues and, optionally, eigenvectors of a
/// Hermitian matrix A using the 2-stage technique for
/// the reduction to tridiagonal. If eigenvectors are desired, it uses a
/// divide and conquer algorithm.
///
/// The divide and conquer algorithm makes very mild assumptions about
/// floating point arithmetic. It will work on machines with a guard
/// digit in add/subtract, or on those binary machines without guard
/// digits which subtract like the Cray X-MP, Cray Y-MP, Cray C-90, or
/// Cray-2. It could conceivably fail on hexadecimal or decimal machines
/// without guard digits, but we know of none.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
/// For real matrices, this is an alias for `lapack::syevd_2stage`.
///
/// @param[in] jobz
///     - lapack::Job::NoVec: Compute eigenvalues only;
///     - lapack::Job::Vec:   Compute eigenvalues and eigenvectors.
///                           Not yet available (as of LAPACK 3.8.0).
///
/// @param[in] uplo
///     - lapack::Uplo::Upper: Upper triangle of A is stored;
///     - lapack::Uplo::Lower: Lower triangle of A is stored.
///
/// @param[in] n
///     The order of the matrix A. n >= 0.
///
/// @param[in,out] A
///     The n-by-n matrix A, stored in an lda-by-n array.
///     On entry, the Hermitian matrix A.
///     - If uplo = Upper, the
///     leading n-by-n upper triangular part of A contains the
///     upper triangular part of the matrix A.
///
///     - If uplo = Lower,
///     the leading n-by-n lower triangular part of A contains
///     the lower triangular part of the matrix A.
///
///     - On exit, if jobz = Vec, then if successful, A contains the
///     orthonormal eigenvectors of the matrix A.
///     If jobz = NoVec, then on exit the lower triangle (if uplo=Lower)
///     or the upper triangle (if uplo=Upper) of A, including the
///     diagonal, is destroyed.
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= max(1,n).
///
/// @param[out] W
///     The vector W of length n.
///     If successful, the eigenvalues in ascending order.
///
/// @return = 0: successful exit
/// @return > 0: if return value = i and jobz = NoVec, then the algorithm failed
///              to converge; i off-diagonal elements of an intermediate
///              tridiagonal form did not converge to zero;
///              if return value = i and jobz = Vec, then the algorithm failed
///              to compute an eigenvalue while working on the submatrix
///              lying in rows and columns info/(n+1) through
///              mod(info,n+1).
///
// -----------------------------------------------------------------------------
/// @par Further Details
///
/// All details about the 2-stage techniques are available in:
///
/// Azzam Haidar, Hatem Ltaief, and Jack Dongarra.
/// Parallel reduction to condensed forms for symmetric eigenvalue problems
/// using aggregated fine-grained and memory-aware kernels. In Proceedings
/// of 2011 International Conference for High Performance Computing,
/// Networking, Storage and Analysis (SC '11), New York, NY, USA,
/// Article 8, 11 pages.
/// http://doi.acm.org/10.1145/2063384.2063394
///
/// A. Haidar, J. Kurzak, P. Luszczek, 2013.
/// An improved parallel singular value algorithm and its implementation
/// for multicore hardware, In Proceedings of 2013 International Conference
/// for High Performance Computing, Networking, Storage and Analysis (SC '13).
/// Denver, Colorado, USA, 2013.
/// Article 90, 12 pages.
/// http://doi.acm.org/10.1145/2503210.2503292
///
/// A. Haidar, R. Solca, S. Tomov, T. Schulthess and J. Dongarra.
/// A novel hybrid CPU-GPU generalized eigensolver for electronic structure
/// calculations based on fine-grained memory aware tasks.
/// International Journal of High Performance Computing Applications.
/// Volume 28 Issue 2, Pages 196-209, May 2014.
/// http://hpc.sagepub.com/content/28/2/196
///
/// @ingroup heev
int64_t heevd_2stage(
    lapack::Job jobz, lapack::Uplo uplo, int64_t n,
    std::complex<double>* A, int64_t lda,
    double* W )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char jobz_ = to_char( jobz );
    char uplo_ = to_char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    double qry_rwork[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    zheevd_2stage_(
        &jobz_, &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        W,
        (lapack_complex_double*) qry_work, &ineg_one,
        qry_rwork, &ineg_one,
        qry_iwork, &ineg_one, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);
    lapack_int lrwork_ = real(qry_rwork[0]);
    lapack_int liwork_ = real(qry_iwork[0]);

    // allocate workspace
    lapack::vector< std::complex<double> > work( lwork_ );
    lapack::vector< double > rwork( lrwork_ );
    lapack::vector< lapack_int > iwork( liwork_ );

    zheevd_2stage_(
        &jobz_, &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        W,
        (lapack_complex_double*) &work[0], &lwork_,
        &rwork[0], &lrwork_,
        &iwork[0], &liwork_, &info_
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack

#endif  // LAPACK >= 3.7
