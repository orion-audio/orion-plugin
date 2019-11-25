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
        
//    int WidthTmp = (OrionGlobalWidth/10)*4;
//    int WidthTmp2 = (OrionGlobalWidth/10)*3;
//    int HeightTmp = OrionGlobalHeight*9/30;
//    
//    int knobHeight = WidthTmp2*0.9/3;
//
//    setBounds(0, 0, WidthTmp, HeightTmp);/* Global: X, Y, W， H */
    
    // slider initialization values
    //=====================================================================
    compRatioSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    compRatioSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    compRatioSlider.setRange(1.0f, 100.0f);
    compRatioSlider.setValue(1.0f);
    compRatioSlider.setTextValueSuffix (":1");
    addAndMakeVisible(compRatioSlider);
    compRatioSlider.setVisible(true);
    
    addAndMakeVisible(compRatioLabel);
    compRatioLabel.setText ("Ratio", dontSendNotification);
//    compRatioLabel.attachToComponent (&compRatioSlider, false);
    
    //=====================================================================
    compAttackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    compAttackSlider.setRange(0.1f, 80.0f);
    compAttackSlider.setValue(0.1f);
    compAttackSlider.setTextValueSuffix (" ms");
    compAttackSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    addAndMakeVisible(compAttackSlider);
    compAttackSlider.setVisible(true);
    
    addAndMakeVisible(compAttackLabel);
    compAttackLabel.setText ("Attack", dontSendNotification);
    
    //=====================================================================
    compReleaseSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    compReleaseSlider.setRange(0.1f, 1000.0f);
    compReleaseSlider.setValue(0.1f);
    compReleaseSlider.setTextValueSuffix (" ms");
    compReleaseSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
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
    addAndMakeVisible(compGainSlider);
    compGainSlider.setVisible(true);
    
    addAndMakeVisible(compGainLabel);
    compGainLabel.setText ("Gain", dontSendNotification);
    
    //=====================================================================
    compThreshSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    compThreshSlider.setRange(-60.0f, 0.0f);
    compThreshSlider.setValue(-60.0f);
    
    compThreshSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 0, 0);
    addAndMakeVisible(compThreshSlider);
    compThreshSlider.setVisible(true);
    
    addAndMakeVisible(compThreshLabel);
    compThreshLabel.setText ("Thresh", dontSendNotification);
    
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
    g.fillAll(Colours::grey);/* 颜色 */
    g.setColour(Colours::black);
    g.fillRect(paintArea);
}

void OrionEffectComp::resized()
{
    Rectangle<int> area = getLocalBounds();
    Rectangle<int> knobArea;
    Rectangle<int> labelArea;
    
    area.removeFromLeft(getWidth() / 2);
    area.removeFromTop(getHeight() / 3);
    area.setSize(area.getWidth() / 2, area.getHeight() / 2);
    area.translate(0, -area.getHeight() * .1);
    paintArea = area;
    knobArea = area;
    labelArea = knobArea.removeFromBottom(knobArea.getHeight() * .25);
    compRatioSlider.setBounds(knobArea);
    compRatioLabel.setBounds(labelArea);
    
    area.translate(area.getWidth(), 0);
    knobArea = area;
    labelArea = knobArea.removeFromBottom(knobArea.getHeight() * .25);
    compAttackSlider.setBounds(knobArea);
    compAttackLabel.setBounds(labelArea);

    area.translate(0, area.getHeight());
    knobArea = area;
    labelArea = knobArea.removeFromBottom(knobArea.getHeight() * .25);
    compGainSlider.setBounds(knobArea);
    compGainLabel.setBounds(labelArea);
    
    area.translate(-area.getWidth(), 0);
    knobArea = area;
    labelArea = knobArea.removeFromBottom(knobArea.getHeight() * .25);
    compReleaseSlider.setBounds(knobArea);
    compReleaseLabel.setBounds(labelArea);

    area.setY(0);
    area.setX(getWidth() - area.getWidth());
    compSwitchButton.setBounds(area);

    area = compRatioSlider.getBounds();
    area.translate(-area.getWidth(), 0);
    area.setHeight(area.getHeight() * 2);
    compThreshSlider.setBounds(area);
    

}

void OrionEffectComp::sliderValueChanged(Slider* slider)
{

    
}
