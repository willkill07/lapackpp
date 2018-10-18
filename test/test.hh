#ifndef TEST_HH
#define TEST_HH

#include "libtest.hh"
#include "lapack_util.hh"
#include "matrix_params.hh"
#include "matrix_generator.hh"

// -----------------------------------------------------------------------------
class Params: public libtest::ParamsBase
{
public:
    const double inf = std::numeric_limits<double>::infinity();
    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double pi  = 3.141592653589793;
    const double e   = 2.718281828459045;

    Params();

    void get_range(
        int64_t n, lapack::Range* range,
        double* vl, double* vu,
        int64_t* il, int64_t* iu );

    void get_range(
        int64_t n, lapack::Range* range,
        float* vl, float* vu,
        int64_t* il, int64_t* iu );

    // Field members are explicitly public.
    // Order here determines output order.

    // ----- test matrix parameters
    MatrixParams matrix;
    MatrixParams matrixB;

    // ----- test framework parameters
    libtest::ParamChar   check;
    libtest::ParamChar   error_exit;
    libtest::ParamChar   ref;
    libtest::ParamDouble tol;
    libtest::ParamInt    repeat;
    libtest::ParamInt    verbose;
    libtest::ParamInt    cache;

    // ----- routine parameters
    libtest::ParamEnum< libtest::DataType > datatype;
    libtest::ParamEnum< blas::Layout >      layout;
    libtest::ParamEnum< lapack::Side >      side;
    libtest::ParamInt                       itype;
    libtest::ParamEnum< lapack::Uplo >      uplo;
    libtest::ParamEnum< lapack::Op >        trans;
    libtest::ParamEnum< lapack::Op >        transA;
    libtest::ParamEnum< lapack::Op >        transB;
    libtest::ParamEnum< lapack::Diag >      diag;
    libtest::ParamEnum< lapack::Norm >      norm;
    libtest::ParamEnum< lapack::Direct >    direct;
    libtest::ParamEnum< lapack::StoreV >    storev;
    libtest::ParamEnum< lapack::Job >       jobz;   // heev
    libtest::ParamEnum< lapack::Job >       jobvl;  // geev
    libtest::ParamEnum< lapack::Job >       jobvr;  // geev
    libtest::ParamEnum< lapack::Job >       jobu;   // gesvd, gesdd
    libtest::ParamEnum< lapack::Job >       jobvt;  // gesvd
    libtest::ParamEnum< lapack::Range >     range;
    libtest::ParamEnum< lapack::MatrixType > matrixtype;
    libtest::ParamEnum< lapack::Factored >  factored;
    libtest::ParamEnum< lapack::Equed >     equed;

    libtest::ParamInt3   dim;
    libtest::ParamInt    l;
    libtest::ParamInt    kd;
    libtest::ParamInt    kl;
    libtest::ParamInt    ku;
    libtest::ParamInt    nrhs;
    libtest::ParamInt    nb;
    libtest::ParamDouble vl;
    libtest::ParamDouble vu;
    libtest::ParamInt    il;
    libtest::ParamInt    il_out;
    libtest::ParamInt    iu;
    libtest::ParamInt    iu_out;
    libtest::ParamDouble fraction_start;
    libtest::ParamDouble fraction;
    libtest::ParamDouble alpha;
    libtest::ParamDouble beta;
    libtest::ParamInt    incx;
    libtest::ParamInt    incy;
    libtest::ParamInt    align;

    // ----- output parameters
    libtest::ParamScientific error;
    libtest::ParamScientific error2;
    libtest::ParamScientific error3;
    libtest::ParamScientific error4;
    libtest::ParamScientific error5;
    libtest::ParamScientific ortho;
    libtest::ParamScientific ortho_U;
    libtest::ParamScientific ortho_V;
    libtest::ParamScientific error_sigma;

    libtest::ParamDouble     time;
    libtest::ParamDouble     gflops;
    libtest::ParamInt        iters;

    libtest::ParamDouble     ref_time;
    libtest::ParamDouble     ref_gflops;
    libtest::ParamInt        ref_iters;

    libtest::ParamOkay       okay;
};

// -----------------------------------------------------------------------------
template< typename T >
inline T roundup( T x, T y )
{
    return T( (x + y - 1) / y ) * y;
}

// -----------------------------------------------------------------------------
#define assert_throw( expr, exception_type ) \
    try { \
        expr; \
        fprintf( stderr, "Error: didn't throw expected exception at %s:%d\n", \
                 __FILE__, __LINE__ ); \
        throw std::exception(); \
    } \
    catch (exception_type& err) { \
        if (verbose >= 3) { \
            printf( "Caught expected exception: %s\n", err.what() ); \
        } \
    }

// -----------------------------------------------------------------------------
// LAPACK
// LU, general
void test_gesv  ( Params& params, bool run );
void test_gesvx ( Params& params, bool run );
void test_getrf ( Params& params, bool run );
void test_getri ( Params& params, bool run );
void test_getrs ( Params& params, bool run );
void test_gecon ( Params& params, bool run );
void test_gerfs ( Params& params, bool run );
void test_geequ ( Params& params, bool run );

// LU, band
void test_gbsv  ( Params& params, bool run );
void test_gbsvx ( Params& params, bool run );
void test_gbtrf ( Params& params, bool run );
void test_gbtrs ( Params& params, bool run );
void test_gbcon ( Params& params, bool run );
void test_gbrfs ( Params& params, bool run );
void test_gbequ ( Params& params, bool run );

// LU, tridiagonal
void test_gtsv  ( Params& params, bool run );
void test_gtsvx ( Params& params, bool run );
void test_gttrf ( Params& params, bool run );
void test_gttrs ( Params& params, bool run );
void test_gtcon ( Params& params, bool run );
void test_gtrfs ( Params& params, bool run );
void test_gtequ ( Params& params, bool run );

// Cholesky
void test_posv  ( Params& params, bool run );
void test_posvx ( Params& params, bool run );
void test_potrf ( Params& params, bool run );
void test_potri ( Params& params, bool run );
void test_potrs ( Params& params, bool run );
void test_pocon ( Params& params, bool run );
void test_porfs ( Params& params, bool run );
void test_poequ ( Params& params, bool run );

// Cholesky, packed
void test_ppsv  ( Params& params, bool run );
void test_pptrf ( Params& params, bool run );
void test_pptrs ( Params& params, bool run );
void test_pptri ( Params& params, bool run );
void test_ppcon ( Params& params, bool run );
void test_pprfs ( Params& params, bool run );
void test_ppequ ( Params& params, bool run );

// Cholesky, band
void test_pbsv  ( Params& params, bool run );
void test_pbtrf ( Params& params, bool run );
void test_pbtrs ( Params& params, bool run );
void test_pbcon ( Params& params, bool run );
void test_pbrfs ( Params& params, bool run );
void test_pbequ ( Params& params, bool run );

// Cholesky, tridiagonal
void test_ptsv  ( Params& params, bool run );
void test_pttrf ( Params& params, bool run );
void test_pttrs ( Params& params, bool run );
void test_ptcon ( Params& params, bool run );
void test_ptrfs ( Params& params, bool run );

// symmetric indefinite
void test_sysv  ( Params& params, bool run );
void test_sytrf ( Params& params, bool run );
void test_sytrs ( Params& params, bool run );
void test_sytri ( Params& params, bool run );
void test_sycon ( Params& params, bool run );
void test_syrfs ( Params& params, bool run );

// symmetric indefinite, packed
void test_spsv  ( Params& params, bool run );
void test_sptrf ( Params& params, bool run );
void test_sptrs ( Params& params, bool run );
void test_sptri ( Params& params, bool run );
void test_spcon ( Params& params, bool run );
void test_sprfs ( Params& params, bool run );

// symmetric indefinite, rook pivoting
void test_sysv_rook          ( Params& params, bool run );
void test_sytrf_rook         ( Params& params, bool run );
void test_sytrs_rook         ( Params& params, bool run );
void test_sytri_rook         ( Params& params, bool run );

// symmetric indefinite, Aasen's
void test_sysv_aa            ( Params& params, bool run );
void test_sytrf_aa           ( Params& params, bool run );
void test_sytrs_aa           ( Params& params, bool run );
void test_sytri_aa           ( Params& params, bool run );

// symmetric indefinite, Aasen's 2-stage
void test_sysv_aasen_2stage  ( Params& params, bool run );
void test_sytrf_aasen_2stage ( Params& params, bool run );
void test_sytrs_aasen_2stage ( Params& params, bool run );
void test_sytri_aasen_2stage ( Params& params, bool run );

// symmetric indefinite, rook pivoting, >= lapack 3.7
void test_sysv_rk            ( Params& params, bool run );
void test_sytrf_rk           ( Params& params, bool run );
void test_sytrs_rk           ( Params& params, bool run );
void test_sytri_rk           ( Params& params, bool run );

// hermetian
void test_hesv  ( Params& params, bool run );
void test_hetrf ( Params& params, bool run );
void test_hetrs ( Params& params, bool run );
void test_hetri ( Params& params, bool run );
void test_hecon ( Params& params, bool run );
void test_herfs ( Params& params, bool run );

// hermetian, packed
void test_hpsv  ( Params& params, bool run );
void test_hptrf ( Params& params, bool run );
void test_hptrs ( Params& params, bool run );
void test_hptri ( Params& params, bool run );
void test_hpcon ( Params& params, bool run );
void test_hprfs ( Params& params, bool run );

// matrix norms
void test_lange ( Params& params, bool run );
void test_lanhe ( Params& params, bool run );
void test_lansy ( Params& params, bool run );
void test_lantr ( Params& params, bool run );

void test_lanhp ( Params& params, bool run );
void test_lansp ( Params& params, bool run );
void test_lantp ( Params& params, bool run );

void test_langb ( Params& params, bool run );
void test_lanhb ( Params& params, bool run );
void test_lansb ( Params& params, bool run );
void test_lantb ( Params& params, bool run );

void test_langt ( Params& params, bool run );
void test_lanht ( Params& params, bool run );
void test_lanst ( Params& params, bool run );

// least squares
void test_gels  ( Params& params, bool run );
void test_gelsy ( Params& params, bool run );
void test_gelsd ( Params& params, bool run );
void test_gelss ( Params& params, bool run );
void test_getsls( Params& params, bool run );
void test_gglse ( Params& params, bool run );
void test_ggglm ( Params& params, bool run );

// QR, LQ, QL, RQ
void test_geqrf ( Params& params, bool run );
void test_gelqf ( Params& params, bool run );
void test_geqlf ( Params& params, bool run );
void test_gerqf ( Params& params, bool run );

void test_ggqrf ( Params& params, bool run );
void test_gglqf ( Params& params, bool run );
void test_ggqlf ( Params& params, bool run );
void test_ggrqf ( Params& params, bool run );

void test_ungqr ( Params& params, bool run );
void test_unglq ( Params& params, bool run );
void test_ungql ( Params& params, bool run );
void test_ungrq ( Params& params, bool run );

void test_unmqr ( Params& params, bool run );
void test_unmlq ( Params& params, bool run );
void test_unmql ( Params& params, bool run );
void test_unmrq ( Params& params, bool run );

// triangle-pentagon QR, LQ
void test_tpqrt ( Params& params, bool run );
void test_tplqt ( Params& params, bool run );

void test_tpqrt2( Params& params, bool run );
void test_tplqt2( Params& params, bool run );

void test_tpmqrt( Params& params, bool run );
void test_tpmlqt( Params& params, bool run );

void test_tprfb ( Params& params, bool run );

// symmetric eigenvalues
void test_heev  ( Params& params, bool run );
void test_heevx ( Params& params, bool run );
void test_heevd ( Params& params, bool run );
void test_heevr ( Params& params, bool run );
void test_hetrd ( Params& params, bool run );
void test_ungtr ( Params& params, bool run );
void test_unmtr ( Params& params, bool run );

void test_hpev  ( Params& params, bool run );
void test_hpevx ( Params& params, bool run );
void test_hpevd ( Params& params, bool run );
void test_hpevr ( Params& params, bool run );
void test_hptrd ( Params& params, bool run );
void test_upgtr ( Params& params, bool run );
void test_upmtr ( Params& params, bool run );

void test_hbev  ( Params& params, bool run );
void test_hbevx ( Params& params, bool run );
void test_hbevd ( Params& params, bool run );
void test_hbevr ( Params& params, bool run );
void test_hbtrd ( Params& params, bool run );
void test_obgtr ( Params& params, bool run );
void test_obmtr ( Params& params, bool run );

// generalized symmetric eigenvalues
void test_hegv  ( Params& params, bool run );
void test_hegvx ( Params& params, bool run );
void test_hegvd ( Params& params, bool run );
void test_hegvr ( Params& params, bool run );
void test_hegst ( Params& params, bool run );

void test_hpgv  ( Params& params, bool run );
void test_hpgvx ( Params& params, bool run );
void test_hpgvd ( Params& params, bool run );
void test_hpgvr ( Params& params, bool run );
void test_hpgst ( Params& params, bool run );

void test_hbgv  ( Params& params, bool run );
void test_hbgvx ( Params& params, bool run );
void test_hbgvd ( Params& params, bool run );
void test_hbgvr ( Params& params, bool run );
void test_hbgst ( Params& params, bool run );

// Implements the QZ method for finding the generalized eigenvalues of the matrix pair (H,T).
void test_hgeqz ( Params& params, bool run );

// nonsymmetric eigenvalues
void test_geev  ( Params& params, bool run );
void test_geevx ( Params& params, bool run );
void test_gees  ( Params& params, bool run );
void test_geesx ( Params& params, bool run );
void test_gehrd ( Params& params, bool run );
void test_unghr ( Params& params, bool run );
void test_unmhr ( Params& params, bool run );
void test_hsein ( Params& params, bool run );
void test_trevc ( Params& params, bool run );

// generalized nonsymmetric eigenvalues
void test_ggev  ( Params& params, bool run );
void test_ggevx ( Params& params, bool run );
void test_gges  ( Params& params, bool run );
void test_ggesx ( Params& params, bool run );

// SVD
void test_gesvd ( Params& params, bool run );
void test_gesdd ( Params& params, bool run );
void test_gesvdx( Params& params, bool run );
void test_gesvd_2stage ( Params& params, bool run );
void test_gesdd_2stage ( Params& params, bool run );
void test_gesvdx_2stage( Params& params, bool run );
void test_gejsv ( Params& params, bool run );
void test_gesvj ( Params& params, bool run );

// auxiliary
void test_lacpy ( Params& params, bool run );
void test_laset ( Params& params, bool run );
void test_laswp ( Params& params, bool run );

// auxiliary - Householder
void test_larfg ( Params& params, bool run );
void test_larf  ( Params& params, bool run );
void test_larfx ( Params& params, bool run );
void test_larfb ( Params& params, bool run );
void test_larft ( Params& params, bool run );

// auxiliary - norms
void test_lange ( Params& params, bool run );
void test_lanhe ( Params& params, bool run );
void test_lansy ( Params& params, bool run );
void test_lantr ( Params& params, bool run );

// auxiliary - matrix generation
void test_lagge ( Params& params, bool run );
void test_lagsy ( Params& params, bool run );
void test_laghe ( Params& params, bool run );
void test_lagtr ( Params& params, bool run );

// additional BLAS
void test_syr   ( Params& params, bool run );

#endif  //  #ifndef TEST_HH
