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
    rSlider->addListener(this);
    addAndMakeVisible(rSlider.get());
      
    rSliderLabel.reset(new Label("0.10 ms", "0.10 ms"));
    rSliderLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(rSliderLabel.get());
    rSliderLabel->setAlpha(0.8);
    
    //Set Knob Range & Init Values
//    aSlider->setRange(0.1f, 1500.0f);
//    aSlider->setValue(0.1f);
//    dSlider->setRange(0.1f, 2500.0f);
//    dSlider->setValue(1250.0f);
//    hSlider->setRange(0.1f, 1500.0f);
//    hSlider->setValue(750.0f);
//    rSlider->setRange(0.1f, 2500.0f);
//    rSlider->setValue(1250.0f);
    
    knobsSetRange();
    
    //------------------------------------ Bend Sliders ------------------------------------//
    // Attack Bend
    aBendSlider.reset(new Slider());
    aBendSlider->setSliderStyle(Slider::SliderStyle::LinearVertical);
    aBendSlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    aBendSlider->setColour(Slider::trackColourId, juce::Colours::grey);
    aBendSlider->setColour(Slider::thumbColourId, juce::Colours::white);
    aBendSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    //aBendSlider->setRange(0.0f, 1.00f);
    //aBendSlider->setValue(0.5f);
    aBendSlider->setRange(-10.0f, 0.0f);
    aBendSlider->setValue(-5.0f);
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
    //dBendSlider->setRange(0.0f, 1.00f);
    //dBendSlider->setValue(0.5f);
    dBendSlider->setRange(-10.0f, 10.0f);
    dBendSlider->setValue(0.0f);
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
    //rBendSlider->setRange(0.000001f, 1.00f);
    //rBendSlider->setValue(0.5f);
    rBendSlider->setRange(-10.0f, 0.0f);
    rBendSlider->setValue(-5.0f);
    rBendSlider->addListener(this);
    addAndMakeVisible(rBendSlider.get());
      
    rBendSliderLabel.reset(new Label("0.5 bd", "0.5 bd"));
    rBendSliderLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(rBendSliderLabel.get());
    rBendSliderLabel->setAlpha(0.8);
    

    
    
}

void OrionEnvConfiguration::paint (Graphics& g)
{
    //std::cout<<"paint ENV : "<<instrumetClickedSerial<<std::endl;
    
    
    
   // envbackground = new File(File::getSpecialLocation(File::globalApplicationsDirectory).getChildFile("Orion").getChildFile("OrionSampler").getChildFile("OrionSampler").getChildFile("Contents").getChildFile("Resources").getChildFile("skin").getChildFile("pictures").getChildFile("orionEnvBackground.png"));
    /*
    Image envbackground = ImageCache::getFromMemory(BinaryData::orionEnvBackground_png, BinaryData::orionEnvBackground_pngSize);
  
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    RectanglePlacement orionBackgroundRectanglePlacement(64);
    g.drawImageWithin(envbackground, 0, 0,OrionGlobalWidth,OrionGlobalHeight/3/11*10,orionBackgroundRectanglePlacement,false);
    */
    

    //paint vertical lines
    
    
    
//    g.setFont (12.0f);
//    g.setColour (Colours::silver);
//    g.drawRoundedRectangle (plotFrame.toFloat(), 5, 2);
//    for (int i=0; i < 40; ++i)
//    {
//        g.setColour (Colours::silver.withAlpha (0.3f));
//        auto x = plotFrame.getX() + plotFrame.getWidth() * i * 0.025f;
//        //std::cout<<"where are you plotting "<<x<<"\n";
//        if (i > 0) g.drawVerticalLine (roundToInt (x), plotFrame.getY(), plotFrame.getBottom());
//        /*
//        g.setColour (Colours::silver);
//        auto freq = getFrequencyForPosition (i * 0.025f);
//        if(abs(round(freq) - freq) < 0.000000000000001){
//            g.drawFittedText ((freq < 1000) ? String (freq) + " Hz" : String (freq / 1000, 1) + " kHz",
//                              roundToInt (x + 3), getHeight()/20, 50, 15, Justification::left, 1);
//        }
//         */
//        
//    }
    
    
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
    
    float switchX = getWidth() * 0.9766;
    float switchY = getWidth()/200;
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
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            //voice->envswitch = !voice->envswitch;
            envSwitches[instrumetClickedSerial] = !envSwitches[instrumetClickedSerial];
            voice->envswitch = envSwitches[instrumetClickedSerial];
            setSwitchImage(voice->envswitch);
        }
    }
}

//MARK:- Knobs Set Range
void OrionEnvConfiguration::knobsSetRange()
{
    aSlider->setRange(0.000f, envelopeMeter->getDecayCoef() - 0.0001f);
    aSlider->setValue(envelopeMeter->getAttackCoef());
    aSlider->repaint();

    dSlider->setRange(envelopeMeter->getAttackCoef() + 0.0001f, envelopeMeter->getSustainCoef() - 0.0001);
    dSlider->setValue(envelopeMeter->getDecayCoef());
    dSlider->repaint();

    hSlider->setRange(envelopeMeter->getDecayCoef() + 0.0001f, envelopeMeter->getReleaseCoef() - 0.0001);
    hSlider->setValue(envelopeMeter->getSustainCoef());
    hSlider->repaint();

    rSlider->setRange(envelopeMeter->getSustainCoef() + 0.0001f, 1.0f);
    rSlider->setValue(envelopeMeter->getReleaseCoef());
    rSlider->repaint();
}






//MARK:- Slider Value Change
void OrionEnvConfiguration::sliderValueChanged (Slider* slider)
{
    //------------------------------------ ADSR ------------------------------------//
    if(slider == aSlider.get())/* Attack */
    {
        DBG("a");
        envAttackCoefficient[instrumetClickedSerial] = aSlider->getValue();
        envelopeMeter->setAttackCoef(envAttackCoefficient[instrumetClickedSerial]);
        
        double attackTime = envAttackCoefficient[instrumetClickedSerial] * envelopeMeter->getSampleLength();
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->env.setAttackTime_mSec(attackTime);//set Attack time
        }
        String value = DigitTransverter(attackTime);
        value.append(" ms",3);
        aSliderLabel->setText(value,dontSendNotification);
    }
    else if(slider == dSlider.get())/* Decay */
    {
        DBG("d");
        envDecayCoefficient[instrumetClickedSerial] = dSlider->getValue();
        envelopeMeter->setDecayCoef(envDecayCoefficient[instrumetClickedSerial]);
        
        double decayTime = (envDecayCoefficient[instrumetClickedSerial] - envelopeMeter->getAttackCoef()) * envelopeMeter->getSampleLength();
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->env.setDecayTime_mSec(decayTime);//set Decay time
        }
        String value = DigitTransverter(decayTime);
        value.append(" ms",3);
        dSliderLabel->setText(value,dontSendNotification);
    }
    else if(slider == hSlider.get())/* Hold */
    {
        DBG("s");
        envSustainCoefficient[instrumetClickedSerial] = hSlider->getValue();
        envelopeMeter->setSustainCoef(envSustainCoefficient[instrumetClickedSerial]);
        
        double sustainTime = (envSustainCoefficient[instrumetClickedSerial] - envelopeMeter->getDecayCoef()) * envelopeMeter->getSampleLength();
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->env.setSustainTime_mSec(sustainTime);//set Sustain time
        }
        String value = DigitTransverter(sustainTime);
        value.append(" ms",3);
        hSliderLabel->setText(value,dontSendNotification);
    }
    else if(slider == rSlider.get())/* Release */
    {
        DBG("r");
        envReleaseCoefficient[instrumetClickedSerial] = rSlider->getValue();
        envelopeMeter->setReleaseCoef(envReleaseCoefficient[instrumetClickedSerial]);
        
        double releaseTime = (envReleaseCoefficient[instrumetClickedSerial] - envelopeMeter->getSustainCoef()) * envelopeMeter->getSampleLength();
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->env.setReleaseTime_mSec(releaseTime);//set Release time
        }
        String value = DigitTransverter(releaseTime);
        value.append(" ms",3);
        rSliderLabel->setText(value,dontSendNotification);
    }
    
    //------------------------------------ Bend ------------------------------------//
    
    if(slider == aBendSlider.get())/* Attack Bend */
    {
        envAttackBendCoefficient[instrumetClickedSerial] = aBendSlider->getValue();

        float meterCoef = jmap<float>(envAttackBendCoefficient[instrumetClickedSerial], -10.0f, 0.0f, 0.0f,1.0f);
        envelopeMeter->setAttackBendCoef(meterCoef);
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->env.setAttackTCO(exp(-(envAttackBendCoefficient[instrumetClickedSerial] + 10)));
        }
        
        String value = DigitTransverter(meterCoef);
        value.append(" bd",3);
        aBendSliderLabel->setText(value,dontSendNotification);
    }
    else if(slider == dBendSlider.get())/* Decay Bend */
    {
        envDecayBendCoefficient[instrumetClickedSerial] = dBendSlider->getValue();
        
        float meterCoef = jmap<float>(envDecayBendCoefficient[instrumetClickedSerial], -10.0f, 10.0f, 0.0f,1.0f);
        envelopeMeter->setDecayBendCoef(meterCoef);
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->env.setDecayTCO(exp(envDecayBendCoefficient[instrumetClickedSerial]));
        }
        
        String value = DigitTransverter(meterCoef);
        value.append(" bd",3);
        dBendSliderLabel->setText(value,dontSendNotification);
    }
    else if(slider == sBendSlider.get())/* Sustain Bend */
    {
        envSustainBendCoefficient[instrumetClickedSerial] = sBendSlider->getValue();
        
        envelopeMeter->setSustainBendCoef(envSustainBendCoefficient[instrumetClickedSerial]);
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->env.setSustainLevel(envSustainBendCoefficient[instrumetClickedSerial]);
        }
        
        String value = DigitTransverter(envSustainBendCoefficient[instrumetClickedSerial]);
        value.append(" bd",3);
        sBendSliderLabel->setText(value,dontSendNotification);
    }
    else if(slider == rBendSlider.get())/* Release Bend */
    {
        envReleaseBendCoefficient[instrumetClickedSerial] = rBendSlider->getValue();
        
        float meterCoef = jmap<float>(envReleaseBendCoefficient[instrumetClickedSerial], -10.0f, 0.0f, 0.0f,1.0f);
        envelopeMeter->setReleaseBendCoef(meterCoef);
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->env.setReleaseTCO(exp(envReleaseBendCoefficient[instrumetClickedSerial]));
        }
        
        String value = DigitTransverter(meterCoef);
        value.append(" bd",3);
        rBendSliderLabel->setText(value,dontSendNotification);
    }
    
    
    
    // Update envelopeMeter
    envelopeMeter->updateEnvelope();
    knobsSetRange();
    
}


void OrionEnvConfiguration::sliderDragEnded (Slider* slider)
{
    knobsSetRange();
}


//MARK:- Knobs Init Range
void OrionEnvConfiguration::knobsInitRange()
{
    
    envelopeMeter->setAttackCoef(envAttackCoefficient[instrumetClickedSerial]);
    
    double attackTime = envAttackCoefficient[instrumetClickedSerial] * envelopeMeter->getSampleLength();
    if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
    {
        voice->env.setAttackTime_mSec(attackTime);//set Attack time
    }
    
    
    envelopeMeter->setDecayCoef(envDecayCoefficient[instrumetClickedSerial]);
    
    double decayTime = (envDecayCoefficient[instrumetClickedSerial] - envelopeMeter->getAttackCoef()) * envelopeMeter->getSampleLength();
    if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
    {
        voice->env.setDecayTime_mSec(decayTime);//set Decay time
    }
    
    envelopeMeter->setSustainCoef(envSustainCoefficient[instrumetClickedSerial]);
    
    double sustainTime = (envSustainCoefficient[instrumetClickedSerial] - envelopeMeter->getDecayCoef()) * envelopeMeter->getSampleLength();
    if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
    {
        voice->env.setSustainTime_mSec(sustainTime);//set Sustain time
    }
    
    envelopeMeter->setReleaseCoef(envReleaseCoefficient[instrumetClickedSerial]);
    
    double releaseTime = (envReleaseCoefficient[instrumetClickedSerial] - envelopeMeter->getSustainCoef()) * envelopeMeter->getSampleLength();
    if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
    {
        voice->env.setReleaseTime_mSec(releaseTime);//set Release time
    }
    
    
    float meterCoef = jmap<float>(envAttackBendCoefficient[instrumetClickedSerial], -10.0f, 0.0f, 0.0f,1.0f);
    envelopeMeter->setAttackBendCoef(meterCoef);
    
    if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
    {
        voice->env.setAttackTCO(exp(-(envAttackBendCoefficient[instrumetClickedSerial] + 10)));
    }
    
    
    meterCoef = jmap<float>(envDecayBendCoefficient[instrumetClickedSerial], -10.0f, 10.0f, 0.0f,1.0f);
    envelopeMeter->setDecayBendCoef(meterCoef);
    
    if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
    {
        voice->env.setDecayTCO(exp(envDecayBendCoefficient[instrumetClickedSerial]));
    }
    
    
    envelopeMeter->setSustainBendCoef(envSustainBendCoefficient[instrumetClickedSerial]);
    
    if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
    {
        voice->env.setSustainLevel(envSustainBendCoefficient[instrumetClickedSerial]);
    }
    
    
    meterCoef = jmap<float>(envReleaseBendCoefficient[instrumetClickedSerial], -10.0f, 0.0f, 0.0f,1.0f);
    envelopeMeter->setReleaseBendCoef(meterCoef);
    
    if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
    {
        voice->env.setReleaseTCO(exp(envReleaseBendCoefficient[instrumetClickedSerial]));
    }
    
}
