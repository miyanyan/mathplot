/*
 * An example morph::Visual scene, containing a Gridv, and using GridvVisual
 */

#include <iostream>
#include <vector>
#include <cmath>

#include <sm/vec>
#include <sm/vvec>
#include <sm/grid>

#include <morph/Visual.h>
#include <morph/VisualDataModel.h>
#include <morph/GridVisual.h>

int main()
{
    morph::Visual v(1600, 1000, "morph::GridVisual");

#ifdef ORTHOGRAPHIC
    // Here's how to set your Visual to do an orthographic projection rather than perspective
    v.ptype = morph::perspective_type::orthographic;
#endif

    // Create a grid to show in the scene
    constexpr unsigned int Nside = 10;
    constexpr sm::vec<float, 2> grid_spacing = {0.1f, 0.1f};

    // The simplest declaration of Grid is:
    //   sm::Grid g(size_t n_x, size_t n_y);
    // grid_spacing, grid_zero, use of memory, wrapping and ordering are all possible arguments to
    // the constructor.
    sm::grid grid(Nside, Nside, grid_spacing);

    std::cout << "Number of pixels in grid:" << grid.n() << std::endl;

    // Make some dummy data (random values) to make an interesting surface
    sm::vvec<float> data(grid.n());
    data.randomize();

    float step = 0.6f;
    // Add a GridVisual to display the Grid within the morph::Visual scene
    sm::vec<float, 3> offset = { -step * grid.width(), -step * grid.width(), 0.0f };

    auto gv = std::make_unique<morph::GridVisual<float>>(&grid, offset);
    v.bindmodel (gv);
    gv->gridVisMode = morph::GridVisMode::Triangles;
    gv->setScalarData (&data);
    gv->cm.setType (morph::ColourMapType::Twilight);
    gv->addLabel ("GridVisMode::Triangles", sm::vec<float>({0,-0.1,0}), morph::TextFeatures(0.05f));
    gv->finalize();
    v.addVisualModel (gv);

    offset = { step * grid.width(), -step * grid.width(), 0.0f };
    gv = std::make_unique<morph::GridVisual<float>>(&grid, offset);
    v.bindmodel (gv);
    gv->gridVisMode = morph::GridVisMode::RectInterp;
    gv->setScalarData (&data);
    gv->cm.setType (morph::ColourMapType::Twilight);
    gv->addLabel ("GridVisMode::RectInterp", sm::vec<float>({0,-0.1,0}), morph::TextFeatures(0.05f));
    gv->finalize();
    v.addVisualModel (gv);

    offset = { -step * grid.width(), step * grid.width(), 0.0f };
    gv = std::make_unique<morph::GridVisual<float>>(&grid, offset);
    v.bindmodel (gv);
    gv->gridVisMode = morph::GridVisMode::Columns;
    gv->interpolate_colour_sides (true);
    gv->setScalarData (&data);
    gv->cm.setType (morph::ColourMapType::Twilight);
    gv->addLabel ("GridVisMode::Columns, interpolated sides", sm::vec<float>({0,-0.1,0}), morph::TextFeatures(0.05f));
    gv->finalize();
    v.addVisualModel (gv);

    offset = { step * grid.width(), step * grid.width(), 0.0f };
    gv = std::make_unique<morph::GridVisual<float>>(&grid, offset);
    v.bindmodel (gv);
    gv->gridVisMode = morph::GridVisMode::Columns;
    //gv->interpolate_colour_sides = false; // default
    //gv->clr_east_column = morph::colour::black; // These are defaults but you can change them
    //gv->clr_north_column = morph::colour::black;
    gv->setScalarData (&data);
    gv->cm.setType (morph::ColourMapType::Twilight);
    gv->addLabel ("GridVisMode::Columns, black sides", sm::vec<float>({0,-0.1,0}), morph::TextFeatures(0.05));
    gv->finalize();
    v.addVisualModel (gv);

    offset = { 3 * step * grid.width(), step * grid.width(), 0.0f };
    gv = std::make_unique<morph::GridVisual<float>>(&grid, offset);
    v.bindmodel (gv);
    gv->gridVisMode = morph::GridVisMode::Pixels;
    gv->setScalarData (&data);
    gv->cm.setType (morph::ColourMapType::Twilight);
    gv->addLabel ("GridVisMode::Pixels", sm::vec<float>({0,-0.1,0}), morph::TextFeatures(0.05));
    gv->finalize();
    v.addVisualModel (gv);

    v.keepOpen();

    return 0;
}
