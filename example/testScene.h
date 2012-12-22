
#pragma once

#include <list>
#include <ofxPickableScene.h>
#include <ofxViewportCam.h>
#include <ofxGrid.h>
#include "PickableBox.h"

class testScene : public ofxPickableScene
{
public:
   //! @brief Constructor.
   testScene();
   //! @brief Destructor.
   virtual ~testScene();

   //! @brief Draw the scene.
   //! @param viewport Current of viewport for camera.
   void draw(const ofRectangle &viewport);

   //! @brief Pick an object in the scene.
   //! @param x Mouse coord x position.
   //! @param y Mouse coord y position.
   void pickObject(int x, int y);

private:
   ofxViewportCam cam;
   ofxGrid grid;
   //ofLight light;
   std::list<PickableBox *> sceneObjects;
};