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
#include "PluginProcessor.h"

class OrionaudioAudioProcessorEditor;

//==============================================================================
/*
*/
class SidePanelComponent : public Component
{
public:
    SidePanelComponent(OrionaudioAudioProcessor*, OrionaudioAudioProcessorEditor*);
    ~SidePanelComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    std::unique_ptr<DraggableFileBrowserComponent> fileBrowser;

private:
    OrionaudioAudioProcessor* processor;
    OrionaudioAudioProcessorEditor* editor;

    std::unique_ptr<ImageComponent> logoImage;
    
    
    std::unique_ptr<ImageButton> dropDownButton;
    
    std::unique_ptr<DrawableImage> backgroundImageView;// 以后删除
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SidePanelComponent)
};
