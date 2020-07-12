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
    pointerPath->setAlpha(0.5);
    
    decoratePathL.reset(new DrawablePath());
    addAndMakeVisible(decoratePathL.get());
    decoratePathL->replaceColour(Colours::black,Colours::darkgrey);
    decoratePathL->setAlpha(0.5);
    
    decoratePathR.reset(new DrawablePath());
    addAndMakeVisible(decoratePathR.get());
    decoratePathR->replaceColour(Colours::black,Colours::darkgrey);
    decoratePathR->setAlpha(0.5);
    
    startTimerHz(30);// Timer - timerCallback 刷新频率
    
    volumeColor = juce::Colours::cyan;
    overdriveColor = juce::Colours::lightpink;
}

ThresholdMeter::~ThresholdMeter()
{
}

void ThresholdMeter::paint (juce::Graphics& g)
{

    //g.setColour (juce::Colours::grey);
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("ThresholdMeter", getLocalBounds(),juce::Justification::centred, true);
    
    //g.setColour (juce::Colours::grey);
    //g.drawRoundedRectangle (getLocalBounds().toFloat(), 7.5, 1);
    
    bool isVertical = getHeight() >= getWidth();
    
    Rectangle<int> area = getLocalBounds();
    Rectangle<int> areaOverDrive = Rectangle<int>(getWidth()*14/15, 0,  getWidth()/15, getHeight());
    
    if(isVertical)
    {
        
    }
    else
    {
        //area = area.removeFromLeft(getWidth());
        float level = 0;

        if (updaterFunction != nullptr)
        {
            level = updaterFunction();
            //DBG(level);
        }
        
        
        
        
        if(level <= 1 && level >= -1)
        {
           if(level == 0)
           {
               area = Rectangle<int>(0, 0,  0, 0);
           }
           else
           {
               area = Rectangle<int>(0, 0,  getWidth()*14/15 * level , getHeight());
           }
           
           g.setColour(volumeColor);
           g.fillRoundedRectangle (area.toFloat(), 7.5f);
        }
        else
        {
            area = Rectangle<int>(0, 0,  getWidth()*14/15 , getHeight());
            g.setColour(volumeColor);
            g.fillRoundedRectangle (areaOverDrive.toFloat(), 7.5f);
            
            g.setColour(overdriveColor);
            g.fillRoundedRectangle (areaOverDrive.toFloat(), 7.5f);
        }
        
        
        
    }
    
        
    
    
    
}

void ThresholdMeter::resized()
{
    //--------- DROPDOWN BUTTONS ---------//
    Path path;
    path.addRectangle (getWidth()*7.5/15, getHeight()*1.25/15, 1, getHeight()*13/15);
    pointerPath->setPath(path);
    
    path.addRectangle (getWidth()/15, getHeight()*1.25/15, 1, getHeight()*13/15);
    decoratePathL->setPath(path);
    
    path.addRectangle (getWidth()*14/15, getHeight()*1.25/15, 1, getHeight()*13/15);
    decoratePathR->setPath(path);

}

void ThresholdMeter::timerCallback()
{
    repaint();
}

void ThresholdMeter::pointerMove(float value)//value range 0->1
{
    Path path;
    path.addRectangle (getWidth()/15 + value * getWidth() * 13/15, getHeight() * 1.25/15, 1, getHeight()*13/15);
    pointerPath->setPath(path);
}



