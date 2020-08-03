/*
  ==============================================================================

    DropdownTable.cpp
    Created: 1 Aug 2020 11:58:04am
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DropdownTable.h"
#include "OrionGlobalVars.h"

//==============================================================================
DropdownTable::DropdownTable(OrionaudioAudioProcessor* p)//: processor(p),
{
    processor = p;
    
    eqConfiguration.reset(new OrionEQConfiguration(*processor));
    addAndMakeVisible(eqConfiguration.get());
    eqConfiguration->setVisible(false);
    
    clipConfiguration.reset(new OrionClipConfiguration(*processor));
    addAndMakeVisible(clipConfiguration.get());
    clipConfiguration->setVisible(false);
    
    envConfiguration.reset(new OrionEnvConfiguration(*processor));
    addAndMakeVisible(envConfiguration.get());
    envConfiguration->setVisible(false);
    
    effectConfiguration.reset(new OrionEffectsConfiguration(*processor));
    addAndMakeVisible(effectConfiguration.get());
    effectConfiguration->setVisible(false);
    
}

DropdownTable::~DropdownTable()
{
    
}


void DropdownTable::paint (Graphics& g)
{
    DBG("DropdownTable ");
    g.fillAll(Colours::black);
    g.setColour (Colours::darkgrey);
    //g.drawHorizontalLine(0, 0, getWidth());
    g.drawLine(0.0f, 0.0f,getWidth(), 0.0f, 0.5f);
    //g.drawRect(0, 0, getWidth(), getHeight());
}


void DropdownTable::resized()
{
    Rectangle<int> area(0, 0, getWidth(), getHeight());
    
    eqConfiguration->setBounds(area);

    clipConfiguration->setBounds(area);

    envConfiguration->setBounds(area);
    
    effectConfiguration->setBounds(area);

}


void DropdownTable::tabChange(int tabNum)
{
    if(tabNum == 0)
    {
        eqConfiguration->setVisible(true);
        clipConfiguration->setVisible(false);
        envConfiguration->setVisible(false);
        effectConfiguration->setVisible(false);
    }
    else if(tabNum == 1)
    {
        eqConfiguration->setVisible(false);
        clipConfiguration->setVisible(true);
        envConfiguration->setVisible(false);
        effectConfiguration->setVisible(false);
    }
    else if(tabNum == 2)
    {
        eqConfiguration->setVisible(false);
        clipConfiguration->setVisible(false);
        envConfiguration->setVisible(true);
        effectConfiguration->setVisible(false);
    }
    else if(tabNum == 3)
    {
        eqConfiguration->setVisible(false);
        clipConfiguration->setVisible(false);
        envConfiguration->setVisible(false);
        effectConfiguration->setVisible(true);
    }
    
}
