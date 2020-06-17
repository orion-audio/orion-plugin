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
#include "CircularMeter.h"
#include <array>
#include "DragAndDropButton.h"
#include "PluginProcessor.h"

class OrionaudioAudioProcessorEditor;

//==============================================================================
/*
*/
class PrimaryPaneComponent : public Component,
                              public Slider::Listener
{
public:
    PrimaryPaneComponent(OrionaudioAudioProcessor*, OrionaudioAudioProcessorEditor*);
    ~PrimaryPaneComponent();

    void paint (Graphics&) override;
    void resized() override;

    std::unique_ptr<WaveWiggle> waveWiggle;
    
    void sliderValueChanged (Slider* slider)override;
private:
    OrionaudioAudioProcessor* processor;
    OrionaudioAudioProcessorEditor* editor;

    // BUTTONS
    std::array<std::unique_ptr<DragAndDropButton>, 8> drumButtons;
    
    std::unique_ptr<ImageButton> dropDownButton;
    
    std::unique_ptr<ImageButton> soloButton;
    std::unique_ptr<ImageButton> muteButton;
    
    std::unique_ptr<CircularMeter> meterLeft;
    std::unique_ptr<CircularMeter> meterRight;
    
    std::unique_ptr<Slider> MasterVolumeSlider;
    
    std::unique_ptr<DrawableImage> backgroundImageView;// 以后删除
    
    ColourGradient backgroundGradient;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrimaryPaneComponent)
};
