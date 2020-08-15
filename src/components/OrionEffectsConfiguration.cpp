/*
  ==============================================================================

    OrionEffectsConfiguration.cpp
    Created: 11 Jun 2019 4:00:32pm
    Author:  Lei Li

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "OrionEffectsConfiguration.h"
#include "OrionGlobalVars.h"
#include "GlobalCoefficients.h"
#include "ThresholdMeter.h"

OrionEffectsConfiguration::OrionEffectsConfiguration(OrionaudioAudioProcessor& p, int serial) : processor(p)
{
    effectSerial = serial;
    //---------------------------------------------
       //addAndMakeVisible(&compGui);
       //addAndMakeVisible(&reverbGui);
       //addAndMakeVisible(&delayGui);
    //--------------------------------------------
    
    //------------------------------------ Background ------------------------------------//
    
    // Background Image
    Image backgroundImage = ImageCache::getFromMemory(BinaryData::FXBackground_png, BinaryData::FXBackground_pngSize);
    backgroundImageView.reset(new DrawableImage());
    backgroundImageView->setImage(backgroundImage);
    addAndMakeVisible(backgroundImageView.get());
        
   
    
    //------------------------------------ Switches ------------------------------------//
    
    // Comp Switch
    compSwitch.reset(new ImageButton());
    compSwitch->setImages(false, true, true,
                          switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
                          Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
    compSwitch->onStateChange = [&]
    {
        switchSerial = 0;
        switchClicked(compSwitch->isDown());
    };
    addAndMakeVisible(compSwitch.get());
       

    // Reverb Switch
    reverbSwitch.reset(new ImageButton());
    reverbSwitch->setImages(false, true, true,
                          switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
                          Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
    reverbSwitch->onStateChange = [&]
    {
        switchSerial = 1;
        switchClicked(reverbSwitch->isDown());
    };
    addAndMakeVisible(reverbSwitch.get());
    
    // Delay Switch
    delaySwitch.reset(new ImageButton());
    delaySwitch->setImages(false, true, true,
                          switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
                          Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
    delaySwitch->onStateChange = [&]
    {
        switchSerial = 2;
        switchClicked(delaySwitch->isDown());
    };
    addAndMakeVisible(delaySwitch.get());
    
    //------------------------------------ Compressor ------------------------------------//
      
    // Compressor Meter
    compressorMeter.reset(new CompressorMeter());
    addAndMakeVisible(compressorMeter.get());
    
    // Compressor-Threshold Meters
    thresholdMeters.reset(new ThresholdMeter());
    thresholdMeters->updaterFunction = [this] { return processor.getOutputLevel(0);};// + processor.getOutputLevel(1))/2
    addAndMakeVisible(thresholdMeters.get());
    
    // Compressor-Threshold-Slider
    compThreshSlider.reset(new Slider());
    compThreshSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    compThreshSlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    compThreshSlider->setColour(Slider::trackColourId, juce::Colours::grey);
    compThreshSlider->setColour(Slider::thumbColourId, juce::Colours::white);
    compThreshSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    compThreshSlider->setRange(-60.0f, 0.0f);
    compThreshSlider->setValue(-30.5f);
    compThreshSlider->addListener(this);
    addAndMakeVisible(compThreshSlider.get());
      
    // Compressor-Ratio-Knob
    compRatioSlider.reset(new Slider());
    compRatioSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    compRatioSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    compRatioSlider->setRange(1.0f, 100.0f);
    compRatioSlider->setValue(1.0f);
    compRatioSlider->addListener(this);
    addAndMakeVisible(compRatioSlider.get());
      
    compRatioLabel.reset(new Label("1.00 : 1", "1.00 : 1"));
    compRatioLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(compRatioLabel.get());
    compRatioLabel->setAlpha(0.8);
      
    // Compressor-Attack-Knob
    compAttackSlider.reset(new Slider());
    compAttackSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    compAttackSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    compAttackSlider->setRange(0.1f, 80.0f);
    compAttackSlider->setValue(0.1f);
    compAttackSlider->addListener(this);
    addAndMakeVisible(compAttackSlider.get());
      
    compAttackLabel.reset(new Label("0.50 ms", "0.50 ms"));
    compAttackLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(compAttackLabel.get());
    compAttackLabel->setAlpha(0.8);

    // Compressor-Release-Knob
    compReleaseSlider.reset(new Slider());
    compReleaseSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    compReleaseSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    compReleaseSlider->setRange(0.1f, 1000.0f);
    compReleaseSlider->setValue(0.1f);
    compReleaseSlider->addListener(this);
    addAndMakeVisible(compReleaseSlider.get());
      
    compReleaseLabel.reset(new Label("0.50 ms", "0.50 ms"));
    compReleaseLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(compReleaseLabel.get());
    compReleaseLabel->setAlpha(0.8);
    
    // Compressor-Gain-Knob
    compGainSlider.reset(new Slider());
    compGainSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    compGainSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    compGainSlider->setRange(0.0f, 20.0f/* init 40 */);
    compGainSlider->setValue(0.0f);
    compGainSlider->addListener(this);
    addAndMakeVisible(compGainSlider.get());
      
    compGainLabel.reset(new Label("0.00 db", "0.00 db"));
    compGainLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(compGainLabel.get());
    compGainLabel->setAlpha(0.8);
    
    
    //------------------------------------ Reverb ------------------------------------//
    
    // Reverb-DryWet
    reverbDrySlider.reset(new Slider());
    reverbDrySlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    reverbDrySlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    reverbDrySlider->setColour(Slider::trackColourId, juce::Colours::grey);
    reverbDrySlider->setColour(Slider::thumbColourId, juce::Colours::white);
    reverbDrySlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    reverbDrySlider->setRange(0.0f, 1.0f);
    reverbDrySlider->setValue(0.3f);
    reverbDrySlider->addListener(this);
    addAndMakeVisible(reverbDrySlider.get());
    
    // Reverb-PreDelay
    reverbPredelaySlider.reset(new Slider());
    reverbPredelaySlider->setSliderStyle(Slider::SliderStyle::Rotary);
    reverbPredelaySlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    reverbPredelaySlider->setRange(0.0f, 1.0f);
    reverbPredelaySlider->setValue(1.0f);
    reverbPredelaySlider->addListener(this);
    addAndMakeVisible(reverbPredelaySlider.get());
    
    reverbPredelayLabel.reset(new Label("1.00 ms", "1.00 ms"));
    reverbPredelayLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(reverbPredelayLabel.get());
    reverbPredelayLabel->setAlpha(0.8);
    
    // Reverb-Decay
    reverbDecaySlider.reset(new Slider());
    reverbDecaySlider->setSliderStyle(Slider::SliderStyle::Rotary);
    reverbDecaySlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    reverbDecaySlider->setRange(0.0f, 1.0f);
    reverbDecaySlider->setValue(0.5f);
    reverbDecaySlider->addListener(this);
    addAndMakeVisible(reverbDecaySlider.get());
    
    reverbDecayLabel.reset(new Label("0.50 ms", "0.50 ms"));
    reverbDecayLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(reverbDecayLabel.get());
    reverbDecayLabel->setAlpha(0.8);

    // Reverb-Size
    reverbSizeSlider.reset(new Slider());
    reverbSizeSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    reverbSizeSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    reverbSizeSlider->setRange(0.0f, 1.0f);
    reverbSizeSlider->setValue(0.5f);
    reverbSizeSlider->addListener(this);
    addAndMakeVisible(reverbSizeSlider.get());
    
    reverbSizeLabel.reset(new Label("0.50 ms", "0.50 ms"));
    reverbSizeLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(reverbSizeLabel.get());
    reverbSizeLabel->setAlpha(0.8);
  
    // Reverb-Color
    reverbColorSlider.reset(new Slider());
    reverbColorSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    reverbColorSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    reverbColorSlider->setRange(-1.0f, 1.0f);
    reverbColorSlider->setValue(0.0f);
    reverbColorSlider->addListener(this);
    addAndMakeVisible(reverbColorSlider.get());
    
    reverbColorLabel.reset(new Label("0.00 cl", "0.00 cl"));
    reverbColorLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(reverbColorLabel.get());
    reverbColorLabel->setAlpha(0.8);

    //------------------------------------ Delay ------------------------------------//
      
    // Delay-DryWet
    delayDryWetSlider.reset(new Slider());
    delayDryWetSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    delayDryWetSlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    delayDryWetSlider->setColour(Slider::trackColourId, juce::Colours::grey);
    delayDryWetSlider->setColour(Slider::thumbColourId, juce::Colours::white);
    delayDryWetSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    delayDryWetSlider->setRange(0.0f, 1.0f);
    delayDryWetSlider->setValue(0.4f);
    delayDryWetSlider->addListener(this);
    addAndMakeVisible(delayDryWetSlider.get());
      
    // Delay-Time
    delayTimeSlider.reset(new Slider());
    delayTimeSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    delayTimeSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    delayTimeSlider->setRange(0.0f, 0.9f);
    delayTimeSlider->setValue(0.01f);
    delayTimeSlider->addListener(this);
    addAndMakeVisible(delayTimeSlider.get());
      
    delayTimeLabel.reset(new Label("0.10 ms", "0.10 ms"));
    delayTimeLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(delayTimeLabel.get());
    delayTimeLabel->setAlpha(0.8);
      
    // Delay-Feedback
    delayFeedbackSlider.reset(new Slider());
    delayFeedbackSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    delayFeedbackSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    delayFeedbackSlider->setRange(0.0f, 0.95f);
    delayFeedbackSlider->setValue(0.0f);
    delayFeedbackSlider->addListener(this);
    addAndMakeVisible(delayFeedbackSlider.get());
      
    delayFeedbackLabel.reset(new Label("0.00 ms", "0.00 ms"));
    delayFeedbackLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(delayFeedbackLabel.get());
    delayFeedbackLabel->setAlpha(0.8);

    // Delay-Color
    delayColorSlider.reset(new Slider());
    delayColorSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    delayColorSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    delayColorSlider->setRange(-1.0f, 1.0f);
    delayColorSlider->setValue(0.0f);
    delayColorSlider->addListener(this);
    addAndMakeVisible(delayColorSlider.get());
      
    delayColorLabel.reset(new Label("0.00 cl", "0.00 cl"));
    delayColorLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(delayColorLabel.get());
    delayColorLabel->setAlpha(0.8);
    
    // Delay-Pan
    delayPanSlider.reset(new Slider());
    delayPanSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    delayPanSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    delayPanSlider->setRange(0.0f, 1.0f);
    delayPanSlider->setValue(0.5f);
    delayPanSlider->addListener(this);
    addAndMakeVisible(delayPanSlider.get());
      
    delayPanLabel.reset(new Label("C", "C"));
    delayPanLabel->setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(delayPanLabel.get());
    delayPanLabel->setAlpha(0.8);
    
}

void OrionEffectsConfiguration::paint(Graphics& g)
{
    //g.fillAll();
    //g.fillAll(Colours::darkgoldenrod);
    std::cout<<"paint FX : "<<instrumetSerial<<std::endl;
}

//MARK:- Resize
void OrionEffectsConfiguration::resized()
{
    
    
    
    /*
    //---------- Previous ---------------//
    Rectangle<int> area = getLocalBounds();
    area = area.removeFromLeft(getWidth() / 3);
    compGui.setBounds(area);
    
    area.translate(getWidth() / 3, 0);
    reverbGui.setBounds(area);
    
    area.translate(getWidth() / 2.5, 0);
    delayGui.setBounds(area);
    */
    
    
    float uniteW = getWidth()/100;
    
    float textHeight = getWidth()/65;
    
    float boxHeight = getHeight()/5.945;
    
    float sliderY = getHeight()/2.775;
    
    float sliderHeight = getWidth()/50;
    
    float knobY = getHeight()/1.675;
    
    float knobSize = getWidth()/25;
    
    float knobVarTextHeight =  getHeight()/1.225;
    
    Rectangle<int> area = getLocalBounds();
    //--------------------------------- Background Image --------------------------------//
    area = Rectangle<int>(0, 0, getWidth(), getHeight());
    backgroundImageView->setTransformToFit(area.toFloat(), RectanglePlacement::stretchToFit);
    
    
    
    
    //------------------------------------ Switches ------------------------------------//
    
    // Compressor Switch
    area = Rectangle<int>(getWidth()/2 - 9.75 * uniteW, 0.75 * uniteW,  2 * uniteW, 2 * uniteW);
    compSwitch->setBounds(area);
    
    // Reverb Switch
    area = Rectangle<int>(getWidth()*2/3 + 2.5 * uniteW, 0.75 * uniteW,  2 * uniteW, 2 * uniteW);
    reverbSwitch->setBounds(area);
    
    // Delay Switch
    area = Rectangle<int>(getWidth() - 3.5 * uniteW, 0.75 * uniteW, 2 * uniteW, 2 * uniteW);
    delaySwitch->setBounds(area);
    
    
    //------------------------------------ Compressor ------------------------------------//
    
    // Compressor-Meter
    area = Rectangle<int>(getWidth() * 0.035, getHeight() * 0.3275,  getWidth() * 0.111, getHeight() * 0.511);
    compressorMeter->setBounds(area);
    
    
    // Threshold-Meters-Compressor
    area = Rectangle<int>(getWidth()/5.59, boxHeight,  getWidth()/4.15, getHeight()/8.5);
    thresholdMeters->setBounds(area);
    
    
    // Threshold-Slider-Compressor
    area = Rectangle<int>(getWidth()/5.3, sliderY,  24 * uniteW, sliderHeight);
    compThreshSlider->setBounds(area);
    
    
    // Ratio-Knob-Compressor
    area = Rectangle<int>(getWidth()/5.65, knobY,  knobSize, knobSize);
    compRatioSlider->setBounds(area);

    area = Rectangle<int>(getWidth()/5.65 - knobSize * 0.125, knobVarTextHeight,  knobSize * 1.25, textHeight);
    compRatioLabel->setBounds(area);
    
    
    // Attack-Knob-Compressor
    area = Rectangle<int>(getWidth()/4.125, knobY,  knobSize, knobSize);
    compAttackSlider->setBounds(area);
    
    area = Rectangle<int>(getWidth()/4.125 - knobSize * 0.125, knobVarTextHeight,  knobSize * 1.25, textHeight);
    compAttackLabel->setBounds(area);

    
    // Release-Knob-Compressor
    area = Rectangle<int>(getWidth()/3.25, knobY,  knobSize, knobSize);
    compReleaseSlider->setBounds(area);
    
    area = Rectangle<int>(getWidth()/3.25 - knobSize * 0.125, knobVarTextHeight,  knobSize * 1.25, textHeight);
    compReleaseLabel->setBounds(area);

    
    // Gain-Knob-Compressor
    area = Rectangle<int>(getWidth()/2.675, knobY,  knobSize, knobSize);
    compGainSlider->setBounds(area);
    
    area = Rectangle<int>(getWidth()/2.675 - knobSize * 0.125, knobVarTextHeight,  knobSize * 1.25, textHeight);
    compGainLabel->setBounds(area);
    

    //------------------------------------ Reverb ------------------------------------//
    
    // DryWet-Slider-Reverb
    area = Rectangle<int>(getWidth()/2.125, sliderY,  24 * uniteW, sliderHeight);
    reverbDrySlider->setBounds(area);
    
    

    // PreDelay-Knob-Reverb
    area = Rectangle<int>(getWidth()/2.15, knobY,  knobSize, knobSize);
    reverbPredelaySlider->setBounds(area);

    area = Rectangle<int>(getWidth()/2.15 - knobSize * 0.125, knobVarTextHeight,  knobSize * 1.25, textHeight);
    reverbPredelayLabel->setBounds(area);
    
    
    // Decay-Knob-Reverb
    area = Rectangle<int>(getWidth()/1.88, knobY,  knobSize, knobSize);
    reverbDecaySlider->setBounds(area);
    
    area = Rectangle<int>(getWidth()/1.88 - knobSize * 0.125, knobVarTextHeight,  knobSize * 1.25, textHeight);
    reverbDecayLabel->setBounds(area);

    
    // Size-Knob-Reverb
    area = Rectangle<int>(getWidth()/1.67, knobY, knobSize, knobSize);
    reverbSizeSlider->setBounds(area);
    
    area = Rectangle<int>(getWidth()/1.67 - knobSize * 0.125, knobVarTextHeight,  knobSize * 1.25, textHeight);
    reverbSizeLabel->setBounds(area);

    
    // Color-Knob-Reverb
    area = Rectangle<int>(getWidth()/1.515, knobY,  knobSize, knobSize);
    reverbColorSlider->setBounds(area);
    
    area = Rectangle<int>(getWidth()/1.515 - knobSize * 0, knobVarTextHeight,  knobSize * 1.25, textHeight);
    reverbColorLabel->setBounds(area);
    
    
    //------------------------------------ Delay ------------------------------------//
    
    // DryWet-Slider-Delay
    area = Rectangle<int>(getWidth()/1.335, sliderY,  24 * uniteW, sliderHeight);
    delayDryWetSlider->setBounds(area);
    
    
    
    // Time-Knob-Delay
    area = Rectangle<int>(getWidth()/1.338, knobY,  knobSize, knobSize);
    delayTimeSlider->setBounds(area);

    area = Rectangle<int>(getWidth()/1.338 - knobSize * 0.125, knobVarTextHeight,  knobSize * 1.25, textHeight);
    delayTimeLabel->setBounds(area);
    
    // Feedback-Knob-Delay
    area = Rectangle<int>(getWidth()/1.235, knobY,  knobSize, knobSize);
    delayFeedbackSlider->setBounds(area);
    
    area = Rectangle<int>(getWidth()/1.235 - knobSize * 0.125, knobVarTextHeight,  knobSize * 1.25, textHeight);
    delayFeedbackLabel->setBounds(area);

    // Color-Knob-Delay
    area = Rectangle<int>(getWidth()/1.1458, knobY,  knobSize, knobSize);
    delayColorSlider->setBounds(area);
    
    area = Rectangle<int>(getWidth()/1.1458 - knobSize * 0.125, knobVarTextHeight,  knobSize * 1.25, textHeight);
    delayColorLabel->setBounds(area);

    // Pan-Knob-Delay
    area = Rectangle<int>(getWidth()/1.0618, knobY,  knobSize, knobSize);
    delayPanSlider->setBounds(area);
    
    area = Rectangle<int>(getWidth()/1.0618 - knobSize * 0.125, knobVarTextHeight,  knobSize * 1.25, textHeight);
    delayPanLabel->setBounds(area);

    
}

//MARK:- Switch Clicker
void OrionEffectsConfiguration::switchClicked(bool isDown)
{
    if(isDown)
    {
        if(switchSerial == 0)/* Compressor Switch */
        {
            
            if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
            {
                voice->compressorswitch = !voice->compressorswitch;
                
                compSwitches[instrumetSerial] = !compSwitches[instrumetSerial];
                setSwitchImage(voice->compressorswitch,switchSerial);
            }
            
        }
        else if(switchSerial == 1)/* Reverb Switch */
        {
            
            if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
            {
                voice->reverbswitch = !voice->reverbswitch;
                
                reverbSwitches[instrumetSerial] = !reverbSwitches[instrumetSerial];
                setSwitchImage(reverbSwitches[instrumetSerial],switchSerial);
            }
            
        }
        else if(switchSerial == 2)/* Delay Switch */
        {
            
            if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
            {
                voice->delayswitch = !voice->delayswitch;
                
                delaySwitches[instrumetSerial] = !delaySwitches[instrumetSerial];
                setSwitchImage(delaySwitches[instrumetSerial],switchSerial);
            }
            
        }
    }
}


//MARK:- Switch Image Changer
void OrionEffectsConfiguration::setSwitchImage(bool On, int Serial)
{
    if(Serial == 0)/* Compressor Switch */
    {
        if(On)
        {
            compSwitch->setImages(false, true, true,
            switchOn, 1.f, Colours::transparentBlack, switchOn, 1.f,
            Colours::transparentBlack, switchOn, 1.f, Colours::transparentBlack);
        }
        else
        {
            compSwitch->setImages(false, true, true,
            switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
            Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
        }

    }
    else if(Serial == 1)/* Reverb Switch */
    {
        if(On)
        {
            reverbSwitch->setImages(false, true, true,
            switchOn, 1.f, Colours::transparentBlack, switchOn, 1.f,
            Colours::transparentBlack, switchOn, 1.f, Colours::transparentBlack);
        }
        else
        {
            reverbSwitch->setImages(false, true, true,
            switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
            Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
        }
    }
    else if(Serial == 2)/* Delay Switch */
    {
        if(On)
        {
            delaySwitch->setImages(false, true, true,
            switchOn, 1.f, Colours::transparentBlack, switchOn, 1.f,
            Colours::transparentBlack, switchOn, 1.f, Colours::transparentBlack);
        }
        else
        {
            delaySwitch->setImages(false, true, true,
            switchOff, 1.f, Colours::transparentBlack, switchOff, 1.f,
            Colours::transparentBlack, switchOff, 1.f, Colours::transparentBlack);
        }
    }
}


String valueDoubleDigitTranslator(double inputValue)
{
    double a = inputValue;
    float b = (int)(a * 100 + .5);
    float c =  (float)b / 100;
    String d = String(c);
    if(d == "0")
    {
        d = "0.00";
    }
    else if(d == "1")
    {
        d = "1.00";
    }
    
    return d;
}




void OrionEffectsConfiguration::sliderValueChanged (Slider* slider)
{
    //------------------------------------ Compressor ------------------------------------//
    if(slider == compThreshSlider.get())// Compressor Threshold
    {
         compressorThreshCoefficient[instrumetSerial] = compThreshSlider->getValue();
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->compressor.threshold_  = compressorThreshCoefficient[instrumetSerial];
            voice->compressor.update();
        }
        
        float meterCoef = jmap<float>(compressorThreshCoefficient[instrumetSerial], -60.0f, 0.0f, 1.0f,0.0f);
        
        compressorMeter->setThreshCoef(meterCoef);
        
       
        thresholdMeters->pointerMove((compressorThreshCoefficient[instrumetSerial] + 60.0f)/60.0f);//--Change Later!!!
    }
    else if(slider == compRatioSlider.get())// Compressor Ratio
    {
        compressorRatioCoefficient[instrumetSerial] = compRatioSlider->getValue();
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->compressor.ratio_  = compressorRatioCoefficient[instrumetSerial];
            voice->compressor.update();
        }
        
        float meterCoef = jmap<float>(compressorRatioCoefficient[instrumetSerial], 1, 100, 1.0f, 0.0f);
        
        compressorMeter->setRatioCoef(meterCoef);
        
        String value = valueDoubleDigitTranslator(compressorRatioCoefficient[instrumetSerial]);
        value.append(" : 1",4);
        compRatioLabel->setText(value,dontSendNotification);
    }
    else if(slider == compAttackSlider.get())// Compressor Attack
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->compressor.tauAttack_  = compAttackSlider->getValue();
            voice->compressor.update();
        }
        
        compressorAttackCoefficient[instrumetSerial] = compAttackSlider->getValue();
        String value = valueDoubleDigitTranslator(compressorAttackCoefficient[instrumetSerial]);
        value.append(" ms",3);// not accurate need to be change later
        compAttackLabel->setText(value,dontSendNotification);
        
    }
    else if(slider == compReleaseSlider.get())// Compressor Release
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->compressor.tauRelease_  = compReleaseSlider->getValue();
        }

        compressorReleaseCoefficient[instrumetSerial] = compReleaseSlider->getValue();
        String value = valueDoubleDigitTranslator(compressorReleaseCoefficient[instrumetSerial]);
        value.append(" ms",3);// not accurate need to be change later
        compReleaseLabel->setText(value,dontSendNotification);
    }
    else if(slider == compGainSlider.get())// Compressor Gain
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->compressor.makeUpGain_  = compGainSlider->getValue();
            voice->compressor.update();
        }
        
        compressorGainCoefficient[instrumetSerial] = compGainSlider->getValue();
        String value = valueDoubleDigitTranslator(compressorGainCoefficient[instrumetSerial]);
        value.append(" db",3); // not accurate need to be change later
        compGainLabel->setText(value,dontSendNotification);
    }
    
    //------------------------------------ Reverb ------------------------------------//
    if(slider == reverbDrySlider.get())// Reverb Dry-Wet
    {
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->reverb_param.dryLevel = 1.0f - reverbDrySlider->getValue();
            voice->reverb_param.wetLevel = 1.0f - 1.0f - reverbDrySlider->getValue();
            
            voice->reverb.setParameters(voice->reverb_param);
            for(size_t i=0;i<5;i++)
            {
                voice->eq.updateBand(i);
            }
            
        }
        
        reverbDryCoefficient[instrumetSerial] = reverbDrySlider->getValue();
    }
    else if(slider == reverbPredelaySlider.get())// Reverb Pre-delay
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->reverb_param.width = reverbPredelaySlider->getValue();
            
            voice->reverb.setParameters(voice->reverb_param);
            for(size_t i=0;i<5;i++)
            {
                voice->eq.updateBand(i);
            }
        }
        
        reverbPredelayCoefficient[instrumetSerial] = reverbPredelaySlider->getValue();
        String value = valueDoubleDigitTranslator(reverbPredelayCoefficient[instrumetSerial]);
        value.append(" db",3); // not accurate need to be change later
        reverbPredelayLabel->setText(value,dontSendNotification);
    }
    else if(slider == reverbDecaySlider.get())// Reverb Decay
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->reverb_param.damping = 1.0f - reverbDecaySlider->getValue();
            
            voice->reverb.setParameters(voice->reverb_param);
            for(size_t i=0;i<5;i++)
            {
                voice->eq.updateBand(i);
            }
        }
        
        reverbDecayCoefficient[instrumetSerial] = reverbDecaySlider->getValue();
        String value = valueDoubleDigitTranslator(reverbDecayCoefficient[instrumetSerial]);
        value.append(" db",3); // not accurate need to be change later
        reverbDecayLabel->setText(value,dontSendNotification);
    }
    else if(slider == reverbSizeSlider.get())// Reverb Size
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->reverb_param.roomSize = reverbSizeSlider->getValue();
            
            voice->reverb.setParameters(voice->reverb_param);
            for(size_t i=0;i<5;i++)
            {
                voice->eq.updateBand(i);
            }
        }
        
        reverbSizeCoefficient[instrumetSerial] = reverbSizeSlider->getValue();
        String value = valueDoubleDigitTranslator(reverbSizeCoefficient[instrumetSerial]);
        value.append(" db",3); // not accurate need to be change later
        reverbSizeLabel->setText(value,dontSendNotification);
    }
    else if(slider == reverbColorSlider.get())// Reverb Color
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->reverbColor =  reverbColorSlider->getValue();
            if(voice->reverbColor == 0)
            {
                voice->reverb_highfreq = 50;
                voice->reverb_lowfreq = 20000;
            }
            else if (voice->reverbColor > 0)
            {
                voice->reverb_highfreq = (float) 50 * pow(2, (6.6 * voice->reverbColor));//color = 1, 5000; color = 0.01, 50
                voice->reverb_lowfreq = 20000;
            }
            else if(voice->reverbColor < 0)
            {
                voice->reverb_highfreq = 50;
                voice->reverb_lowfreq = (float) 200000 * pow(2, (6.6 * voice->reverbColor));
            }
            /* safety belt for low and high freq */
            if(voice->reverb_lowfreq >= 20000)
            {
                voice->reverb_lowfreq = 20000;
            }
            else if(voice->reverb_lowfreq <= 200)
            {
                voice->reverb_lowfreq = 200;
            }
            if(voice->reverb_highfreq >= 5000)
            {
                voice->reverb_highfreq = 5000;
            }
            else if(voice->reverb_highfreq <= 50)
            {
                voice->reverb_highfreq = 50;
            }
            voice->reverb_lowpass.setCoefficients(voice->lowcoef.makeLowPass(voice->getSampleRate(),
                                                                             voice->reverb_lowfreq));
            voice->reverb_highpass.setCoefficients(voice->highcoef.makeHighPass(voice->getSampleRate(),
                                                                                voice->reverb_highfreq));
            
            voice->reverb.setParameters(voice->reverb_param);
            for(size_t i=0;i<5;i++)
            {
                voice->eq.updateBand(i);
            }
        
        }
        
        reverbColorCoefficient[instrumetSerial] = reverbColorSlider->getValue();
        String value = valueDoubleDigitTranslator(reverbColorCoefficient[instrumetSerial]);
        value.append(" cl",3); // not real need to be change later
        reverbColorLabel->setText(value,dontSendNotification);
    }
    
    
    
    //------------------------------------ Delay ------------------------------------//
    if(slider == delayDryWetSlider.get())// Delay DryWet
    {
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            //voice->reverb_param.dryLevel = 1.0f - delayDryWetSlider->getValue();
            //voice->reverb_param.wetLevel = 1.0f - 1.0f - delayDryWetSlider->getValue();
            
            voice->delay.dryMix_ = 1.0f - delayDryWetSlider->getValue();
            voice->delay.wetMix_ = 1.0f - voice->delay.dryMix_;
            

            voice->delay.update();
        }
        
        delayDryWetCoefficient[instrumetSerial] = delayDryWetSlider->getValue();
    }
    else if(slider == delayTimeSlider.get())// Delay Time
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->delay.delayLength_ = delayTimeSlider->getValue();
            voice->delay.update();
        }

        delayTimeCoefficient[instrumetSerial] = delayTimeSlider->getValue();
        String value = valueDoubleDigitTranslator(delayTimeCoefficient[instrumetSerial]);
        value.append(" db",3); // not accurate need to be change later
        delayTimeLabel->setText(value,dontSendNotification);
    }
    else if(slider == delayFeedbackSlider.get())// Delay Feedback
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->delay.feedback_ = delayFeedbackSlider->getValue();
            voice->delay.update();
        }
        
        delayFeedbackCoefficient[instrumetSerial] = delayFeedbackSlider->getValue();
        String value = valueDoubleDigitTranslator(delayFeedbackCoefficient[instrumetSerial]);
        value.append(" db",3); // not accurate need to be change later
        delayFeedbackLabel->setText(value,dontSendNotification);
    }
    else if(slider == delayColorSlider.get())// Delay Color
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->delay.color_ = delayColorSlider->getValue();
            voice->delay.update();
        }

        delayColorCoefficient[instrumetSerial] = delayColorSlider->getValue();
        String value = valueDoubleDigitTranslator(delayColorCoefficient[instrumetSerial]);
        value.append(" cl",3); // not accurate need to be change later
        delayColorLabel->setText(value,dontSendNotification);
    }
    else if(slider == delayPanSlider.get())// Delay Pan
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(instrumetSerial)))
        {
            voice->delay.panIndicator_ = delayPanSlider->getValue();
            voice->delay.update();
        }
        
        delayPanCoefficient[instrumetSerial] = delayPanSlider->getValue();
        
        String value;
        //value = valueDoubleDigitTranslator(delayPanCoefficient[instrumetSerial]);
        
        if(delayPanSlider->getValue() < 0.5)
        {
            value = "L ";
            value.append(valueDoubleDigitTranslator((0.5f - delayPanCoefficient[instrumetSerial])*200),4);// not accurate need to be change later
            
        }
        else if(delayPanSlider->getValue() > 0.5)
        {
            DBG(delayPanCoefficient[instrumetSerial]);
            value = valueDoubleDigitTranslator((delayPanCoefficient[instrumetSerial] - 0.5F)*200);
            value.append(" R",2); // not accurate need to be change later
        }
        else
        {
            value = "C";
        }
            
    
        delayPanLabel->setText(value,dontSendNotification);
    }
    
}


//MARK:- Destructor
OrionEffectsConfiguration::~OrionEffectsConfiguration()
{
    
}


