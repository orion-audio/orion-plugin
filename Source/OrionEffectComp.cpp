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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    //setBounds(10, 10, 80, 80);/* Global: X, Y, W， H */
    //setBounds((getWidth()/3)*2, 0, getHeight()/3, getHeight());/* Global: X, Y, W， H */
    //setSize (OrionGlobalWidth, getHeight);
    effectCompSerial = serial;
    
    int WidthTmp = (OrionGlobalWidth/10)*4;
    int WidthTmp2 = (OrionGlobalWidth/10)*3;
    int HeightTmp = OrionGlobalHeight*9/30;
    
    int knobHeight = WidthTmp2*0.9/3;
    
    //cout<<"Height 2: "<<HeightTmp<<endl;//!!!!!!!
    
    //setBounds(WidthTmp, 0, WidthTmp, HeightTmp);/* Global: X, Y, W， H */
    
    setBounds(0, 0, WidthTmp, HeightTmp);/* Global: X, Y, W， H */
    //cout<<"Width: "<<getWidth()/3<<endl;
    //cout<<"Height: "<<getHeight()/3<<endl;
    
    // slider initialization values
    //=====================================================================
    compRatioSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    compRatioSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    compRatioSlider.setRange(1.0f, 100.0f);
    compRatioSlider.setValue(1.0f);
    compRatioSlider.setTextValueSuffix (":1");
    //compRatioSlider.addListener(this);
    compRatioSlider.setBounds(WidthTmp/4*2, HeightTmp/4, WidthTmp2*0.9/3, HeightTmp*0.9/3);/* local: X, Y, W， H */
    addAndMakeVisible(compRatioSlider);
    compRatioSlider.setVisible(true);
    
    addAndMakeVisible(compRatioLabel);
    compRatioLabel.setText ("Ratio", dontSendNotification);
    compRatioLabel.setBounds(WidthTmp*1.55/3, (HeightTmp/4) + (HeightTmp/3.5), WidthTmp/3, HeightTmp/20);
    //compRatioLabel.attachToComponent (&compRatioSlider, false);
    
    //=====================================================================
    compAttackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    compAttackSlider.setRange(0.1f, 80.0f);
    compAttackSlider.setValue(0.1f);
    compAttackSlider.setTextValueSuffix (" ms");
    compAttackSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    compAttackSlider.setBounds(WidthTmp/4*3, HeightTmp/4, WidthTmp2*0.9/3, HeightTmp*0.9/3);/* local: X, Y, W， H */
    //compAttackSlider->addListener(this);
    addAndMakeVisible(compAttackSlider);
    compAttackSlider.setVisible(true);
    
    addAndMakeVisible(compAttackLabel);
    compAttackLabel.setText ("Attack", dontSendNotification);
    //compAttackLabel.attachToComponent (&compAttackSlider, false);
    compAttackLabel.setBounds(WidthTmp*2.3/3, (HeightTmp/4) + (HeightTmp/3.5), WidthTmp/3, HeightTmp/20);
    
    
    
    //=====================================================================
    compReleaseSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    compReleaseSlider.setRange(0.1f, 1000.0f);
    compReleaseSlider.setValue(0.1f);
    compReleaseSlider.setTextValueSuffix (" ms");
    compReleaseSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    compReleaseSlider.setBounds(WidthTmp/4*2, HeightTmp/4 + HeightTmp/3, WidthTmp2*0.9/3, HeightTmp*0.9/3);/* local: X, Y, W， H */
    //compReleaseSlider.addListener(this);
    addAndMakeVisible(compReleaseSlider);
    compReleaseSlider.setVisible(true);
    
    addAndMakeVisible(compReleaseLabel);
    compReleaseLabel.setText ("Release", dontSendNotification);
    compReleaseLabel.setBounds(WidthTmp*1.53/3, (HeightTmp/4) + HeightTmp/3 + (HeightTmp/3.5), WidthTmp2/3, HeightTmp/20);
    //compReleaseLabel.attachToComponent (&compReleaseSlider, false);

    //=====================================================================
    compGainSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    compGainSlider.setRange(0.0f, 40.0f);
    compGainSlider.setValue(0.1f);
    compGainSlider.setTextValueSuffix (" db");
    compGainSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    compGainSlider.setBounds(WidthTmp/4*3, HeightTmp/4 + HeightTmp/3, WidthTmp2*0.9/3, HeightTmp*0.9/3);/* local: X, Y, W， H */
    //compGainSlider->addListener(this);
    addAndMakeVisible(compGainSlider);
    compGainSlider.setVisible(true);
    
    addAndMakeVisible(compGainLabel);
    compGainLabel.setText ("Gain", dontSendNotification);
    
    compGainLabel.setBounds(WidthTmp*2.4/3, (HeightTmp/4) + HeightTmp/3 + (HeightTmp/3.5), WidthTmp2/3, HeightTmp/20);
    //compGainLabel.attachToComponent (&compGainSlider, false);
    
    
    
    
    //=====================================================================
    compThreshSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    compThreshSlider.setRange(-60.0f, 0.0f);
    compThreshSlider.setValue(-60.0f);
    
    compThreshSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 0, 0);
    compThreshSlider.setBounds(WidthTmp/4*1.3, HeightTmp/4*1.3, HeightTmp/3, HeightTmp/3*1.3);/* local: X, Y, W， H */
    //compThreshSlider->addListener(this);
    addAndMakeVisible(compThreshSlider);
    compThreshSlider.setVisible(true);
    
    addAndMakeVisible(compThreshLabel);
    compThreshLabel.setText ("Thresh", dontSendNotification);
    compThreshLabel.setBounds(WidthTmp/4*1.5, HeightTmp/4*2.3, HeightTmp/3, HeightTmp/3*1.3);
    //compThreshLabel.attachToComponent (&compThreshSlider, false);
    
    
    //=====================================================================
    compSwitchButton.setButtonText(translate("On/Off"));
    compSwitchButton.setBounds(WidthTmp2*3.3/3, HeightTmp/10, WidthTmp2/3.1, HeightTmp/10);
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
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    
    //    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    //
    //    g.setColour (Colours::grey);
    //    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    //
    //    g.setColour (Colours::white);
    //    g.setFont (14.0f);
    //    g.drawText ("OrionEffectDelay", getLocalBounds(),
    //                Justification::centred, true);   // draw some placeholder text
    g.fillAll(Colours::grey);/* 颜色 */
    
    /* Customize the sliders*/
    OrionRotarySlider* cusRotarySliderlook = new OrionRotarySlider();
    if(auto* newl = dynamic_cast<juce::LookAndFeel*> (cusRotarySliderlook))
    {
        compRatioSlider.setLookAndFeel(newl);
        compAttackSlider.setLookAndFeel(newl);
        compReleaseSlider.setLookAndFeel(newl);
        compGainSlider.setLookAndFeel(newl);
    }
}

void OrionEffectComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    //setBounds(10, 10, getWidth()/3, getHeight()/3);/* Global: X, Y, W， H */
    // compRatio, compAttack, compRelease, compGain, compThresh

    
}

void OrionEffectComp::sliderValueChanged(Slider* slider)
{

    
}
