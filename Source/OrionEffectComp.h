/*
  ==============================================================================

    OrionEffectComp.h
    Created: 11 Jun 2019 11:35:50pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "OrionRotarySlider.h"
//==============================================================================
/*
 */

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class OrionEffectComp    : public Component,
                           public Slider::Listener
{
public:
    OrionEffectComp(OrionaudioAudioProcessor&, int serial);
    ~OrionEffectComp();
    
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override;
    int effectCompSerial;
    
private:
    OrionaudioAudioProcessor& processor;
    
    std::unique_ptr<SliderAttachment> compRatioTree;
    std::unique_ptr<SliderAttachment> compAttackTree;
    std::unique_ptr<SliderAttachment> compReleaseTree;
    std::unique_ptr<SliderAttachment> compGainTree;
    std::unique_ptr<SliderAttachment> compThreshTree;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> compSwitchButtonAttachment;
    
    Slider compRatioSlider;
    Slider compAttackSlider;
    Slider compReleaseSlider;
    Slider compGainSlider;
    Slider compThreshSlider;
    
    
    ToggleButton compSwitchButton;
    
    Label compRatioLabel;
    Label compAttackLabel;
    Label compReleaseLabel;
    Label compGainLabel;
    Label compThreshLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionEffectComp)
};

