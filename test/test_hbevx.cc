#include "test.hh"
#include "lapack.hh"
#include "lapack_flops.hh"
#include "print_matrix.hh"
#include "error.hh"

#include <vector>

// -----------------------------------------------------------------------------
// simple overloaded wrappers around LAPACKE
static lapack_int LAPACKE_hbevx(
    char jobz, char range, char uplo, lapack_int n, lapack_int kd, float* AB, lapack_int ldab, float* Q, lapack_int ldq, float vl, float vu, lapack_int il, lapack_int iu, float abstol, lapack_int* m, float* W, float* Z, lapack_int ldz, lapack_int* ifail )
{
    return LAPACKE_ssbevx( LAPACK_COL_MAJOR, jobz, range, uplo, n, kd, AB, ldab, Q, ldq, vl, vu, il, iu, abstol, m, W, Z, ldz, ifail );
}

static lapack_int LAPACKE_hbevx(
    char jobz, char range, char uplo, lapack_int n, lapack_int kd, double* AB, lapack_int ldab, double* Q, lapack_int ldq, double vl, double vu, lapack_int il, lapack_int iu, double abstol, lapack_int* m, double* W, double* Z, lapack_int ldz, lapack_int* ifail )
{
    return LAPACKE_dsbevx( LAPACK_COL_MAJOR, jobz, range, uplo, n, kd, AB, ldab, Q, ldq, vl, vu, il, iu, abstol, m, W, Z, ldz, ifail );
}

static lapack_int LAPACKE_hbevx(
    char jobz, char range, char uplo, lapack_int n, lapack_int kd, std::complex<float>* AB, lapack_int ldab, std::complex<float>* Q, lapack_int ldq, float vl, float vu, lapack_int il, lapack_int iu, float abstol, lapack_int* m, float* W, std::complex<float>* Z, lapack_int ldz, lapack_int* ifail )
{
    return LAPACKE_chbevx( LAPACK_COL_MAJOR, jobz, range, uplo, n, kd, AB, ldab, Q, ldq, vl, vu, il, iu, abstol, m, W, Z, ldz, ifail );
}

static lapack_int LAPACKE_hbevx(
    char jobz, char range, char uplo, lapack_int n, lapack_int kd, std::complex<double>* AB, lapack_int ldab, std::complex<double>* Q, lapack_int ldq, double vl, double vu, lapack_int il, lapack_int iu, double abstol, lapack_int* m, double* W, std::complex<double>* Z, lapack_int ldz, lapack_int* ifail )
{
    return LAPACKE_zhbevx( LAPACK_COL_MAJOR, jobz, range, uplo, n, kd, AB, ldab, Q, ldq, vl, vu, il, iu, abstol, m, W, Z, ldz, ifail );
}

// -----------------------------------------------------------------------------
template< typename scalar_t >
void test_hbevx_work( Params& params, bool run )
{
    using namespace libtest;
    using namespace blas;
    typedef typename traits< scalar_t >::real_t real_t;
    typedef long long lld;

    // get & mark input values
    lapack::Job jobz = params.jobz.value();
    lapack::Uplo uplo = params.uplo.value();
    int64_t n = params.dim.n();
    int64_t kd = params.kd.value();
    int64_t align = params.align.value();

    lapack::Range range;
    real_t  vl;  // = params.vl.value();
    real_t  vu;  // = params.vu.value();
    int64_t il;  // = params.il.value();
    int64_t iu;  // = params.iu.value();
    params.get_range( n, &range, &vl, &vu, &il, &iu );

    // mark non-standard output values
    params.ref_time.value();
    // params.ref_gflops.value();
    // params.gflops.value();

    if (! run)
        return;

    // ---------- setup
    int64_t ldab = roundup( kd + 1, align );
    int64_t ldq = roundup( max( 1, n ), align );
    real_t abstol = 0; // use default
    int64_t m_tst;
    lapack_int m_ref;
    int64_t ldz = ( jobz==lapack::Job::NoVec ? 1: roundup( max( 1, n ), align ) );
    size_t size_AB = (size_t) ldab * n;
    size_t size_Q = (size_t) ldq * n;
    size_t size_W = (size_t) (n);
    size_t size_Z = (size_t) ldz * max(1,n);
    size_t size_ifail = (size_t) (n);

    std::vector< scalar_t > AB_tst( size_AB );
    std::vector< scalar_t > AB_ref( size_AB );
    std::vector< scalar_t > Q_tst( size_Q );
    std::vector< scalar_t > Q_ref( size_Q );
    std::vector< real_t > W_tst( size_W );
    std::vector< real_t > W_ref( size_W );
    std::vector< scalar_t > Z_tst( size_Z );
    std::vector< scalar_t > Z_ref( size_Z );
    std::vector< int64_t > ifail_tst( size_ifail );
    std::vector< lapack_int > ifail_ref( size_ifail );

    int64_t idist = 1;
    int64_t iseed[4] = { 0, 1, 2, 3 };
    lapack::larnv( idist, iseed, AB_tst.size(), &AB_tst[0] );
    AB_ref = AB_tst;

    // ---------- run test
    libtest::flush_cache( params.cache.value() );
    double time = get_wtime();
    int64_t info_tst = lapack::hbevx( jobz, range, uplo, n, kd, &AB_tst[0], ldab, &Q_tst[0], ldq, vl, vu, il, iu, abstol, &m_tst, &W_tst[0], &Z_tst[0], ldz, &ifail_tst[0] );
    time = get_wtime() - time;
    if (info_tst != 0) {
        fprintf( stderr, "lapack::hbevx returned error %lld\n", (lld) info_tst );
    }

    params.time.value() = time;
    // double gflop = lapack::Gflop< scalar_t >::hbevx( jobz, range, n, kd );
    // params.gflops.value() = gflop / time;

    if (params.ref.value() == 'y' || params.check.value() == 'y') {
        // ---------- run reference
        libtest::flush_cache( params.cache.value() );
        time = get_wtime();
        int64_t info_ref = LAPACKE_hbevx( job2char(jobz), range2char(range), uplo2char(uplo), n, kd, &AB_ref[0], ldab, &Q_ref[0], ldq, vl, vu, il, iu, abstol, &m_ref, &W_ref[0], &Z_ref[0], ldz, &ifail_ref[0] );
        time = get_wtime() - time;
        if (info_ref != 0) {
            fprintf( stderr, "LAPACKE_hbevx returned error %lld\n", (lld) info_ref );
        }

        params.ref_time.value() = time;
        // params.ref_gflops.value() = gflop / time;

        // ---------- check error compared to reference
        real_t error = 0;
        if (info_tst != info_ref) {
            error = 1;
        }
        error += abs_error( AB_tst, AB_ref );
        error += abs_error( Q_tst, Q_ref );
        error += std::abs( m_tst - m_ref );
        error += abs_error( W_tst, W_ref );
        error += abs_error( Z_tst, Z_ref );
        // for ifail, just compare the first m_tst values
        for ( size_t i = 0; i < (size_t)m_tst; i++ )
            error += std::abs( ifail_tst[i] - ifail_ref[i] );
        params.error.value() = error;
        params.okay.value() = (error == 0);  // expect lapackpp == lapacke
    }
}

// -----------------------------------------------------------------------------
void test_hbevx( Params& params, bool run )
{
    switch (params.datatype.value()) {
        case libtest::DataType::Integer:
            throw std::exception();
            break;

        case libtest::DataType::Single:
            test_hbevx_work< float >( params, run );
            break;

        case libtest::DataType::Double:
            test_hbevx_work< double >( params, run );
            break;

        case libtest::DataType::SingleComplex:
            test_hbevx_work< std::complex<float> >( params, run );
            break;

        case libtest::DataType::DoubleComplex:
            test_hbevx_work< std::complex<double> >( params, run );
            break;
    }
}
