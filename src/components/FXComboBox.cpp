/*
  ==============================================================================

    FXComboBox.cpp
    Created: 18 Aug 2020 3:17:40pm
    Author:  Lei Li

  ==============================================================================
*/


#include "../JuceLibraryCode/JuceHeader.h"
#include "FXComboBox.h"

//==============================================================================
FXComboBox::FXComboBox()
{

    decoratePath.reset(new DrawablePath());
    addAndMakeVisible(decoratePath.get());
    decoratePath->replaceColour(Colours::black,Colours::darkgrey);
    decoratePath->setAlpha(0.75);
    
 
    comboBoxColour =  Colour(0xFF1E1D1E);
    textColour = Colour (0xFF18F5F5);

    
    
    // Sidechain Switch
    comboSwitch.reset(new TextButton());
    comboSwitch->setButtonText("None");
    comboSwitch->setColour(TextButton::textColourOnId, comboBoxColour);
    comboSwitch->setColour(TextButton::textColourOffId, textColour);
    comboSwitch->setColour(TextButton::buttonOnColourId, comboBoxColour);
    comboSwitch->setColour(TextButton::buttonColourId, comboBoxColour);
    comboSwitch->setColour(ComboBox::outlineColourId,comboBoxColour);
    addAndMakeVisible(comboSwitch.get());
    
}

FXComboBox::~FXComboBox()
{
    
}

void FXComboBox::paint (juce::Graphics& g)
{

}

void FXComboBox::resized()
{
    
    Rectangle<int> area = getLocalBounds();
    comboSwitch->setBounds(area);

}
