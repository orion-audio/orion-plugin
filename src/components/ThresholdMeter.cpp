/*
  ==============================================================================

    ThresholdMeter.cpp
    Created: 8 Jul 2020 5:48:05pm
    Author:  Lei Li

  ==============================================================================
*/

//#include <JuceHeader.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "ThresholdMeter.h"

//==============================================================================
ThresholdMeter::ThresholdMeter()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    pointerPath.reset(new DrawablePath());
    addAndMakeVisible(pointerPath.get());
    pointerPath->replaceColour(Colours::black,Colours::darkgrey);

}



void ThresholdMeter::paint (juce::Graphics& g)
{

    //g.setColour (juce::Colours::grey);
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("ThresholdMeter", getLocalBounds(),juce::Justification::centred, true);
    
    g.setColour (juce::Colours::grey);
    g.drawRoundedRectangle (getLocalBounds().toFloat(), 7.5, 1);
    
    
    
    bool isVertical = getHeight() >= getWidth();
    Rectangle<int> area = getLocalBounds();
    
    if(isVertical)
    {
    }
    else
    {
        area = area.removeFromLeft(getWidth());
        float level = 0;

        if (updaterFunction != nullptr)
        {
            level = updaterFunction();
            //DBG(level);
        }
        
        area = Rectangle<int>(0, 0,  getWidth() * level, getHeight());
        
        g.setColour(juce::Colours::cyan);
        g.fillRoundedRectangle (area.toFloat(), 7.5f);
        area.translate(area.getWidth(), 0);
    }
    
        
    
    
    
}

void ThresholdMeter::resized()
{
    //--------- DROPDOWN BUTTONS ---------//
    Path path;
    path.addRectangle (getWidth()/15, 0, 1, getHeight());
    pointerPath->setPath(path);

}

void ThresholdMeter::timerCallback()
{
    repaint();
}

void ThresholdMeter::pointerMove(float value)
{
    Path path;
    path.addRectangle (getWidth()/15 + value, 0, 1, getHeight());//--Change Later!!!
    pointerPath->setPath(path);
}


ThresholdMeter::~ThresholdMeter()
{
}
