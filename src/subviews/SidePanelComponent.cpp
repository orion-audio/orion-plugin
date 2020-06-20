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

    
    
    // Background Image
    Image backgroundImage = ImageCache::getFromMemory(BinaryData::sidePanelBackground_png, BinaryData::sidePanelBackground_pngSize);
    backgroundImageView.reset(new DrawableImage());
    backgroundImageView->setImage(backgroundImage);
    addAndMakeVisible(backgroundImageView.get());
    
    // Logo Image
    logoImage.reset(new ImageComponent());
    logoImage->setImage(ImageCache::getFromMemory(BinaryData::logo_png, BinaryData::logo_pngSize), RectanglePlacement::fillDestination);
    addAndMakeVisible(logoImage.get());
    
    // FileBrowser Image
    fileBrowser.reset(new DraggableFileBrowserComponent());
    addAndMakeVisible(fileBrowser.get());
}

SidePanelComponent::~SidePanelComponent()
{
    
}

void SidePanelComponent::paint (Graphics& g)
{
    //g.fillAll(Colours::red);
}

void SidePanelComponent::resized()
{
    
    //Background
    Rectangle<int> backgroundArea(0, 0, getWidth(), getHeight());
    backgroundImageView->setTransformToFit(backgroundArea.toFloat(), RectanglePlacement::stretchToFit);
    
    auto area = getLocalBounds();
    auto logoArea = area.removeFromTop(getHeight() / 12);
    
    logoImage->setBounds(logoArea);
    
    Rectangle<int> fileBrowerframeSize(0, getHeight() / 12, getWidth(), getHeight() * 9 / 12);
    fileBrowser->setBounds(fileBrowerframeSize);
}
