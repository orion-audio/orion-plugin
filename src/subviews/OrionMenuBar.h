/*
  ==============================================================================

    OrionMenuBar.h
    Created: 6 Feb 2020 1:03:58pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "CircularMeter.h"
#include "AutoLabel.h"

class OrionaudioAudioProcessorEditor;

//==============================================================================
/*
*/
class OrionMenuBar : public Component
{
public:
    OrionMenuBar(OrionaudioAudioProcessor*, OrionaudioAudioProcessorEditor*);
    ~OrionMenuBar();

    void paint (Graphics&) override;
    void resized() override;
    
    
private:
    OrionaudioAudioProcessor* processor;
    OrionaudioAudioProcessorEditor* editor;
    
    // COMBOS
    std::unique_ptr<ComboBox> kitsCombo;
    std::unique_ptr<ComboBox> uiScaleCombo;
    
    // BUTTONS
    std::unique_ptr<DrawableButton> settingsButton;
    std::unique_ptr<DrawableButton> helpButton;
    std::unique_ptr<ImageButton> arrangeButton;
     
    // METER
    std::unique_ptr<CircularMeter> inputMeter;
    
    // LABELS
    std::unique_ptr<Label> inputMeterLabel;
    
    ColourGradient backgroundGradient;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionMenuBar)
};
