/*
  ==============================================================================

    ImagerMeter.h
    Created: 26 Aug 2020 3:38:47pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GlobalCoefficients.h"

//==============================================================================
/*
*/
class ImagerMeter  : public Component
{
public:
    ImagerMeter();
    ~ImagerMeter() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setImagerCoef(float inputVal)
    {
        imagerCoef = inputVal;
        updateImager();
        repaint();
    };
    
    void setImagerMode(bool inputVal)
    {
        mode = inputVal;
        updateImager();
        repaint();
    };
    
    void updateImager();
    
    //--------------------------------------
private:
    
    Colour lineColor;
    Colour shadowColor;
    
    std::unique_ptr<DrawablePath> imagerPath;
    
    bool mode = false;
    
    float imagerCoef = 0.5f;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImagerMeter)
};
