#include <wx/wx.h>

#define GLAD_GL_IMPLEMENTATION
#include <mplot/glad/gl.h> // must be included before glcanvas.h

#include <wx/glcanvas.h>

#include <wx/colordlg.h>

#include <sm/vec>

#include <mplot/gl/version.h>
#include <mplot/wx/viswx.h>
#include <mplot/TriaxesVisual.h>

constexpr int gl_version = mplot::gl::version_4_1; // options in mplot/gl/version.h

// Your application-specific frame, deriving from mplot::wx:Frame. In this frame, I'll set up VisualModels
class MyFrame : public mplot::wx::Frame<gl_version>
{
public:
    MyFrame(const wxString &title) : mplot::wx::Frame<gl_version>(title)
    {
        auto sizer = new wxBoxSizer(wxVERTICAL);
        // Adding ONLY the GL canvas, where all the mplotologica stuff will be drawn
        sizer->Add (this->canvas, 1, wxEXPAND);
        SetSizerAndFit(sizer);
    }

    // To set up the VisualModels in the widget, the GL context must have been initialized. So I'll
    // have to have a callback in viswidget (soon to be viscanvas) which will call this function
    // after gl init has completed.
    void setupVisualModels()
    {
        if (this->canvas->ready()) {
            auto tav = std::make_unique<mplot::TriaxesVisual<float, gl_version>> (sm::vec<float,3>({0,0,0}));
            this->canvas->v.bindmodel (tav);
            tav->axisstyle = mplot::axisstyle::L;
            // Specify axes min and max with a min and max vector
            //                                         x      y       z
            tav->input_min = sm::vec<float, 3>({ -1.0f,  0.0f,   0.0f });
            tav->input_max = sm::vec<float, 3>({  1.0f, 10.0f, 100.0f });
            // Set the axis labels
            tav->xlabel = "x";
            tav->ylabel = "y";
            tav->zlabel = "z";
            tav->finalize();
            this->canvas->v.addVisualModel (tav);
        } else {
            // Not ready
            throw std::runtime_error ("Canvas is not ready (no gl context yet)");
        }
    }

};

// Your app, containing your frame
class MyApp : public wxApp
{
public:
    MyApp() {}
    bool OnInit();
};

bool MyApp::OnInit()
{
    if (!wxApp::OnInit()) { return false; }
    MyFrame *frame = new MyFrame("mplot::TriaxesVisual");
    frame->Show(true);
    frame->setupVisualModels(); // After calling Show()
    return true;
}

wxIMPLEMENT_APP(MyApp);
