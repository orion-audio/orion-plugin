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
SidePanelComponent::SidePanelComponent()
{
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
    g.setColour(Colours::red);//- Test -!!!!!
    Rectangle<int> area(getParentMonitorArea());//- Test -!!!!!
    g.drawRect (area, .01);//- Test -!!!!!
    g.fillAll();
    //g.fillAll(Colours::red);
}

void SidePanelComponent::resized()
{
    auto area = getLocalBounds();
    auto logoArea = area.removeFromTop(getHeight() * .1);
    logoImage->setBounds(logoArea);
    fileBrowser->setBounds(area);
}
