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

OrionEffectsConfiguration::OrionEffectsConfiguration(OrionaudioAudioProcessor& p, int serial) : processor(p), compGui(p,serial), reverbGui(p,serial), delayGui(p,serial)
{

    
    effectSerial = serial;
    
    //---------------------------------------------
       addAndMakeVisible(&compGui);
       //addAndMakeVisible(&reverbGui);
       addAndMakeVisible(&delayGui);
    //---------------------------------------------
    
    
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
    
    
    //------------------------------------ Reverb ------------------------------------//
    
    // Dry-Wet
    reverbDrySlider.reset(new Slider());
    reverbDrySlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    reverbDrySlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    reverbDrySlider->setColour(Slider::trackColourId, juce::Colours::grey);
    reverbDrySlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    reverbDrySlider->setRange(0.0f, 1.0f);
    reverbDrySlider->setValue(0.4f);
    reverbDrySlider->addListener(this);
    addAndMakeVisible(reverbDrySlider.get());
    
    // Pre-Delay
    reverbPredelaySlider.reset(new Slider());
    reverbPredelaySlider->setSliderStyle(Slider::SliderStyle::Rotary);
    reverbPredelaySlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    reverbPredelaySlider->setRange(0.0f, 1.0f);
    reverbPredelaySlider->setValue(1.0f);
    reverbPredelaySlider->addListener(this);
    addAndMakeVisible(reverbPredelaySlider.get());
    
    // Decay
    reverbDecaySlider.reset(new Slider());
    reverbDecaySlider->setSliderStyle(Slider::SliderStyle::Rotary);
    reverbDecaySlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    reverbDecaySlider->setRange(0.0f, 1.0f);
    reverbDecaySlider->setValue(0.5f);
    reverbDecaySlider->addListener(this);
    addAndMakeVisible(reverbDecaySlider.get());

    // Size
    reverbSizeSlider.reset(new Slider());
    reverbSizeSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    reverbSizeSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    reverbSizeSlider->setRange(0.0f, 1.0f);
    reverbSizeSlider->setValue(0.5f);
    reverbSizeSlider->addListener(this);
    addAndMakeVisible(reverbSizeSlider.get());
  
    // Color
    reverbColorSlider.reset(new Slider());
    reverbColorSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    reverbColorSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text
    reverbColorSlider->setRange(-1.0f, 1.0f);
    reverbColorSlider->setValue(0.0f);
    reverbColorSlider->addListener(this);
    addAndMakeVisible(reverbColorSlider.get());

    
    
    
    

}

void OrionEffectsConfiguration::paint(Graphics& g)
{
    //g.fillAll();
    //g.fillAll(Colours::darkgoldenrod);
}

//MARK:- Resize
void OrionEffectsConfiguration::resized()
{
    
    //--------- Background Image ---------//
    Rectangle<int> backgroundArea(0, 0, getWidth(), getHeight());
    backgroundImageView->setTransformToFit(backgroundArea.toFloat(), RectanglePlacement::stretchToFit);
    
    
    //------------------------------------ Previous ------------------------------------//
    Rectangle<int> area = getLocalBounds();
    area = area.removeFromLeft(getWidth() / 3);
    compGui.setBounds(area);
    
    area.translate(getWidth() / 3, 0);
    reverbGui.setBounds(area);
    
    area.translate(getWidth() / 2.5, 0);
    delayGui.setBounds(area);
    
    float uniteW = getWidth()/100;
    
    //------------------------------------ Switches ------------------------------------//
    area = Rectangle<int>(getWidth()/2 - 10 * uniteW, 1 * uniteW,  2 * uniteW, 2 * uniteW);
    compSwitch->setBounds(area);
    
    area = Rectangle<int>(getWidth()*2/3 + 2 * uniteW, 1 * uniteW,  2 * uniteW, 2 * uniteW);
    reverbSwitch->setBounds(area);
    
    area = Rectangle<int>(getWidth() - 4 * uniteW,    1 * uniteW, 2 * uniteW, 2 * uniteW);
    delaySwitch->setBounds(area);
    

    //------------------------------------ Reverb ------------------------------------//
    // Dry-Wet
    area = Rectangle<int>(getWidth()/2 - 3 * uniteW, getHeight()/2 - 2 * uniteW,  24 * uniteW, 2 * uniteW);
    reverbDrySlider->setBounds(area);

    // Pre-Delay
    area = Rectangle<int>(getWidth()/2 - 4 * uniteW, getHeight() - 8 * uniteW,  5 * uniteW, 5 * uniteW);
    reverbPredelaySlider->setBounds(area);

    // Decay
    area = Rectangle<int>(getWidth()/2 + 3 * uniteW, getHeight() - 8 * uniteW,  5 * uniteW, 5 * uniteW);
    reverbDecaySlider->setBounds(area);

    // Size
    area = Rectangle<int>(getWidth()/2 + 10.5 * uniteW, getHeight() - 8 * uniteW,  5 * uniteW, 5 * uniteW);
    reverbSizeSlider->setBounds(area);

    // Color
    area = Rectangle<int>(getWidth()/2 + 17.5 * uniteW, getHeight() - 8 * uniteW,  5 * uniteW, 5 * uniteW);
    reverbColorSlider->setBounds(area);
    

    
}

//MARK:- Switch Clicker
void OrionEffectsConfiguration::switchClicked(bool isDown)
{
    if(isDown)
    {
        if(switchSerial == 0)/* Compressor Switch */
        {
            
            if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(effectSerial)))
            {
                voice->compressorswitch = !voice->compressorswitch;
                
                compSwitches[instrumetSerial] = !compSwitches[instrumetSerial];
                setSwitchImage(voice->compressorswitch,switchSerial);
            }
            
        }
        else if(switchSerial == 1)/* Reverb Switch */
        {
            
            if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(effectSerial)))
            {
                voice->reverbswitch = !voice->reverbswitch;
                
                reverbSwitches[instrumetSerial] = !reverbSwitches[instrumetSerial];
                setSwitchImage(reverbSwitches[instrumetSerial],switchSerial);
            }
            
        }
        else if(switchSerial == 2)/* Delay Switch */
        {
            
            if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(effectSerial)))
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


void OrionEffectsConfiguration::sliderValueChanged (Slider* slider)
{
    
    if(slider == reverbDrySlider.get())// Reverb Dry-Wet
    {
        
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(effectSerial)))
        {
            voice->reverb_param.dryLevel = 1.0f - reverbDrySlider->getValue();
            voice->reverb_param.wetLevel = 1.0f - 1.0f - reverbDrySlider->getValue();
            
            voice->reverb.setParameters(voice->reverb_param);
            for(size_t i=0;i<5;i++)
            {
                voice->eq.updateBand(i);
            }
            
        }
        
        reverbDryCoefficient[instrumetSerial] = 1.0f - reverbDrySlider->getValue();
    }
    else if(slider == reverbPredelaySlider.get())// Reverb Pre-delay
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(effectSerial)))
        {
            voice->reverb_param.width = reverbPredelaySlider->getValue();
            
            voice->reverb.setParameters(voice->reverb_param);
            for(size_t i=0;i<5;i++)
            {
                voice->eq.updateBand(i);
            }
        }
        
        reverbPredelayCoefficient[instrumetSerial] = reverbPredelaySlider->getValue();
    }
    else if(slider == reverbDecaySlider.get())// Reverb Decay
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(effectSerial)))
        {
            voice->reverb_param.damping = 1.0f - reverbDecaySlider->getValue();
            
            voice->reverb.setParameters(voice->reverb_param);
            for(size_t i=0;i<5;i++)
            {
                voice->eq.updateBand(i);
            }
        }
        
        reverbDecayCoefficient[instrumetSerial] = 1.0f - reverbDecaySlider->getValue();
    }
    else if(slider == reverbSizeSlider.get())// Reverb Size
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(effectSerial)))
        {
            voice->reverb_param.roomSize = reverbSizeSlider->getValue();
            
            voice->reverb.setParameters(voice->reverb_param);
            for(size_t i=0;i<5;i++)
            {
                voice->eq.updateBand(i);
            }
        }
        
        reverbSizeCoefficient[instrumetSerial] = reverbSizeSlider->getValue();
    }
    else if(slider == reverbColorSlider.get())// Reverb Color
    {
        if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(effectSerial)))
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
    }
    
}


//void OrionEffectsConfiguration::sliderValueChanged (Slider* slider)
//{
//
//    if(slider == reverbDrySlider.get())
//    {
//        reverbDryCoefficient[instrumetSerial] = 1.0f - reverbDrySlider->getValue();
//    }
//    else if(slider == reverbPredelaySlider.get())
//    {
//        reverbPredelayCoefficient[instrumetSerial] = reverbPredelaySlider->getValue();
//    }
//    else if(slider == reverbDecaySlider.get())
//    {
//        reverbDecayCoefficient[instrumetSerial] = 1.0f - reverbDecaySlider->getValue();
//    }
//    else if(slider == reverbSizeSlider.get())
//    {
//        reverbSizeCoefficient[instrumetSerial] = reverbSizeSlider->getValue();
//    }
//    else if(slider == reverbColorSlider.get())
//    {
//        reverbColorCoefficient[instrumetSerial] = reverbColorSlider->getValue();
//    }
//
//    if(auto* voice = dynamic_cast<OrionSamplerVoice*> (processor.getSampler()->getVoice(effectSerial)))
//    {
//        voice->reverbUpdate();
//    }
//    //
//
//
//
//}




//MARK:- Destructor
OrionEffectsConfiguration::~OrionEffectsConfiguration()
{
    
}


