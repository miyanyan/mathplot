/*
 * Voronoi grid on a more or less rectangular grid
 *
 * Author Seb James
 * Date 2024
 */
#include <iostream>
#include <sm/vec>
#include <sm/random>
#include <mplot/Visual.h>
#include <mplot/VoronoiVisual.h>

static constexpr int n_side = 3;
static constexpr int n_points = n_side * n_side;

int main()
{
    int rtn = -1;

    mplot::Visual v(1024, 768, "VoronoiVisual");

    sm::rand_uniform<float> rngxy(-2.0f, 2.0f, 1000);
    sm::rand_uniform<float> rngz(0.8f, 1.0f, 1000);

    // make n_points random coordinates
    std::vector<sm::vec<float>> points(n_points);
    std::vector<float> data(n_points);

    for (unsigned int i = 0; i < n_side; ++i) {
        for (unsigned int j = 0; j < n_side; ++j) {
            points[i + n_side * j] = { i * 0.05f, j * 0.05f, 0.0f };
            //data[i + n_side * j] = static_cast<float>(i + n_side * j) / n_side * n_side;
            unsigned int ri = i + n_side * j;
            data[ri] = 0.05f + 0.05f * std::sin(20.0f * points[ri][0]) * std::sin(10.0f*points[ri][1]) ; // Range 0->1
            points[ri][2] = data[ri];
        }
    }

    mplot::ColourMapType cmap_t = mplot::ColourMapType::Plasma;

    sm::vec<float, 3> offset = { 0.0f };
    auto vorv = std::make_unique<mplot::VoronoiVisual<float>> (offset);
    v.bindmodel (vorv);
    vorv->show_voronoi2d = false; // true to show the 2D voronoi edges
    vorv->debug_dataCoords = false; // true to show coordinate spheres
    vorv->debug_edges = false;
    float length_scale = 0.5f / n_side;
    vorv->border_width  = length_scale;
    vorv->cm.setType (cmap_t);
    vorv->setDataCoords (&points);
    vorv->setScalarData (&data);
    vorv->finalize();
    v.addVisualModel (vorv);
    v.keepOpen();
    return rtn;
}
