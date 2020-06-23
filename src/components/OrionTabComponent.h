/*
  ==============================================================================

    OrionTabComponent.h
    Created: 11 Jun 2019 3:02:11pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "OrionEQConfiguration.h"
#include "OrionEnvConfiguration.h"
#include "OrionClipConfiguration.h"
#include "OrionEffectsConfiguration.h"
#include "OrionTabButton.h"

//==============================================================================
/*
*/
class OrionTabComponent : public TabbedComponent
{
public:
    OrionTabComponent(OrionaudioAudioProcessor& p, int serial);
    ~OrionTabComponent();

    void paint (Graphics&) override;
    void resized() override;
    OrionTabButton::ButtonType getType(String type);
    
    int TabSerial;
    unsigned int tabIndex = 3;
    
    std::unique_ptr<OrionEQConfiguration> eqConfiguration;
    std::unique_ptr<OrionEffectsConfiguration> effectConfiguration;
    std::unique_ptr<OrionEnvConfiguration> envConfiguration;
    std::unique_ptr<OrionClipConfiguration> clipConfiguration;
private:
    
    OrionaudioAudioProcessor& processor;    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionTabComponent)
    
    
};
