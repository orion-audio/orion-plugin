/*
  ==============================================================================

    OrionResizableCornerComponent.h
    Created: 28 Oct 2019 2:25:36pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

template <class Editor>

class OrionResizableCornerComponent : public ResizableCornerComponent
{
public:
    OrionResizableCornerComponent (Editor* e, Component *componentToResize, ComponentBoundsConstrainer *constrainer) : ResizableCornerComponent(componentToResize, constrainer)
    {
        editor = e;
    }
    
    void mouseUp(const MouseEvent &e) override
    {
        if (e.getNumberOfClicks() >= 2)
            editor->setDefaultSize();
        
        ResizableCornerComponent::mouseUp(e);
    }
    
private:
    Editor* editor;

};
