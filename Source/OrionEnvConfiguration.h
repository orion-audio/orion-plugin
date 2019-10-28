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

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
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
    
    std::unique_ptr<SliderAttachment> envAttackTree;
    std::unique_ptr<SliderAttachment> envHoldTree;
    std::unique_ptr<SliderAttachment> envDecayTree;
    std::unique_ptr<SliderAttachment> envReleaseTree;
    
    std::unique_ptr<SliderAttachment> envAttackBendTree;
    std::unique_ptr<SliderAttachment> envSustainTree;
    std::unique_ptr<SliderAttachment> envDecayBendTree;
    std::unique_ptr<SliderAttachment> envReleaseBendTree;
    
    
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
