// Compute a Gaussian with a vvec
#include <sm/vec>
#include <sm/vvec>
#include <morph/Visual.h>
#include <morph/GraphVisual.h>

int main()
{
    sm::vvec<double> x;
    double sigma = 1.5;
    unsigned int nsigma = 3;
    double hw = sigma * nsigma;
    x.linspace (-hw, hw, 60);
    sm::vvec<double> y = x.gauss (sigma);

    // Graph x and y
    morph::Visual v(1024, 768, "1D convolutions with sm::vvec");
    auto gv = std::make_unique<morph::GraphVisual<double>> (sm::vec<float>({0,0,0}));
    v.bindmodel (gv);
    gv->setdata (x, y, "gauss");
    gv->finalize();
    v.addVisualModel (gv);
    v.keepOpen();

    return 0;
}
