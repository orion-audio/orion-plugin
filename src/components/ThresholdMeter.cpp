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
    decoratePathL->setAlpha(0.0);
    
    decoratePathR.reset(new DrawablePath());
    addAndMakeVisible(decoratePathR.get());
    decoratePathR->replaceColour(Colours::black,Colours::darkgrey);
    decoratePathR->setAlpha(0.5);
    
    
    meterPath.reset(new DrawablePath());
    addAndMakeVisible(meterPath.get());
    meterPath->replaceColour(Colours::black,Colours::cyan);

    
    startTimerHz(30);// Timer - timerCallback 刷新频率
    
    volumeColor = juce::Colours::cyan;
    overdriveColor = juce::Colours::lightpink;
    
    
}

ThresholdMeter::~ThresholdMeter()
{
    
}

void ThresholdMeter::paint (juce::Graphics& g)
{

    //isVertical = getHeight() >= getWidth();
    //g.setColour (juce::Colours::grey);
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("ThresholdMeter", getLocalBounds(),juce::Justification::centred, true);
    
    //g.setColour (juce::Colours::grey);
    //g.drawRoundedRectangle (getLocalBounds().toFloat(), 7.5, 1);

    //Rectangle<int> area = getLocalBounds();
    
    

   
    /*
    if (updaterFunction != nullptr)
    {
        float levelLocal = updaterFunction();
        
        if(levelLocal <= 1)
        {
            //DBG(level);
            if(levelLocal == 0)
            {
                area = Rectangle<int>(0, 0,  0, 0);
            }
            else
            {
                area = Rectangle<int>(0, 0,  getWidth()*14/15 * levelLocal , getHeight());
            }
            
            g.setColour(volumeColor);
            g.fillRoundedRectangle (area.toFloat(), 7.5f);
            preLevel = levelLocal;
            meterUpdated = true;

        }
        else
        {
            area = Rectangle<int>(0, 0,  getWidth()*14/15 , getHeight());
            g.setColour(volumeColor);
            g.fillRoundedRectangle (area.toFloat(), 7.5f);
            
            Rectangle<int> areaOverDrive = Rectangle<int>(getWidth()*14/15, 0,  getWidth()/15, getHeight());
            g.setColour(overdriveColor);
            g.fillRoundedRectangle (areaOverDrive.toFloat(), 7.5f);
        }
    }
    
    
    
    if(meterUpdated)
    {
        Rectangle<int> area = Rectangle<int>(0, 0, preLevel * count * getWidth()*14/15, getHeight());
        g.setColour(volumeColor);
        g.fillRoundedRectangle (area.toFloat(), 7.5f);

        count = count - 0.001f;
        if(count == 0.0f)
        {
            meterUpdated = false;
            count = 1.0f;
        }
    }
     
     */
    
}

void ThresholdMeter::resized()
{
    //--------- DROPDOWN BUTTONS ---------//
    Path path;
    
//    path.addRectangle (getWidth()*7.5/15, getHeight()*1.25/15, 1, getHeight()*13/15);
//    pointerPath->setPath(path);
    
    path.addRectangle (getWidth()/15, getHeight()*1.25/15, 1, getHeight()*13/15);
    decoratePathL->setPath(path);
    
    path.addRectangle (getWidth()*14/15, getHeight()*1.25/15, 1, getHeight()*13/15);
    decoratePathR->setPath(path);

}

void ThresholdMeter::timerCallback()
{
    //repaint();
    if(serial == instrumetSerial && dropdownTabSerial == 3 && compSwitches[instrumetSerial])
    {
      meterUpdate();
      std::cout<<"Call: "<<serial<<std::endl;
    }

}

void ThresholdMeter::pointerMove(float value)//value range 0<->1
{
    Path path;
    path.addRectangle (getWidth()/15 + value * getWidth() * 13/15, getHeight() * 1.25/15, 1, getHeight()*13/15);
    pointerPath->setPath(path);
}

void ThresholdMeter::meterUpdate()
{
    if (updaterFunction != nullptr)
    {
        level = updaterFunction();
        
        //-----------------------------------
        
        float inputVolume = 20.0f * log10(level);
    
        if(inputVolume < 0.0f && inputVolume > -100.0f)
        {
            inputVolume = inputVolume;
        }
    
        else
        {
            inputVolume = -100.0f;
        
            if(inputVolume > 0.0f)
            {
                inputVolume = 0.0f;
            }
        }
    
        //std::cout << inputVolume << std::endl;
        int gainLevel = 100 - (inputVolume + 100);
        
        //-----------------------------------
        

        Path path;

        if(level>preLevel)
        {
            if(level <= 1)
            {

                if(level == 0)
                {
                    path.addRectangle(0, 0,  0, 0);
                }
                else
                {
                    //path.addRectangle(0, 0, level * getWidth()*14/15 , getHeight());
                    path.addRectangle(gainLevel, 0, (getWidth()*14/15 - gainLevel) , getHeight());
                }


                meterPath->setPath(path);
                preLevel = level;
                meterUpdated = true;

            }
            else
            {
                path.addRectangle(0, 0,  getWidth()*14/15 , getHeight());
                meterPath->setPath(path);

                preLevel = 1;
                meterUpdated = true;
            }

        }



        if(meterUpdated)
        {
            Path path;
            path.addRoundedRectangle(0, 0,  preLevel * getWidth()*14/15 , getHeight(), 5, 5,
                                     true /* curveTopLeft */,
                                     false /*curveTopRight */,
                                     true /*curveBottomLeft */,
                                     false /*curveBottomRight */);

            meterPath->setPath(path);

            preLevel = preLevel - 0.05f;
            if(preLevel <= 0.0f)
            {
                preLevel = 0;
                meterUpdated = false;
            }
        }

    }
    
    
//    if (updaterFunction != nullptr)
//    {
//        level = updaterFunction();
//        Path path;
//        path.addRectangle(0, 0, level * getWidth()*14/15 , getHeight());
//        meterPath->setPath(path);
//        preLevel = level;
//
//    }
    

    
    
}
