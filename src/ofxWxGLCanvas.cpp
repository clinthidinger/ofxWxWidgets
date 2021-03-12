
#include "ofxWxGLCanvas.h"
#include <assert.h>
#include <wx/wxprec.h>
#include <wx/dir.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "ofBaseApp.h"
#include "ofEvents.h"
#include "ofUtils.h"
#include "ofGraphics.h"
#include "ofAppRunner.h"
#include "ofConstants.h"



BEGIN_EVENT_TABLE(ofxWxGLCanvas, wxGLCanvas)
EVT_SIZE(ofxWxGLCanvas::OnSize)
EVT_PAINT(ofxWxGLCanvas::OnPaint)
EVT_IDLE(ofxWxGLCanvas::OnIdle)
EVT_ERASE_BACKGROUND(ofxWxGLCanvas::OnEraseBackground)
EVT_MOUSE_EVENTS(ofxWxGLCanvas::OnMouse)
EVT_KEY_DOWN(ofxWxGLCanvas::OnKeyDown)
EVT_KEY_UP(ofxWxGLCanvas::OnKeyUp)
EVT_DROP_FILES(ofxWxGLCanvas::OnDropFiles)
END_EVENT_TABLE()

//----------------------------------------------------------
ofxWxGLCanvas::ofxWxGLCanvas(wxWindow *parent, int width, int height)
   : wxGLCanvas(parent, wxID_ANY, wxPoint(-1, -1), wxSize(width, height), wxSUNKEN_BORDER, wxT("Viewport"), NULL)
{
    timeNow          = 0;
    timeThen         = 0;
    fps              = 60.0; //give a realistic starting value - win32 issues
    frameRate        = 60.0;
    framesForFPS     = 0;
    bFrameRateSet    = false;
    millisForFrame   = 0;
    prevMillis	     = 0;
    diffMillis	     = 0;
    lastFrameTime    = 0.0;
    nFrameCount      = 0;
    bDoubleBuffered  = true;
    
    // Explicitly create a new rendering context instance for this canvas.
    wxGLRC = new wxGLContext(this);
    assert(wxGLRC != NULL);
    bDoAutoRedraw = true;
    bDoKeyTranslate  = true;
    orientation = OF_ORIENTATION_DEFAULT;
    DragAcceptFiles(true);
    Connect(wxEVT_DROP_FILES, wxDropFilesEventHandler(ofxWxGLCanvas::OnDropFiles), NULL, this);
}

//----------------------------------------------------------
ofxWxGLCanvas::~ofxWxGLCanvas()
{
    if(wxGLRC != NULL)
    {
        delete wxGLRC;
        wxGLRC = NULL;
    }
}

//----------------------------------------------------------
void ofxWxGLCanvas::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    // This is required even though dc is not used otherwise.
    wxPaintDC dc(this);
    draw();
    
    //if(bDoAutoRedraw)
    //{
    //  Refresh(false);
    //}
    
    return;
}

//----------------------------------------------------------
void ofxWxGLCanvas::OnSize(wxSizeEvent &event)
{
    wxSize size = event.GetSize();
    wxGLCanvas::OnSize(event);
    SetCurrent(*wxGLRC);
    ofViewport(0, 0, size.x, size.y);
    ofSetupScreen();
    ofNotifyWindowResized(size.x, size.y);
}

//----------------------------------------------------------
void ofxWxGLCanvas::OnIdle(wxIdleEvent & event)
{
    //! @note Copy and paste code from ofAppGlutWindow.
   SetCurrent(*wxGLRC);

   if (nFrameCount != 0 && bFrameRateSet == true)
   {
      diffMillis = ofGetElapsedTimeMillis() - prevMillis;
      if (diffMillis > millisForFrame)
      {
         // we do nothing, we are already slower than target frame
      }
      else
      {
         int waitMillis = millisForFrame - diffMillis;
#ifdef TARGET_WIN32
         Sleep(waitMillis);         //windows sleep in milliseconds
#else
         usleep(waitMillis * 1000);   //mac sleep in microseconds - cooler :)
#endif
      }
   }
   prevMillis = ofGetElapsedTimeMillis(); // you have to measure here

   // -------------- fps calculation:
   // theo - now moved from display to idle_cb
   // discuss here: http://github.com/openframeworks/openFrameworks/issues/labels/0062#issue/187
   //
   //
   // theo - please don't mess with this without letting me know.
   // there was some very strange issues with doing ( timeNow-timeThen ) producing different values to: double diff = timeNow-timeThen;
   // http://www.openframeworks.cc/forum/viewtopic.php?f=7&t=1892&p=11166#p11166

   timeNow = ofGetElapsedTimef();
   double diff = timeNow - timeThen;
   if(diff  > 0.00001)
   {
      fps = 1.0 / diff;
      frameRate	*= 0.9f;
      frameRate	+= 0.1f * fps;
   }
   lastFrameTime = diff;
   timeThen = timeNow;
   // --------------

   if(this->bDoAutoRedraw)
   {
      draw();
      event.RequestMore();
   }
}

//----------------------------------------------------------
void ofxWxGLCanvas::draw()
{
    SetCurrent(*this->wxGLRC);
    
    float *bgPtr = ofBgColorPtr();
    bool bClearAuto = ofbClearBg();
    if(bClearAuto)
    {
        ofClear(bgPtr[0] * 255, bgPtr[1] * 255, bgPtr[2] * 255, bgPtr[3] * 255);
    }
    ofNotifyUpdate();
    ofNotifyDraw();
    SwapBuffers();
    this->nFrameCount++;
}

//----------------------------------------------------------
void ofxWxGLCanvas::OnEraseBackground(wxEraseEvent &WXUNUSED(event))
{
}

//----------------------------------------------------------
void ofxWxGLCanvas::OnMouse(wxMouseEvent &event)
{
    int x = event.GetX();
    int y = event.GetY();
    int button = event.GetButton() - 1;
    
    rotateMouseXY(orientation, x, y);
    
    if (event.Dragging())
    {
        ofDragInfo info;
        info.position.x = x;
        info.position.y = y;
        
        ofNotifyDragEvent(info);
        if(ofGetMousePressed(0))
        {
            ofNotifyMouseDragged(x, y, 0);
        }
        if(ofGetMousePressed(1))
        {
            ofNotifyMouseDragged(x, y, 1);
        }
        if(ofGetMousePressed(2))
        {
            ofNotifyMouseDragged(x, y, 2);
        }
    }
    else if(event.Moving())
    {
        ofNotifyMouseDragged(x, y, button);
    }
    
    if(event.Entering())
    {
        SetFocus(); //! @note Needed for key events to work.
        ofNotifyWindowEntry(1);
    }
    else if(event.Leaving())
    {
        ofNotifyWindowEntry(0);
        // Relase all mouse buttons.
        if(ofGetMousePressed(0))
        {
            ofNotifyMouseReleased(x, y, 0);
        }
        if(ofGetMousePressed(1))
        {
            ofNotifyMouseReleased(x, y, 1);
        }
        if(ofGetMousePressed(2))
        {
            ofNotifyMouseReleased(x, y, 2);
        }
    }
    
    if(event.ButtonDown())
    {
        ofNotifyMousePressed(x, y,  button);
    }
    else if(event.ButtonUp())
    {
        ofNotifyMouseReleased(x, y, button);
    }
}

//----------------------------------------------------------
int ofxWxGLCanvas::translateKey(int key)
{
    switch(key)
    {
        case WXK_RETURN:
            key = OF_KEY_RETURN;
            break;
        case WXK_ESCAPE:
            key = OF_KEY_ESC;
            break;
        case WXK_CONTROL:
            key = OF_KEY_CTRL;
            break;
        case WXK_ALT:
            key = OF_KEY_ALT;
            break;
        case WXK_SHIFT:
            key = OF_KEY_SHIFT;
            break;
        case WXK_BACK:
            key = OF_KEY_BACKSPACE;
            break;
        case WXK_DELETE:
            key = OF_KEY_DEL;
            break;
        case WXK_F1:
            key = OF_KEY_F1;
            break;
        case WXK_F2:
            key = OF_KEY_F2;
            break;
        case WXK_F3:
            key = OF_KEY_F3;
            break;
        case WXK_F4:
            key = OF_KEY_F4;
            break;
        case WXK_F5:
            key = OF_KEY_F5;
            break;
        case WXK_F6:
            key = OF_KEY_F6;
            break;
        case WXK_F7:
            key = OF_KEY_F7;
            break;
        case WXK_F8:
            key = OF_KEY_F8;
            break;
        case WXK_F9:
            key = OF_KEY_F9;
            break;
        case WXK_F10:
            key = OF_KEY_F10;
            break;
        case WXK_F11:
            key = OF_KEY_F11;
            break;
        case WXK_F12:
            key = OF_KEY_F12;
            break;
        case WXK_LEFT:
            key = OF_KEY_LEFT;
            break;
        case WXK_UP:
            key = OF_KEY_UP;
            break;
        case WXK_RIGHT:
            key = OF_KEY_RIGHT;
            break;
        case WXK_DOWN:
            key = OF_KEY_DOWN;
            break;
        case  WXK_PAGEUP:
            key = OF_KEY_PAGE_UP;
            break;
        case WXK_PAGEDOWN:
            key = OF_KEY_PAGE_DOWN;
            break;
        case WXK_HOME:
            key = OF_KEY_HOME;
            break;
        case WXK_END:
            key = OF_KEY_END;
            break;
        case WXK_INSERT:
            key = OF_KEY_INSERT;
            break;
        default:
            break;
    }
    return key;
}

//----------------------------------------------------------
void ofxWxGLCanvas::OnKeyDown(wxKeyEvent &event)
{
    int key = event.GetKeyCode();
    if(bDoKeyTranslate)
    {
        key = translateKey(key);
    }
    ofNotifyKeyPressed(key);
}

//----------------------------------------------------------
void ofxWxGLCanvas::OnKeyUp(wxKeyEvent &event)
{
    int key = event.GetKeyCode();
    if(bDoKeyTranslate)
    {
        key = translateKey(key);
    }
    ofNotifyKeyReleased(key);
}

//----------------------------------------------------------
void ofxWxGLCanvas::OnDropFiles(wxDropFilesEvent &event)
{
    if (event.GetNumberOfFiles() > 0)
    {
        wxString* dropped = event.GetFiles();
        wxASSERT(dropped);
        
        wxBusyCursor busyCursor;
        wxWindowDisabler disabler;
        //wxBusyInfo busyInfo(_("Adding files, wait please..."));
        
        wxString name;
        wxArrayString files;
        
        for (int fileIdx = 0; fileIdx < event.GetNumberOfFiles(); ++fileIdx)
        {
            name = dropped[fileIdx];
            if (wxFileExists(name))
            {
                files.push_back(name);
            }
            else if (wxDirExists(name))
            {
                wxDir::GetAllFiles(name, &files);
            }
        }
        wxPoint point(event.GetPosition());
        ofDragInfo info;
        info.position.x = point.x;
        info.position.y = ofGetHeight() - point.y;
        
        for (int fileIdx = 0; fileIdx <  files.size(); ++fileIdx)
        {
            string fileName(files[fileIdx]);
            info.files.push_back(fileName);
        }
        
        ofNotifyDragEvent(info);
        //ofAppPtr->dragEvent(info);
    }
}

//------------------------------------------------------------
void ofxWxGLCanvas::rotateMouseXY(ofOrientation orientation, int &x, int &y)
{
	int savedY = 0;
	switch(orientation)
    {
		case OF_ORIENTATION_180:
			x = ofGetWidth() - x;
			y = ofGetHeight() - y;
			break;
            
		case OF_ORIENTATION_90_RIGHT:
			savedY = y;
			y = x;
			x = ofGetWidth()-savedY;
			break;
            
		case OF_ORIENTATION_90_LEFT:
			savedY = y;
			y = ofGetHeight() - x;
			x = savedY;
			break;
            
		case OF_ORIENTATION_DEFAULT:
		default:
			break;
	}
}

//------------------------------------------------------------
void ofxWxGLCanvas::setFrameRate(float targetRate)
{
    if (targetRate == 0)
    {
        bFrameRateSet = false;
        return;
    }
    
    bFrameRateSet = true;
    float durationOfFrame = 1.0f / static_cast<float>(targetRate);
    millisForFrame = static_cast<int>(1000.0f * durationOfFrame);
    
    frameRate = targetRate;
}
