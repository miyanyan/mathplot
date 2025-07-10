// Demo Zernike polynomials

#include <format>
#include <complex>
#include <sm/mathconst>
#include <sm/algo>
#include <sm/vvec>
#include <mplot/Visual.h>
#include <mplot/PolarVisual.h>

int main()
{
    // You can require that n - |m| is even to "ensure the rotational invariant property is met"
    // (see https://doi.org/10.7554/eLife.54026, p 18)
    constexpr bool require_n_minus_abs_m_even = false;

    using mc = sm::mathconst<double>;

    mplot::Visual<> v (1024, 768, "Zernike Polynomials");

    constexpr std::size_t N = 200;
    sm::vvec<double> rho;
    rho.linspace (0.0, 1.0, N);

    sm::vvec<double> theta;
    theta.linspace (0.0, mc::two_pi, N);

    for (unsigned int n = 0; n < 20; ++n) {

        for (int m = 0; m <= static_cast<int>(n); ++m) {

            if constexpr (require_n_minus_abs_m_even) { if ((n - std::abs(m)) % 2 != 0) { continue; } }

            auto pv = std::make_unique<mplot::PolarVisual<double>> (sm::vec<float>{1.1f * n, 1.1f * m, 0});
            v.bindmodel (pv);
            pv->cm.setType (mplot::ColourMapType::Cork);
            pv->setFrameTextColour (mplot::colour::goldenrod1);
            pv->radius = 0.5f;
            pv->tf.fontsize = 0.0f;
            pv->zScale.reset();
            pv->zScale.do_autoscale = true;
            pv->numrings = N;
            pv->numsegs = N;
            pv->addLabel (std::format ("n{}, m{}", n, m), sm::vec<float>{-0.1,-0.58,0}, mplot::TextFeatures(0.08f));
            pv->twodimensional = false;

            sm::vvec<double> Vnm_real;
            for (auto rh : rho) {
                double r_nm = sm::algo::zern_radial_poly (n, m, rh);
                for (auto th : theta) {
                    Vnm_real.push_back (std::real(sm::algo::zern_polynomial (m, r_nm, th)));
                }
            }
            pv->setScalarData (&Vnm_real);

            pv->finalize();
            v.addVisualModel (pv);
        }
    }

    v.keepOpen();
}
