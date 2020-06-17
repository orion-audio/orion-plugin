/*
  ==============================================================================

    SequencerButton.cpp
    Created: 16 Jun 2020 8:49:02pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SequencerButton.h"

//==============================================================================
SequencerButton::SequencerButton()
{
    setColour(SequencerButton::ColourIds::borderColourOn, Colours::white);
    setColour(SequencerButton::ColourIds::borderColourOff, Colours::white);
    setColour(SequencerButton::ColourIds::fillColourOn, Colours::white);
    setColour(SequencerButton::ColourIds::borderColourOn, Colours::transparentBlack);
}

SequencerButton::~SequencerButton()
{
}

void SequencerButton::paint (Graphics& g)
{
    Colour colour;
    if (getToggleState() == true && frameCount == 0) {
        colour = findColour(ColourIds::fillColourOn);
    }
    
    else if (getToggleState() == false) {
        colour = findColour(ColourIds::fillColourOff);
    }
    
    else if (frameCount != 0) {
        float normalizedCount = (frameCount - 0) / (ANIMATION_LENGTH - 0);
        float opacity = 1.f - normalizedCount;
        colour = findColour(ColourIds::fillColourOn).withAlpha(opacity);
    }
    
    g.setColour(colour);
    g.fillEllipse(getLocalBounds().toFloat());
}

void SequencerButton::timerCallback() {
    frameCount += 1;
    if (frameCount >= ANIMATION_LENGTH) {
        frameCount = 0;
        stopTimer();
    }
}

void SequencerButton::startAnimation() {
    startTimerHz(30);
}
