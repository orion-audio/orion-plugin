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
    
    for (int i = 0; i < drumButtons.size(); i++)
    {
        drumButtons[i].reset(new DragAndDropButton());
        drumButtons[i]->onClick = [&] { waveWiggle->startAnimation(); };
        addAndMakeVisible(drumButtons[i].get());
    }
    
    Image downImage;
    Image upImage;
    
    // DRUM VOICE BUTTONS
    
    downImage = ImageCache::getFromMemory(BinaryData::kick_on_png, BinaryData::kick_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::kick_off_png, BinaryData::kick_off_pngSize);
    drumButtons[0]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    drumButtons[0]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::kick, orion::Tabs::kickTab, drumButtons[0]->isDown()); };
    
    downImage = ImageCache::getFromMemory(BinaryData::snare_on_png, BinaryData::snare_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::snare_off_png, BinaryData::snare_off_pngSize);
    drumButtons[1]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    drumButtons[1]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::snare, orion::Tabs::snareTab, drumButtons[1]->isDown()); };

    downImage = ImageCache::getFromMemory(BinaryData::clap_on_png, BinaryData::clap_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::clap_off_png, BinaryData::clap_off_pngSize);
    drumButtons[2]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    drumButtons[2]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::clap, orion::Tabs::clapTab, drumButtons[2]->isDown()); };

    downImage = ImageCache::getFromMemory(BinaryData::perc_on_png, BinaryData::perc_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::perc_off_png, BinaryData::perc_off_pngSize);
    drumButtons[3]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    drumButtons[3]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::perc, orion::Tabs::percTab, drumButtons[3]->isDown()); };

    
    downImage = ImageCache::getFromMemory(BinaryData::snap_on_png, BinaryData::snap_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::snap_off_png, BinaryData::snap_off_pngSize);
    drumButtons[4]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    drumButtons[4]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::snap, orion::Tabs::snareTab, drumButtons[4]->isDown()); };

    
    downImage = ImageCache::getFromMemory(BinaryData::hho_on_png, BinaryData::hho_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::hho_off_png, BinaryData::hho_off_pngSize);
    drumButtons[5]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    drumButtons[5]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::hho, orion::Tabs::hhoTab, drumButtons[5]->isDown()); };

    
    downImage = ImageCache::getFromMemory(BinaryData::hhc_on_png, BinaryData::hhc_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::hhc_off_png, BinaryData::hhc_off_pngSize);
    drumButtons[6]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    drumButtons[6]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::hhc, orion::Tabs::hhcTab, drumButtons[6]->isDown()); };

    
    downImage = ImageCache::getFromMemory(BinaryData::crash_on_png, BinaryData::crash_on_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::crash_off_png, BinaryData::crash_off_pngSize);
    drumButtons[7]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack);
    drumButtons[7]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::crash, orion::Tabs::crashTab, drumButtons[7]->isDown()); };

    
    downImage = ImageCache::getFromMemory(BinaryData::arrow_down_png, BinaryData::arrow_down_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::arrow_up_png, BinaryData::arrow_up_pngSize);

    // DROPDOWN BUTTON
    dropDownButton.reset(new ImageButton());
    dropDownButton->setClickingTogglesState(true);
    dropDownButton->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    dropDownButton->onStateChange = [&] { editor->updateDropDownState(dropDownButton->getToggleState()); };
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
    g.setGradientFill(backgroundGradient);
    g.fillAll();
}

void PrimaryPaneComponent::resized()
{
    backgroundGradient = ColourGradient::horizontal(Colour(0xFF0C0C0D), 0, Colours::black, getWidth() / 2);
    
    Rectangle<int> area(getParentHeight() * .025, getParentHeight() * .025, getParentHeight() * .05, getParentHeight() * .05);
    soloButton->setBounds(area);
    area.translate(area.getWidth(), 0);
    muteButton->setBounds(area);
    
    area = getLocalBounds();
    int buttonWidth = getWidth() * .2;
    int drumCount = 0;
    area.setSize(getWidth() / 4, getHeight() * .25);
    area.setY(soloButton->getBottom() * 1.5);
    for (int i = 0; i < 2; i++)
    {
        area.setX(0);
        for (int j = 0; j < 4; j++)
        {
            drumButtons[drumCount]->setBounds(area.withSizeKeepingCentre(buttonWidth, area.getHeight()));
            drumCount++;
            area.translate(getWidth() / 4, 0);
        }
        area.translate(0, area.getHeight());
    }
    
    area = Rectangle<int>(0, 0, getParentHeight() * .1, getParentHeight() * .1);
    area.setPosition(0, getHeight() - area.getHeight());
    dropDownButton->setBounds(area);
    
    area = Rectangle<int>(0, drumButtons[4]->getBottom(), getWidth(), getParentHeight() * .1);
    area = area.withSizeKeepingCentre(area.getWidth() * .85, area.getHeight());
    waveWiggle->setBounds(area);
    
    repaint();
}
