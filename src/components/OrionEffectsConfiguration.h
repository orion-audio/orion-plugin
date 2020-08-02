/*
  ==============================================================================

    OrionEffectsConfiguration.h
    Created: 11 Jun 2019 4:00:32pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ThresholdMeter.h"

//#include "OrionEffectComp.h"
//#include "OrionEffectReverb.h"
//#include "OrionEffectDelay.h"


class OrionEffectsConfiguration : public Component,
                                  public Slider::Listener
{
public:
    OrionEffectsConfiguration(OrionaudioAudioProcessor& p, int serial = 0);
    ~OrionEffectsConfiguration();
    
    void paint(Graphics& g) override;
    void resized() override;
    int effectSerial;

//    OrionEffectComp compGui;
//    OrionEffectReverb reverbGui;
//    OrionEffectDelay delayGui;

    void sliderValueChanged (Slider* slider)override;
    
    void switchClicked(bool isDown);
    void setSwitchImage(bool On, int Serial);
    
private:
    OrionaudioAudioProcessor& processor;
    
    std::unique_ptr<DrawableImage> backgroundImageView;
    
    /* Images */
    Image switchOn = ImageCache::getFromMemory(BinaryData::PowerOn_png, BinaryData::PowerOn_pngSize);
    Image switchOff = ImageCache::getFromMemory(BinaryData::PowerOff_png, BinaryData::PowerOff_pngSize);
    
    /* Switches */
    int switchSerial = 0;
    std::unique_ptr<ImageButton> compSwitch;
    std::unique_ptr<ImageButton> reverbSwitch;
    std::unique_ptr<ImageButton> delaySwitch;
    
    

    /* Compressor */
    std::unique_ptr<ThresholdMeter> thresholdMeters;
    std::unique_ptr<Slider> compThreshSlider;
    
    std::unique_ptr<Slider> compRatioSlider;
    std::unique_ptr<Slider> compAttackSlider;
    std::unique_ptr<Slider> compReleaseSlider;
    std::unique_ptr<Slider> compGainSlider;
    
    std::unique_ptr<Label> compRatioLabel;
    std::unique_ptr<Label> compAttackLabel;
    std::unique_ptr<Label> compReleaseLabel;
    std::unique_ptr<Label> compGainLabel;
    
    
    /* Reverb */
    std::unique_ptr<Slider> reverbDrySlider;
    
    std::unique_ptr<Slider> reverbPredelaySlider;
    std::unique_ptr<Slider> reverbDecaySlider;
    std::unique_ptr<Slider> reverbSizeSlider;
    std::unique_ptr<Slider> reverbColorSlider;
    
    std::unique_ptr<Label> reverbPredelayLabel;
    std::unique_ptr<Label> reverbDecayLabel;
    std::unique_ptr<Label> reverbSizeLabel;
    std::unique_ptr<Label> reverbColorLabel;
    
    
    /* Delay */
    std::unique_ptr<Slider> delayDryWetSlider;
    
    std::unique_ptr<Slider> delayTimeSlider;
    std::unique_ptr<Slider> delayFeedbackSlider;
    std::unique_ptr<Slider> delayColorSlider;
    std::unique_ptr<Slider> delayPanSlider;
    
    std::unique_ptr<Label> delayTimeLabel;
    std::unique_ptr<Label> delayFeedbackLabel;
    std::unique_ptr<Label> delayColorLabel;
    std::unique_ptr<Label> delayPanLabel;

    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionEffectsConfiguration)

};
