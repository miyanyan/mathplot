/*!
 * \file
 *
 * Declares a VisualResource class to hold the information about Freetype and any other
 * one-per-program resources.
 *
 * \author Seb James
 * \date November 2020
 */

#pragma once

#include <mplot/VisualFaceMX.h>
#include <mplot/VisualResourcesBase.h>
#include <mplot/gl/util_mx.h>

namespace mplot {

    // Pointers to mplot::VisualBase are used to index font faces
    template<int>
    class VisualBase;

    //! Singleton resource class for mplot::Visual scenes.
    template <int glver>
    class VisualResourcesMX : public VisualResourcesBase<glver>
    {
    private:
        VisualResourcesMX(){}
        ~VisualResourcesMX() { this->faces.clear(); }

        //! The collection of VisualFaces generated for this instance of the
        //! application. Create one VisualFace for each unique combination of VisualFont
        //! and fontpixels (the texture resolution)
        std::map<std::tuple<mplot::VisualFont, unsigned int, mplot::VisualBase<glver>*>,
                 std::unique_ptr<mplot::visgl::VisualFaceMX>> faces;
    public:
        VisualResourcesMX(const VisualResourcesMX<glver>&) = delete;
        VisualResourcesMX& operator=(const VisualResourcesMX<glver> &) = delete;
        VisualResourcesMX(VisualResourcesMX<glver> &&) = delete;
        VisualResourcesMX & operator=(VisualResourcesMX<glver> &&) = delete;

        //! Initialize a freetype library instance and add to this->freetypes. I wanted
        //! to have only a single freetype library instance, but this didn't work, so I
        //! create one FT_Library for each OpenGL context (i.e. one for each mplot::Visual
        //! window). Thus, arguably, the FT_Library should be a member of mplot::Visual,
        //! but that's a task for the future, as I coded it this way under the false
        //! assumption that I'd only need one FT_Library.
        void freetype_init (mplot::VisualBase<glver>* _vis, GladGLContext* glfn = nullptr)
        {
            FT_Library freetype = nullptr;
            try {
                freetype = this->freetypes.at (_vis);
            } catch (const std::out_of_range&) {
                // Use of gl calls here may make it neat to set up GL here in VisualResources?
                glfn->PixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
                mplot::gl::Util::checkError (__FILE__, __LINE__, glfn);

                if (FT_Init_FreeType (&freetype)) {
                    std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
                } else {
                    // Successfully initialized freetype
                    this->freetypes[_vis] = freetype;
                }
            }
        }

        //! The instance public function. Uses the very short name 'i' to keep code tidy.
        //! This relies on C++11 magic statics (N2660).
        static auto& i()
        {
            static VisualResourcesMX<glver> instance;
            return instance;
        }

        //! A function to call to simply make sure the singleton instance exists
        void create() final {}

        //! Return a pointer to a VisualFace for the given \a font at the given texture
        //! resolution, \a fontpixels and the given window (i.e. OpenGL context) \a _win.
        mplot::visgl::VisualFaceMX* getVisualFace (mplot::VisualFont font, unsigned int fontpixels,
                                                   mplot::VisualBase<glver>* _vis, GladGLContext* glfn)
        {
            mplot::visgl::VisualFaceMX* rtn = nullptr;
            auto key = std::make_tuple(font, fontpixels, _vis);
            try {
                rtn = this->faces.at(key).get();
            } catch (const std::out_of_range&) {
                this->faces[key] = std::make_unique<mplot::visgl::VisualFaceMX> (font, fontpixels, this->freetypes.at(_vis), glfn);
                rtn = this->faces.at(key).get();
            }
            return rtn;
        }

        mplot::visgl::VisualFaceMX* getVisualFace (const mplot::TextFeatures& tf,
                                                   mplot::VisualBase<glver>* _vis, GladGLContext* glfn)
        {
            return this->getVisualFace (tf.font, tf.fontres, _vis, glfn);
        }

        //! Loop through this->faces clearing out those associated with the given mplot::Visual
        void clearVisualFaces (mplot::VisualBase<glver>* _vis) final
        {
            auto f = this->faces.begin();
            while (f != this->faces.end()) {
                // f->first is a key. If its third, Visual<>* element == _vis, then delete and erase
                if (std::get<mplot::VisualBase<glver>*>(f->first) == _vis) {
                    f = this->faces.erase (f);
                } else { f++; }
            }
        }
    };

} // namespace mplot
