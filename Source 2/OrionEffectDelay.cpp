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
    
    int WidthTmp = (OrionGlobalWidth/7)*2+2;
    int HeightTmp = OrionGlobalHeight/3;
    
    setBounds((OrionGlobalWidth/7)*5, 0, WidthTmp, HeightTmp);/* Global: X, Y, W， H */
    

    //cout<<"Width: "<<getWidth()/3<<endl;//!!!!!!!!
    //cout<<"Height: "<<getHeight()/3<<endl;//!!!!!!!
    
    //cout<<"Height 1: "<<HeightTmp<<endl;//!!!!!!!
    // slider initialization values
    
    //=====================================================================
    //delayTimeSlider = new Slider("delayTimeSlider"+String(effectDelaySerial));
    delayTimeSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    delayTimeSlider.setTextBoxStyle(Slider::TextBoxRight, true, 40.0, 15.0);
    delayTimeSlider.setRange(0.0f, 0.5f);
    delayTimeSlider.setValue(0.1f);
    delayTimeSlider.setTextValueSuffix (" ms");
    //delayTimeSlider.onValueChange = [this] { delayTimeSlider.setValue (delayTimeSlider.getValue() * 10000, dontSendNotification); };
    delayTimeSlider.setBounds(0, HeightTmp/4, HeightTmp/3, HeightTmp/3);/* local: X, Y, W， H */
    addAndMakeVisible(delayTimeSlider);
    delayTimeSlider.setVisible(true);
    
//    delayTimeSlider = new Slider("delayTimeSlider"+String(effectDelaySerial));
//    delayTimeSlider->setSliderStyle(Slider::SliderStyle::Rotary);
//    delayTimeSlider->setTextBoxStyle(Slider::TextBoxRight, true, 30.0, 15.0);
//    delayTimeSlider->setRange(0.00, 0.50);
//    delayTimeSlider->setValue(0.1);
//    delayTimeSlider->setTextValueSuffix (" %");
//    delayTimeSlider->setBounds(80, 0, 90, 90);/* local: X, Y, W， H */
//    addAndMakeVisible(delayTimeSlider);
//    delayTimeSlider->setVisible(true);
    
    
    
    addAndMakeVisible(delayTimeLabel);
    delayTimeLabel.setText ("Time", dontSendNotification);
    delayTimeLabel.attachToComponent (&delayTimeSlider, false);

    
    
    
    //=====================================================================
    delayFeedbackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    delayFeedbackSlider.setTextBoxStyle(Slider::TextBoxRight, true, 40.0, 15.0);
    delayFeedbackSlider.setRange(0.0f, 0.95f);
    delayFeedbackSlider.setValue(0.0f);
    delayFeedbackSlider.setTextValueSuffix (" %");
    delayFeedbackSlider.setBounds(WidthTmp/3, HeightTmp/4, HeightTmp/3, HeightTmp/3);/* local: X, Y, W， H */
    addAndMakeVisible(delayFeedbackSlider);
    delayFeedbackSlider.setVisible(true);
    
//    delayFeedbackSlider = new Slider("delayFeedbackSlider"+String(effectDelaySerial));
//    delayFeedbackSlider->setSliderStyle(Slider::SliderStyle::Rotary);
//    delayFeedbackSlider->setTextBoxStyle(Slider::TextBoxRight, true, 30.0, 15.0);
//    delayFeedbackSlider->setRange(0.00, 0.95);
//    delayFeedbackSlider->setValue(0.00);
//    delayFeedbackSlider->setTextValueSuffix (" %");
//    delayFeedbackSlider->setBounds(80, 0, 90, 90);/* local: X, Y, W， H */
//    addAndMakeVisible(delayFeedbackSlider);
//    delayFeedbackSlider->setVisible(true);
    
    
    
    addAndMakeVisible(delayFeedbackLabel);
    delayFeedbackLabel.setText ("Feedback", dontSendNotification);
    delayFeedbackLabel.attachToComponent (&delayFeedbackSlider, false);
    
    
    
    
    
    //=====================================================================
    delayColorSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    delayColorSlider.setTextBoxStyle(Slider::TextBoxRight, true, 40.0, 15.0);
    delayColorSlider.setRange(-1.0f, 1.0f);
    delayColorSlider.setValue(0.0f);
    delayColorSlider.setBounds(WidthTmp/3*2, HeightTmp/4, HeightTmp/3, HeightTmp/3);/* local: X, Y, W， H */
    addAndMakeVisible(delayColorSlider);
    delayColorSlider.setVisible(true);
    
//    delayColorSlider = new Slider("delayColorSlider"+String(effectDelaySerial));
//    delayColorSlider->setSliderStyle(Slider::SliderStyle::Rotary);
//    delayColorSlider->setTextBoxStyle(Slider::TextBoxRight, true, 30.0, 15.0);
//    delayColorSlider->setRange(-1.00, 1.00);
//    delayColorSlider->setValue(0.00);
//    delayColorSlider->setBounds(160, 0, 90, 90);/* local: X, Y, W， H */
//    addAndMakeVisible(delayColorSlider);
//    delayColorSlider->setVisible(true);
    
    addAndMakeVisible(delayColorLabel);
    delayColorLabel.setText ("Color", dontSendNotification);
    delayColorLabel.attachToComponent (&delayColorSlider, false);


    
    //=====================================================================
    delayPanSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    delayPanSlider.setTextBoxStyle(Slider::TextBoxRight, true, 40.0, 15.0);
    delayPanSlider.setRange(-1.0f, 1.0f);
    delayPanSlider.setValue(0.0f);
    delayPanSlider.setBounds(0, HeightTmp/4*2, HeightTmp/3, HeightTmp/3);/* local: X, Y, W， H */
    addAndMakeVisible(delayPanSlider);
    delayPanSlider.setVisible(true);
    
//    delayPanSlider = new Slider("delayPanSlider"+String(effectDelaySerial));
//    delayPanSlider->setSliderStyle(Slider::SliderStyle::Rotary);
//    delayPanSlider->setTextBoxStyle(Slider::TextBoxRight, true, 30.0, 15.0);
//    delayPanSlider->setRange(-1.0f, 1.0f);
//    delayPanSlider->setValue(0.0f);
//    delayPanSlider->setBounds(0, 80, 90, 90);/* local: X, Y, W， H */
//    addAndMakeVisible(delayPanSlider);
//    delayPanSlider->setVisible(true);
    
    addAndMakeVisible(delayPanLabel);
    delayPanLabel.setText ("Pan", dontSendNotification);
    delayPanLabel.attachToComponent (&delayPanSlider, false);
   
    
    //=====================================================================
    delayDryWetSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    delayDryWetSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 0, 0);
    delayDryWetSlider.setRange(0.0f, 1.0f);
    delayDryWetSlider.setValue(0.3f);
    delayDryWetSlider.setBounds(WidthTmp/3, HeightTmp/4*2, HeightTmp/3*2, HeightTmp/3);/* local: X, Y, W， H */
    addAndMakeVisible(delayDryWetSlider);
    delayDryWetSlider.setVisible(true);
    
//    delayDryWetSlider = new Slider("delayDryWetSlider"+String(effectDelaySerial));
//    delayDryWetSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
//    delayDryWetSlider->setTextBoxStyle(Slider::TextBoxBelow, true, 0, 0);
//    delayDryWetSlider->setRange(0.0f, 1.0f);
//    delayDryWetSlider->setValue(0.3f);
//    delayDryWetSlider->setBounds(80, 80, 130, 90);/* local: X, Y, W， H */
//    addAndMakeVisible(delayDryWetSlider);
//    delayDryWetSlider->setVisible(true);
    
    addAndMakeVisible(delayDryWetLabel);
    delayDryWetLabel.setText ("Wet                                 Dry", dontSendNotification);
    delayDryWetLabel.attachToComponent (&delayDryWetSlider, false);

    
    
    //sends value of the sliders to the tree state in the processor
    delayTimeTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayTime"+String(effectDelaySerial), delayTimeSlider);
    delayFeedbackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayFeedback"+String(effectDelaySerial), delayFeedbackSlider);
    delayColorTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayColor"+String(effectDelaySerial), delayColorSlider);
    delayPanTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayPan"+String(effectDelaySerial), delayPanSlider);
    delayDryWetTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayDryWet"+String(effectDelaySerial), delayDryWetSlider);
    
//    delayTimeTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayTime"+String(effectDelaySerial), *delayTimeSlider);
//    delayFeedbackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayFeedback"+String(effectDelaySerial), *delayFeedbackSlider);
//    delayColorTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayColor"+String(effectDelaySerial), *delayColorSlider);
//    delayPanTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayPan"+String(effectDelaySerial), *delayPanSlider);
//    delayDryWetTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayDryWet"+String(effectDelaySerial), *delayDryWetSlider);

    
    //std::cout<<"serial number "<<effectDelaySerial<<"\n";
    
    
}

OrionEffectDelay::~OrionEffectDelay()
{
    delayTimeTree = nullptr;
    delayFeedbackTree = nullptr;
    delayColorTree = nullptr;
    delayPanTree = nullptr;
    delayDryWetTree = nullptr;
}

void OrionEffectDelay::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.*/
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
}

void OrionEffectDelay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //setBounds(10, 10, getWidth()/3, getHeight()/3);/* Global: X, Y, W， H */

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


