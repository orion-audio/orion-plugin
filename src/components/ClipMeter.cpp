/*
  ==============================================================================

    ClipMeter.cpp
    Created: 12 Sep 2020 9:00:56pm
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ClipMeter.h"
#include "GlobalCoefficients.h"


ClipMeter::ClipMeter()
{
    
    waveColor = juce::Colours::cyan;
    
    
    zonePath.reset(new DrawablePath());
    addAndMakeVisible(zonePath.get());
    zonePath->replaceColour(Colours::black,waveColor);
    
}

void ClipMeter::paint (Graphics& g)
{
    //g.fillAll();
    //g.setColour (juce::Colours::white);
    //g.drawRect (getLocalBounds().toFloat(),  0.5);
    //std::cout<<"Paint Clip Meter: "<<instrumetClickedSerial<<std::endl;

    //------------------------------------ Draw Waveform -------------------------------------//
    /* Creat Path & Init Start Point & Change Pencil Color & Change Pencil Opeacity*/
    Path p;
    p.clear();
    p.startNewSubPath(0, getHeight()/2);
    g.setColour (waveColor);
    g.setOpacity(0.7);

    /* Get Waveform */
    int ratio = instrumentSampleContainer[instrumetClickedSerial].getNumSamples()/getWidth();
    auto buffer = instrumentSampleContainer[instrumetClickedSerial].getReadPointer(0);
    std::vector<float> mAudioPoints;

    /* Scale Audio File To Window On X Axis */
    for (int sample = 0; sample < instrumentSampleContainer[instrumetClickedSerial].getNumSamples(); sample+=ratio)
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


    

}


void ClipMeter::resized()
{
    DBG("Resize");
}


void ClipMeter::updateZone()
{
    Path p;
    
    float LX  = getWidth() * startPointCoefficient[instrumetClickedSerial];

    float RX  = getWidth() * endPointCoefficient[instrumetClickedSerial];

    

    Point<float> point1     = {static_cast<float>(LX),static_cast<float>(getHeight())};
    
    Point<float> point2      = {static_cast<float>(LX),static_cast<float>(0.0f)};
    
    Point<float> point3    = {static_cast<float>(RX),static_cast<float>(0.0f)};
    
    Point<float> point4    = {static_cast<float>(RX),static_cast<float>(getHeight())};

    
    
    p.startNewSubPath(point1);
    p.lineTo(point2);
    p.lineTo(point3);
    p.lineTo(point4);
    
    
    zonePath->setAlpha(0.3);
    zonePath->setPath(p);
}




//MARK:- Destructor
ClipMeter::~ClipMeter()
{
    
}
