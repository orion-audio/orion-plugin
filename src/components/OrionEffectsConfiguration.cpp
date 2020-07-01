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
    
    // Background Image
    Image backgroundImage = ImageCache::getFromMemory(BinaryData::FXBackground_png, BinaryData::FXBackground_pngSize);
    backgroundImageView.reset(new DrawableImage());
    backgroundImageView->setImage(backgroundImage);
    addAndMakeVisible(backgroundImageView.get());
        
    
    
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
    
    //--------- Background Image ---------//
    Rectangle<int> backgroundArea(0, 0, getWidth(), getHeight());
    backgroundImageView->setTransformToFit(backgroundArea.toFloat(), RectanglePlacement::stretchToFit);
    
    Rectangle<int> area = getLocalBounds();
    area = area.removeFromLeft(getWidth() / 3);
    compGui.setBounds(area);
    
    area.translate(getWidth() / 3, 0);
    reverbGui.setBounds(area);
    
    area.translate(getWidth() / 3, 0);
    delayGui.setBounds(area);

    
}

OrionEffectsConfiguration::~OrionEffectsConfiguration()
{
    
}


