
#pragma once

#include <ofNode.h>
#include <ofColor.h>
#include "ofxIPickable.h"

class PickableBox : public ofNode, public ofxIPickable
{
public:
   PickableBox();
   virtual ~PickableBox();

   virtual void drawForSelection(unsigned int componentMode);
   virtual void setSelectionColor(const ofColor &color,
                                  ofxIPickable::PickableComponentMap &componentMap,
                                  unsigned int componentMode);
   virtual void postSelectionRestore(int componentMode);
   virtual bool isVisible();
   virtual void setVisible(bool state);
   virtual const ofColor &getColor() const;
   virtual void setColor(const ofColor &c);
   virtual void setSelected(bool selected);
   virtual bool isSelected();
   virtual void customDraw();

private:
   bool isVis;
   bool isSel;
   ofColor color;
   ofColor selectionColor;
};