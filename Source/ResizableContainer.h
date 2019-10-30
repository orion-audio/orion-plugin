/*
  ==============================================================================

    ResizableContainer.h
    Created: 8 Aug 2019 8:10:49pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class ResizableContainer
{
public:
    
    Rectangle<int> setBoundsScaled(Component* comp, Rectangle<int> bounds)
    {
        jassert(comp != nullptr);
        
        Path p;
        p.addRectangle(bounds);
        p.applyTransform(AffineTransform::scale(uiScale));
        Rectangle<int> newBounds = p.getBounds().toNearestInt();
        comp->setBounds(newBounds);
        return newBounds;
    }
    
    Rectangle<int> setBoundsScaled(Component* comp, int x, int y, int width, int height)
    {
        jassert(comp != nullptr);
        Rectangle<int> bounds(x, y, width, height);
        Path p;
        p.addRectangle(bounds);
        p.applyTransform(AffineTransform::scale(uiScale));
        Rectangle<int> newBounds = p.getBounds().toNearestInt();
        comp->setBounds(newBounds);
        return newBounds;
    }

    
    void setUIScale(double newScale)
    {
        jassert(newScale > 0);
        
        uiScale = newScale;
    }
    
    double getUIScale() { return uiScale; }
    
private:
    double uiScale = 1;
};
