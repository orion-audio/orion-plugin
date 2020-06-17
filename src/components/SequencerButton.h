/*
  ==============================================================================

    SequencerButton.h
    Created: 16 Jun 2020 8:49:02pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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
    
    SequencerButton();
    ~SequencerButton();
    
    virtual void timerCallback() override;


    
    virtual void paint (Graphics&) override;
    void startAnimation();

private:
    int frameCount = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequencerButton)
};
