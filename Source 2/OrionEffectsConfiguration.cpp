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
    //attackSlider = new Slider("attackSlider");
    //attackSlider->setSliderStyle(Slider::LinearVertical);
    //attackSlider->setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    //attackSlider->setBounds(40, 120, 40, 136);
    //attackSlider->setRange(0.0f, 500.0f);
    //attackSlider->setValue(0.0f);
    //addAndMakeVisible(attackSlider);
    //setColour(OrionEffectsConfiguration::buttonColourId, Colours::darkgrey);
    
    //effectDelay = new OrionEffectDelay*(p);
    //delayGui.effectDelaySerial = effectSerial;
    //compGui.effectCompSerial = effectSerial;
    
    effectSerial = serial;
    
    setBounds(0, 0, OrionGlobalWidth, OrionGlobalHeight/3);
    
    addAndMakeVisible(&compGui);
    addAndMakeVisible(&reverbGui);
    addAndMakeVisible(&delayGui);

}

void OrionEffectsConfiguration::paint(Graphics& g)
{
    g.fillAll(Colours::darkgoldenrod);
}

void OrionEffectsConfiguration::resized()
{
    
}

OrionEffectsConfiguration::~OrionEffectsConfiguration()
{
    
}


