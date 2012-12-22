
#include "PickableBox.h"

//-----------------------------------------------------------------------------
PickableBox::PickableBox()
   : isVis(true),
     isSel(false),
     color(ofColor::white),
     selectionColor(ofColor::white)
{

}

//-----------------------------------------------------------------------------
PickableBox::~PickableBox()
{
}

//-----------------------------------------------------------------------------
void PickableBox::setSelectionColor(const ofColor &color,
                                 ofxIPickable::PickableComponentMap &componentMap,
                                 unsigned int componentMode)
{
    this->selectionColor = color;
    ColorIndex colorIdx = colorToIndex(this->selectionColor);
    componentMap[colorIdx] = this;
}

//-----------------------------------------------------------------------------
void PickableBox::drawForSelection(unsigned int componentMode)
{
    if(!this->isVis)
    {
        return;
    }
    ofColor currentColor = this->color;
    this->color = this->selectionColor;
    draw();
    this->color = currentColor;
}

//-----------------------------------------------------------------------------
void PickableBox::postSelectionRestore(int componentMode)
{
    
}

//-----------------------------------------------------------------------------
bool PickableBox::isVisible()
{
    return this->isVis;
}

//-----------------------------------------------------------------------------
void PickableBox::setVisible(bool state)
{
    this->isVis = state;
}

//-----------------------------------------------------------------------------
const ofColor &PickableBox::getColor() const
{
    return this->color;
}

//-----------------------------------------------------------------------------
void PickableBox::setColor(const ofColor &c)
{
    this->color = c;
}

//-----------------------------------------------------------------------------
void PickableBox::setSelected(bool selectedState)
{
   this->isSel = selectedState;
   this->color = (this->isSel) ? ofColor::red : ofColor::white;
}

//-----------------------------------------------------------------------------
bool PickableBox::isSelected()
{
   return this->isSel;
}

//-----------------------------------------------------------------------------
void PickableBox::customDraw()
{
   if(!this->isVis)
   {
      return;
   }
   ofPushStyle();
   ofSetColor(this->color);
   ofBox(10);
   ofPopStyle();
}

