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
    sequencerViewport.setViewedComponent(sequencerComponent.get(), false);
//    addAndMakeVisible(sequencerComponent.get());
    sequencerViewport.setScrollBarsShown(false, true);
    addAndMakeVisible(sequencerViewport);
    
    sequenceLengthSlider.reset(new Slider());
    sequenceLengthSlider->setRange(1, 128, 1);
    sequenceLengthSlider->addListener(this);
    addAndMakeVisible(sequenceLengthSlider.get());
}

ArrangementWindowComponent::~ArrangementWindowComponent()
{
    
}

void ArrangementWindowComponent::paint (Graphics& g)
{

}

void ArrangementWindowComponent::resized()
{
    auto area = getLocalBounds();
    area.removeFromLeft(getWidth() * .25);
    area.removeFromBottom(getHeight() * .25);
    sequencerViewport.setBounds(area);
    sequencerComponent->setSizeWithOverflow(area.getHeight());

    area = getLocalBounds().removeFromBottom(getHeight() * .25);
    sequenceLengthSlider->setBounds(area);
    
}

void ArrangementWindowComponent::sliderValueChanged(Slider *slider) {
    if (slider == sequenceLengthSlider.get()) {
        sequencerComponent->setSequenceLength(sequenceLengthSlider->getValue());
    }
}

