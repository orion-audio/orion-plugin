/*
  ==============================================================================

    OrionClipConfiguration.cpp
    Created: 21 Jun 2019 1:10:50pm
    Author:  Lei Li

  ==============================================================================
*/

#include "OrionClipConfiguration.h"


//==============================================================================
OrionClipConfiguration::OrionClipConfiguration(OrionaudioAudioProcessor& p) : processor(p)
{
    // Background Image
    Image backgroundImage = ImageCache::getFromMemory(BinaryData::clipBackground_png, BinaryData::clipBackground_pngSize);
    backgroundImageView.reset(new DrawableImage());
    backgroundImageView->setImage(backgroundImage);
    addAndMakeVisible(backgroundImageView.get());
    
    
    
    
    
    //------------------------------------ Clip EFX Knobs ------------------------------------//
    // Saturation
    saturationKnob.reset(new Slider());
    saturationKnob->setSliderStyle(Slider::SliderStyle::Rotary);
    saturationKnob->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    saturationKnob->setRange(0.0f, 1.0f);
    saturationKnob->setValue(0.0f);
    saturationKnob->addListener(this);
    addAndMakeVisible(saturationKnob.get());
      
    saturationLabel.reset(new Label("0.0 %", "0.0 %"));
    saturationLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(saturationLabel.get());
    saturationLabel->setAlpha(0.8);
    
    // Stretch
    stretchKnob.reset(new Slider());
    stretchKnob->setSliderStyle(Slider::SliderStyle::Rotary);
    stretchKnob->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    stretchKnob->setRange(0, 1);
    stretchKnob->setValue(0.5);
    stretchKnob->addListener(this);
    addAndMakeVisible(stretchKnob.get());
      
    stretchLabel.reset(new Label("100.0 %", "100.0 %"));
    stretchLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(stretchLabel.get());
    stretchLabel->setAlpha(0.8);
    
    // Pitch
    pitchKnob.reset(new Slider());
    pitchKnob->setSliderStyle(Slider::SliderStyle::Rotary);
    pitchKnob->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    pitchKnob->setRange(-36, 36);
    pitchKnob->setValue(0);
    pitchKnob->addListener(this);
    addAndMakeVisible(pitchKnob.get());
      
    pitchLabel.reset(new Label("0 tune", "0 tune"));
    pitchLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(pitchLabel.get());
    pitchLabel->setAlpha(0.8);
    
    // Fine Tune
    fineTuneKnob.reset(new Slider());
    fineTuneKnob->setSliderStyle(Slider::SliderStyle::Rotary);
    fineTuneKnob->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    fineTuneKnob->setRange(-1.0, 1.0f);
    fineTuneKnob->setValue(0);
    fineTuneKnob->addListener(this);
    addAndMakeVisible(fineTuneKnob.get());
      
    fineTuneLabel.reset(new Label("0 cent", "0 cent"));
    fineTuneLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(fineTuneLabel.get());
    fineTuneLabel->setAlpha(0.8);
    
    
    // Reverse Label
    reverseLabel.reset(new Label("Reverse", "Reverse"));
    reverseLabel->setJustificationType(juce::Justification::left);
    addAndMakeVisible(reverseLabel.get());
    reverseLabel->setAlpha(0.5);
    
    
    
 
    //------------------------------------ Meters ------------------------------------//
    // Clip Meter
    clipMeter.reset(new ClipMeter());
    addAndMakeVisible(clipMeter.get());

    // Imager Meter
    imagerMeter.reset(new ImagerMeter());
    addAndMakeVisible(imagerMeter.get());
    
    //------------------------------------ Imager ------------------------------------//
    
    
    // Reverse Label
    reverseLabel.reset(new Label("Reverse", "Reverse"));
    reverseLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(reverseLabel.get());
    reverseLabel->setAlpha(0.5);
    
    // Imager Label
    imagerLabel.reset(new Label("Stereo Imager", "Stereo Imager"));
    imagerLabel->setJustificationType(juce::Justification::left);
    addAndMakeVisible(imagerLabel.get());
    imagerLabel->setAlpha(0.5);
    
    // Imager M Label
    imagerMLabel.reset(new Label("M", "M"));
    imagerMLabel->setJustificationType(juce::Justification::left);
    addAndMakeVisible(imagerMLabel.get());
    imagerMLabel->setAlpha(0.5);
    
    
    // Imager S Label
    imagerSLabel.reset(new Label("S", "S"));
    imagerSLabel->setJustificationType(juce::Justification::left);
    addAndMakeVisible(imagerSLabel.get());
    imagerSLabel->setAlpha(0.5);
    
    // Imager Center Label
    //imagerCenterLabel.reset(new Label("0", "0"));
    //imagerCenterLabel->setJustificationType(juce::Justification::left);
    //addAndMakeVisible(imagerCenterLabel.get());
    //imagerCenterLabel->setAlpha(0.5);
    //imagerCenterLabel->setVisible(false);//-!!!!!!!!!!
    
    
    // Imager Slider
    clipImagerSlider.reset(new Slider());
    clipImagerSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    clipImagerSlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    clipImagerSlider->setColour(Slider::trackColourId, juce::Colours::grey);
    clipImagerSlider->setColour(Slider::thumbColourId, juce::Colours::white);
    clipImagerSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    clipImagerSlider->setRange(0, 1);
    clipImagerSlider->setValue(0.5f);
    clipImagerSlider->addListener(this);
    addAndMakeVisible(clipImagerSlider.get());
    
    // clipImagerSharpSlider
    clipImagerSharpSlider.reset(new Slider());
    clipImagerSharpSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    clipImagerSharpSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    clipImagerSharpSlider->setRange(0.0075f, 0.1f);
    clipImagerSharpSlider->setValue(0.0075f);
    clipImagerSharpSlider->addListener(this);
    addAndMakeVisible(clipImagerSharpSlider.get());
    
    // clipImagerRightSlider
    clipImagerRightSlider.reset(new Slider());
    clipImagerRightSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    clipImagerRightSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    clipImagerRightSlider->setRange(0.0075f, 0.1f);
    clipImagerRightSlider->setValue(0.0075f);
    clipImagerRightSlider->addListener(this);
    addAndMakeVisible(clipImagerRightSlider.get());
    
    
    
    //------------------------------------ Switches ------------------------------------//
    // Clip On Off Switch
    clipOnOffSwitch.reset(new ImageButton());
    clipOnOffSwitch->setImages(false, true, true,
                               switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
                               Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
    clipOnOffSwitch->onStateChange = [&]
    {
        clipOnOffSwitchClicked(clipOnOffSwitch->isDown());
    };
    addAndMakeVisible(clipOnOffSwitch.get());
    
    // Imager On Off Switch
    imagerOnOffSwitch.reset(new ImageButton());
    imagerOnOffSwitch->setImages(false, true, true,
                                 switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
                                 Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
    imagerOnOffSwitch->onStateChange = [&]
    {
        imagerOnOffSwitchClicked(imagerOnOffSwitch->isDown());
    };
    addAndMakeVisible(imagerOnOffSwitch.get());
    
    // Reverse Switch
    reverseSwitch.reset(new ImageButton());
    reverseSwitch->setImages(false, true, true,
                          reverseSwitchOff, 1.f, Colours::transparentBlack, reverseSwitchOff, 1.f,
                          Colours::transparentBlack, reverseSwitchOff, 1.f, Colours::transparentBlack);
    reverseSwitch->onStateChange = [&]
    {
        reverseSwitchClicked(reverseSwitch->isDown());
    };
    addAndMakeVisible(reverseSwitch.get());
    
    // Imager Mode Switch
    imagerModeSwitch.reset(new ImageButton());
    imagerModeSwitch->setImages(false, true, true,
                          modeSwitchOff, 1.f, Colours::transparentBlack, modeSwitchOff, 1.f,
                          Colours::transparentBlack, modeSwitchOff, 1.f, Colours::transparentBlack);
    imagerModeSwitch->onStateChange = [&]
    {
        imagerSwitchClicked(imagerModeSwitch->isDown());
    };
    addAndMakeVisible(imagerModeSwitch.get());
    
    
    
    // SEPoint Slider
    SEPointSlider.reset(new DoubleThumbSlider(clipMeter.get()));
    addAndMakeVisible(SEPointSlider.get());
    
}

void OrionClipConfiguration::paint (Graphics& g)
{
    //std::cout<<"paint Clip : "<<instrumetClickedSerial<<std::endl;
}

void OrionClipConfiguration::resized()
{
    Rectangle<int> area(0, 0, getWidth(), getHeight());
    backgroundImageView->setTransformToFit(area.toFloat(), RectanglePlacement::stretchToFit);
    
    float knobY1 = getWidth()/30;
    float knobY2 = getWidth()/8.25;
    float knobSize = getWidth()/25;
    
    float TextY1 =  getWidth()/13.25;
    float TextY2 =  getWidth()/6.00;
    float TextHeight =  getWidth()/60;
    
    float onOffSwitchSize = getWidth() * 0.0181;
    float switchSize = getWidth()/69;
    float reverseSwitchSize = getWidth()/77;
    
    // Clip On/Off Switch
    area = Rectangle<int>(getWidth() * 0.1970, getHeight() * 0.020, onOffSwitchSize, onOffSwitchSize);
    clipOnOffSwitch->setBounds(area);

    // Imager On/Off Switch
    area = Rectangle<int>(getWidth() * 0.889, getHeight() * 0.640, onOffSwitchSize, onOffSwitchSize);
    imagerOnOffSwitch->setBounds(area);
    
    // Reverse Switch
    area = Rectangle<int>(getWidth() * 0.720, getHeight() * 0.740,  reverseSwitchSize, switchSize);
    reverseSwitch->setBounds(area);
    
    // Imager Mode Switch
    area = Rectangle<int>(getWidth() * 0.8925, getHeight() * 0.845,  switchSize, switchSize);
    imagerModeSwitch->setBounds(area);
    
    //------------------------------------ ADSR Knobs ------------------------------------//
    // Attack
    area = Rectangle<int>(getWidth()/29, knobY1,  knobSize, knobSize);
    saturationKnob->setBounds(area);

    area = Rectangle<int>(getWidth()/29 - knobSize/2, TextY1,  2 * knobSize, TextHeight);
    saturationLabel->setBounds(area);
  
    // Decay
    area = Rectangle<int>(getWidth()/7, knobY1,  knobSize, knobSize);
    stretchKnob->setBounds(area);

    area = Rectangle<int>(getWidth()/7 - knobSize/2, TextY1,  2 * knobSize, TextHeight);
    stretchLabel->setBounds(area);
   
    // Hold
    area = Rectangle<int>(getWidth()/29, knobY2,  knobSize, knobSize);
    pitchKnob->setBounds(area);

    area = Rectangle<int>(getWidth()/29 - knobSize/2, TextY2,  2 * knobSize, TextHeight);
    pitchLabel->setBounds(area);
    
    // Release
    area = Rectangle<int>(getWidth()/7, knobY2,  knobSize, knobSize);
    fineTuneKnob->setBounds(area);

    area = Rectangle<int>(getWidth()/7 - knobSize/2, TextY2,  2 * knobSize, TextHeight);
    fineTuneLabel->setBounds(area);
    
    
    //------------------------------------ Meters ------------------------------------//
    // Clip Meter
    area = Rectangle<int>(getWidth() * 0.2175, 0,  getWidth() * 0.580, getHeight() * 0.625);
    clipMeter->setBounds(area);
    
    
    // Imager Meter
    area = Rectangle<int>(getWidth() * 0.7975, 0,  getWidth() * 0.2025, getHeight() * 0.6225);
    imagerMeter->setBounds(area);
    
    
    // SEPoint Slider
    area = Rectangle<int>(getWidth() * 0.2129, getHeight() * 0.598,  getWidth() * 0.588, getHeight() * 0.0500);
    SEPointSlider->setBounds(area);
    
    //------------------------------------ Imager ------------------------------------//
    // Imager Slider
    float sliderHeight = getWidth() * 0.02;
    float sliderWidth = getWidth() * 0.1245;
    
    area = Rectangle<int>(getWidth() * 0.8365, getHeight() * 0.715,  sliderWidth, sliderHeight);
    clipImagerSlider->setBounds(area);
    
    // Imager Sharp Slider
    area = Rectangle<int>(getWidth() * 0.8000, getHeight() * 0.680,  knobSize, knobSize);
    clipImagerSharpSlider->setBounds(area);
    
    // Imager Right Slider
    area = Rectangle<int>(getWidth() * 0.9570, getHeight() * 0.680,  knobSize, knobSize);
    clipImagerRightSlider->setBounds(area);
    

    // Imager Labels
    float labelHeight = getWidth() * 0.0215;
    float labelWidth = getWidth() * 0.08;
    
    float RX = getWidth() * 0.715;
    float RY = getHeight() * 0.7125;
    
    float MX = getWidth() * 0.832;
    float SX = getWidth() * 0.949;
    float MSY = getHeight() * 0.615;
    
    float imagerLableX = getWidth() * 0.862;
    float imagerLabelY = getHeight() * 0.765;
    
    area = Rectangle<int>(RX, RY,  labelWidth, labelHeight * 1.05);
    reverseLabel->setBounds(area);
    
    area = Rectangle<int>(imagerLableX, imagerLabelY,  labelWidth, labelHeight * 1.05);
    imagerLabel->setBounds(area);
    
    area = Rectangle<int>(MX, MSY,  labelWidth, labelHeight);
    imagerMLabel->setBounds(area);
    
    area = Rectangle<int>(SX, MSY,  labelWidth, labelHeight);
    imagerSLabel->setBounds(area);
    
    //area = Rectangle<int>(MX + ((SX - MX)/2), MSY,  labelWidth, labelHeight);
    //imagerCenterLabel->setBounds(area);
    
}


//MARK:- Clip On/Off Switch
// Set Imager On/Off Switch  Image
void OrionClipConfiguration::setClipOnOffSwitchImage(bool On)
{
    if(On)
    {
        clipOnOffSwitch->setImages(false, true, true,
                                   switchOn, 1.f, Colours::transparentBlack, switchOn, 1.f,
                                   Colours::transparentBlack, switchOn, 1.f, Colours::transparentBlack);
    }
    else
    {
        clipOnOffSwitch->setImages(false, true, true,
                                   switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
                                   Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
    }
}

// Imager On/Off Switch Clicked
void OrionClipConfiguration::clipOnOffSwitchClicked(bool isDown)
{
    if(isDown)
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            //voice->envswitch = !voice->envswitch;
            clipOnOffSwitches[instrumetClickedSerial] = !clipOnOffSwitches[instrumetClickedSerial];
            voice->clipOnOffSwitch = clipOnOffSwitches[instrumetClickedSerial];
            std::cout<<"instrumetClickedSerial: "<<instrumetClickedSerial<<std::endl;
            std::cout<<"voice->clipOnOffSwitch: "<<voice->clipOnOffSwitch<<std::endl;
            
            setClipOnOffSwitchImage(voice->clipOnOffSwitch);
        }
    }
}



//MARK:- Imager On/Off Switch
// Set Imager On/Off Switch  Image
void OrionClipConfiguration::setImagerOnOffSwitchImage(bool On)
{
    if(On)
    {
        imagerOnOffSwitch->setImages(false, true, true,
                                     switchOn, 1.f, Colours::transparentBlack, switchOn, 1.f,
                                     Colours::transparentBlack, switchOn, 1.f, Colours::transparentBlack);
    }
    else
    {
        imagerOnOffSwitch->setImages(false, true, true,
                                     switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
                                     Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
    }
}

// Imager On/Off Switch Clicked
void OrionClipConfiguration::imagerOnOffSwitchClicked(bool isDown)
{
    if(isDown)
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            imagerOnOffSwitches[instrumetClickedSerial] = !imagerOnOffSwitches[instrumetClickedSerial];
            voice->imagerOnOffSwitch = imagerOnOffSwitches[instrumetClickedSerial];
            setImagerOnOffSwitchImage(voice->imagerOnOffSwitch);
        }
    }
}







//MARK:- Reverse Switch
// Set Reverse Switch Image
void OrionClipConfiguration::setReverseSwitchImage(bool On)
{
    if(On)
    {
        reverseSwitch->setImages(false, true, true,
        reverseSwitchOn, 1.f, Colours::transparentBlack, reverseSwitchOn, 1.f,
        Colours::transparentBlack, reverseSwitchOn, 1.f, Colours::transparentBlack);
    }
    else
    {
        reverseSwitch->setImages(false, true, true,
        reverseSwitchOff, 1.f, Colours::transparentBlack, reverseSwitchOff, 1.f,
        Colours::transparentBlack, reverseSwitchOff, 1.f, Colours::transparentBlack);
    }
}

// Reverse Switch Clicked
void OrionClipConfiguration::reverseSwitchClicked(bool isDown)
{
    if(isDown)
    {
        instrumentSampleContainer[instrumetClickedSerial].reverse(0, instrumentSampleContainer[instrumetClickedSerial].getNumSamples());
        reverseSwitches[instrumetClickedSerial] = !reverseSwitches[instrumetClickedSerial];
        setReverseSwitchImage(reverseSwitches[instrumetClickedSerial]);
        clipMeter->setReverseMode(reverseSwitches[instrumetClickedSerial]);
        
        SEPointSlider->audioRangeChange();
    }
}


//MARK:- Switch Image Changer
void OrionClipConfiguration::setimagerSwitchImage(bool On)
{
    if(On)
    {
        imagerModeSwitch->setImages(false, true, true,
        modeSwitchOn, 1.f, Colours::transparentBlack, modeSwitchOn, 1.f,
        Colours::transparentBlack, modeSwitchOn, 1.f, Colours::transparentBlack);
    }
    else
    {
        imagerModeSwitch->setImages(false, true, true,
        modeSwitchOff, 1.f, Colours::transparentBlack, modeSwitchOff, 1.f,
        Colours::transparentBlack, modeSwitchOff, 1.f, Colours::transparentBlack);
    }
}

//MARK:- Switch Clicker
void OrionClipConfiguration::imagerSwitchClicked(bool isDown)
{
    if(isDown)
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            //voice->envswitch = !voice->envswitch;
            imagerModeSwitches[instrumetClickedSerial] = !imagerModeSwitches[instrumetClickedSerial];
            voice->clipImagerMode = imagerModeSwitches[instrumetClickedSerial];
            setimagerSwitchImage(voice->clipImagerMode);
            imagerMeter->setImagerMode(voice->clipImagerMode);
        }
    }
}


void OrionClipConfiguration::sliderValueChanged (Slider* slider)
{
    
    //------------------------------------ Clip EFX ------------------------------------//
    if(slider == saturationKnob.get())// Saturation Knob
    {
        
        clipSaturationCoefficient[instrumetClickedSerial] = saturationKnob->getValue();
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*>(processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->setSaturationVal(clipSaturationCoefficient[instrumetClickedSerial]);
        }
        
        String value = String(int(clipSaturationCoefficient[instrumetClickedSerial]* 100) );
        value.append(" %",5);
        saturationLabel->setText(value,dontSendNotification);

    }
    else if(slider == stretchKnob.get())// Stretch Knob
    {
        
    }
    else if(slider == pitchKnob.get())// Pitch Knob
    {
        clipPitchCoefficient[instrumetClickedSerial] = pitchKnob->getValue();
        if(auto* voice = dynamic_cast<OrionSamplerVoice*>(processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->setPitchVal(clipPitchCoefficient[instrumetClickedSerial]);
        }
        
        String value = String(int(clipPitchCoefficient[instrumetClickedSerial]));
        value.append(" tune",5);
        pitchLabel->setText(value,dontSendNotification);
    }
    else if(slider == fineTuneKnob.get())// FineTune Knob
    {
        clipFineTuneCoefficient[instrumetClickedSerial] = fineTuneKnob->getValue();
        if(auto* voice = dynamic_cast<OrionSamplerVoice*>(processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->setPitchCent(clipFineTuneCoefficient[instrumetClickedSerial]);
        }
        
        double tmp = jmap<double>(clipFineTuneCoefficient[instrumetClickedSerial], -1.0f, 1.0f, -12.0f, 12.0f);
        
        String value = String(int(tmp));
        value.append(" cent",5);
        fineTuneLabel->setText(value,dontSendNotification);
    }
    
    
    
    //------------------------------------ Imager ------------------------------------//
    if(slider == clipImagerSlider.get())// Imager Slider
    {
        imagerCoefficient[instrumetClickedSerial] = clipImagerSlider->getValue();
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*>(processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->ImagerCoefChange(imagerCoefficient[instrumetClickedSerial]);
        }
         
        imagerMeter->setImagerCoef(imagerCoefficient[instrumetClickedSerial] );
    }
    else if(slider == clipImagerSharpSlider.get())// Imager Speed Slider
    {
        imagerSharpCoefficient[instrumetClickedSerial] = clipImagerSharpSlider->getValue();
        if(auto* voice = dynamic_cast<OrionSamplerVoice*>(processor.getSampler()->getVoice(instrumetClickedSerial)))
        {
            voice->imagerSharp = imagerSharpCoefficient[instrumetClickedSerial];
        }
        
        imagerMeter->updateImager();
        
    }
    
}



OrionClipConfiguration::~OrionClipConfiguration()
{
    
}
