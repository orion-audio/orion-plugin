/*
  ==============================================================================

    OrionClipConfiguration.cpp
    Created: 21 Jun 2019 1:10:50pm
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionClipConfiguration.h"
#include "OrionGlobalVars.h"

//==============================================================================
OrionClipConfiguration::OrionClipConfiguration(OrionaudioAudioProcessor& p) : processor(p)
{
    // Background Image
    Image backgroundImage = ImageCache::getFromMemory(BinaryData::clipBackground_png, BinaryData::clipBackground_pngSize);
    backgroundImageView.reset(new DrawableImage());
    backgroundImageView->setImage(backgroundImage);
    addAndMakeVisible(backgroundImageView.get());
}

void OrionClipConfiguration::paint (Graphics& g)
{
    
//    Image clipbackground = ImageCache::getFromMemory(BinaryData::orionClipBackground_png, BinaryData::orionClipBackground_pngSize);
//    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
//    RectanglePlacement orionBackgroundRectanglePlacement(64);
//    g.drawImageWithin(clipbackground, 0, 0,OrionGlobalWidth,OrionGlobalHeight/3/11*10,orionBackgroundRectanglePlacement,false);
    
}

void OrionClipConfiguration::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains.
    //--------- Background Image ---------//
    Rectangle<int> backgroundArea(0, 0, getWidth(), getHeight());
    backgroundImageView->setTransformToFit(backgroundArea.toFloat(), RectanglePlacement::stretchToFit);
}

OrionClipConfiguration::~OrionClipConfiguration()
{
    
}
