
#include "testScene.h"

//-----------------------------------------------------------------------------
testScene::testScene() : grid(ofColor::gray, ofVec3f::zero(), ofVec3f(100.0f, 100.0f, 100.0f), 20.0f)
{
   PickableBox *box1 = new PickableBox();
   PickableBox *box2 = new PickableBox();
   PickableBox *box3 = new PickableBox();

   box1->setGlobalPosition(-30.0f, 0.0, 0.0f);
   box2->setGlobalPosition(0.0f, 30.0, 0.0f);
   box3->setGlobalPosition(30.0f, 0.0, 0.0f);

   sceneObjects.push_back(box1);
   sceneObjects.push_back(box2);
   sceneObjects.push_back(box3);
}

//-----------------------------------------------------------------------------
testScene::~testScene()
{
   std::list<PickableBox *>::iterator objIter = this->sceneObjects.begin();
   std::list<PickableBox *>::iterator objEnd = this->sceneObjects.end();
   for(; objIter != objEnd; ++objIter)
   {
      if(*objIter != NULL)
      {
         delete *objIter;
         *objIter = NULL;
      }
   }
   this->sceneObjects.clear();
}

//-----------------------------------------------------------------------------
void testScene::pickObject(int x, int y)
{
    std::list<PickableBox *>::iterator objIter = this->sceneObjects.begin();
    std::list<PickableBox *>::iterator objEnd = this->sceneObjects.end();
    for(; objIter != objEnd; ++objIter)
    {
       PickableBox *box = *objIter;
       // Clear prev selection.
       box->setSelected(false);
       // Add to selectable list of objects.  Could add some filtering here.  
       add(box);
    }
    
    // Pick object.
    ofxIPickable *obj = ofxPickableScene::pick(x, y, this->cam, 0);
    if(obj != NULL)
    {
        // If we got a hit, set selected.
        PickableBox *box = dynamic_cast<PickableBox *>(obj);
        if(box != NULL)
        {
           box->setSelected(true);
        }
    }
    clearPickableObjects();
}

//-----------------------------------------------------------------------------
void testScene::draw(const ofRectangle &viewport)
{
   cam.begin(viewport);
   grid.draw();

   // Draw each object in the scene.
   std::list<PickableBox *>::iterator objIter = this->sceneObjects.begin();
   std::list<PickableBox *>::iterator objEnd = this->sceneObjects.end();
   for(; objIter != objEnd; ++objIter)
   {
      PickableBox *box = *objIter;
      box->draw();
   }
   cam.end();
}

