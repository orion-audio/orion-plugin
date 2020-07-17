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
#include "GlobalCoefficients.h"


#include "DigitTransverter.h"

//==============================================================================
OrionEnvConfiguration::OrionEnvConfiguration(OrionaudioAudioProcessor& p, int serial) : processor(p)
{
    envSerial = serial;
    
    
    audioFile = &instrumentSamplePathes[serial];
    //-------------------------------- Background Image -------------------------------//
    Image backgroundImage = ImageCache::getFromMemory(BinaryData::ENVBackground_png, BinaryData::ENVBackground_pngSize);
    backgroundImageView.reset(new DrawableImage());
    backgroundImageView->setImage(backgroundImage);
    addAndMakeVisible(backgroundImageView.get());
    
    
    //-------------------------------- Envelope Meter -------------------------------//
    envelopeMeter.reset(new EnvelopeMeter());
    envelopeMeter->serial = serial;
    addAndMakeVisible(envelopeMeter.get());
    
    
    
    //-------------------------------- Envelope Switch -------------------------------//
    envSwitch.reset(new ImageButton());
    envSwitch->setImages(false, true, true,
                          switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
                          Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
    envSwitch->onStateChange = [&]
    {
        switchClicked(envSwitch->isDown());
    };
    addAndMakeVisible(envSwitch.get());
    
    //------------------------------------ ADSR Knobs ------------------------------------//
    // Attack
    aSlider.reset(new Slider());
    aSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    aSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    aSlider->setRange(0.1f, 1500.0f);
    aSlider->setValue(0.1f);
    aSlider->addListener(this);
    addAndMakeVisible(aSlider.get());
      
    aSliderLabel.reset(new Label("0.10 ms", "0.10 ms"));
    aSliderLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(aSliderLabel.get());
    aSliderLabel->setAlpha(0.8);
    
    // Decay
    dSlider.reset(new Slider());
    dSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    dSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    dSlider->setRange(0.1f, 2500.0f);
    dSlider->setValue(1250.0f);
    dSlider->addListener(this);
    addAndMakeVisible(dSlider.get());
      
    dSliderLabel.reset(new Label("0.10 ms", "0.10 ms"));
    dSliderLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(dSliderLabel.get());
    dSliderLabel->setAlpha(0.8);
    
    // Hold
    hSlider.reset(new Slider());
    hSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    hSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    hSlider->setRange(0.1f, 1500.0f);
    hSlider->setValue(750.0f);
    hSlider->addListener(this);
    addAndMakeVisible(hSlider.get());
      
    hSliderLabel.reset(new Label("0.10 ms", "0.10 ms"));
    hSliderLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(hSliderLabel.get());
    hSliderLabel->setAlpha(0.8);
    
    // Release
    rSlider.reset(new Slider());
    rSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    rSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    rSlider->setRange(0.1f, 2500.0f);
    rSlider->setValue(1250.0f);
    rSlider->addListener(this);
    addAndMakeVisible(rSlider.get());
      
    rSliderLabel.reset(new Label("0.10 ms", "0.10 ms"));
    rSliderLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(rSliderLabel.get());
    rSliderLabel->setAlpha(0.8);
    
    
    //------------------------------------ Bend Sliders ------------------------------------//
    // Attack Bend
    aBendSlider.reset(new Slider());
    aBendSlider->setSliderStyle(Slider::SliderStyle::LinearVertical);
    aBendSlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    aBendSlider->setColour(Slider::trackColourId, juce::Colours::grey);
    aBendSlider->setColour(Slider::thumbColourId, juce::Colours::white);
    aBendSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    aBendSlider->setRange(0.0f, 1.00f);
    aBendSlider->setValue(0.5f);
    aBendSlider->addListener(this);
    addAndMakeVisible(aBendSlider.get());
      
    aBendSliderLabel.reset(new Label("0.5 bd", "0.5 bd"));
    aBendSliderLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(aBendSliderLabel.get());
    aBendSliderLabel->setAlpha(0.8);
    
    // Decay Bend
    dBendSlider.reset(new Slider());
    dBendSlider->setSliderStyle(Slider::SliderStyle::LinearVertical);
    dBendSlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    dBendSlider->setColour(Slider::trackColourId, juce::Colours::grey);
    dBendSlider->setColour(Slider::thumbColourId, juce::Colours::white);
    dBendSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    dBendSlider->setRange(0.0f, 1.00f);
    dBendSlider->setValue(0.5f);
    dBendSlider->addListener(this);
    addAndMakeVisible(dBendSlider.get());
      
    dBendSliderLabel.reset(new Label("0.5 bd", "0.5 bd"));
    dBendSliderLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(dBendSliderLabel.get());
    dBendSliderLabel->setAlpha(0.8);
    
    // Sustain Bend
    sBendSlider.reset(new Slider());
    sBendSlider->setSliderStyle(Slider::SliderStyle::LinearVertical);
    sBendSlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    sBendSlider->setColour(Slider::trackColourId, juce::Colours::grey);
    sBendSlider->setColour(Slider::thumbColourId, juce::Colours::white);
    sBendSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    sBendSlider->setRange(0.0f, 1.00f);
    sBendSlider->setValue(0.5f);
    sBendSlider->addListener(this);
    addAndMakeVisible(sBendSlider.get());
      
    sBendSliderLabel.reset(new Label("0.5 bd", "0.5 bd"));
    sBendSliderLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(sBendSliderLabel.get());
    sBendSliderLabel->setAlpha(0.8);
    
    // Release Bend
    rBendSlider.reset(new Slider());
    rBendSlider->setSliderStyle(Slider::SliderStyle::LinearVertical);
    rBendSlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    rBendSlider->setColour(Slider::trackColourId, juce::Colours::grey);
    rBendSlider->setColour(Slider::thumbColourId, juce::Colours::white);
    rBendSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    rBendSlider->setRange(0.0f, 1.00f);
    rBendSlider->setValue(0.5f);
    rBendSlider->addListener(this);
    addAndMakeVisible(rBendSlider.get());
      
    rBendSliderLabel.reset(new Label("0.5 bd", "0.5 bd"));
    rBendSliderLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(rBendSliderLabel.get());
    rBendSliderLabel->setAlpha(0.8);
    
    //----------------------------------------------------------------------------------//
    
    
//    int WidthTmp = OrionGlobalWidth;
//    int HeightTmp = OrionGlobalHeight*9/30;
//
//    int textboxHeight = OrionGlobalHeight/60;
//    int knobWidth = OrionGlobalWidth*1/25;
//    int knobHeight = knobWidth + textboxHeight;
//
//
//    setBounds(0, 0, OrionGlobalWidth, OrionGlobalHeight/3);
//    /**************** slider initialization values ********************/
//
//    //==================================================================
//    envAttackSlider.setSliderStyle(Slider::SliderStyle::Rotary);
//    envAttackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
//    envAttackSlider.setRange(0.1f, 1500.0f);
//    envAttackSlider.setValue(0.1f);
//    envAttackSlider.setTextValueSuffix (" ms");
//    envAttackSlider.setBounds(((WidthTmp*2/10)/2) - knobWidth*1.5, HeightTmp/6, knobWidth, knobHeight);/* local: X, Y, W， H */
//    //addAndMakeVisible(envAttackSlider);
//    //envAttackSlider.setVisible(true);
//    //addAndMakeVisible(envAttackLabel);
//    envAttackLabel.setText ("Attack", dontSendNotification);
//    envAttackLabel.setColour(Label::textColourId, Colours::lightgrey);
//    envAttackLabel.attachToComponent (&envAttackSlider, false);
//
//
//
//    //==================================================================
//    envDecaySlider.setSliderStyle(Slider::SliderStyle::Rotary);
//    envDecaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
//    envDecaySlider.setRange(0.1f, 2500.0f);
//    envDecaySlider.setValue(0.1f);
//    envDecaySlider.setTextValueSuffix (" ms");
//    envDecaySlider.setBounds(((WidthTmp*2/10)/2) + knobWidth*1, HeightTmp/6, knobWidth, knobHeight);/* local: X, Y, W， H */
//    //addAndMakeVisible(envDecaySlider);
//    //envDecaySlider.setVisible(true);
//    //addAndMakeVisible(envDecayLabel);
//    envDecayLabel.setText ("Decay", dontSendNotification);
//    envDecayLabel.setColour(Label::textColourId, Colours::lightgrey);
//    envDecayLabel.attachToComponent (&envDecaySlider, false);
//
//
//    //==================================================================
//    envHoldSlider.setSliderStyle(Slider::SliderStyle::Rotary);
//    envHoldSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
//    envHoldSlider.setRange(0.1f, 1500.0f);
//    envHoldSlider.setValue(0.1f);
//    envHoldSlider.setTextValueSuffix (" ms");
//    envHoldSlider.setBounds(((WidthTmp*2/10)/2) - knobWidth*1.5, HeightTmp*4/6, knobWidth, knobHeight);/* local: X, Y, W， H */
//    //addAndMakeVisible(envHoldSlider);
//    //envHoldSlider.setVisible(true);
//    //addAndMakeVisible(envAttackLabel);
//    envHoldLabel.setText ("Hold", dontSendNotification);
//    envHoldLabel.setColour(Label::textColourId, Colours::lightgrey);
//    envHoldLabel.attachToComponent (&envHoldSlider, false);
//
//    //==================================================================
//    envReleaseSlider.setSliderStyle(Slider::SliderStyle::Rotary);
//    envReleaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
//    envReleaseSlider.setRange(0.1f, 2500.0f);
//    envReleaseSlider.setValue(0.1f);
//    envReleaseSlider.setTextValueSuffix (" ms");
//    envReleaseSlider.setBounds(((WidthTmp*2/10)/2) + knobWidth*1, HeightTmp*4/6, knobWidth, knobHeight);/* local: X, Y, W， H */
//    //addAndMakeVisible(envReleaseSlider);
//    //envReleaseSlider.setVisible(true);
//    //addAndMakeVisible(envReleaseLabel);
//    envReleaseLabel.setText ("Release", dontSendNotification);
//    envReleaseLabel.setColour(Label::textColourId, Colours::lightgrey);
//    envReleaseLabel.attachToComponent (&envReleaseSlider, false);
//
//
//
//
//    //==================================================================
//    envAttackBendSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
//    envAttackBendSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
//    envAttackBendSlider.setRange(0.0f, 1.00f);
//    envAttackBendSlider.setValue(0.01f);
//    envAttackBendSlider.setTextValueSuffix (" ms");
//    envAttackBendSlider.setBounds((WidthTmp*9/10) - knobWidth*1.5, HeightTmp/6, knobWidth, knobHeight);/* local: X, Y, W， H */
//    //addAndMakeVisible(envAttackBendSlider);
//    envAttackBendSlider.setVisible(true);
//    envAttackBendSlider.setColour(Slider::thumbColourId, Colours::darkgrey);
//    envAttackBendSlider.setColour(Slider::trackColourId, Colours::grey);
//    envAttackBendSlider.setColour(Slider::backgroundColourId, Colours::grey);
//
//    //addAndMakeVisible(envAttackBendLabel);
//    envAttackBendLabel.setText ("A-Bend", dontSendNotification);
//    envAttackBendLabel.setColour(Label::textColourId, Colours::lightgrey);
//    envAttackBendLabel.attachToComponent (&envAttackBendSlider, false);
//
//
//
//
//    //==================================================================
//    envSustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
//    envSustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
//    envSustainSlider.setRange(0.0f, 1.00f);
//    envSustainSlider.setValue(0.01f);
//    envSustainSlider.setTextValueSuffix (" ms");
//    envSustainSlider.setBounds((WidthTmp*9/10) - knobWidth*1.5, HeightTmp*4/6, knobWidth, knobHeight);/* local: X, Y, W， H */
//    //addAndMakeVisible(envSustainSlider);
//    envSustainSlider.setVisible(true);
//    envSustainSlider.setColour(Slider::thumbColourId, Colours::darkgrey);
//    envSustainSlider.setColour(Slider::trackColourId, Colours::grey);
//    envSustainSlider.setColour(Slider::backgroundColourId, Colours::grey);
//
//    //addAndMakeVisible(envSustainLabel);
//    envSustainLabel.setText ("Sustain", dontSendNotification);
//    envSustainLabel.setColour(Label::textColourId, Colours::lightgrey);
//    envSustainLabel.attachToComponent (&envSustainSlider, false);
//
//
//
//
//    //==================================================================
//    envDecayBendSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
//    envDecayBendSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
//    envDecayBendSlider.setRange(0.0f, 1.00f);
//    envDecayBendSlider.setValue(0.01f);
//    envDecayBendSlider.setTextValueSuffix (" ms");
//    envDecayBendSlider.setBounds((WidthTmp*9/10) + knobWidth*1, HeightTmp/6, knobWidth, knobHeight);/* local: X, Y, W， H */
//    //addAndMakeVisible(envDecayBendSlider);
//
//    envDecayBendSlider.setVisible(true);
//    envDecayBendSlider.setColour(Slider::thumbColourId, Colours::darkgrey);
//    envDecayBendSlider.setColour(Slider::trackColourId, Colours::grey);
//    envDecayBendSlider.setColour(Slider::backgroundColourId, Colours::grey);
//
//    //addAndMakeVisible(envDecayBendLabel);
//    envDecayBendLabel.setText ("D-Bend", dontSendNotification);
//    envDecayBendLabel.setColour(Label::textColourId, Colours::lightgrey);
//    envDecayBendLabel.attachToComponent (&envDecayBendSlider, false);
//
//    //==================================================================
//    envReleaseBendSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
//    envReleaseBendSlider.setTextBoxStyle(Slider::TextBoxBelow, false, OrionGlobalWidth/23, textboxHeight);
//    envReleaseBendSlider.setRange(0.0f, 1.00f);
//    envReleaseBendSlider.setValue(0.01f);
//    envReleaseBendSlider.setTextValueSuffix (" ms");
//    envReleaseBendSlider.setBounds((WidthTmp*9/10) + knobWidth*1, HeightTmp*4/6, knobWidth, knobHeight);/* local: X, Y, W， H */
//    //addAndMakeVisible(envReleaseBendSlider);
//    envReleaseBendSlider.setVisible(true);
//    envReleaseBendSlider.setColour(Slider::thumbColourId, Colours::darkgrey);
//    envReleaseBendSlider.setColour(Slider::trackColourId, Colours::grey);
//    envReleaseBendSlider.setColour(Slider::backgroundColourId, Colours::grey);
//
//    //addAndMakeVisible(envReleaseBendLabel);
//    envReleaseBendLabel.setText ("R-Bend", dontSendNotification);
//    envReleaseBendLabel.setColour(Label::textColourId, Colours::lightgrey);
//    envReleaseBendLabel.attachToComponent (&envReleaseBendSlider, false);
//
//
//
//
//    //==================================================================
//    envAttackTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envAttack"+String(envSerial), envAttackSlider));
//    envHoldTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envHold"+String(envSerial), envHoldSlider));
//    envDecayTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envDecay"+String(envSerial), envDecaySlider));
//    envReleaseTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envRelease"+String(envSerial), envReleaseSlider));
//
//    envAttackBendTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envAttackBend"+String(envSerial), envAttackBendSlider));
//    envSustainTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envSustain"+String(envSerial), envSustainSlider));
//    envDecayBendTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envDecayBend"+String(envSerial), envDecayBendSlider));
//    envReleaseBendTree.reset(new AudioProcessorValueTreeState::SliderAttachment (processor.getValueTree(), "envReleaseBend"+String(envSerial), envReleaseBendSlider));
    
    
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
    
    
    //******** for the horizontal lines *************
    //g.setColour (Colours::silver.withAlpha (0.3f));
    //g.drawHorizontalLine (roundToInt (plotFrame.getY() + 0.25 * plotFrame.getHeight()), plotFrame.getX(), plotFrame.getRight());
    //g.drawHorizontalLine (roundToInt (plotFrame.getY() + 0.75 * plotFrame.getHeight()), plotFrame.getX(), plotFrame.getRight());
    //g.setColour (Colours::silver);
}

void OrionEnvConfiguration::resized()
{
    //--------- Background Image ---------//
    Rectangle<int> area = getLocalBounds();
    backgroundImageView->setTransformToFit(area.toFloat(), RectanglePlacement::stretchToFit);
    
    //plotFrame = getLocalBounds().reduced (270, 3);
    
    float envlopeMeterX = getWidth()/4.625;
    float envlopeMeterWidth = getWidth()*5.68/10;
    float envlopeMeterHeight = getWidth()/5.45;
    
    float switchX = getWidth() * 0.7666;
    float switchY = getWidth()/800;
    float switchSize = getWidth()/55;
    
    float knobY1 = getWidth()/30;
    float knobY2 = getWidth()/8.25;
    float knobSize = getWidth()/25;
    
    float sliderY1 = getWidth()/100;
    float sliderY2 = getWidth()/10;
    float sliderHeight = getWidth()/15;
    float sliderWidth = getWidth()/50;
    
    float TextY1 =  getWidth()/13.25;
    float TextY2 =  getWidth()/6.00;
    float TextHeight =  getWidth()/60;
    
    
    //-------------------------------- Envelope Meter -------------------------------//
    area = Rectangle<int>(envlopeMeterX, 0,  envlopeMeterWidth, envlopeMeterHeight);
    envelopeMeter->setBounds(area);
    
    //-------------------------------- Envelope Switch -------------------------------//
    area = Rectangle<int>(switchX, switchY,  switchSize, switchSize);
    envSwitch->setBounds(area);
    

    //------------------------------------ ADSR Knobs ------------------------------------//
    // Attack
    area = Rectangle<int>(getWidth()/29, knobY1,  knobSize, knobSize);
    aSlider->setBounds(area);

    area = Rectangle<int>(getWidth()/29 - knobSize/2, TextY1,  2 * knobSize, TextHeight);
    aSliderLabel->setBounds(area);
  
    // Decay
    area = Rectangle<int>(getWidth()/7, knobY1,  knobSize, knobSize);
    dSlider->setBounds(area);

    area = Rectangle<int>(getWidth()/7 - knobSize/2, TextY1,  2 * knobSize, TextHeight);
    dSliderLabel->setBounds(area);
   
    // Hold
    area = Rectangle<int>(getWidth()/29, knobY2,  knobSize, knobSize);
    hSlider->setBounds(area);

    area = Rectangle<int>(getWidth()/29 - knobSize/2, TextY2,  2 * knobSize, TextHeight);
    hSliderLabel->setBounds(area);
    
    // Release
    area = Rectangle<int>(getWidth()/7, knobY2,  knobSize, knobSize);
    rSlider->setBounds(area);

    area = Rectangle<int>(getWidth()/7 - knobSize/2, TextY2,  2 * knobSize, TextHeight);
    rSliderLabel->setBounds(area);

    //------------------------------------ Bend Sliders ------------------------------------//
    // Attack Bend
    area = Rectangle<int>(getWidth()/1.205, sliderY1,  sliderWidth, sliderHeight);
    aBendSlider->setBounds(area);

    area = Rectangle<int>(getWidth()/1.220, TextY1,  knobSize, TextHeight);
    aBendSliderLabel->setBounds(area);

    // Decay Bend
    area = Rectangle<int>(getWidth()/1.0665, sliderY1,  sliderWidth, sliderHeight);
    dBendSlider->setBounds(area);

    area = Rectangle<int>(getWidth()/1.0750, TextY1,  knobSize, TextHeight);
    dBendSliderLabel->setBounds(area);

    // Sustain Bend
    area = Rectangle<int>(getWidth()/1.205, sliderY2,  sliderWidth, sliderHeight);
    sBendSlider->setBounds(area);

    area = Rectangle<int>(getWidth()/1.220, TextY2,  knobSize, TextHeight);
    sBendSliderLabel->setBounds(area);

    // Release Bend
    area = Rectangle<int>(getWidth()/1.0665, sliderY2,  sliderWidth, sliderHeight);
    rBendSlider->setBounds(area);

    area = Rectangle<int>(getWidth()/1.0750, TextY2,  knobSize, TextHeight);
    rBendSliderLabel->setBounds(area);

}

OrionEnvConfiguration::~OrionEnvConfiguration()
{
//    envAttackTree.reset();
//    envHoldTree.reset();
//    envDecayTree.reset();
//    envReleaseTree.reset();
//
//    envAttackBendTree.reset();
//    envSustainTree.reset();
//    envDecayBendTree.reset();
//    envReleaseBendTree.reset();
//
//    envSwitchButtonAttachment.reset();

}


//String valueDoubleDigitTranslator(double inputValue)
//{
//    double a = inputValue;
//    float b = (int)(a * 100 + .5);
//    float c =  (float)b / 100;
//    String d = String(c);
//    if(d == "0")
//    {
//        d = "0.00";
//    }
//    else if(d == "1")
//    {
//        d = "1.00";
//    }
//
//    return d;
//}


//MARK:- Switch Image Changer
void OrionEnvConfiguration::setSwitchImage(bool On)
{
    if(On)
    {
        envSwitch->setImages(false, true, true,
        switchOn, 1.f, Colours::transparentBlack, switchOn, 1.f,
        Colours::transparentBlack, switchOn, 1.f, Colours::transparentBlack);
    }
    else
    {
        envSwitch->setImages(false, true, true,
        switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
        Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
    }
}

//MARK:- Switch Clicker
void OrionEnvConfiguration::switchClicked(bool isDown)
{
    if(isDown)
    {
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(envSerial)))
        {
            voice->envswitch = !voice->envswitch;
            
            envSwitches[instrumetSerial] = !envSwitches[instrumetSerial];
            setSwitchImage(voice->envswitch);
        }

    }
}


//MARK:- Slider Value Change
void OrionEnvConfiguration::sliderValueChanged (Slider* slider)
{
    //------------------------------------ ADSR ------------------------------------//
    
    if(slider == aSlider.get())// Attack
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(envSerial)))
        {
            voice->env.setAttackTime_mSec(aSlider->getValue());
        }
        
        envAttackCoefficient[instrumetSerial] = aSlider->getValue();
        String value = DigitTransverter(envAttackCoefficient[instrumetSerial]);
        value.append(" ms",3);
        aSliderLabel->setText(value,dontSendNotification);
        
    }
    else if(slider == dSlider.get())// Decay
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(envSerial)))
        {
            voice->env.setDecayTime_mSec(dSlider->getValue());
        }
        
        envDecayCoefficient[instrumetSerial] = dSlider->getValue();
        String value = DigitTransverter(envDecayCoefficient[instrumetSerial]);
        value.append(" ms",3);
        dSliderLabel->setText(value,dontSendNotification);
        
    }
    else if(slider == hSlider.get())// Hold
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(envSerial)))
        {
            voice->env.setSustainTime_mSec(hSlider->getValue());
        }
        
        envSustainCoefficient[instrumetSerial] = hSlider->getValue();
        String value = DigitTransverter(envSustainCoefficient[instrumetSerial]);
        value.append(" ms",3);
        hSliderLabel->setText(value,dontSendNotification);
        
    }
    else if(slider == rSlider.get())// Release
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(envSerial)))
        {
            voice->env.setReleaseTime_mSec(rSlider->getValue());
        }
        
        
        envReleaseCoefficient[instrumetSerial] = rSlider->getValue();
        String value = DigitTransverter(envReleaseCoefficient[instrumetSerial]);
        value.append(" ms",3);
        rSliderLabel->setText(value,dontSendNotification);
        
    }
    
    
    //------------------------------------ Bend ------------------------------------//
    
    if(slider == aBendSlider.get())// Attack Bend
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(envSerial)))
        {

        }

        envAttackBendCoefficient[instrumetSerial] = aBendSlider->getValue();
        String value = DigitTransverter(envAttackBendCoefficient[instrumetSerial]);
        value.append(" bd",3);
        aBendSliderLabel->setText(value,dontSendNotification);
    }
    else if(slider == dBendSlider.get())// Decay Bend
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(envSerial)))
        {

        }

        envDecayBendCoefficient[instrumetSerial] = dBendSlider->getValue();
        String value = DigitTransverter(envDecayBendCoefficient[instrumetSerial]);
        value.append(" bd",3);
        dBendSliderLabel->setText(value,dontSendNotification);
    }
    else if(slider == sBendSlider.get())// Sustain Bend
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(envSerial)))
        {
            voice->env.setSustainLevel(sBendSlider->getValue());
        }

        envSustainBendCoefficient[instrumetSerial] = sBendSlider->getValue();
        envelopeMeter->setSustainBendCoefficient(envSustainBendCoefficient[instrumetSerial]);
        String value = DigitTransverter(envSustainBendCoefficient[instrumetSerial]);
        value.append(" bd",3);
        sBendSliderLabel->setText(value,dontSendNotification);

    }
    else if(slider == rBendSlider.get())// Release Bend
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(envSerial)))
        {

        }

        envReleaseBendCoefficient[instrumetSerial] = rBendSlider->getValue();
        String value = DigitTransverter(envReleaseBendCoefficient[instrumetSerial]);
        value.append(" bd",3);
        rBendSliderLabel->setText(value,dontSendNotification);

    }
    
    envelopeMeter->updateEnvelope();
    
}
