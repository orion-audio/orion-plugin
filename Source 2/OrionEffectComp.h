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
//==============================================================================
/*
 */
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
    
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> compRatioTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> compAttackTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> compReleaseTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> compGainTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> compThreshTree;
    
    Slider compRatioSlider;
    Slider compAttackSlider;
    Slider compReleaseSlider;
    Slider compGainSlider;
    Slider compThreshSlider;
    
    Label compRatioLabel;
    Label compAttackLabel;
    Label compReleaseLabel;
    Label compGainLabel;
    Label compThreshLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionEffectComp)
};

