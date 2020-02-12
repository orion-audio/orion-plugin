/*
  ==============================================================================

    OrionEnvConfiguration.cpp
    Created: 21 Jun 2019 1:10:03pm
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionEnvConfiguration.h"
#include "OrionGlobalVars.h"

//==============================================================================
OrionEnvConfiguration::OrionEnvConfiguration(OrionaudioAudioProcessor& p, int serial) : processor(p)
{
    envSerial = serial;
    
    int WidthTmp = OrionGlobalWidth;
    int HeightTmp = OrionGlobalHeight*9/30;
    
    int textboxHeight = OrionGlobalHeight/60;
    int knobWidth = OrionGlobalWidth*1/25;
    int knobHeight = knobWidth + textboxHeight;
    
   // setBounds(0, 0, WidthTmp, HeightTmp);/* Global: X, Y, W， H */
    setBounds(0, 0, OrionGlobalWidth, OrionGlobalHeight/3);
    /**************** slider initialization values ********************/
    
    //==================================================================
    envAttackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    envAttackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
    envAttackSlider.setRange(0.1f, 1500.0f);
    envAttackSlider.setValue(0.1f);
    envAttackSlider.setTextValueSuffix (" ms");
    envAttackSlider.setBounds(((WidthTmp*2/10)/2) - knobWidth*1.5, HeightTmp/6, knobWidth, knobHeight);/* local: X, Y, W， H */
    addAndMakeVisible(envAttackSlider);
    envAttackSlider.setVisible(true);
    
    addAndMakeVisible(envAttackLabel);
    envAttackLabel.setText ("Attack", dontSendNotification);
    envAttackLabel.setColour(Label::textColourId, Colours::lightgrey);
    envAttackLabel.attachToComponent (&envAttackSlider, false);
    
    //==================================================================
    envHoldSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    envHoldSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
    envHoldSlider.setRange(0.1f, 1500.0f);
    envHoldSlider.setValue(0.1f);
    envHoldSlider.setTextValueSuffix (" ms");
    envHoldSlider.setBounds(((WidthTmp*2/10)/2) + knobWidth*1, HeightTmp/6, knobWidth, knobHeight);/* local: X, Y, W， H */
    addAndMakeVisible(envHoldSlider);
    envHoldSlider.setVisible(true);
    
    addAndMakeVisible(envAttackLabel);
    envHoldLabel.setText ("Hold", dontSendNotification);
    envHoldLabel.setColour(Label::textColourId, Colours::lightgrey);
    envHoldLabel.attachToComponent (&envHoldSlider, false);
    
    //==================================================================
    envDecaySlider.setSliderStyle(Slider::SliderStyle::Rotary);
    envDecaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
    envDecaySlider.setRange(0.1f, 2500.0f);
    envDecaySlider.setValue(0.1f);
    envDecaySlider.setTextValueSuffix (" ms");
    envDecaySlider.setBounds(((WidthTmp*2/10)/2) - knobWidth*1.5, HeightTmp*4/6, knobWidth, knobHeight);/* local: X, Y, W， H */
    addAndMakeVisible(envDecaySlider);
    envDecaySlider.setVisible(true);
    
    addAndMakeVisible(envDecayLabel);
    envDecayLabel.setText ("Decay", dontSendNotification);
    envDecayLabel.setColour(Label::textColourId, Colours::lightgrey);
    envDecayLabel.attachToComponent (&envDecaySlider, false);
    
    //==================================================================
    envReleaseSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    envReleaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
    envReleaseSlider.setRange(0.1f, 2500.0f);
    envReleaseSlider.setValue(0.1f);
    envReleaseSlider.setTextValueSuffix (" ms");
    envReleaseSlider.setBounds(((WidthTmp*2/10)/2) + knobWidth*1, HeightTmp*4/6, knobWidth, knobHeight);/* local: X, Y, W， H */
    addAndMakeVisible(envReleaseSlider);
    envReleaseSlider.setVisible(true);
    
    addAndMakeVisible(envReleaseLabel);
    envReleaseLabel.setText ("Release", dontSendNotification);
    envReleaseLabel.setColour(Label::textColourId, Colours::lightgrey);
    envReleaseLabel.attachToComponent (&envReleaseSlider, false);
    
    
    
    
    //==================================================================
    envAttackBendSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    envAttackBendSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
    envAttackBendSlider.setRange(0.0f, 1.00f);
    envAttackBendSlider.setValue(0.01f);
    envAttackBendSlider.setTextValueSuffix (" ms");
    envAttackBendSlider.setBounds((WidthTmp*9/10) - knobWidth*1.5, HeightTmp/6, knobWidth, knobHeight);/* local: X, Y, W， H */
    addAndMakeVisible(envAttackBendSlider);
    envAttackBendSlider.setVisible(true);
    envAttackBendSlider.setColour(Slider::thumbColourId, Colours::darkgrey);
    envAttackBendSlider.setColour(Slider::trackColourId, Colours::grey);
    envAttackBendSlider.setColour(Slider::backgroundColourId, Colours::grey);
    
    addAndMakeVisible(envAttackBendLabel);
    envAttackBendLabel.setText ("A-Bend", dontSendNotification);
    envAttackBendLabel.setColour(Label::textColourId, Colours::lightgrey);
    envAttackBendLabel.attachToComponent (&envAttackBendSlider, false);
    
    
    
    
    //==================================================================
    envSustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    envSustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
    envSustainSlider.setRange(0.0f, 1.00f);
    envSustainSlider.setValue(0.01f);
    envSustainSlider.setTextValueSuffix (" ms");
    envSustainSlider.setBounds((WidthTmp*9/10) + knobWidth*1, HeightTmp/6, knobWidth, knobHeight);/* local: X, Y, W， H */
    addAndMakeVisible(envSustainSlider);
    envSustainSlider.setVisible(true);
    envSustainSlider.setColour(Slider::thumbColourId, Colours::darkgrey);
    envSustainSlider.setColour(Slider::trackColourId, Colours::grey);
    envSustainSlider.setColour(Slider::backgroundColourId, Colours::grey);
    
    addAndMakeVisible(envSustainLabel);
    envSustainLabel.setText ("Sustain", dontSendNotification);
    envSustainLabel.setColour(Label::textColourId, Colours::lightgrey);
    envSustainLabel.attachToComponent (&envSustainSlider, false);
    
    
    
    
    //==================================================================
    envDecayBendSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    envDecayBendSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
    envDecayBendSlider.setRange(0.0f, 1.00f);
    envDecayBendSlider.setValue(0.01f);
    envDecayBendSlider.setTextValueSuffix (" ms");
    envDecayBendSlider.setBounds((WidthTmp*9/10) - knobWidth*1.5, HeightTmp*4/6, knobWidth, knobHeight);/* local: X, Y, W， H */
    addAndMakeVisible(envDecayBendSlider);
    envDecayBendSlider.setVisible(true);
    envDecayBendSlider.setColour(Slider::thumbColourId, Colours::darkgrey);
    envDecayBendSlider.setColour(Slider::trackColourId, Colours::grey);
    envDecayBendSlider.setColour(Slider::backgroundColourId, Colours::grey);
    
    addAndMakeVisible(envDecayBendLabel);
    envDecayBendLabel.setText ("D-Bend", dontSendNotification);
    envDecayBendLabel.setColour(Label::textColourId, Colours::lightgrey);
    envDecayBendLabel.attachToComponent (&envDecayBendSlider, false);
    
    //==================================================================
    envReleaseBendSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    envReleaseBendSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
    envReleaseBendSlider.setRange(0.0f, 1.00f);
    envReleaseBendSlider.setValue(0.01f);
    envReleaseBendSlider.setTextValueSuffix (" ms");
    envReleaseBendSlider.setBounds((WidthTmp*9/10) + knobWidth*1, HeightTmp*4/6, knobWidth, knobHeight);/* local: X, Y, W， H */
    addAndMakeVisible(envReleaseBendSlider);
    envReleaseBendSlider.setVisible(true);
    envReleaseBendSlider.setColour(Slider::thumbColourId, Colours::darkgrey);
    envReleaseBendSlider.setColour(Slider::trackColourId, Colours::grey);
    envReleaseBendSlider.setColour(Slider::backgroundColourId, Colours::grey);
    
    addAndMakeVisible(envReleaseBendLabel);
    envReleaseBendLabel.setText ("R-Bend", dontSendNotification);
    envReleaseBendLabel.setColour(Label::textColourId, Colours::lightgrey);
    envReleaseBendLabel.attachToComponent (&envReleaseBendSlider, false);
    
    
    
    
    //==================================================================
    envAttackTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envAttack"+String(envSerial), envAttackSlider));
    envHoldTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envHold"+String(envSerial), envHoldSlider));
    envDecayTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envDecay"+String(envSerial), envDecaySlider));
    envReleaseTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envRelease"+String(envSerial), envReleaseSlider));
    
    envAttackBendTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envAttackBend"+String(envSerial), envAttackBendSlider));
    envSustainTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envSustain"+String(envSerial), envSustainSlider));
    envDecayBendTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envDecayBend"+String(envSerial), envDecayBendSlider));
    envReleaseBendTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envReleaseBend"+String(envSerial), envReleaseBendSlider));
}

void OrionEnvConfiguration::paint (Graphics& g)
{
    
    
   // envbackground = new File(File::getSpecialLocation(File::globalApplicationsDirectory).getChildFile("Orion").getChildFile("OrionSampler").getChildFile("OrionSampler").getChildFile("Contents").getChildFile("Resources").getChildFile("skin").getChildFile("pictures").getChildFile("orionEnvBackground.png"));
    /*
    Image envbackground = ImageCache::getFromMemory(BinaryData::orionEnvBackground_png, BinaryData::orionEnvBackground_pngSize);
  
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    RectanglePlacement orionBackgroundRectanglePlacement(64);
    g.drawImageWithin(envbackground, 0, 0,OrionGlobalWidth,OrionGlobalHeight/3/11*10,orionBackgroundRectanglePlacement,false);
    */
    
    /* Customize the sliders*/
    OrionRotarySlider* cusRotarySliderlook = new OrionRotarySlider();
    if(auto* newl = dynamic_cast<juce::LookAndFeel*> (cusRotarySliderlook))
    {
        envAttackSlider.setLookAndFeel(newl);
        envHoldSlider.setLookAndFeel(newl);
        envDecaySlider.setLookAndFeel(newl);
        envReleaseSlider.setLookAndFeel(newl);\
        
    }
    //paint vertical lines
    
    Image eqbackground = ImageCache::getFromMemory(BinaryData::EQ_Background_png, BinaryData::EQ_Background_pngSize);
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    RectanglePlacement orionBackgroundRectanglePlacement(64);
    g.drawImageWithin(eqbackground, 0, 0,OrionGlobalWidth,OrionGlobalHeight/3/11*10,orionBackgroundRectanglePlacement,false);
    
    
    g.setFont (12.0f);
    g.setColour (Colours::silver);
    g.drawRoundedRectangle (plotFrame.toFloat(), 5, 2);
    for (int i=0; i < 40; ++i) {
        g.setColour (Colours::silver.withAlpha (0.3f));
        auto x = plotFrame.getX() + plotFrame.getWidth() * i * 0.025f;
        //std::cout<<"where are you plotting "<<x<<"\n";
        if (i > 0) g.drawVerticalLine (roundToInt (x), plotFrame.getY(), plotFrame.getBottom());
        /*
        g.setColour (Colours::silver);
        auto freq = getFrequencyForPosition (i * 0.025f);
        if(abs(round(freq) - freq) < 0.000000000000001){
            g.drawFittedText ((freq < 1000) ? String (freq) + " Hz" : String (freq / 1000, 1) + " kHz",
                              roundToInt (x + 3), getHeight()/20, 50, 15, Justification::left, 1);
        }
         */
        
    }
    //********for the horizontal lines*************
    g.setColour (Colours::silver.withAlpha (0.3f));
    g.drawHorizontalLine (roundToInt (plotFrame.getY() + 0.25 * plotFrame.getHeight()), plotFrame.getX(), plotFrame.getRight());
    g.drawHorizontalLine (roundToInt (plotFrame.getY() + 0.75 * plotFrame.getHeight()), plotFrame.getX(), plotFrame.getRight());
    
    g.setColour (Colours::silver);
}

void OrionEnvConfiguration::resized()
{
  plotFrame = getLocalBounds().reduced (270, 3);
}

OrionEnvConfiguration::~OrionEnvConfiguration()
{
    envAttackTree.reset();
    envHoldTree.reset();
    envDecayTree.reset();
    envReleaseTree.reset();
    
    envAttackBendTree.reset();
    envSustainTree.reset();
    envDecayBendTree.reset();
    envReleaseBendTree.reset();
    
    envSwitchButtonAttachment.reset();

}
