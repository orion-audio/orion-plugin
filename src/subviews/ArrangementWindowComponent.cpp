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
    //    sequencerViewport.setScrollBarsShown(false, true);
    //    addAndMakeVisible(sequencerViewport);
    
    sequenceLengthSlider.reset(new Slider());
    sequenceLengthSlider->setRange(1, 128, 1);
    sequenceLengthSlider->addListener(this);
    addAndMakeVisible(sequenceLengthSlider.get());
    
    StringArray subdivisions;
    subdivisions.add("2n");
    subdivisions.add("4n");
    subdivisions.add("8n");
    subdivisions.add("16n");
    subdivisions.add("32n");
    
    subdivisionCombo.addItemList(subdivisions, 1);
    subdivisionCombo.onChange = [&] {
        NoteSequence::SubDivision newSubdivision;
        
        switch (subdivisionCombo.getSelectedId()) {
            case 1:
                newSubdivision = NoteSequence::SubDivision::half;
                break;
            case 2:
                newSubdivision = NoteSequence::SubDivision::quarter;
                break;
            case 3:
                newSubdivision = NoteSequence::SubDivision::eighth;
                break;
            case 4:
                newSubdivision = NoteSequence::SubDivision::sixteenth;
                break;
            case 5:
                newSubdivision = NoteSequence::SubDivision::thirtysecond;
                break;
            default:
                break;
        }
        sequencerComponent->setSubDivision(newSubdivision);
        
    };
    addAndMakeVisible(subdivisionCombo);
    
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
    sequencerComponent->setBounds(getLocalBounds().removeFromBottom(getHeight() * .9));
    
    area = getLocalBounds().removeFromTop(getHeight() * .1);
    subdivisionCombo.setBounds(area);
        
}

void ArrangementWindowComponent::sliderValueChanged(Slider *slider) {
    if (slider == sequenceLengthSlider.get()) {
        sequencerComponent->setSequenceLength(sequenceLengthSlider->getValue());
    }
}

