/*
  ==============================================================================

    OrionEffectDelay.h
    Created: 11 Jun 2019 9:28:51pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class OrionEffectDelay    : public Component,
                            public Slider::Listener
{
public:
    OrionEffectDelay(OrionaudioAudioProcessor&, int serial);
    ~OrionEffectDelay();

    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override;
    int effectDelaySerial;
    
   //void componentMovedOrResized (Component& component, bool /*wasMoved*/, bool /*wasResized*/) override;

private:
  
    OrionaudioAudioProcessor& processor;
    
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> delayTimeTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> delayFeedbackTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> delayColorTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> delayPanTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> delayDryWetTree;
    
    //ScopedPointer<Slider> delayTimeSlider;
    
    Slider delayTimeSlider;
    Slider delayFeedbackSlider;
    Slider delayColorSlider;
    Slider delayPanSlider;
    Slider delayDryWetSlider;
    
    Label delayTimeLabel;
    Label delayFeedbackLabel;
    Label delayColorLabel;
    Label delayPanLabel;
    Label delayDryWetLabel;
    
    
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
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionEffectDelay)
};
