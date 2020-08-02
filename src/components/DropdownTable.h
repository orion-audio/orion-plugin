/*
  ==============================================================================

    DropdownTable.h
    Created: 1 Aug 2020 11:58:04am
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

class DropdownTable : public Component
{
    
private:
    
    OrionaudioAudioProcessor* processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DropdownTable)
public:
    
    DropdownTable(OrionaudioAudioProcessor* p);
    ~DropdownTable();
    int currentTab = 0;//Instrument Tab
    void paint (Graphics&) override;
    void resized() override;
    
    std::unique_ptr<OrionEQConfiguration> eqConfiguration;
    std::unique_ptr<OrionEffectsConfiguration> effectConfiguration;
    std::unique_ptr<OrionEnvConfiguration> envConfiguration;
    std::unique_ptr<OrionClipConfiguration> clipConfiguration;
    
    void tabChange(int tabNum);
    
};
