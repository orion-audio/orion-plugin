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
OrionEffectsConfiguration::OrionEffectsConfiguration(OrionaudioAudioProcessor& p, int serial) : processor(p), compGui(p,serial), reverbGui(p,serial), delayGui(p,serial)
{

    
    effectSerial = serial;
    
    //--------------------------------------------!!!!!!!!!! Delete--------------------------------------------//
//    Image backgroundImage = ImageCache::getFromMemory(BinaryData::FXBackground_png, BinaryData::FXBackground_pngSize);
//    backgroundButton.reset(new DrawableImage());
//    backgroundButton->setImage(backgroundImage);
//    addAndMakeVisible(backgroundButton.get());
    //--------------------------------------------!!!!!!!!!! Delete--------------------------------------------//
        
    
    
    addAndMakeVisible(&compGui);
    addAndMakeVisible(&reverbGui);
    addAndMakeVisible(&delayGui);

}

void OrionEffectsConfiguration::paint(Graphics& g)
{
    //g.fillAll();
    //g.fillAll(Colours::darkgoldenrod);
}

void OrionEffectsConfiguration::resized()
{
    
    //--------------------------------------------!!!!!!!!!! Delete--------------------------------------------//
//    Rectangle<float> backgroundArea(0, 0, getWidth(), getHeight());//--------Delete!!!!
//    backgroundButton->setBoundingBox(backgroundArea);//--------Delete!!!!
    //--------------------------------------------!!!!!!!!!! Delete--------------------------------------------//
    
    Rectangle<int> area = getLocalBounds();
    area = area.removeFromLeft(getWidth() / 3);
    
    compGui.setBounds(area);
    
   
    
    area.translate(getWidth() / 3, 0);
    delayGui.setBounds(area);
    
    area.translate(getWidth() / 3, 0);
    reverbGui.setBounds(area);

    
}

OrionEffectsConfiguration::~OrionEffectsConfiguration()
{
    
}


