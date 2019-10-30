/*
  ==============================================================================

    OrionEffectComp.cpp
    Created: 11 Jun 2019 11:35:50pm
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionEffectComp.h"
#include "OrionGlobalVars.h"
using namespace std;
//==============================================================================
OrionEffectComp::OrionEffectComp(OrionaudioAudioProcessor& p, int serial):
processor(p)
{
    effectCompSerial = serial;
        
    int WidthTmp = (OrionGlobalWidth/10)*4;
    int WidthTmp2 = (OrionGlobalWidth/10)*3;
    int HeightTmp = OrionGlobalHeight*9/30;
    
    int knobHeight = WidthTmp2*0.9/3;

    setBounds(0, 0, WidthTmp, HeightTmp);/* Global: X, Y, W， H */
    
    // slider initialization values
    //=====================================================================
    compRatioSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    compRatioSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    compRatioSlider.setRange(1.0f, 100.0f);
    compRatioSlider.setValue(1.0f);
    compRatioSlider.setTextValueSuffix (":1");
    addAndMakeVisible(compRatioSlider);
    compRatioSlider.setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());
    compRatioSlider.setVisible(true);
    
    addAndMakeVisible(compRatioLabel);
    compRatioLabel.setText ("Ratio", dontSendNotification);
    //compRatioLabel.attachToComponent (&compRatioSlider, false);
    
    //=====================================================================
    compAttackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    compAttackSlider.setRange(0.1f, 80.0f);
    compAttackSlider.setValue(0.1f);
    compAttackSlider.setTextValueSuffix (" ms");
    compAttackSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    compAttackSlider.setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());
    addAndMakeVisible(compAttackSlider);
    compAttackSlider.setVisible(true);
    
    addAndMakeVisible(compAttackLabel);
    compAttackLabel.setText ("Attack", dontSendNotification);
    //compAttackLabel.attachToComponent (&compAttackSlider, false);
    
    
    
    //=====================================================================
    compReleaseSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    compReleaseSlider.setRange(0.1f, 1000.0f);
    compReleaseSlider.setValue(0.1f);
    compReleaseSlider.setTextValueSuffix (" ms");
    compReleaseSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    compReleaseSlider.setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());
    addAndMakeVisible(compReleaseSlider);
    compReleaseSlider.setVisible(true);
    
    addAndMakeVisible(compReleaseLabel);
    compReleaseLabel.setText ("Release", dontSendNotification);
    //compReleaseLabel.attachToComponent (&compReleaseSlider, false);

    //=====================================================================
    compGainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    compGainSlider.setRange(0.0f, 40.0f);
    compGainSlider.setValue(0.1f);
    compGainSlider.setTextValueSuffix (" db");
    compGainSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    compGainSlider.setLookAndFeel(&LookAndFeel::getDefaultLookAndFeel());
    addAndMakeVisible(compGainSlider);
    compGainSlider.setVisible(true);
    
    addAndMakeVisible(compGainLabel);
    compGainLabel.setText ("Gain", dontSendNotification);
    
    //compGainLabel.attachToComponent (&compGainSlider, false);
    
    
    
    
    //=====================================================================
    compThreshSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    compThreshSlider.setRange(-60.0f, 0.0f);
    compThreshSlider.setValue(-60.0f);
    
    compThreshSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 0, 0);
    //compThreshSlider->addListener(this);
    addAndMakeVisible(compThreshSlider);
    compThreshSlider.setVisible(true);
    
    addAndMakeVisible(compThreshLabel);
    compThreshLabel.setText ("Thresh", dontSendNotification);
    //compThreshLabel.attachToComponent (&compThreshSlider, false);
    
    
    //=====================================================================
    compSwitchButton.setButtonText(translate("On/Off"));
    addAndMakeVisible(compSwitchButton);
    
    //sends value of the sliders to the tree state in the processor
    // compRatio, compAttack, compRelease, compGain, compThresh
    
    compRatioTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "compRatio"+String(effectCompSerial), compRatioSlider);
    compAttackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "compAttack"+String(effectCompSerial), compAttackSlider);
    compReleaseTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "compRelease"+String(effectCompSerial), compReleaseSlider);
    compGainTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "compGain"+String(effectCompSerial), compGainSlider);
    compThreshTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "compThresh"+String(effectCompSerial), compThreshSlider);
    
    compSwitchButtonAttachment = new AudioProcessorValueTreeState::ButtonAttachment (processor.getValueTree(), "compSwitch"+String(effectCompSerial), compSwitchButton);
    
}

OrionEffectComp::~OrionEffectComp()
{
    compRatioTree = nullptr;
    compAttackTree = nullptr;
    compReleaseTree = nullptr;
    compGainTree = nullptr;
    compThreshTree = nullptr;
    setLookAndFeel(nullptr);
}

void OrionEffectComp::paint (Graphics& g)
{
    g.fillAll(Colours::red);/* 颜色 */
}

void OrionEffectComp::resized()
{
    Rectangle<int> area = getLocalBounds();
    int WidthTmp = (OrionGlobalWidth/10)*4;
    int WidthTmp2 = (OrionGlobalWidth/10)*3;
    int HeightTmp = OrionGlobalHeight*9/30;
    
    int knobHeight = WidthTmp2*0.9/3;

    compRatioSlider.setBounds(WidthTmp/4*2, HeightTmp/4, WidthTmp2*0.9/3, HeightTmp*0.9/3);
    
    compGainSlider.setBounds(WidthTmp/4*3, HeightTmp/4 + HeightTmp/3, WidthTmp2*0.9/3, HeightTmp*0.9/3);

    compRatioLabel.setBounds(WidthTmp*1.55/3, (HeightTmp/4) + (HeightTmp/3.5), WidthTmp/3, HeightTmp/20);

    compAttackSlider.setBounds(WidthTmp/4*3, HeightTmp/4, WidthTmp2*0.9/3, HeightTmp*0.9/3);
    
    compThreshSlider.setBounds(WidthTmp/4*1.3, HeightTmp/4*1.3, HeightTmp/3, HeightTmp/3*1.3);
    
    compAttackLabel.setBounds(WidthTmp*2.3/3, (HeightTmp/4) + (HeightTmp/3.5), WidthTmp/3, HeightTmp/20);

    compReleaseSlider.setBounds(WidthTmp/4*2, HeightTmp/4 + HeightTmp/3, WidthTmp2*0.9/3, HeightTmp*0.9/3);

    compReleaseLabel.setBounds(WidthTmp*1.53/3, (HeightTmp/4) + HeightTmp/3 + (HeightTmp/3.5), WidthTmp2/3, HeightTmp/20);


    compGainLabel.setBounds(WidthTmp*2.4/3, (HeightTmp/4) + HeightTmp/3 + (HeightTmp/3.5), WidthTmp2/3, HeightTmp/20);

    compThreshLabel.setBounds(WidthTmp/4*1.5, HeightTmp/4*2.3, HeightTmp/3, HeightTmp/3*1.3);

    compSwitchButton.setBounds(WidthTmp2*3.3/3, HeightTmp/10, WidthTmp2/3.1, HeightTmp/10);

}

void OrionEffectComp::sliderValueChanged(Slider* slider)
{

    
}
