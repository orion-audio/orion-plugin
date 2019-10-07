/*
  ==============================================================================

    OrionEnvConfiguration.h
    Created: 21 Jun 2019 1:10:03pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"

//==============================================================================
class OrionEnvConfiguration    : public Component
{
public:
    OrionEnvConfiguration(OrionaudioAudioProcessor& p);
    ~OrionEnvConfiguration();

    void paint(Graphics& g) override;
    void resized() override;

private:
    OrionaudioAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionEnvConfiguration)
};
