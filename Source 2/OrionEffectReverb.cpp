/*
  ==============================================================================

    OrionEffectReverb.cpp
    Created: 28 Jun 2019 10:45:30am
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionEffectReverb.h"
#include "OrionGlobalVars.h"
using namespace std;
//==============================================================================


OrionEffectReverb::OrionEffectReverb(OrionaudioAudioProcessor& p, int serial):
processor(p)
{
    effectReverbSerial = serial;
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    //setBounds(10, 10, 80, 80);/* Global: X, Y, W， H */
    //setBounds((getWidth()/3)*2, 0, getHeight()/3, getHeight());/* Global: X, Y, W， H */
    //setSize (OrionGlobalWidth, getHeight);
    
    int WidthTmp = (OrionGlobalWidth/7)*2+2;
    int HeightTmp = OrionGlobalHeight/3;
    
    setBounds((OrionGlobalWidth/7)*3, 0, WidthTmp, HeightTmp);/* Global: X, Y, W， H */
    cout<<"Reverb Width: "<< OrionGlobalWidth <<endl;//!!!!!!!!
    cout<<"Reverb Height: "<< OrionGlobalHeight <<endl;//!!!!!!!
    
    
    
    // slider initialization values
    
    //=====================================================================
    //delayTimeSlider = new Slider("delayTimeSlider"+String(effectDelaySerial));
    reverbPredelaySlider.setSliderStyle(Slider::SliderStyle::Rotary);
    reverbPredelaySlider.setTextBoxStyle(Slider::TextBoxRight, true, 40.0, 15.0);
    reverbPredelaySlider.setRange(0.0f, 0.5f);
    reverbPredelaySlider.setValue(0.0f);
    reverbPredelaySlider.setTextValueSuffix (" ms");
    //delayTimeSlider.onValueChange = [this] { delayTimeSlider.setValue (delayTimeSlider.getValue() * 10000, dontSendNotification); };
    reverbPredelaySlider.setBounds(0, HeightTmp/4, HeightTmp/3, HeightTmp/3);/* local: X, Y, W， H */
    addAndMakeVisible(reverbPredelaySlider);
    reverbPredelaySlider.setVisible(true);
    
    //    delayTimeSlider = new Slider("delayTimeSlider"+String(effectDelaySerial));
    //    delayTimeSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    //    delayTimeSlider->setTextBoxStyle(Slider::TextBoxRight, true, 30.0, 15.0);
    //    delayTimeSlider->setRange(0.00, 0.50);
    //    delayTimeSlider->setValue(0.1);
    //    delayTimeSlider->setTextValueSuffix (" %");
    //    delayTimeSlider->setBounds(80, 0, 90, 90);/* local: X, Y, W， H */
    //    addAndMakeVisible(delayTimeSlider);
    //    delayTimeSlider->setVisible(true);
    
    
    
    addAndMakeVisible(reverbPredelayLabel);
    reverbPredelayLabel.setText ("Pre-Delay", dontSendNotification);
    reverbPredelayLabel.attachToComponent (&reverbPredelaySlider, false);
    
    
    
    
    //=====================================================================
    reverbSizeSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    reverbSizeSlider.setTextBoxStyle(Slider::TextBoxRight, true, 40.0, 15.0);
    reverbSizeSlider.setRange(0.0f, 0.95f);
    reverbSizeSlider.setValue(0.0f);
    reverbSizeSlider.setTextValueSuffix (" ms");
    reverbSizeSlider.setBounds(WidthTmp/3, HeightTmp/4, HeightTmp/3, HeightTmp/3);/* local: X, Y, W， H */
    addAndMakeVisible(reverbSizeSlider);
    reverbSizeSlider.setVisible(true);
    
    //    delayFeedbackSlider = new Slider("delayFeedbackSlider"+String(effectDelaySerial));
    //    delayFeedbackSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    //    delayFeedbackSlider->setTextBoxStyle(Slider::TextBoxRight, true, 30.0, 15.0);
    //    delayFeedbackSlider->setRange(0.00, 0.95);
    //    delayFeedbackSlider->setValue(0.00);
    //    delayFeedbackSlider->setTextValueSuffix (" %");
    //    delayFeedbackSlider->setBounds(80, 0, 90, 90);/* local: X, Y, W， H */
    //    addAndMakeVisible(delayFeedbackSlider);
    //    delayFeedbackSlider->setVisible(true);
    
    
    
    addAndMakeVisible(reverbSizeLabel);
    reverbSizeLabel.setText ("Size", dontSendNotification);
    reverbSizeLabel.attachToComponent (&reverbSizeSlider, false);
    
    
    
    
    
    //=====================================================================
    reverbColorSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    reverbColorSlider.setTextBoxStyle(Slider::TextBoxRight, true, 40.0, 15.0);
    reverbColorSlider.setRange(-1.0f, 1.0f);
    reverbColorSlider.setValue(0.0f);
    reverbSizeSlider.setTextValueSuffix (" ms");
    reverbColorSlider.setBounds(WidthTmp/3*2, HeightTmp/4, HeightTmp/3, HeightTmp/3);/* local: X, Y, W， H */
    addAndMakeVisible(reverbColorSlider);
    reverbColorSlider.setVisible(true);
    
    //    delayColorSlider = new Slider("delayColorSlider"+String(effectDelaySerial));
    //    delayColorSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    //    delayColorSlider->setTextBoxStyle(Slider::TextBoxRight, true, 30.0, 15.0);
    //    delayColorSlider->setRange(-1.00, 1.00);
    //    delayColorSlider->setValue(0.00);
    //    delayColorSlider->setBounds(160, 0, 90, 90);/* local: X, Y, W， H */
    //    addAndMakeVisible(delayColorSlider);
    //    delayColorSlider->setVisible(true);
    
    addAndMakeVisible(reverbColorLabel);
    reverbColorLabel.setText ("Color", dontSendNotification);
    reverbColorLabel.attachToComponent (&reverbColorSlider, false);
    
    
    
    //=====================================================================
    reverbDecaySlider.setSliderStyle(Slider::SliderStyle::Rotary);
    reverbDecaySlider.setTextBoxStyle(Slider::TextBoxRight, true, 40.0, 15.0);
    reverbDecaySlider.setRange(-1.0f, 1.0f);
    reverbDecaySlider.setValue(0.0f);
    reverbDecaySlider.setTextValueSuffix (" %");
    reverbDecaySlider.setBounds(0, HeightTmp/4*2, HeightTmp/3, HeightTmp/3);/* local: X, Y, W， H */
    addAndMakeVisible(reverbDecaySlider);
    reverbDecaySlider.setVisible(true);
    
    //    delayPanSlider = new Slider("delayPanSlider"+String(effectDelaySerial));
    //    delayPanSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    //    delayPanSlider->setTextBoxStyle(Slider::TextBoxRight, true, 30.0, 15.0);
    //    delayPanSlider->setRange(-1.0f, 1.0f);
    //    delayPanSlider->setValue(0.0f);
    //    delayPanSlider->setBounds(0, 80, 90, 90);/* local: X, Y, W， H */
    //    addAndMakeVisible(delayPanSlider);
    //    delayPanSlider->setVisible(true);
    
    addAndMakeVisible(reverbDecayLabel);
    reverbDecayLabel.setText ("Decay", dontSendNotification);
    reverbDecayLabel.attachToComponent (&reverbDecaySlider, false);
    
    
    //=====================================================================
    reverbDrySlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    reverbDrySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 0, 0);
    reverbDrySlider.setRange(0.0f, 1.0f);
    reverbDrySlider.setValue(0.3f);
    reverbDrySlider.setTextValueSuffix (" ms");
    reverbDrySlider.setBounds(WidthTmp/3, HeightTmp/4*2, HeightTmp/3*2, HeightTmp/3);/* local: X, Y, W， H */
    addAndMakeVisible(reverbDrySlider);
    reverbDrySlider.setVisible(true);
    
    //    delayDryWetSlider = new Slider("delayDryWetSlider"+String(effectDelaySerial));
    //    delayDryWetSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    //    delayDryWetSlider->setTextBoxStyle(Slider::TextBoxBelow, true, 0, 0);
    //    delayDryWetSlider->setRange(0.0f, 1.0f);
    //    delayDryWetSlider->setValue(0.3f);
    //    delayDryWetSlider->setBounds(80, 80, 130, 90);/* local: X, Y, W， H */
    //    addAndMakeVisible(delayDryWetSlider);
    //    delayDryWetSlider->setVisible(true);
    
    addAndMakeVisible(reverbDryLabel);
    reverbDryLabel.setText ("Wet                                 Dry", dontSendNotification);
    reverbDryLabel.attachToComponent (&reverbDrySlider, false);
    
    
    
    //sends value of the sliders to the tree state in the processor
    reverbPredelayTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "reverbPredelay"+String(effectReverbSerial), reverbPredelaySlider);
    reverbSizeTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "reverbSize"+String(effectReverbSerial), reverbSizeSlider);
    reverbColorTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "reverbColor"+String(effectReverbSerial), reverbColorSlider);
    reverbDecayTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "reverbDecay"+String(effectReverbSerial), reverbDecaySlider);
    reverbDryTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "reverbDry"+String(effectReverbSerial), reverbDrySlider);
    
    //    delayTimeTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayTime"+String(effectDelaySerial), *delayTimeSlider);
    //    delayFeedbackTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayFeedback"+String(effectDelaySerial), *delayFeedbackSlider);
    //    delayColorTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayColor"+String(effectDelaySerial), *delayColorSlider);
    //    delayPanTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayPan"+String(effectDelaySerial), *delayPanSlider);
    //    delayDryWetTree = new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "delayDryWet"+String(effectDelaySerial), *delayDryWetSlider);
    
    
    //std::cout<<"serial number "<<effectDelaySerial<<"\n";
    
    
}

OrionEffectReverb::~OrionEffectReverb()
{
    reverbPredelayTree = nullptr;
    reverbSizeTree = nullptr;
    reverbColorTree = nullptr;
    reverbDecayTree = nullptr;
    reverbDryTree = nullptr;
}

void OrionEffectReverb::paint (Graphics& g)
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
    g.fillAll(Colours::goldenrod);/* 颜色 */
}

void OrionEffectReverb::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //setBounds(10, 10, getWidth()/3, getHeight()/3);/* Global: X, Y, W， H */
    
}
void OrionEffectReverb::sliderValueChanged(Slider* slider)
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
