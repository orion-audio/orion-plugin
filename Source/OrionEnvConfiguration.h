/*
  ==============================================================================

    OrionEnvConfiguration.h
    Created: 21 Jun 2019 1:10:03pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "OrionRotarySlider.h"

//==============================================================================
class OrionEnvConfiguration    : public Component
{
public:
    OrionEnvConfiguration(OrionaudioAudioProcessor& p,int serial);
    ~OrionEnvConfiguration();

    void paint(Graphics& g) override;
    void resized() override;
    int envSerial;
private:
    OrionaudioAudioProcessor& processor;
    
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> envAttackTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> envHoldTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> envDecayTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> envReleaseTree;
    
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> envAttackBendTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> envSustainTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> envDecayBendTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> envReleaseBendTree;
    
    
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> envSwitchButtonAttachment;
    
    
    Slider envAttackSlider;
    Slider envHoldSlider;
    Slider envDecaySlider;
    Slider envReleaseSlider;
    
    Slider envAttackBendSlider;
    Slider envSustainSlider;
    Slider envDecayBendSlider;
    Slider envReleaseBendSlider;
    
    
    ToggleButton envSwitchButton;
    
    Label envAttackLabel;
    Label envHoldLabel;
    Label envDecayLabel;
    Label envReleaseLabel;
    
    Label envAttackBendLabel;
    Label envSustainLabel;
    Label envDecayBendLabel;
    Label envReleaseBendLabel;
    
    
    File* envbackground;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionEnvConfiguration)
};
