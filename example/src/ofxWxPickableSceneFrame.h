
#pragma once

#include "ofxWxPickableSceneBase.h"

class ofxAppWxWindow;
class testApp;

class ofxWxPickableSceneFrame : public ofxWxPickableSceneFrameBase
{
public:
   ofxWxPickableSceneFrame(wxWindow *parent);
   virtual ~ofxWxPickableSceneFrame();
   virtual void OnHiButtonClick(wxCommandEvent &event);
   void initRendering();
   ofxAppWxWindow *getWindow();

private:
   ofxAppWxWindow *window;
};

inline ofxAppWxWindow *ofxWxPickableSceneFrame::getWindow() { return window; }