/*
  ==============================================================================

    CircularMeter.cpp
    Created: 2 Oct 2019 12:34:36pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "CircularMeter.h"

//==============================================================================
CircularMeter::CircularMeter()
{
    setColour(ColourIds::backgroundColourId, Colour(0xff635E5D));
    setColour(ColourIds::filledColourId, Colour(0xff42f5cb));
    setColour(ColourIds::clipColourId, Colours::red);
    startTimerHz(30);
}

CircularMeter::~CircularMeter()
{
}

void CircularMeter::paint (Graphics& g)
{
    bool isVertical = getHeight() >= getWidth();
    
    g.setColour(Colours::black);
//    g.drawRect(getLocalBounds());
    auto area = getLocalBounds();
    
    if(isVertical){
        area = area.removeFromTop(getHeight() / numCircles);
        g.setColour(findColour(ColourIds::backgroundColourId));
        int w = area.getWidth() * .6;
        int h = w;
        for (int i = 0; i < numCircles; i++){
            g.fillEllipse(area.withSizeKeepingCentre(w, h).toFloat());
            area.translate(0, area.getHeight());
        }
        
        float level = 0;
        int numFilled = 0;
        if (updaterFunction != nullptr)
        {
            level = updaterFunction();
            DBG(level);
            for (int i = 0; i < numCircles; i++){
                if (level > i * (1.f / numCircles))
                {
                    numFilled++;
                }
            }
        }
        g.setColour(findColour(ColourIds::filledColourId));
        area = getLocalBounds();
        area = area.removeFromBottom(getHeight() / numCircles);
        w = area.getWidth() * .6;
        h = w;
        for (int i = 0; i < numFilled; i++){
            if (i == numCircles - 1)
                g.setColour(findColour(ColourIds::clipColourId));
            g.fillEllipse(area.withSizeKeepingCentre(w, h).toFloat());
            area.translate(0, -area.getHeight());
        }
    }else if(!isVertical){
        area = area.removeFromLeft(getWidth() / numCircles);///
        
        g.setColour(findColour(ColourIds::backgroundColourId));
        int h = area.getHeight() * .6;
        int w = h;
        for (int i = 0; i < numCircles; i++){
            g.fillEllipse(area.withSizeKeepingCentre(w, h).toFloat());
            
            area.translate(area.getWidth(), 0);
        }
        
        float level = 0;
        int numFilled = 0;
        if (updaterFunction != nullptr)
        {
            level = updaterFunction();
            for (int i = 0; i < numCircles; i++){
                if (level > i * (1.f / numCircles))
                {
                    numFilled++;
                }
            }
        }
        g.setColour(findColour(ColourIds::filledColourId));
        area = getLocalBounds();
        area = area.removeFromLeft(getWidth() / numCircles);///
        h = area.getHeight() * .6;
        w = h;
        for (int i = 0; i < numFilled; i++){
            if (i == numCircles - 1)
                g.setColour(findColour(ColourIds::clipColourId));
            g.fillEllipse(area.withSizeKeepingCentre(w, h).toFloat());
            area.translate(area.getWidth(), 0);
        }
    }

 
}

void CircularMeter::resized()
{

}

void CircularMeter::timerCallback()
{
    repaint();
}
