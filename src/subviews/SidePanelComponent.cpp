/*
  ==============================================================================

    SidePanelComponent.cpp
    Created: 6 Feb 2020 2:08:33pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SidePanelComponent.h"

//==============================================================================
SidePanelComponent::SidePanelComponent(OrionaudioAudioProcessor* p, OrionaudioAudioProcessorEditor* e)
{
    processor = p;
    editor = e;

    fileBrowser.reset(new DraggableFileBrowserComponent());
    addAndMakeVisible(fileBrowser.get());
    
    logoImage.reset(new ImageComponent());
    logoImage->setImage(ImageCache::getFromMemory(BinaryData::logo_png, BinaryData::logo_pngSize), RectanglePlacement::fillDestination);
    addAndMakeVisible(logoImage.get());
}

SidePanelComponent::~SidePanelComponent()
{
    
}

void SidePanelComponent::paint (Graphics& g)
{
    g.fillAll(Colours::red);
}

void SidePanelComponent::resized()
{
    auto area = getLocalBounds();
    auto logoArea = area.removeFromTop(getParentHeight() * .1);
    logoImage->setBounds(logoArea);
    fileBrowser->setBounds(area);
}
