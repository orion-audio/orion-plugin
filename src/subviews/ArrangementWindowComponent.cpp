/*
 ==============================================================================
 
 ArrangementWindowComponent.cpp
 Created: 12 Feb 2020 4:38:01pm
 Author:  Quin Scacheri
 
 ==============================================================================
 */

#include "../../JuceLibraryCode/JuceHeader.h"
#include "ArrangementWindowComponent.h"
#include "PluginEditor.h"

//==============================================================================
ArrangementWindowComponent::ArrangementWindowComponent(OrionaudioAudioProcessor* p, OrionaudioAudioProcessorEditor* e)
{
    processor = p;
    editor = e;
    
    sequencerComponent.reset(new SequencerComponent(*processor->getSequencer()));
    //    sequencerViewport.setViewedComponent(sequencerComponent.get(), false);
    addAndMakeVisible(sequencerComponent.get());
    
}

ArrangementWindowComponent::~ArrangementWindowComponent()
{
    
}

void ArrangementWindowComponent::paint (Graphics& g)
{
    
}

void ArrangementWindowComponent::resized()
{
    sequencerComponent->setBounds(getLocalBounds());        
}

void ArrangementWindowComponent::sliderValueChanged(Slider *slider) {
}

