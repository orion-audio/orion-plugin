/*
  ==============================================================================

    ClipMeter.h
    Created: 12 Sep 2020 9:00:56pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
//#include "GlobalCoefficients.h"


class ClipMeter  : public Component
{
public:
    ClipMeter();
    ~ClipMeter() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    void updateZone();
//    void ULButtonClicked(bool isDown);
//    void URButtonClicked(bool isDown);
    
    
//    float getSampleLength()
//    {
//        float sampleLengthInMS = 1000 * instrumentSampleBuffer[instrumetClickedSerial]->getNumSamples()/globalSampleRate;
//        return sampleLengthInMS;
//    };
    
    void setReverseMode(bool inputVal)
    {
//        mode = inputVal;
//        updateImager();
        repaint();
    };

private:

    Colour waveColor;

    std::unique_ptr<DrawablePath> zonePath;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClipMeter)
};
