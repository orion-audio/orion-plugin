/*
  ==============================================================================

    OrionEQConfiguration.cpp
    Created: 11 Jun 2019 9:44:35pm
    Author:  Lei Li

  ==============================================================================
*/

#include "OrionEQConfiguration.h"
#include "OrionGlobalVars.h"

OrionEQConfiguration::OrionEQConfiguration(OrionaudioAudioProcessor& p) : processor(p)
{
    //attackSlider = new Slider("attackSlider");
    //attackSlider->setSliderStyle(Slider::LinearVertical);
    //attackSlider->setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    //attackSlider->setBounds(40, 120, 40, 136);
    //attackSlider->setRange(0.0f, 500.0f);
    //attackSlider->setValue(0.0f);
    //addAndMakeVisible(attackSlider);
    //setColour(OrionEffectsConfiguration::buttonColourId, Colours::darkgrey);
    setBounds(0, 0, OrionGlobalWidth, OrionGlobalHeight/3);
}

void OrionEQConfiguration::paint(Graphics& g)
{
    g.fillAll(Colours::aqua);
}

void OrionEQConfiguration::resized()
{
    
}

OrionEQConfiguration::~OrionEQConfiguration()
{
    
}


