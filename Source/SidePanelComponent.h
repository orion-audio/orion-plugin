/*
  ==============================================================================

    SidePanelComponent.h
    Created: 6 Feb 2020 2:08:33pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DraggableFileBrowserComponent.h"

//==============================================================================
/*
*/
class SidePanelComponent    : public Component
{
public:
    SidePanelComponent();
    ~SidePanelComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    std::unique_ptr<ImageComponent> logoImage;
    std::unique_ptr<DraggableFileBrowserComponent> fileBrowser;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidePanelComponent)
};
