/*
  ==============================================================================

    OrionEffectDelay.cpp
    Created: 11 Jun 2019 9:28:51pm
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionEffectDelay.h"
#include "OrionGlobalVars.h"
using namespace std;
//==============================================================================


OrionEffectDelay::OrionEffectDelay(OrionaudioAudioProcessor& p, int serial):
processor(p)
{
    effectDelaySerial = serial;
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    //setBounds(10, 10, 80, 80);/* Global: X, Y, W， H */
    //setBounds((getWidth()/3)*2, 0, getHeight()/3, getHeight());/* Global: X, Y, W， H */
    //setSize (OrionGlobalWidth, getHeight);
    
    float WidthTmp = (OrionGlobalWidth/10)*3;
    float HeightTmp = OrionGlobalHeight*9/30;
    
    setBounds((OrionGlobalWidth/10)*7, 0, WidthTmp, HeightTmp);/* Global: X, Y, W， H */

    //=====================================================================
    delayTimeSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    delayTimeSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    delayTimeSlider.setRange(0.0f, 0.5f);
    delayTimeSlider.setValue(0.1f);
    delayTimeSlider.setTextValueSuffix (" ms");

    delayTimeSlider.setBounds(WidthTmp*0.1/3, HeightTmp/4, WidthTmp*0.9/3, HeightTmp*0.9/3);/* local: X, Y, W， H */
    addAndMakeVisible(delayTimeSlider);
    delayTimeSlider.setVisible(true);
    
    addAndMakeVisible(delayTimeLabel);
    delayTimeLabel.setText ("Time", dontSendNotification);
    //delayTimeLabel.attachToComponent (&delayTimeSlider, false);
    delayTimeLabel.setBounds(WidthTmp*0.2/3, (HeightTmp/4) + (HeightTmp/3.5), WidthTmp/3, HeightTmp/20);

    
    
    
    //=====================================================================
    delayFeedbackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    delayFeedbackSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    delayFeedbackSlider.setRange(0.0f, 0.95f);
    delayFeedbackSlider.setValue(0.0f);
    delayFeedbackSlider.setTextValueSuffix (" %");
    delayFeedbackSlider.setBounds(WidthTmp*1.1/3, HeightTmp/4, WidthTmp*0.9/3, HeightTmp*0.9/3);/* local: X, Y, W， H */
    addAndMakeVisible(delayFeedbackSlider);
    delayFeedbackSlider.setVisible(true);
    
    
    
    
    addAndMakeVisible(delayFeedbackLabel);
    delayFeedbackLabel.setText ("Feedback", dontSendNotification);
    //delayFeedbackLabel.attachToComponent (&delayFeedbackSlider, false);
    delayFeedbackLabel.setBounds(WidthTmp*1.12/3, (HeightTmp/4) + (HeightTmp/3.5), WidthTmp/3, HeightTmp/20);
    
    
    
    
    //=====================================================================
    delayColorSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    delayColorSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    delayColorSlider.setRange(-1.0f, 1.0f);
    delayColorSlider.setValue(0.0f);
    delayColorSlider.setBounds(WidthTmp*2.1/3, HeightTmp/4, WidthTmp*0.9/3, HeightTmp*0.9/3);/* local: X, Y, W， H */
    addAndMakeVisible(delayColorSlider);
    delayColorSlider.setVisible(true);
    
    
    addAndMakeVisible(delayColorLabel);
    delayColorLabel.setText ("Color", dontSendNotification);
    //delayColorLabel.attachToComponent (&delayColorSlider, false);
    delayColorLabel.setBounds(WidthTmp*2.22/3, (HeightTmp/4) + (HeightTmp/3.5), WidthTmp/3, HeightTmp/20);


    
    //=====================================================================
    delayPanSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    delayPanSlider.setTextBoxStyle(Slider::TextBoxRight, true, OrionGlobalWidth/30, OrionGlobalHeight/60);
    delayPanSlider.setRange(-1.0f, 1.0f);
    delayPanSlider.setValue(0.0f);
    
    if(delayPanSlider.getValue()<0.0f){
        delayPanSlider.setTextValueSuffix (" L");
    }
    else if(delayPanSlider.getValue()> 0.0f)
    {
         delayPanSlider.setTextValueSuffix (" R");
    }

    
    delayPanSlider.setBounds(WidthTmp*0.1/3, HeightTmp/4 + HeightTmp/3, WidthTmp*0.9/3, HeightTmp*0.9/3);/* local: X, Y, W， H */
    addAndMakeVisible(delayPanSlider);
    delayPanSlider.setVisible(true);
    

    
    addAndMakeVisible(delayPanLabel);
    delayPanLabel.setText ("Pan", dontSendNotification);
    //delayPanLabel.attachToComponent (&delayPanSlider, false);
    delayPanLabel.setBounds(WidthTmp*0.23/3, (HeightTmp/4) + HeightTmp/3 + (HeightTmp/3.5), WidthTmp/3, HeightTmp/20);
    
    
    
    
    //=====================================================================
    delayDryWetSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    delayDryWetSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 0, 0);
    delayDryWetSlider.setRange(0.0f, 1.0f);
    delayDryWetSlider.setValue(0.3f);
    delayDryWetSlider.setBounds(WidthTmp/3, HeightTmp/4 + HeightTmp/3, WidthTmp*2*0.9/3, HeightTmp/3);/* local: X, Y, W， H */
    addAndMakeVisible(delayDryWetSlider);
    delayDryWetSlider.setVisible(true);
    
    
    
    addAndMakeVisible(delayDryWetLabel);
    delayDryWetLabel.setText ("Wet                                 Dry", dontSendNotification);
    //delayDryWetLabel.attachToComponent (&delayDryWetSlider, false);
    delayDryWetLabel.setBounds(WidthTmp*1.1/3, (HeightTmp/4) + HeightTmp/3 + (HeightTmp/3.5), WidthTmp*2/3, HeightTmp/20);

    
    
    delaySwitchButton.setButtonText(translate("On/Off"));
    delaySwitchButton.setBounds(WidthTmp*2.3/3, HeightTmp/10, WidthTmp/3.1, HeightTmp/10);
    addAndMakeVisible(delaySwitchButton);
    
    
    //=====================================================================
    /* Look and Feel General Change */
    getLookAndFeel().setColour(Slider::thumbColourId, juce::Colours::lightgrey); //set thumb color of the Slider, Global
    getLookAndFeel().setColour(Slider::rotarySliderOutlineColourId, juce::Colours::azure); //set fill color of the Slider, Global
    getLookAndFeel().setColour(Slider::rotarySliderFillColourId, juce::Colours::blue); //set fill color of the Slider, Global
    
    /* Individual look and feel */
    rotarySliderLAFV1.setColour(Slider::thumbColourId, juce::Colours::green);
    delayTimeSlider.setLookAndFeel(&rotarySliderLAFV1);
    
    /* Customize Look and Feel class */
    delayPanSlider.setLookAndFeel(&rotarySliderLookAndFeelTest);
    
    
    //=====================================================================
    //sends value of the sliders to the tree state in the processor
    delayTimeTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayTime"+String(effectDelaySerial), delayTimeSlider);
    delayFeedbackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayFeedback"+String(effectDelaySerial), delayFeedbackSlider);
    delayColorTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayColor"+String(effectDelaySerial), delayColorSlider);
    delayPanTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayPan"+String(effectDelaySerial), delayPanSlider);
    delayDryWetTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayDryWet"+String(effectDelaySerial), delayDryWetSlider);
    
    delaySwitchButtonAttachment = new AudioProcessorValueTreeState::ButtonAttachment (processor.getValueTree(), "delaySwitch"+String(effectDelaySerial), delaySwitchButton);
    
    
}

OrionEffectDelay::~OrionEffectDelay()
{
    setLookAndFeel(nullptr);
    delayTimeSlider.setLookAndFeel(nullptr);
    delayFeedbackSlider.setLookAndFeel(nullptr);
    delayColorSlider.setLookAndFeel(nullptr);
    delayPanSlider.setLookAndFeel(nullptr);
    delayDryWetSlider.setLookAndFeel(nullptr);
    delayTimeTree = nullptr;
    delayFeedbackTree = nullptr;
    delayColorTree = nullptr;
    delayPanTree = nullptr;
    delayDryWetTree = nullptr;
}

void OrionEffectDelay::paint (Graphics& g)
{
    /* Background color */
    g.fillAll(Colours::grey);
    
    /* Define Local Bound */
    float WidthTmp = (OrionGlobalWidth/10)*3;
    float HeightTmp = OrionGlobalHeight/3;
    
    /* For test slider area */
//    g.setColour(Colours::aqua);
    
//    Rectangle<float> dialTime (0, HeightTmp/4, WidthTmp/3, HeightTmp/3);
//    Rectangle<float> dialFeedback (WidthTmp/3, HeightTmp/4, WidthTmp/3, HeightTmp/3);
//    Rectangle<float> dialColor (WidthTmp*2/3, HeightTmp/4, WidthTmp/3, HeightTmp/3);
//    Rectangle<float> dialPan (0, HeightTmp/4 + HeightTmp/3, WidthTmp/3, HeightTmp/3);
//    Rectangle<float> sliderDryWet (WidthTmp/3, HeightTmp/4 + HeightTmp/3, WidthTmp*2/3, HeightTmp/3);
//
//    g.drawRect(dialTime);
//    g.drawRect(dialFeedback);
//    g.drawRect(dialColor);
//    g.drawRect(dialPan);
//    g.drawRect(sliderDryWet);
    
    
    
    /* Customize the sliders*/
    OrionRotarySlider* cusRotarySliderlook = new OrionRotarySlider();
    if(auto* newl = dynamic_cast<juce::LookAndFeel*> (cusRotarySliderlook))
    {
        delayColorSlider.setLookAndFeel(newl);
        delayFeedbackSlider.setLookAndFeel(newl);
        delayTimeSlider.setLookAndFeel(newl);
        delayPanSlider.setLookAndFeel(newl);
    }

    
}

void OrionEffectDelay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    float WidthTmp = (OrionGlobalWidth/10)*3;
    float HeightTmp = OrionGlobalHeight/3;
    
    //int border =
    

}
void OrionEffectDelay::sliderValueChanged(Slider* slider)
{
    //    if (slider == &attackSlider)
    //    {
    //        processor.attackTime = attackSlider.getValue();
    //    }
    //
    //    if (slider == &decaySlider)
    //    {
    //        processor.decayTime = decaySlider.getValue();
    //    }
    //
    //    if (slider == &sustainSlider)
    //    {
    //        processor.sustainTime = sustainSlider.getValue();
    //    }
    //
    //    if (slider == &releaseSlider)
    //    {
    //        processor.releaseTime = releaseSlider.getValue();
    //    }
    
}


