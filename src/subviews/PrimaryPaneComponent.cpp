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
//==============================================================================
PrimaryPaneComponent::PrimaryPaneComponent(OrionaudioAudioProcessor* p, OrionaudioAudioProcessorEditor* e)
{
    processor = p;
    editor = e;
    
    //--------------------------------------------!!!!!!!!!! Delete--------------------------------------------//
    //Image backgroundImage = ImageCache::getFromMemory(BinaryData::PrimaryPaneBackground_png, BinaryData::PrimaryPaneBackground_pngSize);
    //backgroundButton.reset(new ImageButton());
    //backgroundButton->setImages(false, true, true, backgroundImage, 1.f, Colours::transparentBlack, backgroundImage, 1.f, Colours::transparentBlack, backgroundImage, 1.f, Colours::transparentBlack);
    //addAndMakeVisible(backgroundButton.get());
    //--------------------------------------------!!!!!!!!!! Delete--------------------------------------------//
    
    
    for (int i = 0; i < drumButtons.size(); i++)
    {
        drumButtons[i].reset(new DragAndDropButton());
        drumButtons[i]->onClick = [&] { waveWiggle->startAnimation(); };
  
        addAndMakeVisible(drumButtons[i].get());
    }
    
    
    
    
    
    
    
    // DRUM VOICE BUTTONS
    
    Image downImage;
    Image upImage;
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
    drumButtons[4]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::snap, orion::Tabs::snareTab, drumButtons[4]->isDown()); };

    
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
            int unite = editor->getHeight()/18;
            editor->setSize(unite * 30, unite * 25);
            editor->constrainer.setFixedAspectRatio((float)editor->getWidth()/editor->getHeight());
        }else{
            int unite = editor->getHeight()/25;
            
            editor->setSize(unite * 30, unite * 18);
            editor->constrainer.setFixedAspectRatio((float)editor->getWidth()/editor->getHeight());
        };
        editor->updateDropDownState(dropDownButton->getToggleState());
    };
    addAndMakeVisible(dropDownButton.get());

    // SOLO & MUTE BUTTONS
    upImage = ImageCache::getFromMemory(BinaryData::s_png, BinaryData::s_pngSize);
    soloButton.reset(new ImageButton());
    soloButton->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    addAndMakeVisible(soloButton.get());
    
    upImage = ImageCache::getFromMemory(BinaryData::m_png, BinaryData::m_pngSize);
    muteButton.reset(new ImageButton());
    muteButton->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    addAndMakeVisible(muteButton.get());
    
    // WAVE WIGGLE
    waveWiggle.reset(new WaveWiggle());
    addAndMakeVisible(waveWiggle.get());
    
    
    
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
    
    //--------------------------------------------!!!!!!!!!! Delete--------------------------------------------//
    //Rectangle<int> backgroundArea(0, 0, getWidth(), getHeight());//--------Delete!!!!
    //backgroundButton->setBounds(backgroundArea);//--------Delete!!!!
    //--------------------------------------------!!!!!!!!!! Delete--------------------------------------------//
    
    double uniteW = getWidth()/25;

    //std::cout<<"uniteW: "<< uniteW << std::endl;

    // Solo and Mute Buttons
    Rectangle<int> area(1.25 * uniteW, 1.25 * uniteW, uniteW, uniteW);
    soloButton->setBounds(area);
    area.translate(1.25 * area.getWidth(), 0);
    muteButton->setBounds(area);
    
    // Pads
    area.setSize(getWidth() / 4, getHeight() * .25);
    int drumCount = 0;
    double localWidth = 3.5 * uniteW;
    double localHeight = 3.5 * uniteW;
    area.setSize(localWidth, localHeight);
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            area.setPosition(3.25 * uniteW + j * localWidth * 1.5, 3.75 * uniteW + i * localHeight * 1);
            drumButtons[drumCount]->setBounds(area);
            drumCount++;
        }
    }

    // Wave Wiggle
    area = Rectangle<int>(8.25 * uniteW, 9.75 * uniteW, 11.5 * uniteW, 5 * uniteW);
    waveWiggle->setBounds(area);
    
    
    // Drop Down Button
    area = Rectangle<int>(1 * uniteW, 15.25 * uniteW, uniteW, uniteW);
    dropDownButton->setBounds(area);

    
    repaint();
}
