/*
  ==============================================================================

    PrimaryPaneComponent.cpp
    Created: 6 Feb 2020 1:20:29pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PrimaryPaneComponent.h"
#include "PluginEditor.h"
#include "OrionGlobalVars.h"
#include "PluginEditor.h"
#include "OrionSamplerVoice.h"

#include <iostream>
#include <string>
#include "GlobalCoefficients.h"





//==============================================================================
PrimaryPaneComponent::PrimaryPaneComponent(OrionaudioAudioProcessor* p, OrionaudioAudioProcessorEditor* e)
{
    processor = p;
    editor = e;
    

    
    
    // Background Image
    Image backgroundImage = ImageCache::getFromMemory(BinaryData::PrimaryPane_Footer_png, BinaryData::PrimaryPane_Footer_pngSize);
    backgroundImageView.reset(new DrawableImage());
    backgroundImageView->setImage(backgroundImage);
    addAndMakeVisible(backgroundImageView.get());
    
    
    
    Image downImage;
    Image upImage;
    
    // SOLO & MUTE BUTTONS
    downImage = ImageCache::getFromMemory(BinaryData::SoloOn_png, BinaryData::SoloOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::SoloOff_png, BinaryData::SoloOff_pngSize);
    soloButton.reset(new ImageButton());
    soloButton->setImages(false, true, true, soloButtonUp, 1.f, Colours::transparentBlack, soloButtonUp, 1.f, Colours::transparentBlack, soloButtonUp, 1.f, Colours::transparentBlack);
    soloButton->onStateChange = [&] { instrumentSoloButtonClicked(soloButton->isDown());};
    addAndMakeVisible(soloButton.get());
    
    downImage = ImageCache::getFromMemory(BinaryData::MuteOn_png, BinaryData::MuteOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::MuteOff_png, BinaryData::MuteOff_pngSize);
    muteButton.reset(new ImageButton());
    muteButton->setImages(false, true, true, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack);
    muteButton->onStateChange = [&] { instrumentMuteButtonClicked(muteButton->isDown());};
    addAndMakeVisible(muteButton.get());
    
    for (int i = 0; i < drumButtons.size(); i++)
    {
        drumButtons[i].reset(new DragAndDropButton());
        
        /*
        drumButtons[i]->onClick = [&] {
            waveWiggle->startAnimation();
        };
        */
  
        addAndMakeVisible(drumButtons[i].get());
    }
    
    
    // DRUM VOICE BUTTONS
    
    
    downImage = ImageCache::getFromMemory(BinaryData::KickOn_png, BinaryData::KickOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::KickOff_png, BinaryData::KickOff_pngSize);
    drumButtons[0]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    drumButtons[0]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::kick, orion::Tabs::kickTab, drumButtons[0]->isDown()); };
    
    downImage = ImageCache::getFromMemory(BinaryData::SnareOn_png, BinaryData::SnareOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::SnareOff_png, BinaryData::SnareOff_pngSize);
    drumButtons[1]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    drumButtons[1]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::snare, orion::Tabs::snareTab, drumButtons[1]->isDown()); };

    downImage = ImageCache::getFromMemory(BinaryData::ClapOn_png, BinaryData::ClapOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::ClapOff_png, BinaryData::ClapOff_pngSize);
    drumButtons[2]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    drumButtons[2]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::clap, orion::Tabs::clapTab, drumButtons[2]->isDown()); };

    downImage = ImageCache::getFromMemory(BinaryData::PercOn_png, BinaryData::PercOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::PercOff_png, BinaryData::PercOff_pngSize);
    drumButtons[3]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    drumButtons[3]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::perc, orion::Tabs::percTab, drumButtons[3]->isDown()); };

    
    downImage = ImageCache::getFromMemory(BinaryData::SnapOn_png, BinaryData::SnapOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::SnapOff_png, BinaryData::SnapOff_pngSize);
    drumButtons[4]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    drumButtons[4]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::snap, orion::Tabs::snapTab, drumButtons[4]->isDown()); };

    
    downImage = ImageCache::getFromMemory(BinaryData::HHOOn_png, BinaryData::HHOOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::HHOOff_png, BinaryData::HHOOff_pngSize);
    drumButtons[5]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    drumButtons[5]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::hho, orion::Tabs::hhoTab, drumButtons[5]->isDown()); };

    
    downImage = ImageCache::getFromMemory(BinaryData::HHCOn_png, BinaryData::HHCOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::HHCOff_png, BinaryData::HHCOff_pngSize);
    drumButtons[6]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    drumButtons[6]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::hhc, orion::Tabs::hhcTab, drumButtons[6]->isDown()); };

    
    downImage = ImageCache::getFromMemory(BinaryData::CrashOn_png, BinaryData::CrashOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::CrashOff_png, BinaryData::CrashOff_pngSize);
    drumButtons[7]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    drumButtons[7]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::crash, orion::Tabs::crashTab, drumButtons[7]->isDown()); };

    
    //METERS
    meterLeft.reset(new CircularMeter());
    meterLeft->updaterFunction = [this] { return processor->getOutputLevel(0);};
    meterLeft->numCircles = 8;
    //meterLeft->backgroundColorHide();
    meterLeft->setColour(meterRight->ColourIds::backgroundColourId, Colours::darkgrey);
    meterLeft->setColour(meterRight->ColourIds::filledColourId, Colours::lightgrey);
    addAndMakeVisible(meterLeft.get());
    
    meterRight.reset(new CircularMeter());
    meterRight->updaterFunction = [this] { return processor->getOutputLevel(1);};
    meterRight->numCircles = 8;
    //meterRight->backgroundColorHide();
    meterRight->setColour(meterRight->ColourIds::backgroundColourId, Colours::darkgrey);
    meterRight->setColour(meterRight->ColourIds::filledColourId, Colours::lightgrey);
    addAndMakeVisible(meterRight.get());
    

    // DROPDOWN BUTTON
    downImage = ImageCache::getFromMemory(BinaryData::arrow_down_png, BinaryData::arrow_down_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::arrow_up_png, BinaryData::arrow_up_pngSize);
    dropDownButton.reset(new ImageButton());
    dropDownButton->setClickingTogglesState(true);
    dropDownButton->setImages(false, true, true, downImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    //dropDownButton->onStateChange = [&] { editor->updateDropDownState(dropDownButton->getToggleState()); };
    dropDownButton->onClick = [&] {
        //printf("Click!");
        if(!editor->getDropdownVisible()){
            int unite = editor->getHeight()/36;
            editor->setSize(unite * 60, unite * 50);
            editor->constrainer.setFixedAspectRatio((float)editor->getWidth()/editor->getHeight());
        }else{
            int unite = editor->getHeight()/50;
            
            editor->setSize(unite * 60, unite * 36);
            editor->constrainer.setFixedAspectRatio((float)editor->getWidth()/editor->getHeight());
        };
        editor->updateDropDownState(dropDownButton->getToggleState());
    };
    addAndMakeVisible(dropDownButton.get());

    
    
    // WAVE WIGGLE
    waveWiggle.reset(new WaveWiggle());
    addAndMakeVisible(waveWiggle.get());
    waveWiggle->setVisible(false);
    
    // INSTRUMETS VOLUME SLIDER
    instrumentsVolumeSlider.reset(new Slider());
    instrumentsVolumeSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    instrumentsVolumeSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text Box
    instrumentsVolumeSlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    instrumentsVolumeSlider->setColour(Slider::trackColourId, juce::Colours::grey);
    instrumentsVolumeSlider->setRange(0.0f, 1.0f);
    instrumentsVolumeSlider->setValue(0.75f);
    instrumentsVolumeSlider->addListener(this);
    addAndMakeVisible(instrumentsVolumeSlider.get());
    // INSTRUMETS VOLUME SLIDER LABEL
    instrumentsVolumeSliderLabel.reset(new Label("0.75db", "0.75db"));
    addAndMakeVisible(instrumentsVolumeSliderLabel.get());
    instrumentsVolumeSliderLabel->setAlpha(0.5);
    
    // INSTRUMETS PAN SLIDER
    instrumentsPanSlider.reset(new Slider());
    instrumentsPanSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    instrumentsPanSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text Box
    instrumentsPanSlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    instrumentsPanSlider->setColour(Slider::trackColourId, juce::Colours::grey);
    instrumentsPanSlider->setRange(-1.0f, 1.0f);
    instrumentsPanSlider->setValue(0.0f);
    instrumentsPanSlider->addListener(this);
    addAndMakeVisible(instrumentsPanSlider.get());
    
    
    // MASTER VOLUME SLIDER
    MasterVolumeSlider.reset(new Slider());
    MasterVolumeSlider->setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    MasterVolumeSlider->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);//Hide Text Box
    MasterVolumeSlider->setColour(Slider::backgroundColourId, juce::Colours::grey);
    MasterVolumeSlider->setColour(Slider::trackColourId, juce::Colours::grey);
    MasterVolumeSlider->setRange(0.0f, 1.0f);
    MasterVolumeSlider->setValue(0.75f);
    MasterVolumeSlider->addListener(this);
    addAndMakeVisible(MasterVolumeSlider.get());
    // INSTRUMETS VOLUME SLIDER LABEL
    MasterVolumeSliderLabel.reset(new Label("0.75db", "0.75db"));
    addAndMakeVisible(MasterVolumeSliderLabel.get());
    //MasterVolumeSliderLabel->setColour(Slider::backgroundColourId, juce::Colours::darkgrey);
    MasterVolumeSliderLabel->setAlpha(0.5);

    
}

PrimaryPaneComponent::~PrimaryPaneComponent()
{
    
}

void PrimaryPaneComponent::paint (Graphics& g)
{
    //g.setGradientFill(backgroundGradient);
    
    //Image background = ImageCache::getFromMemory(BinaryData::PrimaryPaneBackground_png, BinaryData::PrimaryPaneBackground_pngSize);
  
    //g.drawImageAt (background, 0, 0);
    
    g.fillAll();
}

void PrimaryPaneComponent::resized()
{
    //backgroundGradient = ColourGradient::horizontal(Colour(0xFF0C0C0D), 0, Colours::black, getWidth() / 2);
    
    //Background
    Rectangle<int> backgroundArea(0, 0, getWidth(), getHeight());//--------Delete!!!!
    //backgroundImageView->setBounds(backgroundArea);//--------Delete!!!!
    
    backgroundImageView->setTransformToFit(backgroundArea.toFloat(), RectanglePlacement::stretchToFit);
    //--------------------------------------------!!!!!!!!!! Delete--------------------------------------------//
    
    float uniteW = getWidth()/100;

    //std::cout<<"uniteW: "<< uniteW << std::endl;

    // Solo and Mute Buttons
    Rectangle<int> area(4 * uniteW, 2.5 * uniteW, 4 * uniteW, 4 * uniteW);
    soloButton->setBounds(area);
    area.translate(6 * uniteW, 0);
    muteButton->setBounds(area);
    
    // Instrumet Pads
    int drumCount = 0;
    double localWidth = 14 * uniteW;
    double localHeight = 14 * uniteW;
    area.setSize(localWidth, localHeight);
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            area.setPosition(10 * uniteW + j * localWidth * 1.6, 13 * uniteW + i * localHeight * 1);
            drumButtons[drumCount]->setBounds(area);
            drumCount++;
        }
    }

    // Wave Wiggle
    area = Rectangle<int>(32.8 * uniteW, 39 * uniteW, 42 * uniteW, 16 * uniteW);
    waveWiggle->setBounds(area);
    
    //waveWiggle->setCentrePosition(getWidth()/2,39 * uniteW);
    
    // Meters
    area = Rectangle<int>(getWidth() - 12 * uniteW, getHeight() - 24.5 * uniteW, 2 * uniteW, 13 * uniteW);
    meterLeft->setBounds(area);
    //meterLeft->repaint();
    
    area = Rectangle<int>(getWidth() - 10 * uniteW, getHeight() - 24.5 * uniteW, 2 * uniteW, 13 * uniteW);
    meterRight->setBounds(area);
    //meterRight->repaint();
    
    // Drop Down Button
    area = Rectangle<int>(7.2 * uniteW, getHeight() - 7 * uniteW, 4 * uniteW, 4 * uniteW);
    dropDownButton->setBounds(area);
    
    // Instruments Volume Slider
    area = Rectangle<int>(16 * uniteW, 3.6 * uniteW, 14 * uniteW, 2 * uniteW);
    instrumentsVolumeSlider->setBounds(area);
    // Instruments Volume Slider Label
    area = Rectangle<int>(20.5 * uniteW, 6 * uniteW, 14 * uniteW, 2 * uniteW);
    instrumentsVolumeSliderLabel->setBounds(area);
    
    
    // Instruments Pan Slider
    area = Rectangle<int>(2 * uniteW, getHeight() - 16 * uniteW, 14 * uniteW, 2 * uniteW);
    instrumentsPanSlider->setBounds(area);
    
    // Master Volume Slider
    area = Rectangle<int>(getWidth() - 21.25 * uniteW, getHeight() - 5.6 * uniteW, 14 * uniteW, 2 * uniteW);
    MasterVolumeSlider->setBounds(area);
    // Master Volume Slider Label
    area = Rectangle<int>(getWidth() - 16.5 * uniteW, getHeight() - 3.5 * uniteW, 14 * uniteW, 2 * uniteW);
    MasterVolumeSliderLabel->setBounds(area);

    repaint();
}


void PrimaryPaneComponent::sliderValueChanged (Slider* slider)
{
    if(slider == MasterVolumeSlider.get())
    {
        masterVolumeCoefficient = MasterVolumeSlider->getValue();
        
        double a = masterVolumeCoefficient;
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
        d.append("db",2);
        MasterVolumeSliderLabel->setText(d,dontSendNotification);
    }
    else if(slider == instrumentsVolumeSlider.get())
    {
        instrumentsVolumeCoefficient[instrumetSerial] = instrumentsVolumeSlider->getValue();
        
        double a = instrumentsVolumeCoefficient[instrumetSerial];
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
        d.append("db",2);
        instrumentsVolumeSliderLabel->setText(d,dontSendNotification);
    }
    else if(slider == instrumentsPanSlider.get())
    {
        instrumentsPanCoefficient[instrumetSerial] = instrumentsPanSlider->getValue();
    }
}




void PrimaryPaneComponent::instrumentSoloButtonClicked(bool isDown)
{
    if(isDown)
    {
        instrumentsSoloStates[instrumetSerial] = !instrumentsSoloStates[instrumetSerial];
        
      
        if(instrumentsSoloStates[instrumetSerial])
        {
            instrumentsMuteStates[instrumetSerial] = false;
            soloButton->setImages(false, true, true, soloButtonDown, 1.f, Colours::transparentBlack, soloButtonDown, 1.f, Colours::transparentBlack, soloButtonDown, 1.f, Colours::transparentBlack);
            muteButton->setImages(false, true, true, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack);
            
            /* Set Solo & Mute Button state Arrays */
            for (int i = 0; i < instrumentAmount; i++)
            {
                if(instrumentsSoloStates[i])
                {
                    instrumentsMuteStates[i] = false;
                }
                else
                {
                    instrumentsMuteStates[i] = true;
                }
            }
        }
        else
        {
            soloButton->setImages(false, true, true, soloButtonUp, 1.f, Colours::transparentBlack, soloButtonUp, 1.f, Colours::transparentBlack, soloButtonUp, 1.f, Colours::transparentBlack);
            
            /* Incase Every Solo Button Back to Normal */
            int count = 0;
            for (int i = 0; i < instrumentAmount; i++)
            {
                if(instrumentsMuteStates[i])
                {
                    count += 1;
                }
            }
            
            DBG(count);
            if(count == instrumentAmount - 1)
            {
                DBG("Hey");
                for (int j = 0; j < instrumentAmount; j++)
                {
                    instrumentsMuteStates[j] = false;
                    instrumentsSoloStates[j] = false;
                }
                soloButton->setImages(false, true, true, soloButtonUp, 1.f, Colours::transparentBlack, soloButtonUp, 1.f, Colours::transparentBlack, soloButtonUp, 1.f, Colours::transparentBlack);
                muteButton->setImages(false, true, true, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack);
            }
            else
            {
                for (int j = 0; j < instrumentAmount; j++)
                {
                    if(instrumentsSoloStates[j])
                    {
                        instrumentsMuteStates[j] = false;
                    }
                    else
                    {
                        instrumentsMuteStates[j] = true;
                    }
                }
            }
        }
        
        
        
        /* Incase Previous Mute State */
        if(instrumentsMuteStates[instrumetSerial])
        {
            muteButton->setImages(false, true, true, muteButtonDown, 1.f, Colours::transparentBlack, muteButtonDown, 1.f, Colours::transparentBlack, muteButtonDown, 1.f, Colours::transparentBlack);
        }
        else
        {
            muteButton->setImages(false, true, true, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack);
        }
        
    }
}


void PrimaryPaneComponent::instrumentMuteButtonClicked(bool isDown)
{
    if(isDown)
    {
        instrumentsMuteStates[instrumetSerial] = !instrumentsMuteStates[instrumetSerial];
        
        /* Set Solo & Mute Button Images */
        if(instrumentsMuteStates[instrumetSerial])
        {
            instrumentsSoloStates[instrumetSerial] = false;
            muteButton->setImages(false, true, true, muteButtonDown, 1.f, Colours::transparentBlack, muteButtonDown, 1.f, Colours::transparentBlack, muteButtonDown, 1.f, Colours::transparentBlack);
            
            soloButton->setImages(false, true, true, soloButtonUp, 1.f, Colours::transparentBlack, soloButtonUp, 1.f, Colours::transparentBlack, soloButtonUp, 1.f, Colours::transparentBlack);
        }
        else
        {
            muteButton->setImages(false, true, true, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack, muteButtonUp, 1.f, Colours::transparentBlack);
        }

    }
}
