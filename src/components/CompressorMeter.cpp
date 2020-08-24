/*
  ==============================================================================

    CompressorMeter.cpp
    Created: 11 Aug 2020 5:34:21pm
    Author:  Lei Li

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "CompressorMeter.h"
#include "math.h"
#include "GlobalCoefficients.h"

CompressorMeter::CompressorMeter()
{
    lineColor = juce::Colours::cyan;
    //compressorPath.reset(new DrawablePath());
    //addAndMakeVisible(compressorPath.get());
    //compressorPath->replaceColour(Colours::black,lineColor);

}

void CompressorMeter::paint (Graphics& g)
{
    //std::cout<<"Paint Compressor Meter: "<<instrumetClickedSerial<<std::endl;

    //g.fillAll();

    //g.setColour (juce::Colours::lightyellow);
    //g.drawRect (getLocalBounds().toFloat(),  0.5);

    g.setOpacity(1.0);
    g.setColour (lineColor);

    Path p;

    float threshX  = getWidth()/2;
    float threshY  = getHeight() * threshCoef;

    float degree = atan((getHeight() - threshY)/(getWidth()/2))  * 180 / globalPi;;

    float endY = threshY - tan(degree * ratioCoef * globalPi / 180) * getWidth()/2;

    Point<float> startPoint        = {static_cast<float>(0.0f),static_cast<float>(getHeight())};
    Point<float> threshStartPoint  = {static_cast<float>(threshX),static_cast<float>(threshY)};
    Point<float> endPoint          = {static_cast<float>(getWidth()),static_cast<float>(endY)};

    /* Draw Points */
    float ellipseSize = 2.0f;

    g.drawEllipse (startPoint.getX() + 0.5, startPoint.getY() - 1.5, ellipseSize, ellipseSize, ellipseSize);
    g.drawEllipse (threshStartPoint.getX(), threshStartPoint.getY()-1.0, ellipseSize, ellipseSize, ellipseSize);
    g.drawEllipse (endPoint.getX() - 1.5, endPoint.getY() + 0.25f, ellipseSize, ellipseSize, ellipseSize);


    /* Draw Compressor Bend Path */
    p.startNewSubPath(startPoint);
    p.lineTo(threshStartPoint);

    //Point<float> mid = {static_cast<float>(threshX + (getWidth() - threshX)/2),static_cast<float>(threshY - endY/10)};
    //p.quadraticTo(mid,endPoint);
    p.lineTo(endPoint);

    g.strokePath(p, PathStrokeType(1.0,
    PathStrokeType::JointStyle::curved,
    PathStrokeType::EndCapStyle::rounded));


    /* Draw Frame */
    g.setOpacity(0.2);

//    p.startNewSubPath(startPoint);
//    p.lineTo(0.0,0.0);
//    g.strokePath(p, PathStrokeType(0.2,
//    PathStrokeType::JointStyle::curved,
//    PathStrokeType::EndCapStyle::rounded));

//    p.startNewSubPath(getWidth()/2 + 0.1,0.0);
//    p.lineTo(getWidth()/2 + 0.1,getHeight());
//    g.strokePath(p, PathStrokeType(0.1,
//    PathStrokeType::JointStyle::curved,
//    PathStrokeType::EndCapStyle::rounded));

//    p.startNewSubPath(getWidth(),0.0);
//    p.lineTo(getWidth(),getHeight());
//    g.strokePath(p, PathStrokeType(0.2,
//    PathStrokeType::JointStyle::curved,
//    PathStrokeType::EndCapStyle::rounded));

    g.drawRect (getLocalBounds().toFloat(),  0.2);

}

void CompressorMeter::updateMeter()
{
    //compressorPath->setPath(p);
    //Path p2;
}


void CompressorMeter::resized()
{
    //updateMeter();
}


CompressorMeter::~CompressorMeter()
{

}
