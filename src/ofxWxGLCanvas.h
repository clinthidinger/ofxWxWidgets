
#pragma once

#define wxUSE_GLCANVAS 1
#include <ofConstants.h>
#include <wx/glcanvas.h>


//! @brief wxGLCanvas for openframeworks.
//! @note More or less ripped from ofAppGlutWindow with tweaks for Wx.
class ofxWxGLCanvas : public wxGLCanvas
{
public:
   //! @brief Constructor.
   //! @param parent The parent window.
   //! @param width Canvas width.
   //! @param height Canvas height.
   ofxWxGLCanvas(wxWindow *parent, int width, int height);

   //! @brief Destructor.
   virtual ~ofxWxGLCanvas();

   //! brief Draw the canvas.
   void draw();

   //! @brief Get orientation.
   //! @return The orientation.
   inline ofOrientation GetOrientation() const { return orientation; }

   //! @brief Set the orientation.
   //! @param Set the orientation.
   inline void SetOrientation(ofOrientation o) { orientation = o; }

   //! @brief Get the GL context.
   //! @return The GL context.
   inline wxGLContext *GetGLContex() { return  this->wxGLRC; }

   //! @brief Get the GL context.
   //! @return The GL context.
   inline const wxGLContext *GetGLContex() const { return  this->wxGLRC; }

   //! @brief Get the frame rate.
   //! @return The frame rate.
   inline float getFrameRate() const { return this->frameRate; }

   //! @brief Get the last frame's time.
   //! return The last frame's time.
   inline double getLastFrameTime() const { return this->lastFrameTime; }

   //! @brief Get the frame count.
   //! @rteurn The frame count.
   inline int getFrameCount() const { return this->nFrameCount; }

   //! @brief Set the auto-redraw flag.
   //! @param Auto-redraw state.
   inline void setAutoRedraw(bool state) { this->bDoAutoRedraw = state; }

   //! @brief Get the auto-redraw flag.
   //! @return Auto-redraw state.
   inline bool getAutoRedraw() const { return this->bDoAutoRedraw; }

   //! @brief Set the target frame rate.
   //! @param Target frame rate.
   void setFrameRate(float targetRate);

private:
   float 		  frameRate;
   double		  lastFrameTime;
   float		     timeNow;
   float         timeThen;
   float         fps;
   int			  framesForFPS;
   int			  nFrameCount;
   bool			  bDoubleBuffered;
   bool			  bFrameRateSet;
   int 			  millisForFrame;
   int 			  prevMillis;
   int 			  diffMillis;
   wxGLContext  *wxGLRC;
   ofOrientation orientation;
   bool          bDoKeyTranslate;
   bool          bDoAutoRedraw;

   //! @brief Wx OnPaint event callback.
   void OnPaint(wxPaintEvent &event);

   //! @brief Wx OnKeyDown event callback.
   void OnKeyDown(wxKeyEvent &event);

   //! @brief Wx OnKeyUp event callback.
   void OnKeyUp(wxKeyEvent &event);

   //! @brief Wx OnSize event callback.
   void OnSize(wxSizeEvent& event);

   //! @brief Wx OnEraseBackground event callback.
   void OnEraseBackground(wxEraseEvent &event);

   //! @brief Wx OnMouse event callback.
   void OnMouse(wxMouseEvent& event);

   //! @brief Wx OnDropFiles event callback.
   void OnDropFiles(wxDropFilesEvent &event);

   //! @brief Wx OnIdle event callback.
   void OnIdle(wxIdleEvent & event);
   
   //! @brief Rotate the mouse for different orientations.
   //! @param orientation Orientation to rotate for.
   //! @param x In/Out param for mouse x.
   //! @param y In/Out param for mouse y.
   void rotateMouseXY(ofOrientation orientation, int &x, int &y);

   //! @brief Translate key from Wx to openframeworks.
   int translateKey(int key);

   wxDECLARE_NO_COPY_CLASS(ofxWxGLCanvas);
   DECLARE_EVENT_TABLE()
};

