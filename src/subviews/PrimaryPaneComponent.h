/*
  ==============================================================================

    PrimaryPaneComponent.h
    Created: 6 Feb 2020 1:20:29pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveWiggle.h"
#include <array>
#include "DragAndDropButton.h"

class OrionaudioAudioProcessorEditor;

//==============================================================================
/*
*/
class PrimaryPaneComponent : public Component
{
public:
    PrimaryPaneComponent(OrionaudioAudioProcessorEditor* editor);
    ~PrimaryPaneComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    // BUTTONS
    std::array<std::unique_ptr<DragAndDropButton>, 8> drumButtons;
    std::unique_ptr<WaveWiggle> waveWiggle;

    std::unique_ptr<ImageButton> dropDownButton;
    
    std::unique_ptr<ImageButton> soloButton;
    std::unique_ptr<ImageButton> muteButton;
    
    ColourGradient backgroundGradient;
    OrionaudioAudioProcessorEditor* editor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrimaryPaneComponent)
};
