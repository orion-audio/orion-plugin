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
    addAndMakeVisible(kitsCombo.get());
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
    backgroundGradient = ColourGradient::vertical(Colour(0xFF4C4C4E), 0, Colour(0xFF222020), getHeight() / 2.f);
    
    auto area = getLocalBounds();
    area.removeFromTop(getHeight() / 4);
    area.removeFromBottom(getHeight() / 4);
    area.removeFromLeft(getHeight() / 4);
    area.setWidth(getWidth() * .15);
    
    kitsCombo->setBounds(area);
    
    

}
