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

//==============================================================================
/*
*/
class OrionTabComponent    : public Component
{
public:
    OrionTabComponent(OrionaudioAudioProcessor& p,int serial);
    ~OrionTabComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    TabbedComponent& getTabbedComponent(){return *tabbedComponent;}
    
    int TabSerial;
    unsigned int tabIndex = 3;
    
    OrionEQConfiguration* eqConfiguration;
    OrionEffectsConfiguration* effectConfiguration;
    OrionEnvConfiguration* envConfiguration;
    OrionClipConfiguration* clipConfiguration;

private:
    OrionaudioAudioProcessor& processor;
    ScopedPointer<TabbedComponent> tabbedComponent;
    
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionTabComponent)
    
    
};
