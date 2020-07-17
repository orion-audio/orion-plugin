/*
  ==============================================================================

    EnvelopeMeter.h
    Created: 16 Jul 2020 11:41:29am
    Author:  Lei Li

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GlobalCoefficients.h"

class EnvelopeMeter  : public Component
{
public:
    EnvelopeMeter();
    ~EnvelopeMeter() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    //------------------------------------
    int serial = -1;
    
    void setSustainBendCoefficient(float SBC){sustainBendCoef = SBC;};
        

private:
    
    Colour waveColor;
    Colour EnvelopeColor;
    
    
    float attackCoef  = 0.1f;
    float decayCoef   = 0.2f;
    float sustainCoef = 0.5f;
    float releaseCoef = 1.0f;

    float attackBendCoef  = 0.5f;
    float decayBendCoef   = 0.5f;
    float sustainBendCoef = 0.5f;
    float releaseBendCoef = 0.5f;
    

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeMeter)
};
