/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "OrionTabComponent.h"


//==============================================================================
/**
*/
class OrionaudioAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    OrionaudioAudioProcessorEditor (OrionaudioAudioProcessor&);
    ~OrionaudioAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void tabComponentChanged(int serial);
 
    std::unique_ptr<AudioFormatReaderSource> playSource;
private:
    
    OrionaudioAudioProcessor& processor;
    //ScopedPointer<OrionTabComponent> tabComponent;
    OrionTabComponent *tabComponent[7];
    //ScopedPointer<CTAGTabComponent> tabComponent;
    
    
    void kickButtonClicked();
    void snareButtonClicked();
    void clapButtonClicked();
    void percButtonClicked();
    
    
    void HiHatButtonClicked();
    void cymbalButtonClicked();
    void snapButtonClicked();
    
    TextButton instrumentTriggers[6];
    
    
    TextButton kickButton;
    TextButton snareButton;
    TextButton clapButton;
    TextButton percButton;
    
    TextButton HiHatButton;
    TextButton cymbalButton;
    TextButton snapButton;
    
    AudioFormatManager formatManager;
   
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionaudioAudioProcessorEditor)
};
