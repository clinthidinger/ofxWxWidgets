

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofEnableAlphaBlending();
    
   
    bool r1 = srcImg.loadImage("A.jpg");
    bool r2 = dstImg.loadImage("B.jpg");
    bool r3 = brushImg.loadImage("brush.png");
    
    int width = srcImg.getWidth();
    int height = srcImg.getHeight();
    //*
    maskFbo.allocate(width,height);
    fbo.allocate(width,height);
    
    ofSetWindowShape(width, height);
    
    
    // There are 3 of ways of loading a shader:
    //
    //  1 - Using just the name of the shader and ledding ofShader look for .frag and .vert: 
    //      Ex.: shader.load( "myShader");
    //
    //  2 - Giving the right file names for each one: 
    //      Ex.: shader.load( "myShader.vert","myShader.frag");
    //
    //  3 - And the third one it«s passing the shader programa on a single string;
    //
    string shaderProgram = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable\n \
    \
    uniform sampler2DRect tex0;\
    uniform sampler2DRect maskTex;\
    \
    void main (void){\
    vec2 pos = gl_TexCoord[0].st;\
    \
    vec3 src = texture2DRect(tex0, pos).rgb;\
    float mask = texture2DRect(maskTex, pos).r;\
    \
    gl_FragColor = vec4( src , mask);\
    }";
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader.linkProgram(); 
    
    // Let«s clear the FBO«s
    // otherwise it will bring some junk with it from the memory    
    maskFbo.begin();
    ofClear(0, 0, 0, 255);
    maskFbo.end();
    
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();
    //*/
    bBrushDown = false;
}

//--------------------------------------------------------------
void testApp::update()
{
    // MASK (frame buffer object)
    //
    maskFbo.begin();
    if (bBrushDown)
    {
        brushImg.draw(mouseX - 25, mouseY - 25, 50, 50);
    }
    maskFbo.end();
    
    // HERE the shader-masking happends
    //
    fbo.begin();
    // Cleaning everthing with alpha mask on 0 in order to make it transparent for default
    ofClear(0, 0, 0, 0); 
    
    shader.begin();
    shader.setUniformTexture("maskTex", maskFbo.getTextureReference(), 1 );
    
    srcImg.draw(0, 0);

    shader.end();
    fbo.end();

}

//--------------------------------------------------------------
void testApp::draw()
{
   //ofSphere(ofPoint(0, 0, 0), 400);


   //*
    ofSetColor(255, 255);
   
    dstImg.draw(0, 0);
    fbo.draw(0, 0);
    
    ofDrawBitmapString("Drag the Mouse to draw", 15, 15);
    ofDrawBitmapString("Press spacebar to clear", 15, 30);
    //*/

   /*
   ofRectangle viewport2D;
   viewport2D.x = 0;//ofGetWidth();
	viewport2D.y = 0;//ofGetHeight();
	viewport2D.width = ofGetWidth();
	viewport2D.height = ofGetHeight();

   //ofRectangle viewport3D;

   ofEasyCam camera;

   // keep a copy of your viewport and transform matrices for later
	ofPushView();

	// tell OpenGL to change your viewport. note that your transform matrices will now need setting up
	ofViewport(viewport2D);

	// setup transform matrices for normal oF-style usage, i.e.
	//  0,0=left,top
	//  ofGetViewportWidth(),ofGetViewportHeight()=right,bottom
	ofSetupScreen();

	ofFill();
	ofSetColor(220);
	for(int x = 0; x < 1000; x += 20){
		for(int y = 0; y < 1000; y += 20){
			ofCircle(x, y, sin((x + y) / 100.0f + ofGetElapsedTimef()) * 5.0f);
		}
	}

	// restore the old viewport (now full view and oF coords)
	ofPopView();
	//--


	//--
	// 3d view

	//drawViewportOutline(viewport3D);

	// note the camera accepts the viewport as an argument
	// this is so that the camera can be aware of which viewport
	// it is acting on
	//
	// ofPushView() / ofPopView() are automatic
	camera.begin(viewport2D);
	ofDrawGrid(100);
	camera.end();
	//--


	ofDrawBitmapString("Press [space] to randomize viewports", 20, 20);
   //*/
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    maskFbo.begin();
    ofClear(0, 0, 0, 255);
    maskFbo.end();
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
    bBrushDown = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
    bBrushDown = false;
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

