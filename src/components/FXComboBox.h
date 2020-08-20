/*
  ==============================================================================

    FXComboBox.h
    Created: 18 Aug 2020 3:17:40pm
    Author:  Lei Li

  ==============================================================================
*/
#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GlobalCoefficients.h"


//==============================================================================
/*
*/

class FXComboBox  : public Component
{
public:
    FXComboBox();
    ~FXComboBox() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    std::unique_ptr<TextButton> comboSwitch;
    
private:
    
    Colour comboBoxColour;
    Colour textColour;
    
    std::unique_ptr<DrawablePath> decoratePath;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FXComboBox)
};






