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

//==============================================================================
/*
*/
class PrimaryPaneComponent : public Component
{
public:
    PrimaryPaneComponent();
    ~PrimaryPaneComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    // BUTTONS
    std::array<std::unique_ptr<DragAndDropButton>, 8> drumButtons;
    std::unique_ptr<WaveWiggle> waveWiggle;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrimaryPaneComponent)
};
