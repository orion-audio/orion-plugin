/*
  ==============================================================================

    PrimaryPaneComponent.cpp
    Created: 6 Feb 2020 1:20:29pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PrimaryPaneComponent.h"

//==============================================================================
PrimaryPaneComponent::PrimaryPaneComponent()
{
    for (int i = 0; i < drumButtons.size(); i++)
    {
        drumButtons[i].reset(new DragAndDropButton());
        addAndMakeVisible(drumButtons[i].get());
    }
    
    Image downImage;
    Image upImage;
    
    downImage = ImageCache::getFromMemory(BinaryData::kick_on_png, BinaryData::kick_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::kick_off_png, BinaryData::kick_off_pngSize);
    drumButtons[0]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    
    downImage = ImageCache::getFromMemory(BinaryData::snare_on_png, BinaryData::snare_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::snare_off_png, BinaryData::snare_off_pngSize);
    drumButtons[1]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);

    downImage = ImageCache::getFromMemory(BinaryData::snare_on_png, BinaryData::snare_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::snare_off_png, BinaryData::snare_off_pngSize);
    drumButtons[2]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);

    downImage = ImageCache::getFromMemory(BinaryData::snare_on_png, BinaryData::snare_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::snare_off_png, BinaryData::snare_off_pngSize);
    drumButtons[3]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);

    
    downImage = ImageCache::getFromMemory(BinaryData::snare_on_png, BinaryData::snare_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::snare_off_png, BinaryData::snare_off_pngSize);
    drumButtons[4]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);

    
    downImage = ImageCache::getFromMemory(BinaryData::snare_on_png, BinaryData::snare_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::snare_off_png, BinaryData::snare_off_pngSize);
    drumButtons[5]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);

    
    downImage = ImageCache::getFromMemory(BinaryData::snare_on_png, BinaryData::snare_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::snare_off_png, BinaryData::snare_off_pngSize);
    drumButtons[6]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);

    
    downImage = ImageCache::getFromMemory(BinaryData::snare_on_png, BinaryData::snare_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::snare_off_png, BinaryData::snare_off_pngSize);
    drumButtons[7]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);


}

PrimaryPaneComponent::~PrimaryPaneComponent()
{
}

void PrimaryPaneComponent::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void PrimaryPaneComponent::resized()
{
    auto area = getLocalBounds();
    int buttonWidth = getWidth() * .2;
    int drumCount = 0;
    area.setSize(getWidth() / 4, getHeight() * .25);
    area.translate(0, area.getHeight() / 2);
    for (int i = 0; i < 2; i++)
    {
        area.setX(0);
        for (int j = 0; j < 4; j++)
        {
            drumButtons[drumCount]->setBounds(area.withSizeKeepingCentre(buttonWidth, area.getHeight()));
            drumCount++;
            area.translate(getWidth() / 4, 0);
        }
        area.translate(0, area.getHeight());
    }
}
