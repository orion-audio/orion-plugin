/*
  ==============================================================================

    OrionEQConfiguration.h
    Created: 11 Jun 2019 9:44:35pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"

//==============================================================================
class OrionEQConfiguration : public Component
{
public:
    OrionEQConfiguration(OrionaudioAudioProcessor& p);
    ~OrionEQConfiguration();
    
    void paint(Graphics& g) override;
    void resized() override;
    
private:
    OrionaudioAudioProcessor& processor;
    //ScopedPointer<Slider> attackSlider;
    
};
