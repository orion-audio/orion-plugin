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
#include "OrionEffectComp.h"
#include "OrionEffectReverb.h"
#include "OrionEffectDelay.h"


class OrionEffectsConfiguration : public Component,
                                  public Slider::Listener
{
public:
    OrionEffectsConfiguration(OrionaudioAudioProcessor& p, int serial);
    ~OrionEffectsConfiguration();
    
    void paint(Graphics& g) override;
    void resized() override;
    int effectSerial;

    OrionEffectComp compGui;
    OrionEffectReverb reverbGui;
    OrionEffectDelay delayGui;

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

    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionEffectsConfiguration)

};
