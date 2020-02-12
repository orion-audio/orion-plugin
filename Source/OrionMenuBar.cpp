/*
  ==============================================================================

    OrionMenuBar.cpp
    Created: 6 Feb 2020 1:03:58pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionMenuBar.h"

//==============================================================================
OrionMenuBar::OrionMenuBar()
{
    kitsCombo.reset(new ComboBox());
    kitsCombo->setText("Isaac's Kit");
    addAndMakeVisible(kitsCombo.get());
    
    arrangeButton.reset(new ImageButton());
    Image upImage = ImageCache::getFromMemory(BinaryData::a_png, BinaryData::a_pngSize);
    arrangeButton->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    addAndMakeVisible(arrangeButton.get());
    
}

OrionMenuBar::~OrionMenuBar()
{
}

void OrionMenuBar::paint (Graphics& g)
{
    g.setGradientFill(backgroundGradient);
    g.fillAll();
}

void OrionMenuBar::resized()
{
    int spacing = getWidth() * JUCE_LIVE_CONSTANT(.1);
    backgroundGradient = ColourGradient::vertical(Colour(0xFF4C4C4E), 0, Colour(0xFF222020), getHeight() / 2.f);
    
    auto area = getLocalBounds();
    area.removeFromTop(getHeight() / 4);
    area.removeFromBottom(getHeight() / 4);
    area.removeFromLeft(getHeight() / 4);
    area.setWidth(getWidth() * .2);
    kitsCombo->setBounds(area);

    area.translate(area.getWidth() + spacing, 0);
    area.translate(area.getWidth() + spacing, 0);

    arrangeButton->setBounds(area.withWidth(area.getHeight()));
    

}
