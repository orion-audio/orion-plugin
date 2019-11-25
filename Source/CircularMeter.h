/*
  ==============================================================================

    CircularMeter.h
    Created: 2 Oct 2019 12:34:36pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class CircularMeter : public Component, public Timer
{
public:
    enum ColourIds : int
    {
        backgroundColourId = 1,
        filledColourId,
        clipColourId
    };
    CircularMeter();
    ~CircularMeter();

    void paint (Graphics&) override;
    void resized() override;
    
    void timerCallback() override;

    int numCircles = 6;
    
    std::function<float()> updaterFunction;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CircularMeter)
};
