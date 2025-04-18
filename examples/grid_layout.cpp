/*
 * An example program showing you how the indices are arranged in Grids with different orders. This
 * prints out the grid to stdout for inspection.
 */
#include "morph/grid.h"
#include <iostream>

int main()
{
    morph::vec<float, 2> dx = { 1, 1 };
    morph::vec<float, 2> offset = { 0, 0 };

    morph::griddomainwrap wrap = morph::griddomainwrap::none;

    morph::grid<int, float> g_bltr(4, 2, dx, offset, wrap, morph::gridorder::bottomleft_to_topright);
    morph::grid<int, float> g_tlbr(4, 2, dx, offset, wrap, morph::gridorder::topleft_to_bottomright);
    morph::grid<int, float> g_bltrc(4, 2, dx, offset, wrap, morph::gridorder::bottomleft_to_topright_colmaj);
    morph::grid<int, float> g_tlbrc(4, 2, dx, offset, wrap, morph::gridorder::topleft_to_bottomright_colmaj);

    std::cout << "Calling grid::str() for a width 4, height 2 grid (different orders; offset (0,0)):\n\n";
    std::cout << g_bltr.str() << std::endl;
    std::cout << g_tlbr.str() << std::endl;
    std::cout << g_bltrc.str() << std::endl;
    std::cout << g_tlbrc.str() << std::endl;
    return 0;
}
