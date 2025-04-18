/*
 * This example shows you how to write simulation data out using HdfData
 *
 * Author: Seb James
 * Date: September 2021
 */

#include <morph/hdfdata.h>
#include <vector>
#include <deque>
#include <iostream>
#include <morph/vvec.h>

int main()
{
    // Write data into the file test.h5
    std::vector<double> vd = { 10.0, 12.0, 13.0, 14.0 };
    {
        morph::hdfdata data("test.h5", std::ios::out | std::ios::trunc);
        data.add_contained_vals ("/testvectordouble", vd);
    } // data closes when out of scope

    // Read data from test.h5 into the container vdread.
    std::deque<double> vdread;
    {
        morph::hdfdata data("test.h5", std::ios::in);
        data.read_contained_vals ("/testvectordouble", vdread);
    }

    for (auto d : vdread) {
        std::cout << "Read the number " << d << " from test.h5...\n";
    }

    // Create a file containing a sequence of floating point numbers
    {
        morph::hdfdata dseq("dseq.h5", std::ios::out | std::ios::trunc);
        morph::vvec<float> theseq (256, 0.0f);
        for (int i = 0; i < 256; i++) { theseq[i] = 1.0f * i; }
        dseq.add_contained_vals ("/theseq", theseq);
    }

    return 0;
}
