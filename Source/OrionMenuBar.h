/*
  ==============================================================================

    OrionMenuBar.h
    Created: 6 Feb 2020 1:03:58pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class OrionMenuBar    : public Component
{
public:
    OrionMenuBar();
    ~OrionMenuBar();

    void paint (Graphics&) override;
    void resized() override;
    
    
private:
        
    // COMBOS
    std::unique_ptr<ComboBox> kitsCombo;
    std::unique_ptr<ComboBox> uiScaleCombo;
    
    // BUTTONS
    std::unique_ptr<DrawableButton> settingsButton;
    std::unique_ptr<DrawableButton> helpButton;
    std::unique_ptr<ImageButton> arrangeButton;
     
    ColourGradient backgroundGradient;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionMenuBar)
};
