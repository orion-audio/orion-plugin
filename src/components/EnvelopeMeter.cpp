/*
  ==============================================================================

    EnvelopeMeter.cpp
    Created: 16 Jul 2020 11:41:29am
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "EnvelopeMeter.h"
EnvelopeMeter::EnvelopeMeter()
{
    
    waveColor = juce::Colours::greenyellow;
    EnvelopeColor = juce::Colours::cyan;
    
}

void EnvelopeMeter::paint (Graphics& g)
{
    //g.fillAll();
    //g.setColour (juce::Colours::lightyellow);
    //g.drawRect (getLocalBounds().toFloat(),  1);
    
    
    float attackEndX  = getWidth() * attackCoef;
    float decayEndX   = getWidth() * decayCoef;
    float sustainEndX = getWidth() * sustainCoef;
    float releaseEndX = getWidth() * releaseCoef;
    
    float sustainY = getHeight() * (1 - sustainBendCoef);
    
    Point<float> attackStartPoint  = {static_cast<float>(0.0f),static_cast<float>(getHeight())};
    Point<float> decayStartPoint   = {static_cast<float>(attackEndX),static_cast<float>(0.0f)};
    Point<float> sustainStartPoint = {static_cast<float>(decayEndX),static_cast<float>(sustainY)};
    Point<float> releaseStartPoint = {static_cast<float>(sustainEndX),static_cast<float>(sustainY)};
    Point<float> releaseEndPoint   = {static_cast<float>(releaseEndX),static_cast<float>(getHeight())};
    
    Path EnvPath;
    
    g.setColour (EnvelopeColor);
    
    EnvPath.startNewSubPath(attackStartPoint);
    
    EnvPath.lineTo(decayStartPoint);
    
    EnvPath.lineTo(sustainStartPoint);

    EnvPath.lineTo(releaseStartPoint);

    EnvPath.lineTo(releaseEndPoint);
    
    g.strokePath(EnvPath, PathStrokeType(1.0,
                                         PathStrokeType::JointStyle::curved,
                                         PathStrokeType::EndCapStyle::rounded));
    
}

void EnvelopeMeter::resized()
{
    
}



EnvelopeMeter::~EnvelopeMeter()
{
    
}
