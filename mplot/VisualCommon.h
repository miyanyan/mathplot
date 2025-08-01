#pragma once

/*
 * Common code for GL functionality in mplotologica programs.
 *
 * Author: Seb James.
 */

#include <stdexcept>
#include <iostream>
#include <cstring>
#include <sm/vec>
#include <mplot/tools.h>

namespace mplot {

    namespace visgl {

        // A container struct for the shader program identifiers used in a mplot::Visual. Separate
        // from mplot::Visual so that it can be used in mplot::VisualModel as well, which does not
        // #include mplot/Visual.h.
        struct visual_shaderprogs
        {
            //! An OpenGL shader program for graphical objects
            unsigned int /*GLuint*/ gprog = 0;
            //! A text shader program, which uses textures to draw text on quads.
            unsigned int /*GLuint*/ tprog = 0;
        };

        // This defines different graphics shader types, as used in mplot::Visual. The essential
        // difference between the current shaders is that they render different projection types
        enum class graphics_shader_type
        {
            none,         // Unset/unknown graphics shader type
            projection2d, // both orthographic and perspective projections to a 2D surface
            cylindrical,  // A cylindrical projection
            spherical     // not implemented, but we could have a spherical projection
        };

        //! The locations for the position, normal and colour vertex attributes in the
        //! mplot::Visual GLSL programs
        enum AttribLocn { posnLoc = 0, normLoc = 1, colLoc = 2, textureLoc = 3 };

        //! A struct to hold information about font glyph properties
        struct CharInfo
        {
            //! ID handle of the glyph texture
            unsigned int textureID;
            //! Size of glyph
            sm::vec<int,2>  size;
            //! Offset from baseline to left/top of glyph
            sm::vec<int,2>  bearing;
            //! Offset to advance to next glyph
            unsigned int advance;
        };

    } // namespace gl
} // namespace
