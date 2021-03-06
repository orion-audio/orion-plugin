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
#include "CompressorSidechainSelectWindow.h"
#include "FXComboBox.h"
#include "CompressorMeter.h"


class OrionEffectsConfiguration : public Component,
                                  public Slider::Listener
{
public:
    OrionEffectsConfiguration(OrionaudioAudioProcessor& p, int serial = 0);
    ~OrionEffectsConfiguration();
    
    void paint(Graphics& g) override;
    void resized() override;
    int effectSerial;

    void sliderValueChanged (Slider* slider)override;
    void setCompressorComboBoxDisplay(String name){compressorComboBox->comboSwitch->setButtonText(name);};
    void sidechainSwitchClicked(bool isDown);
    void sidechainCellClicked(bool isDown, int tag);
    void switchClicked(bool isDown);
    void setSwitchImage(bool On, int Serial);
    
    void compThreshSliderValueChange(double value){compThreshSlider->setValue(value,sendNotificationSync);};
    void compRatioSliderValueChange(double value){compRatioSlider->setValue(value,sendNotificationSync);};
    void compAttackSliderValueChange(double value){compAttackSlider->setValue(value,sendNotificationSync);};
    void compReleaseSliderValueChange(double value){compReleaseSlider->setValue(value,sendNotificationSync);};
    void compGainSliderValueChange(double value){compGainSlider->setValue(value,sendNotificationSync);};
    
    void reverbDrySliderValueChange(double value){reverbDrySlider->setValue(value,sendNotificationSync);};
    void reverbPredelaySliderValueChange(double value){reverbPredelaySlider->setValue(value,sendNotificationSync);};
    void reverbDecaySliderValueChange(double value){reverbDecaySlider->setValue(value,sendNotificationSync);};
    void reverbSizeSliderValueChange(double value){reverbSizeSlider->setValue(value,sendNotificationSync);};
    void reverbColorSliderValueChange(double value){reverbColorSlider->setValue(value,sendNotificationSync);};
    
    void delayDryWetSliderValueChange(double value){delayDryWetSlider->setValue(value,sendNotificationSync);};
    void delayTimeSliderValueChange(double value){delayTimeSlider->setValue(value,sendNotificationSync);};
    void delayFeedbackSliderValueChange(double value){delayFeedbackSlider->setValue(value,sendNotificationSync);};
    void delayColorSliderValueChange(double value){delayColorSlider->setValue(value,sendNotificationSync);};
    void delayPanSliderValueChange(double value){delayPanSlider->setValue(value,sendNotificationSync);};
    
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
    std::unique_ptr<FXComboBox> compressorComboBox;
    std::unique_ptr<CompressorSidechainSelectWindow> compressorSidechainSelectWindow;
    std::unique_ptr<CompressorMeter> compressorMeter;
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
