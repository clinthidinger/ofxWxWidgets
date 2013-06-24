#pragma once


#include <ofMain.h>

class ofxAppWxWindow;
class testScene;

//! @brief The test app.
class testApp : public ofBaseApp
{
public:
    
   testApp(ofxAppWxWindow *win);
   virtual ~testApp();
    
    void currentCaptureChanged();
    void currentFrameChanged();
    void propertiesChanged();
    
    virtual void setup();
    virtual void update();
    virtual void draw();
    virtual void exit();
    
    virtual void keyPressed  (int key);
    virtual void keyReleased(int key);
    virtual void mouseMoved(int x, int y );
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void windowResized(int w, int h);
    virtual void dragEvent(ofDragInfo dragInfo);
    virtual void gotMessage(ofMessage msg);
     
private:
    ofxAppWxWindow *window;
    testScene *scene;
};
