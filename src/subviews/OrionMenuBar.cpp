/*
  ==============================================================================

    OrionMenuBar.cpp
    Created: 6 Feb 2020 1:03:58pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionMenuBar.h"
#include "PluginEditor.h"

//==============================================================================
OrionMenuBar::OrionMenuBar(OrionaudioAudioProcessor* p, OrionaudioAudioProcessorEditor* e)
{
    processor = p;
    editor = e;
    
    kitsCombo.reset(new ComboBox());
    kitsCombo->setText("Isaac's Kit");
    addAndMakeVisible(kitsCombo.get());
    
    arrangeButton.reset(new ImageButton());
    Image upImage = ImageCache::getFromMemory(BinaryData::a_png, BinaryData::a_pngSize);
    arrangeButton->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    arrangeButton->setClickingTogglesState(true);
    arrangeButton->onStateChange = [&] { editor->toggleArrangmentWindow(arrangeButton->getToggleState()); };
    addAndMakeVisible(arrangeButton.get());
    
    inputMeter.reset(new CircularMeter());
    inputMeter->updaterFunction = [this] { return processor->getInputLevel();};
    addAndMakeVisible(inputMeter.get());
    
    inputMeterLabel.reset(new Label("Mic", "Mic"));
    addAndMakeVisible(inputMeterLabel.get());
    
}

OrionMenuBar::~OrionMenuBar()
{
    
}

void OrionMenuBar::paint (Graphics& g)
{
    
    
    const String colourString ("0000000");
    const Colour colour (Colour::fromString ("FF" + colourString));
    
    //g.setColour(Colours::black);
    g.setColour(colour);
    
    //g.setGradientFill(backgroundGradient);
    g.fillAll();
    
    Rectangle<float> area;
    area.setX(inputMeterLabel->getX());
    area.setY(inputMeterLabel->getY());
    area.setRight(inputMeter->getRight());
    area.setHeight(inputMeterLabel->getHeight());
    
    g.fillRoundedRectangle(area, 2.f);
    
}

void OrionMenuBar::resized()
{
    int spacing = getWidth() * (.1);
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
    
    area.translate(spacing, 0);
    
    area.setWidth(area.getWidth() * .3);
    inputMeterLabel->setBounds(area);
    area = area.withSizeKeepingCentre(area.getWidth() * 3, area.getHeight() * .5);
    area.setX(inputMeterLabel->getRight());
    inputMeter->setBounds(area);
}
