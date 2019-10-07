/*
  ==============================================================================

    OrionEffectReverb.h
    Created: 28 Jun 2019 10:45:30am
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
class OrionEffectReverb    : public Component,
                            public Slider::Listener
{
public:
    OrionEffectReverb(OrionaudioAudioProcessor&, int serial);
    ~OrionEffectReverb();
    
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override;
    int effectReverbSerial;
    
    //void componentMovedOrResized (Component& component, bool /*wasMoved*/, bool /*wasResized*/) override;
    
private:
    
    OrionaudioAudioProcessor& processor;
    
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> reverbPredelayTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> reverbSizeTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> reverbColorTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> reverbDecayTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> reverbDryTree;
    
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> reverbSwitchButtonAttachment;
    
    //ScopedPointer<Slider> delayTimeSlider;
    
    Slider reverbPredelaySlider;
    Slider reverbSizeSlider;
    Slider reverbColorSlider;
    Slider reverbDecaySlider;
    Slider reverbDrySlider;
    
    ToggleButton reverbSwitchButton;
    
    Label reverbPredelayLabel;
    Label reverbSizeLabel;
    Label reverbColorLabel;
    Label reverbDecayLabel;
    Label reverbDryLabel;
    
    
    //    ScopedPointer<Slider> delayTimeSlider;
    //    ScopedPointer<Slider> delayFeedbackSlider;
    //    ScopedPointer<Slider> delayColorSlider;
    //    ScopedPointer<Slider> delayPanSlider;
    //    ScopedPointer<Slider> delayDryWetSlider;
    //
    //    ScopedPointer<Label> delayTimeLabel;
    //    ScopedPointer<Label> delayFeedbackLabel;
    //    ScopedPointer<Label> delayColorLabel;
    //    ScopedPointer<Label> delayPanLabel;
    //    ScopedPointer<Label> delayDryWetLabel;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionEffectReverb)
};


