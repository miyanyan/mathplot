// Visualize a graph. Minimal example showing how a default graph appears
#include <mplot/VisualNoMX.h>
#include <mplot/GraphVisual.h>
#include <sm/vec>
#include <sm/vvec>

int main()
{
    // Set up a mplot::Visual 'scene environment'.
    mplot::VisualNoMX v(1024, 768, "Made with mplot::GraphVisual"); // global GL function aliases with VisualNoMX
    // Create a GraphVisual object (obtaining a unique_ptr to the object) with a spatial offset within the scene of 0,0,0
    auto gv = std::make_unique<mplot::GraphVisual<double>> (sm::vec<float, 3>{0.0f});
    // This mandatory line of boilerplate code sets the parent pointer in GraphVisual and binds some functions
    v.bindmodel (gv);
    // Data for the x axis. A vvec is like std::vector, but with built-in maths methods
    sm::vvec<double> x;
    // This works like numpy's linspace() (the 3 args are "start", "end" and "num"):
    x.linspace (-0.5, 0.8, 14);
    // Set a graph up of y = x^3
    gv->setdata (x, x.pow(3));
    // finalize() makes the GraphVisual compute the vertices of the OpenGL model
    gv->finalize();
    // Add the GraphVisual OpenGL model to the Visual scene, transferring ownership of the unique_ptr
    v.addVisualModel (gv);
    // Render the scene on the screen until user quits with 'Ctrl-q'
    v.keepOpen();
    // Because v owns the unique_ptr to the GraphVisual, its memory will be deallocated when v goes out of scope.
    return 0;
}
