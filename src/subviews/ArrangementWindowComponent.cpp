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
    addAndMakeVisible(sequencerComponent.get());
}

ArrangementWindowComponent::~ArrangementWindowComponent()
{
    
}

void ArrangementWindowComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("ArrangementWindowComponent", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void ArrangementWindowComponent::resized()
{
    sequencerComponent->setBounds(getLocalBounds());
}
