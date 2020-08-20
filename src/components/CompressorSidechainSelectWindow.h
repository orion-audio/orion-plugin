/*
  ==============================================================================

    CompressorSidechainSelectWindow.h
    Created: 19 Aug 2020 9:04:44pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GlobalCoefficients.h"


//==============================================================================
/*
*/


class CompressorSidechainSelectCell  : public TextButton
{
public:
    int tag = -1;
    CompressorSidechainSelectCell(){};
    ~CompressorSidechainSelectCell(){};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorSidechainSelectCell)
};

class CompressorSidechainSelectWindow  : public Component
{
public:
    CompressorSidechainSelectWindow();
    ~CompressorSidechainSelectWindow() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    std::array<std::unique_ptr<CompressorSidechainSelectCell>, 9> sidechainSelectCells;
    
private:
    
    Colour comboBoxColour;
    Colour textColour;
    
    std::unique_ptr<DrawablePath> decoratePath;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorSidechainSelectWindow)
};
