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
#include "OrionRotarySlider.h"

//==============================================================================

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

class rotarySliderLookAndFeelTest: public LookAndFeel_V4
{
public:
    /* Constructor */
    rotarySliderLookAndFeelTest()
    {
        setColour(Slider::thumbColourId, juce::Colours::chocolate);
        setColour(Slider::rotarySliderOutlineColourId, juce::Colours::black);
        setColour(Slider::rotarySliderFillColourId, juce::Colours::blanchedalmond);
    }
    
};
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
    
    LookAndFeel_V4 rotarySliderLAFV1;

    std::unique_ptr<SliderAttachment> delayTimeTree;
    std::unique_ptr<SliderAttachment> delayFeedbackTree;
    std::unique_ptr<SliderAttachment> delayColorTree;
    std::unique_ptr<SliderAttachment> delayPanTree;
    std::unique_ptr<SliderAttachment> delayDryWetTree;
    
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> delaySwitchButtonAttachment;
    
    
    Slider delayTimeSlider;
    Slider delayFeedbackSlider;
    Slider delayColorSlider;
    Slider delayPanSlider;
    Slider delayDryWetSlider;
    
    
    ToggleButton delaySwitchButton;
    
    Label delayTimeLabel;
    Label delayFeedbackLabel;
    Label delayColorLabel;
    Label delayPanLabel;
    Label delayDryWetLabel;
    
    
    rotarySliderLookAndFeelTest rotarySliderLookAndFeelTest;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionEffectDelay)
};




