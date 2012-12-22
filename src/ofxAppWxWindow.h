#pragma once

#include "ofConstants.h"
#include "ofAppBaseWindow.h"
#include "ofEvents.h"
#include "ofTypes.h"

//#include "wx/wx.h"
#define wxUSE_GLCANVAS 1
#include "wx/glcanvas.h"
#include "wx/frame.h"
#include "wx/panel.h"
#include "wx/window.h"
#include "wx/sizer.h"



class ofBaseApp;
class ofGLContext;
class ofxWxGLCanvas;

//! @brief WxWidgets window for openframeworks. 
//! @note More or less ripped from ofAppGlutWindow with tweaks for Wx.
class ofxAppWxWindow : public ofAppBaseWindow
{
public:
   //! @brief Constructor.
   //! param glCanvasParent Parent Wx panel of the canvas.
   ofxAppWxWindow(wxWindow *glCanvasParent);

   //! @brief Destructor.
   virtual ~ofxAppWxWindow();

   //! @brief Set up for OpenGL override.
   virtual void setupOpenGL(int w, int h, int screenMode);

   //! @brief Set double buffering.
   //! @note Does nothing.
   virtual void setDoubleBuffering(bool _bDoubleBuffered);

   //! @brief Initialize the window.
   virtual void initializeWindow();

   //! @brief Pretty much what the name of the func says.
   virtual void runAppViaInfiniteLoop(ofBaseApp *appPtr);

   //! @brief Hide the cursor.
   virtual void hideCursor();

   //! @brief Show the cursor.
   virtual void showCursor();

   //! @brief Set full screen.
   //! @param fullScreen State flag. 
   virtual void setFullscreen(bool fullScreen);

   //! @brief Toggle full screen.
   virtual void toggleFullscreen();

   //! @brief Set the window title.
   virtual void setWindowTitle(std::string title);

   //! @brief Set the window position.
   //! @param x Mouse x pos.
   //! @param y Mouse y pos.
   virtual void setWindowPosition(int x, int y);

   //! @brief Set the window shape.
   //! @param x Mouse x pos.
   //! @param y Mouse y pos.
   virtual void setWindowShape(int w, int h);

   //! @brief Get the window position.
   virtual ofPoint getWindowPosition();

   //! @brief Get the window size.
   virtual ofPoint getWindowSize();

   //! @brief Get the window screen size.
   virtual ofPoint getScreenSize();

   //! @brief Set the window orientation.
   //! @param orientation The window orientation.
   virtual void setOrientation(ofOrientation orientation);

   //! @brief Get the window orientation.
   //! @return The window orientation.
   virtual ofOrientation getOrientation();

   //! @brief Get the window width.
   virtual int getWidth();

   //! @brief Get the window height.
   virtual int	getHeight();

   //! @brief Get the window mode.
   virtual int	getWindowMode();

   //! @brief Get the current frame num.
   virtual int	getFrameNum();

   //! @brief Get the current frame rate.
   virtual float getFrameRate();

   //! @brief Get the last frame time.
   virtual double getLastFrameTime();

   //! @brief Set the frame rate.
   //! @param targetRate The target frame rate.
   virtual void setFrameRate(float targetRate);

   //! @brief Enable setup screen.
   virtual void enableSetupScreen();

   //! @brief Disable setup screen.
   virtual void disableSetupScreen();

   //! @brief Get the wxGLCanvas (non-const).
   //! @return The wxGLCanvas.
   inline ofxWxGLCanvas *getWxGLCanvas() { return glCanvas; }

   //! @brief Get the wxGLCanvas (const).
   //! @return The wxGLCanvas.
   inline const ofxWxGLCanvas *getWxGLCanvas() const { return glCanvas; }

private:

   wxSize         mWxCursorSize;
   int            nFramesSinceWindowResized;
   int			   windowMode;
   bool			   bEnableSetupScreen;
   ofBaseApp     *ofAppPtr;
   wxWindow      *glCanvasParentWnd;
   ofxWxGLCanvas *glCanvas;
   wxBoxSizer    *glCanvasSizer;
   wxFrame       *topParent;

   //! @brief Destroy the window.
   void destroy();
};

