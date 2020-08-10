/*
  ==============================================================================

    SequencerButton.h
    Created: 16 Jun 2020 8:49:02pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Note.h"

const int ANIMATION_LENGTH = 20;
//==============================================================================
/*
*/
class SequencerButton : public ToggleButton, Timer
{
public:
    enum ColourIds : int {
        borderColourOn = 1,
        borderColourOff,
        fillColourOn,
        fillColourOff
    };
    
    SequencerButton(int p, double b);
    ~SequencerButton();
    
    virtual void paintButton (Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    virtual void timerCallback() override;
    
    void startAnimation();
    
    int getPitch() { return pitch; }
    double getBeat() { return beat; }
    
    void setBeat(double beat) {this->beat = beat;};

private:
    int pitch;
    double beat;

    int frameCount = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequencerButton)
};
