/*
  ==============================================================================

    SequencerRow.h
    Created: 12 Jul 2020 1:35:46pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SequencerRow    : public Component
{
public:
    SequencerRow();
    ~SequencerRow();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequencerRow)
};
