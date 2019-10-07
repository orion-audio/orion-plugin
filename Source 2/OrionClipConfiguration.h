/*
  ==============================================================================

    OrionClipConfiguration.h
    Created: 21 Jun 2019 1:10:50pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"

//==============================================================================
class OrionClipConfiguration    : public Component
{
public:
    OrionClipConfiguration(OrionaudioAudioProcessor& p);
    ~OrionClipConfiguration();
    
    void paint(Graphics& g) override;
    void resized() override;
    
private:
    OrionaudioAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionClipConfiguration)
};
