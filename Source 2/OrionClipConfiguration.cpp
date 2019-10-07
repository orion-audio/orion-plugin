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
    g.fillAll(Colours::aqua);
    g.setFont(Font(36.0f));
    g.drawText("Clip", getLocalBounds(), Justification::centred, true);
}

void OrionClipConfiguration::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains.
}

OrionClipConfiguration::~OrionClipConfiguration()
{
    
}
