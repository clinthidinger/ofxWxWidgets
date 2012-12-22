
#include <assert.h>
#include "ofMain.h"

#include <wx/wxprec.h>
#include <wx/dir.h>
#ifndef WX_PRECOMP
      #include <wx/wx.h>
#endif

#include "ofxWxPickableSceneFrame.h"

//! @brief WxWidgets openframeworks application.
class ofWxApp : public wxApp
{
public:
    //! @brief Constructor.
    ofWxApp() { }
    virtual ~ofWxApp() { }

    //! @brief Initializer.
    //! @return Success or failure.
    virtual bool OnInit();

    //! @brief Clean things up on exit.
    virtual int OnExit();

private:
   ofxWxPickableSceneFrame *testFrame;
};

//-----------------------------------------------------------------------------
bool ofWxApp::OnInit()
{
   if(!wxApp::OnInit())
   {
      return false;
   }

   testFrame = new ofxWxPickableSceneFrame(NULL);
   assert(testFrame != NULL);
   testFrame->Layout();
   testFrame->Show();
   testFrame->Raise();
   testFrame->initRendering();
   SetTopWindow(testFrame);

   return true;
}

//-----------------------------------------------------------------------------
int ofWxApp::OnExit()
{
   // App will delete top window for us.
   return 0;
}

IMPLEMENT_APP(ofWxApp)
