/*!
 * \file Visualize the contents of a mplot::Config
 */

#pragma once

#include <mplot/Config.h>
#include <mplot/VisualModel.h>
#include <mplot/vec.h>
#include <mplot/tools.h>
#include <mplot/TextFeatures.h>
#include <mplot/TextGeometry.h>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>

namespace mplot {

    template<int glver = mplot::gl::version_4_1>
    class ConfigVisual : public VisualModel<glver>
    {
    public:
        ConfigVisual (const mplot::Config* _conf,
                      const std::vector<std::string>& _keys,
                      const mplot::vec<float, 3>& _offset,
                      const mplot::TextFeatures& _tfeatures)
        {
            // Set up...
            this->mv_offset = _offset;
            this->viewmatrix.translate (this->mv_offset);
            this->conf = _conf;
            this->keys = _keys;
            this->tfeatures = _tfeatures;
        }

        void initializeVertices()
        {
            if (conf == nullptr) { return; }
            if (!conf->ready) { return; }

            mplot::vec<float> toffset = {0,0,0};

            // No op, but add text labels for parameters in the config
            for (auto key : this->keys) {
                // For now get value in float format
                float value = conf->get<float>(key, 0.0f);
                std::string lbl = key + std::string(": ") + std::to_string(value);
                mplot::TextGeometry geom = this->addLabel (lbl, toffset, this->tfeatures);
                toffset[1] -= line_spacing * geom.height();
            }
        }

        // You must define the things you want to visualize from the Config. You
        // probably don't want *everything* right?
        std::vector<std::string> keys;

        // The Config thing that you'll get text from
        const mplot::Config* conf = nullptr;

        // How to format the text
        mplot::TextFeatures tfeatures;

        // Spacing between lines of output
        float line_spacing = 1.5f;
    };

} // namespace mplot
