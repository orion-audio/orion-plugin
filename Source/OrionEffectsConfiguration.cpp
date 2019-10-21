/*
  ==============================================================================

    OrionEffectsConfiguration.cpp
    Created: 11 Jun 2019 4:00:32pm
    Author:  Lei Li

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "OrionEffectsConfiguration.h"
#include "OrionGlobalVars.h"
OrionEffectsConfiguration::OrionEffectsConfiguration(OrionaudioAudioProcessor& p, int serial) : processor(p), compGui(p,serial), reverbGui(p,serial), delayGui(p,serial)
{

    
    effectSerial = serial;
    
    setBounds(0, 0, OrionGlobalWidth, OrionGlobalHeight/3);
    
    addAndMakeVisible(&compGui);
    addAndMakeVisible(&reverbGui);
    addAndMakeVisible(&delayGui);

}

void OrionEffectsConfiguration::paint(Graphics& g)
{
    g.fillAll(Colours::blue);
    
}

void OrionEffectsConfiguration::resized()
{
    
}

OrionEffectsConfiguration::~OrionEffectsConfiguration()
{
    
}


