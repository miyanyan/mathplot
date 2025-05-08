#include <sm/vec>
#include <mplot/Visual.h>
#include <mplot/RhomboVisual.h>

int main()
{
    // Create a scene
    mplot::Visual v(1024, 768, "A rhombohedron");
    v.showCoordArrows (true); // Please show the coord arrows by default
    v.lightingEffects();

    // Parameters of the model
    sm::vec<float, 3> offset = { 0,  0,  0 };   // a within-scene offset
    sm::vec<float, 3> e1 = { 0.25,  0,  0 };
    sm::vec<float, 3> e2 = { 0.1,  0.25,  0 };
    sm::vec<float, 3> e3 = { 0,  0.0,  0.25 };
    sm::vec<float, 3> colour1 = { 0.35,  0.76,  0.98 };  // RGB colour triplet

    auto rv = std::make_unique<mplot::RhomboVisual<>> (offset, e1, e2, e3, colour1);
    v.bindmodel (rv);
    rv->finalize();
    v.addVisualModel (rv);
    v.keepOpen();

    return 0;
}
