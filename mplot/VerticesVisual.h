#pragma once

// Create a visual model directly from indices, vertices and normals, which might have been
// harvested from a file (glTF, for example)

#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>

#include <sm/vec>

#include <mplot/VisualModel.h>

namespace mplot {

    template<int glver = mplot::gl::version_4_1>
    class VerticesVisual : public VisualModel<glver>
    {
    public:
        VerticesVisual (sm::mat44<float>& _model_transform,
                        sm::vvec<uint32_t> _ind,
                        sm::vvec<sm::vec<float>> _posn,
                        sm::vvec<sm::vec<float>> _norm,
                        sm::vvec<sm::vec<float>> _colr)
        {
            this->viewmatrix = _model_transform;
            this->mv_offset = _model_transform.translation();
            this->mv_rotation = _model_transform.rotation();
            for (auto i : _ind) { this->indices.push_back (i); }
            for (auto p : _posn) {
                this->vertexPositions.push_back (p[0]);
                this->vertexPositions.push_back (p[1]);
                this->vertexPositions.push_back (p[2]);
            }
            for (auto n : _norm) {
                this->vertexNormals.push_back (n[0]);
                this->vertexNormals.push_back (n[1]);
                this->vertexNormals.push_back (n[2]);
            }
            for (auto c : _colr) {
                this->vertexColors.push_back (c[0]);
                this->vertexColors.push_back (c[1]);
                this->vertexColors.push_back (c[2]);
            }
        }

        // No op, as data is given in constructor
        void initializeVertices() { std::cout << "VerticesVisual::initializeVertices called" << std::endl; }
    };

} // namespace mplot
