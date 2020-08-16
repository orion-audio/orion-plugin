/*
  ==============================================================================

    OrionInstrumentView.cpp
    Created: 16 Aug 2020 12:41:18pm
    Author:  Lei Li

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionInstrumentView.h"
//#include "PluginEditor.h"
OrionInstrumentView::OrionInstrumentView()//OrionaudioAudioProcessorEditor* e
{
    //processor = p;
    //editor = e;
    
    
    for (int i = 0; i < drumButtonCoverImageViews.size(); i++)
    {
        //drumButtons[i].reset(new DragAndDropButton());
        //addAndMakeVisible(drumButtons[i].get());
        
        drumButtonCoverImageViews[i].reset(new DrawableImage());
        addAndMakeVisible(drumButtonCoverImageViews[i].get());
        drumButtonCoverImageViews[i]->setVisible(false);
    }
    
    Image downImage;
    Image upImage;
    
    // DRUM VOICE BUTTONS & DRUM COVER IMAGEVIEW
    downImage = ImageCache::getFromMemory(BinaryData::KickOn_png, BinaryData::KickOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::KickOff_png, BinaryData::KickOff_pngSize);
    //drumButtons[0]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    //drumButtons[0]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::kick, orion::Tabs::kickTab, drumButtons[0]->isDown()); };
    drumButtonCoverImageViews[0]->setImage(downImage);
    

    

    downImage = ImageCache::getFromMemory(BinaryData::SnareOn_png, BinaryData::SnareOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::SnareOff_png, BinaryData::SnareOff_pngSize);
    //drumButtons[1]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    //drumButtons[1]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::snare, orion::Tabs::snareTab, drumButtons[1]->isDown()); };
    drumButtonCoverImageViews[1]->setImage(downImage);

    downImage = ImageCache::getFromMemory(BinaryData::ClapOn_png, BinaryData::ClapOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::ClapOff_png, BinaryData::ClapOff_pngSize);
    //drumButtons[2]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    //drumButtons[2]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::clap, orion::Tabs::clapTab, drumButtons[2]->isDown()); };
    drumButtonCoverImageViews[2]->setImage(downImage);

    downImage = ImageCache::getFromMemory(BinaryData::PercOn_png, BinaryData::PercOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::PercOff_png, BinaryData::PercOff_pngSize);
    //drumButtons[3]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    //drumButtons[3]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::perc, orion::Tabs::percTab, drumButtons[3]->isDown()); };
    drumButtonCoverImageViews[3]->setImage(downImage);

    downImage = ImageCache::getFromMemory(BinaryData::SnapOn_png, BinaryData::SnapOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::SnapOff_png, BinaryData::SnapOff_pngSize);
    //drumButtons[4]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    //drumButtons[4]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::snap, orion::Tabs::snapTab, drumButtons[4]->isDown()); };
    drumButtonCoverImageViews[4]->setImage(downImage);

    downImage = ImageCache::getFromMemory(BinaryData::HHOOn_png, BinaryData::HHOOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::HHOOff_png, BinaryData::HHOOff_pngSize);
    //drumButtons[5]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    //drumButtons[5]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::hho, orion::Tabs::hhoTab, drumButtons[5]->isDown()); };
    drumButtonCoverImageViews[5]->setImage(downImage);

    downImage = ImageCache::getFromMemory(BinaryData::HHCOn_png, BinaryData::HHCOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::HHCOff_png, BinaryData::HHCOff_pngSize);
    //drumButtons[6]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    //drumButtons[6]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::hhc, orion::Tabs::hhcTab, drumButtons[6]->isDown()); };
    drumButtonCoverImageViews[6]->setImage(downImage);

    downImage = ImageCache::getFromMemory(BinaryData::CrashOn_png, BinaryData::CrashOn_pngSize);
    upImage = ImageCache::getFromMemory(BinaryData::CrashOff_png, BinaryData::CrashOff_pngSize);
    //drumButtons[7]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
    //drumButtons[7]->onStateChange = [&] { editor->drumButtonClicked(orion::MidiNotes::crash, orion::Tabs::crashTab, drumButtons[7]->isDown()); };
    drumButtonCoverImageViews[7]->setImage(downImage);
    
    
    startTimerHz(30);
    instrumentOnArray = instrumentsOnStates;
    
}


//MARK:- PAINT
void OrionInstrumentView::paint (Graphics& g)
{
    //g.setColour (juce::Colours::lightyellow);
    //g.drawRect (getLocalBounds().toFloat(),  1);
}

//MARK:- RESIZE
void OrionInstrumentView::resized()
{
    Rectangle<int> area;
    
    double padWidth = getWidth()/5.5;
    double padHeight = getHeight()/2;
    
    area.setSize(padWidth, padHeight);
    
    int drumCount = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            area.setPosition(j * padWidth * 1.5, i * padHeight);
            drumButtonCoverImageViews[drumCount]->setBounds(area);
     
            drumButtonCoverImageViews[drumCount]->setTransformToFit(area.toFloat(), RectanglePlacement::centred);
            drumCount++;
        }
    }
}


void OrionInstrumentView::timerCallback()
{
    for (int i = 0; i < instrumentAmount; i++)
    {
        if( *(instrumentOnArray + i))
        {
            drumButtonCoverImageViews[i]->setVisible(true);
        }
        else
        {
            drumButtonCoverImageViews[i]->setVisible(false);
        }
    }
}


//MARK:- 析构函数
OrionInstrumentView::~OrionInstrumentView()
{
    
}



/*
 for (int i = 0; i < instrumentAmount; i++)
 {
     if( *(instrumentOnArray + i))
     {
         drumButtonCoverImageViews[i]->setVisible(true);
     }
     else
     {
         drumButtonCoverImageViews[i]->setVisible(false);
     }
 }
 
 */
