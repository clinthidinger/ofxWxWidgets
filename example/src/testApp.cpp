
#include "testApp.h"
#include <of3dUtils.h>
#include "ofxAppWxWindow.h"
#include "ofxWxGLCanvas.h"
#include "testScene.h"



//--------------------------------------------------------------
testApp::testApp(ofxAppWxWindow *win) : window(win)
{

}

//--------------------------------------------------------------
testApp::~testApp()
{
   if(scene != NULL)
   {
      delete scene;
      scene = NULL;
   }
}

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetWindowShape(800, 600);
    ofSetVerticalSync(true);
    glEnable(GL_DEPTH_TEST);
    scene = new testScene();
}

//--------------------------------------------------------------
void testApp::update()
{
    float rate = this->window->getWxGLCanvas()->getFrameRate();
    ofPushStyle();
    ofSetColor(ofColor::white);
    std::stringstream ss;
    ss << rate << " fps ";
    ofDrawBitmapString(ss.str(), ofGetWidth() * 0.05f,  ofGetHeight() * 0.05f);
    ofPopStyle();
}

//--------------------------------------------------------------
void testApp::draw()
{
   if(scene != NULL)
   {
      ofRectangle viewport(ofGetCurrentViewport());
      scene->draw(viewport);
   }
}

//--------------------------------------------------------------
void testApp::exit()
{
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
   
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    if(!ofGetKeyPressed(OF_KEY_ALT))
    {
        this->scene->pickObject(x, y);
//#define DEBUG_PICKING 1
#ifdef DEBUG_PICKING
      this->window->getWxGLCanvas()->setAutoRedraw(!this->window->getWxGLCanvas()->getAutoRedraw());
      this->window->getWxGLCanvas()->SwapBuffers();
#endif
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
    
}

