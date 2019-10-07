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
    setBounds(0, 0, OrionGlobalWidth, OrionGlobalHeight/3);
}

void OrionClipConfiguration::paint (Graphics& g)
{
    clipbackground = new File(File::getSpecialLocation(File::globalApplicationsDirectory).getChildFile("Orion").getChildFile("OrionSampler").getChildFile("OrionSampler").getChildFile("Contents").getChildFile("Resources").getChildFile("skin").getChildFile("pictures").getChildFile("orionClipBackground.png"));
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    RectanglePlacement orionBackgroundRectanglePlacement(64);
    g.drawImageWithin(ImageCache::getFromFile(*clipbackground), 0, 0,OrionGlobalWidth,OrionGlobalHeight/3/11*10,orionBackgroundRectanglePlacement,false);
    
}

void OrionClipConfiguration::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains.
}

OrionClipConfiguration::~OrionClipConfiguration()
{
    
}
