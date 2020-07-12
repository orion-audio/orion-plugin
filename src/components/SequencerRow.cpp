/*
  ==============================================================================

    SequencerRow.cpp
    Created: 12 Jul 2020 1:35:46pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SequencerRow.h"

//==============================================================================
SequencerRow::SequencerRow()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SequencerRow::~SequencerRow()
{
}

void SequencerRow::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("SequencerRow", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void SequencerRow::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
