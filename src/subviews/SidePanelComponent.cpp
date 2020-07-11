/*
  ==============================================================================

    SidePanelComponent.cpp
    Created: 6 Feb 2020 2:08:33pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SidePanelComponent.h"
#include "PluginEditor.h"

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
    
    
    //auto area = getLocalBounds();
    //auto logoArea = area.removeFromTop(getHeight() / 12);
    

    float unite = getHeight()/33;
    
    auto logoArea = Rectangle<int>(0, 0, getWidth(), 2.9 * unite);
    
    logoImage->setBounds(logoArea);
    
    Rectangle<int> fileBrowerframeSize(getWidth()/30, 3 * unite, getWidth()*18/20, 28 * unite);
    fileBrowser->setBounds(fileBrowerframeSize);
    
    
}
