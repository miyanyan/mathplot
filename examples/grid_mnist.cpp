/*
 * GridVisual to view an Mnist char
 */

#include <iostream>

#include <sm/vec>
#include <sm/vvec>
#include <sm/grid>

#include <morph/Visual.h>
#include <morph/GridVisual.h>
#include <morph/Mnist.h>

int main (int argc, char** argv)
{
    // Load MNIST data
    morph::Mnist mni(std::string("../standalone_examples/neuralnet/mnist/"));

    int index = 0;
    if (argc > 1) { index = std::stoi(std::string(argv[1])); }

    // Get a specific example
    auto [ id, label, data ] = mni.test_example (index);

    // Create a scene
    morph::Visual v(1280, 1280, "Mnist char");
    // Create a Grid for visualising the numeral...
    constexpr sm::vec<float, 2> grid_spacing = {0.05f, 0.05f};
    sm::grid g(28u, 28u, grid_spacing);

    // Create a visual for the numeral in it's as-written Cartesian representation
    sm::vec<float> offset = {0,0,0};
    auto gv0 = std::make_unique<morph::GridVisual<float>>(&g, offset);
    v.bindmodel (gv0);
    gv0->gridVisMode = morph::GridVisMode::RectInterp;
    gv0->setScalarData (&data);
    gv0->cm.setType (morph::ColourMapType::Berlin);
    gv0->zScale.setParams (-0.1, 0);
    gv0->addLabel(std::to_string(label) + ", Id " + std::to_string(id), sm::vec<float, 3>({0.0f,-0.13f,0.0f}), morph::TextFeatures(0.1f));
    gv0->finalize();

    v.addVisualModel (gv0);
    v.keepOpen();

    return 0;
}
