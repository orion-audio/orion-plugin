/*
  ==============================================================================

    OrionEnvConfiguration.cpp
    Created: 21 Jun 2019 1:10:03pm
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionEnvConfiguration.h"
#include "OrionGlobalVars.h"

//==============================================================================
OrionEnvConfiguration::OrionEnvConfiguration(OrionaudioAudioProcessor& p) : processor(p)
{
    setBounds(0, 0, OrionGlobalWidth, OrionGlobalHeight/3);
}

void OrionEnvConfiguration::paint (Graphics& g)
{
    g.fillAll(Colours::aqua);
    g.setFont(Font(36.0f));
    g.drawText("Envelop", getLocalBounds(), Justification::centred, true);
}

void OrionEnvConfiguration::resized()
{

}

OrionEnvConfiguration::~OrionEnvConfiguration()
{
    
}
