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

class ArrangementWindowComponent : public Component
{
public:
    ArrangementWindowComponent(OrionaudioAudioProcessor*, OrionaudioAudioProcessorEditor*);
    ~ArrangementWindowComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    OrionaudioAudioProcessor* processor;
    OrionaudioAudioProcessorEditor* editor;
    
    std::unique_ptr<SequencerComponent> sequencerComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArrangementWindowComponent)
};

