/*
  ==============================================================================

    OrionEnvConfiguration.h
    Created: 21 Jun 2019 1:10:03pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"
#include "OrionRotarySlider.h"
#include "EnvelopeMeter.h"
//==============================================================================
class OrionEnvConfiguration : public Component,
                              public Slider::Listener
{
public:
    OrionEnvConfiguration(OrionaudioAudioProcessor& p,int serial = 0);
    ~OrionEnvConfiguration();
    void paint(Graphics& g) override;
    void resized() override;
    
    int envSerial;
    void switchClicked(bool isDown);
    void setSwitchImage(bool On);
    void sliderValueChanged (Slider* slider)override;
    void sliderDragEnded (Slider* slider)override;
    
    void knobsSetRange();
    void knobsInitRange();
    
    std::unique_ptr<EnvelopeMeter> envelopeMeter;
    

    
    void aSliderValueChange(double value){aSlider->setValue(value,sendNotificationSync);};
    void dSliderValueChange(double value){dSlider->setValue(value,sendNotificationSync);};
    void hSliderValueChange(double value){hSlider->setValue(value,sendNotificationSync);};
    void rSliderValueChange(double value){rSlider->setValue(value,sendNotificationSync);};
    
    void aBendSliderValueChange(double value){aBendSlider->setValue(value,sendNotificationSync);};
    void dBendSliderValueChange(double value){dBendSlider->setValue(value,sendNotificationSync);};
    void sBendSliderValueChange(double value){sBendSlider->setValue(value,sendNotificationSync);};
    void rBendSliderValueChange(double value){rBendSlider->setValue(value,sendNotificationSync);};

    

    
private:
    
    
    std::unique_ptr<DrawableImage> backgroundImageView;
    Rectangle<int>          plotFrame;

    //--------------------- Previous
    
    
    OrionaudioAudioProcessor& processor;
    File* audioFile;
    
    float sampleLength = 0.0f;
    
    /* Images */
    
    Image switchOn = ImageCache::getFromMemory(BinaryData::PowerOn_png, BinaryData::PowerOn_pngSize);
    Image switchOff = ImageCache::getFromMemory(BinaryData::PowerOff_png, BinaryData::PowerOff_pngSize);
    
    
    std::unique_ptr<ImageButton> envSwitch;
    
    /* ADSR */
    
    std::unique_ptr<Slider> aSlider;
    std::unique_ptr<Slider> dSlider;
    std::unique_ptr<Slider> hSlider;
    std::unique_ptr<Slider> rSlider;
    
    std::unique_ptr<Label> aSliderLabel;
    std::unique_ptr<Label> dSliderLabel;
    std::unique_ptr<Label> hSliderLabel;
    std::unique_ptr<Label> rSliderLabel;
    
    /* ADSR Bend */
    
    std::unique_ptr<Slider> aBendSlider;
    std::unique_ptr<Slider> dBendSlider;
    std::unique_ptr<Slider> sBendSlider;
    std::unique_ptr<Slider> rBendSlider;
    
    std::unique_ptr<Label> aBendSliderLabel;
    std::unique_ptr<Label> dBendSliderLabel;
    std::unique_ptr<Label> sBendSliderLabel;
    std::unique_ptr<Label> rBendSliderLabel;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OrionEnvConfiguration)
};
