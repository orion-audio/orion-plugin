/*
  ==============================================================================

    OrionEQConfiguration.cpp
    Created: 11 Jun 2019 9:44:35pm
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionEQConfiguration.h"
#include "OrionGlobalVars.h"

//==============================================================================
OrionEQConfiguration::OrionEQConfiguration(OrionaudioAudioProcessor& p) : processor(p)
{
    setBounds(0, 0, OrionGlobalWidth, OrionGlobalHeight/3);
}

void OrionEQConfiguration::paint(Graphics& g)
{
    g.fillAll(Colours::aqua);
    g.setFont(Font(36.0f));
    g.drawText("EQ", getLocalBounds(), Justification::centred, true);
}

void OrionEQConfiguration::resized()
{
    
}

OrionEQConfiguration::~OrionEQConfiguration()
{
    
}


