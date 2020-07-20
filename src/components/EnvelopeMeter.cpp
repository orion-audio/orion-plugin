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
    
    waveColor = juce::Colours::cyan;
    //EnvelopeColor = juce::Colours::greenyellow;
    EnvelopeColor = juce::Colours::cyan;
    mFormatManager.registerBasicFormats();
    audioFile = new File();
    
    envelopePath.reset(new DrawablePath());
    addAndMakeVisible(envelopePath.get());
    envelopePath->replaceColour(Colours::black,EnvelopeColor);
    
}

void EnvelopeMeter::paint (Graphics& g)
{
    //g.fillAll();
    //g.setColour (juce::Colours::lightyellow);
    //g.drawRect (getLocalBounds().toFloat(),  1);
    
    
    //------------------------------------ Draw Waveform -------------------------------------//
    
    /* Creat Path & Init Start Point & Change Pencil Color & Change Pencil Opeacity*/
    Path p;
    p.clear();
    p.startNewSubPath(0, getHeight()/2);
    g.setColour (waveColor);
    g.setOpacity(0.7);
    
    /* Get Waveform */
    auto waveform = getWaveForm();
    int ratio = waveform.getNumSamples()/getWidth();
    auto buffer = waveform.getReadPointer(0);
    
    /* Scale Audio File To Window On X Axis */
    for (int sample = 0; sample < mWaveForm.getNumSamples(); sample+=ratio)
    {
        mAudioPoints.push_back(buffer[sample]);
    }
    
    /* Scale Audio File to Window on Y Axis */
    for (int sample = 0; sample < mAudioPoints.size(); ++sample)
    {
        auto point = jmap<float>(mAudioPoints[sample], -1.0f, 1.0f, getHeight(),0);
        p.lineTo(sample,point);
    }
    
    /* Draw Audio Waveform */
    g.strokePath(p, PathStrokeType(1.0,
                                   PathStrokeType::JointStyle::curved,
                                   PathStrokeType::EndCapStyle::rounded));
    
    
    
    //------------------------------------ Draw Envelope -------------------------------------//
    
    /*
    Path EnvPath;
    g.setColour (EnvelopeColor);
    

    
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
    
    
    
    EnvPath.startNewSubPath(attackStartPoint);
    
    EnvPath.lineTo(decayStartPoint);
    
    EnvPath.lineTo(sustainStartPoint);

    EnvPath.lineTo(releaseStartPoint);

    EnvPath.lineTo(releaseEndPoint);
    
    g.strokePath(EnvPath, PathStrokeType(1.0,
                                         PathStrokeType::JointStyle::curved,
                                         PathStrokeType::EndCapStyle::rounded));
     */
    
}

void EnvelopeMeter::updateEnvelope()
{
    Path p;
    
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
    
    
    
    p.startNewSubPath(attackStartPoint);
    
    p.lineTo(decayStartPoint);
    
    p.lineTo(sustainStartPoint);

    p.lineTo(releaseStartPoint);

    p.lineTo(releaseEndPoint);
    
    envelopePath->setAlpha(0.3);
    envelopePath->setPath(p);
}


void EnvelopeMeter::loadAudioFile()
{
    if(audioFile != nullptr)
    {
        audioFile = &instrumentSamplePathes[serial];
        //DBG(audioFile->getFullPathName());//-!!!!!!!!

        mFormatReader = mFormatManager.createReaderFor(instrumentSamplePathes[serial]);
        auto sampleLength = static_cast<int>(mFormatReader->lengthInSamples);
        
        mWaveForm.setSize(1, sampleLength);
        
        mFormatReader->read(&mWaveForm, 0, sampleLength, 0, true, false);

        auto buffer = mWaveForm.getReadPointer(0);//Ch 1

        for (int sample = 0; sample < mWaveForm.getNumSamples(); ++sample)
        {
            DBG(buffer[sample]);
        }
    }
    else
    {
        return;
    }
}


void EnvelopeMeter::initAudioFile(int serialIn)
{
    serial = serialIn;
    if(audioFile != nullptr)
    {
        audioFile = &instrumentSamplePathes[serial];
        DBG(audioFile->getFullPathName());//-!!!!!!!!
        
        mFormatReader = mFormatManager.createReaderFor(instrumentSamplePathes[serial]);
        auto sampleLength = static_cast<int>(mFormatReader->lengthInSamples);
        
        mWaveForm.setSize(1, sampleLength);
        
        mFormatReader->read(&mWaveForm, 0, sampleLength, 0, true, false);

        auto buffer = mWaveForm.getReadPointer(0);//Ch 1

//        for (int sample = 0; sample < mWaveForm.getNumSamples(); ++sample)
//        {
//            DBG(buffer[sample]);
//        }
    }
    else
    {
        return;
    }
}



void EnvelopeMeter::resized()
{
    updateEnvelope();
}


EnvelopeMeter::~EnvelopeMeter()
{
    
}
