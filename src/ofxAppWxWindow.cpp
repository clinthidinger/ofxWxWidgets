
#include "ofxAppWxWindow.h"
#include <assert.h>

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "ofBaseApp.h"
#include "ofEvents.h"
#include "ofUtils.h"
#include "ofGraphics.h"
#include "ofAppRunner.h"
#include "ofConstants.h"
#include "ofxWxGLCanvas.h"

#ifndef _WIN32
#ifdef __MACH__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif
#endif



//----------------------------------------------------------
ofxAppWxWindow::ofxAppWxWindow(wxWindow *glCanvasParent)
{
   windowMode			= OF_WINDOW;
   nFramesSinceWindowResized = 0;
   bEnableSetupScreen = true;
   ofAppPtr          = NULL;
   glCanvas          = NULL;
   glCanvasSizer     = NULL;
   glCanvasParentWnd = glCanvasParent;
   topParent         = NULL;
   if(glCanvasParentWnd != NULL)
   {
      topParent = dynamic_cast<wxFrame *>(::wxGetTopLevelParent(glCanvasParentWnd));
   }
}

//------------------------------------------------------------
ofxAppWxWindow::~ofxAppWxWindow()
{
    //! @note wx frame will delete it's childrend when destroy is called.
    destroy();
}

//------------------------------------------------------------
void ofxAppWxWindow::destroy()
{
    //glCanvas->DoEnable(false);
    glCanvas->Destroy();
    glCanvas = NULL;
}

//------------------------------------------------------------
void ofxAppWxWindow::setDoubleBuffering(bool _bDoubleBuffered)
{
    
}

//------------------------------------------------------------
void ofxAppWxWindow::setupOpenGL(int w, int h, int screenMode)
{
    if(glCanvas != NULL)
    {
        glCanvas->Destroy();
        glCanvas = NULL;
    }
    
    if((glCanvas == NULL) && (this->glCanvasParentWnd != NULL))
    {
#if defined(TARGET_WIN32) && (WINVER == 0x0701) 
        //! @see http://wiki.wxwidgets.org/WxGLCanvas#Multiple_wxGLCanvases
        //! @note Reparent hack that seems necessary on Windoze 7 at the time of testing.
        wxFrame *frame = new wxFrame(NULL, wxID_ANY, wxT("Hack")); //! @note Not supposed to make a frame on the stack.  Mem should be cleaned when frame is destroyed.
        assert(frame != NULL);
        glCanvas = new ofxWxGLCanvas(frame, w, h);
        assert(glCanvas != NULL);
        frame->Show();
        glCanvas->SetCurrent(*this->glCanvas->GetGLContex());
        glCanvas->Reparent(this->glCanvasParentWnd);
        frame->Close();
        frame->Destroy();
        frame = NULL;
#else
        glCanvas = new ofxWxGLCanvas(this->glCanvasParentWnd, w, h);
        assert(glCanvas != NULL);
        glCanvas->SetCurrent(*this->glCanvas->GetGLContex()); 
#if defined(TARGET_LINUX)
        static bool glutInitialized = false;
        if (!glutInitialized)
        {
          char *myargv [1];
          int myargc=1;
          myargv [0]=strdup ("ofxAppWxWindow");
          glutInit(&myargc, myargv);
        }
#endif


#endif
        // Add sizer.
        this->glCanvasSizer = new wxBoxSizer(wxVERTICAL);
        assert(this->glCanvasSizer != NULL);
        glCanvasSizer->Add(this->glCanvas, 1, wxEXPAND | wxGROW | wxALL, 0);
        this->glCanvasParentWnd->SetSizer(this->glCanvasSizer);
    }// end if
}

//------------------------------------------------------------
void ofxAppWxWindow::initializeWindow()
{
   nFramesSinceWindowResized = 0;

   ofRectangle viewport;
   viewport.x = 0;
   viewport.y = 0;
   viewport.width  = glCanvas->GetClientSize().x;
   viewport.height = glCanvas->GetClientSize().y;

   ofViewport(viewport);
   ofSetupScreen();
   ofFill();
   ofSetColor(220);
}

//------------------------------------------------------------
void ofxAppWxWindow::runAppViaInfiniteLoop(ofBaseApp * appPtr)
{
	ofAppPtr = appPtr;
    
	ofNotifySetup();
	ofNotifyUpdate();
}

//------------------------------------------------------------
float ofxAppWxWindow::getFrameRate()
{
	return glCanvas->getFrameRate();
}

//------------------------------------------------------------
double ofxAppWxWindow::getLastFrameTime()
{
	return glCanvas->getLastFrameTime();
}

//------------------------------------------------------------
int ofxAppWxWindow::getFrameNum()
{
	return glCanvas->getFrameCount();
}

//------------------------------------------------------------
void ofxAppWxWindow::setWindowTitle(string title)
{
    if(topParent != NULL)
    {
        topParent->SetTitle(title);
    }
}

//------------------------------------------------------------
ofPoint ofxAppWxWindow::getWindowSize()
{
    wxSize size(glCanvas->GetClientSize());
    return ofPoint(size.x, size.y, 0);
}

//------------------------------------------------------------
ofPoint ofxAppWxWindow::getWindowPosition()
{
    wxRect rect(glCanvas->GetClientRect());
    return ofPoint(rect.x, rect.y, 0);
}

//------------------------------------------------------------
ofPoint ofxAppWxWindow::getScreenSize()
{
	wxSize size(glCanvas->GetClientSize());
    return ofPoint(size.x, size.y, 0);
}

//------------------------------------------------------------
int ofxAppWxWindow::getWidth()
{
   ofOrientation orientation = glCanvas->GetOrientation();
   if(orientation == OF_ORIENTATION_DEFAULT || orientation == OF_ORIENTATION_180)
   {
      return ofGetViewportWidth();
   }
   return ofGetViewportHeight();
}

//------------------------------------------------------------
int ofxAppWxWindow::getHeight()
{
   ofOrientation orientation = glCanvas->GetOrientation();
   if(orientation == OF_ORIENTATION_DEFAULT || orientation == OF_ORIENTATION_180)
   {
      return ofGetViewportHeight();
   }
   return ofGetViewportWidth();
}

//------------------------------------------------------------
void ofxAppWxWindow::setOrientation(ofOrientation orientationIn)
{
	glCanvas->SetOrientation(orientationIn);
}

//------------------------------------------------------------
ofOrientation ofxAppWxWindow::getOrientation()
{
	return glCanvas->GetOrientation();
}

//------------------------------------------------------------
void ofxAppWxWindow::setWindowPosition(int x, int y)
{
	wxPoint point(x, y);
    glCanvas->SetPosition(point);
}

//------------------------------------------------------------
void ofxAppWxWindow::setWindowShape(int w, int h)
{
    glCanvas->SetClientSize(w, h);
    initializeWindow();
    glCanvas->Fit();
}

//------------------------------------------------------------
void ofxAppWxWindow::hideCursor()
{
    // Does this need to happen when we enter the canvas?
    if (windowMode == OF_FULLSCREEN)
    {
        glCanvas->SetCursor(wxCursor(wxCURSOR_BLANK));
    }
    else
    {
        glCanvas->SetCursor(wxNullCursor);
    }
}

//------------------------------------------------------------
void ofxAppWxWindow::showCursor()
{
    glCanvas->SetCursor(*wxSTANDARD_CURSOR);
}

//------------------------------------------------------------
void ofxAppWxWindow::setFrameRate(float targetRate)
{
    glCanvas->setFrameRate(targetRate);
}

//------------------------------------------------------------
int ofxAppWxWindow::getWindowMode()
{
	return windowMode;
}

//------------------------------------------------------------
void ofxAppWxWindow::toggleFullscreen()
{
	if(windowMode == OF_GAME_MODE)
    {
        return;
    }
    
	if(windowMode == OF_WINDOW )
    {
		windowMode = OF_FULLSCREEN;
    }
    else
    {
		windowMode = OF_WINDOW;
	}
    if(topParent != NULL)
    {
        topParent->ShowFullScreen(windowMode == OF_FULLSCREEN);
    }
}

//------------------------------------------------------------
void ofxAppWxWindow::setFullscreen(bool fullscreen)
{
    if(windowMode == OF_GAME_MODE)
    {
        return;
    }
    
    if(topParent != NULL)
    {
        topParent->ShowFullScreen(fullscreen);
    }
    
    if(fullscreen && windowMode != OF_FULLSCREEN)
    {
        windowMode = OF_FULLSCREEN;
    }
    else if(!fullscreen && windowMode != OF_WINDOW)
    {
        windowMode = OF_WINDOW;
    }
}

//------------------------------------------------------------
void ofxAppWxWindow::enableSetupScreen()
{
	bEnableSetupScreen = true;
}

//------------------------------------------------------------
void ofxAppWxWindow::disableSetupScreen()
{
	bEnableSetupScreen = false;
}
