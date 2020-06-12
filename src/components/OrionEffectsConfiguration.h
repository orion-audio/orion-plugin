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


class OrionEffectsConfiguration : public Component
{
public:
    OrionEffectsConfiguration(OrionaudioAudioProcessor& p, int serial);
    ~OrionEffectsConfiguration();
    
    void paint(Graphics& g) override;
    void resized() override;
    
    //void buttonClicked(Button*) override;
    //void sliderValueChanged(Slider* slider) override;
    OrionEffectComp compGui;
    OrionEffectReverb delayGui;
    OrionEffectDelay reverbGui;
    
    
    int effectSerial;
    
    private:
    OrionaudioAudioProcessor& processor;
    std::unique_ptr<DrawableImage> backgroundButton;// 以后删除
    //ScopedPointer<Slider> attackSlider;

};
