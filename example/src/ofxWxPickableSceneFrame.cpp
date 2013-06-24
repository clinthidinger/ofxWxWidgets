
#include "ofxWxPickableSceneFrame.h"
#include <assert.h>
#include <ofxAppWxWindow.h>
#include <ofxWxGLCanvas.h>
#include "testApp.h"



//-----------------------------------------------------------------------------
ofxWxPickableSceneFrame::ofxWxPickableSceneFrame(wxWindow *parent) 
   : ofxWxPickableSceneFrameBase(parent),
     window(NULL)
{

}

//-----------------------------------------------------------------------------
ofxWxPickableSceneFrame::~ofxWxPickableSceneFrame()
{
    if(window != NULL)
    {
        delete window;
        window = NULL;
    }
}

//-----------------------------------------------------------------------------
void ofxWxPickableSceneFrame::OnHiButtonClick(wxCommandEvent &event)
{

}

//-----------------------------------------------------------------------------
void ofxWxPickableSceneFrame::initRendering()
{
    wxWindow *glCanvasParent = FindWindowByName("glCanvasParentPanel");
    assert(glCanvasParent != NULL);
    wxSize canvasSize = glCanvasParent->GetSize();
    window = new ofxAppWxWindow(glCanvasParent);
    assert(window != NULL);
    ofSetupOpenGL(window, 800, 600, OF_WINDOW);
    glCanvasParent->SetMaxClientSize(wxSize(800, 600));
    glCanvasParent->SetMaxSize(wxSize(800, 600));
    glCanvasParent->Fit();
    
    window->getWxGLCanvas()->Show();
    window->getWxGLCanvas()->Raise();
    
    // Force resize to get things to snap in place.
    wxSize size = GetSize();
    SetSize(size.x - 1, size.y - 1);
    
    ofRunApp(new testApp(window)); // Will be deleted on exit.
}
