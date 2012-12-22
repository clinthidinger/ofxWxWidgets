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
    
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
private:
    ofxAppWxWindow *window;
    testScene *scene;
};
