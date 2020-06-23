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
    
    // SOLO & MUTE BUTTONS
    Image soloButtonDown = ImageCache::getFromMemory(BinaryData::SoloOn_png, BinaryData::SoloOn_pngSize);
    Image soloButtonUp = ImageCache::getFromMemory(BinaryData::SoloOff_png, BinaryData::SoloOff_pngSize);

    Image muteButtonDown = ImageCache::getFromMemory(BinaryData::MuteOn_png, BinaryData::MuteOn_pngSize);
    Image muteButtonUp = ImageCache::getFromMemory(BinaryData::MuteOff_png, BinaryData::MuteOff_pngSize);

    void paint (Graphics&) override;
    void resized() override;

    std::unique_ptr<WaveWiggle> waveWiggle;
    
    void sliderValueChanged (Slider* slider)override;
    
    void instrumentSoloButtonClicked(bool isDown);
    
    void instrumentMuteButtonClicked(bool isDown);
    
    void setInstrumetsVolumeSliderValue(float value)
    {
        instrumentsVolumeSlider->setValue(value);
    }
    
    void setInstrumetsPanSliderValue(float value)
    {
        instrumentsPanSlider->setValue(value);
    }
    
    void setInstrumetsSoloButtonImage(bool On)
    {
        if(On)
        {
            soloButton->setImages(false, true, true, soloButtonDown, 1.f, Colours::transparentBlack, soloButtonDown, 1.f, Colours::transparentBlack, soloButtonDown, 1.f, Colours::transparentBlack);
        }
        else
        {
            soloButton->setImages(false, true, true, soloButtonUp, 1.f, Colours::transparentBlack, soloButtonUp, 1.f, Colours::transparentBlack, soloButtonUp, 1.f, Colours::transparentBlack);
        }

    }
    
    void setInstrumetsMuteButtonImage(bool On)
    {
        if(On)
        {
            muteButton->setImages(false, true, true, muteButtonDown, 1.f, Colours::transparentBlack, muteButtonDown, 1.f, Colours::transparentBlack, muteButtonDown, 1.f, Colours::transparentBlack);
        }
        else
        {
            muteButton->setImages(false, true, true, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack);
        }
    }
    
    std::array<std::unique_ptr<DragAndDropButton>, 8> drumButtons;
private:
    OrionaudioAudioProcessor* processor;
    OrionaudioAudioProcessorEditor* editor;
    
    

    // BUTTONS
    
    
    std::unique_ptr<ImageButton> dropDownButton;
    
    std::unique_ptr<ImageButton> soloButton;
    std::unique_ptr<ImageButton> muteButton;
    
    std::unique_ptr<CircularMeter> meterLeft;
    std::unique_ptr<CircularMeter> meterRight;
    
    std::unique_ptr<Slider> instrumentsVolumeSlider;
    std::unique_ptr<Label> instrumentsVolumeSliderLabel;
    
    std::unique_ptr<Slider> instrumentsPanSlider;
    
    std::unique_ptr<Slider> MasterVolumeSlider;
    std::unique_ptr<Label> MasterVolumeSliderLabel;
    
    std::unique_ptr<DrawableImage> backgroundImageView;// 以后删除
    
    ColourGradient backgroundGradient;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrimaryPaneComponent)
};
