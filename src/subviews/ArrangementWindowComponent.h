/*
  ==============================================================================

    ArrangementWindowComponent.h
    Created: 12 Feb 2020 4:38:01pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "SequencerComponent.h"
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class OrionaudioAudioProcessorEditor;

class ArrangementWindowComponent : public Component, public Slider::Listener
{
public:
    ArrangementWindowComponent(OrionaudioAudioProcessor*, OrionaudioAudioProcessorEditor*);
    ~ArrangementWindowComponent();

    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider *slider) override;

private:
    
    OrionaudioAudioProcessor* processor;
    OrionaudioAudioProcessorEditor* editor;
    
    std::unique_ptr<SequencerComponent> sequencerComponent;
    Viewport sequencerViewport;
    
    std::unique_ptr<Slider> sequenceLengthSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArrangementWindowComponent)
};

