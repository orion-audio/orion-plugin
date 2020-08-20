/*
  ==============================================================================

    CompressorSidechainSelectWindow.cpp
    Created: 19 Aug 2020 9:04:44pm
    Author:  Lei Li

  ==============================================================================
*/

#include "CompressorSidechainSelectWindow.h"

//==============================================================================
CompressorSidechainSelectWindow::CompressorSidechainSelectWindow()
{

    decoratePath.reset(new DrawablePath());
    addAndMakeVisible(decoratePath.get());
    decoratePath->replaceColour(Colours::black,Colours::darkgrey);
    decoratePath->setAlpha(0.75);
    
 
    comboBoxColour =  Colour(0xFF1E1D1E);
    textColour = Colour (0xFFFFFFFF);

    
    
    // Sidechain Select Cells
    for (int i = 0; i <= instrumentAmount; i++)
    {
        sidechainSelectCells[i].reset(new CompressorSidechainSelectCell());
        if(i == 0)
        {
          sidechainSelectCells[i]->setButtonText("None");
        }
        else
        {
          sidechainSelectCells[i]->setButtonText(instrumentName[i-1]);
        }
        sidechainSelectCells[i]->setColour(TextButton::textColourOnId, comboBoxColour);
        sidechainSelectCells[i]->setColour(TextButton::textColourOffId, textColour);
        sidechainSelectCells[i]->setColour(TextButton::buttonOnColourId, comboBoxColour);
        sidechainSelectCells[i]->setColour(TextButton::buttonColourId, comboBoxColour);
        sidechainSelectCells[i]->setColour(ComboBox::outlineColourId,comboBoxColour);
        sidechainSelectCells[i]->tag = i;
        addAndMakeVisible(sidechainSelectCells[i].get());
    }

}

CompressorSidechainSelectWindow::~CompressorSidechainSelectWindow()
{
    
}

void CompressorSidechainSelectWindow::paint (juce::Graphics& g)
{
    g.setColour (comboBoxColour);
    g.fillRoundedRectangle (getLocalBounds().toFloat(), 7.5);

}

void CompressorSidechainSelectWindow::resized()
{
    
    Rectangle<int> area = getLocalBounds();
    //sidechainSwitch->setBounds(area);
    
    int XCoef = 0;
    int YCoef = 0;
    
    for (int i = 0; i <= instrumentAmount; i++)
    {
        if(i == 0)
        {
            area = Rectangle<int>(0, 0,  getWidth(), getHeight()/5);
        }
        else
        {
            area = Rectangle<int>(XCoef * getWidth()/2, YCoef * getHeight()/5,  getWidth()/2, getHeight()/5);
        }
        
        sidechainSelectCells[i]->setBounds(area);
        
        double tmp = double(i)/2;
        if(floor(tmp + 0.5) == tmp)
        {
            YCoef += 1;
            XCoef = 0;
        }
        else
        {
            XCoef = 1;
        }
        
    }

}
