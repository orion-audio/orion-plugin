/*
  ==============================================================================

    CompressorMeter.h
    Created: 11 Aug 2020 5:34:21pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GlobalCoefficients.h"

class CompressorMeter  : public Component
{
public:
    
    CompressorMeter();
    ~CompressorMeter() override;
    
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void updateMeter();
        
    float getCompressorRatioCoef(){return ratioCoef;};
    float getCompressorThreshCoef(){return threshCoef;};

    void setRatioCoef(float inputVal)
    {
        ratioCoef = inputVal;
        repaint();
    };
    void setThreshCoef(float inputVal)
    {
        threshCoef = inputVal;
        repaint();
    };

private:
    
    Colour lineColor;

    //std::unique_ptr<DrawablePath> compressorPath;

    float threshCoef   = 0.5f;//0.0f <-> 1.0f
    float ratioCoef  = 1.0f;//1.0f <-> 0.0f

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorMeter)
};
