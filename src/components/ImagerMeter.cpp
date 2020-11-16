/*
  ==============================================================================

    ImagerMeter.cpp
    Created: 26 Aug 2020 3:38:47pm
    Author:  Lei Li

  ==============================================================================
*/


#include "../JuceLibraryCode/JuceHeader.h"
#include "ImagerMeter.h"

ImagerMeter::ImagerMeter()
{
    lineColor = juce::Colours::cyan;
    shadowColor = juce::Colours::cyan;
    //compressorPath.reset(new DrawablePath());
    //addAndMakeVisible(compressorPath.get());
    //compressorPath->replaceColour(Colours::black,lineColor);
    
    imagerPath.reset(new DrawablePath());
    addAndMakeVisible(imagerPath.get());
    imagerPath->replaceColour(Colours::black,shadowColor);
    

}

void ImagerMeter::paint (Graphics& g)
{
    //std::cout<<"Paint Imager Meter: "<<instrumetClickedSerial<<std::endl;
    //g.fillAll();

    //g.setColour (juce::Colours::lightyellow);
    //g.drawRect (getLocalBounds().toFloat(),  0.5);

    g.setOpacity(1.0);
    g.setColour (lineColor);

    
    Path p;
    
    if(mode)// Mid/Side Mode
    {
        float sidesY;
        float LSideX = 0;
        float RSideX = getWidth();
        
        Point<float> CenterControlPoint;
        
        
        CenterControlPoint = {static_cast<float>(getWidth()/2),static_cast<float>(getHeight() - getHeight() * imagerCoef)};
        
        
        sidesY = getHeight() * imagerCoef;

        Point<float> LSidePoint         = {static_cast<float>(LSideX),static_cast<float>(sidesY)};
        Point<float> RSidePoint         = {static_cast<float>(RSideX),static_cast<float>(sidesY)};
        Point<float> CenterPoint        = {static_cast<float>(getWidth()/2),static_cast<float>(0.0f)};
        
        
        // Draw Side Path
        p.startNewSubPath(LSidePoint);
        p.lineTo(CenterControlPoint);
        p.lineTo(RSidePoint);
        g.strokePath(p, PathStrokeType(1.0,
        PathStrokeType::JointStyle::curved,
        PathStrokeType::EndCapStyle::rounded));
        
//        p.startNewSubPath(CenterPoint);
//        p.lineTo(RSidePoint);
//        g.strokePath(p, PathStrokeType(1.0,
//        PathStrokeType::JointStyle::curved,
//        PathStrokeType::EndCapStyle::rounded));
//
//        p.startNewSubPath(LSidePoint);
//        p.quadraticTo(CenterControlPoint/* Control Point */,RSidePoint/* End Point */);
//        g.strokePath(p, PathStrokeType(1.0,
//        PathStrokeType::JointStyle::curved,
//        PathStrokeType::EndCapStyle::rounded));
    }
    else// Stereo<->Mono Mode
    {
        float sidesY = getHeight() * imagerCoef;
        float LSideX;
        float RSideX;
        
        Point<float> CenterControlPoint = {static_cast<float>(getWidth()/2),static_cast<float>(getHeight()/4 * imagerCoef)};
        
//        if(imagerCoef >= 0.5f)
//        {
//            LSideX = 0;
//            RSideX = getWidth();
//        }
//        else
//        {
//            LSideX = (getWidth()/2) * jmap<float>(imagerCoef, 0.5f, 0.0f, 0.0f,1.0f);
//            RSideX =  getWidth()    * jmap<float>(imagerCoef, 0.5f, 0.0f, 1.0f, 0.5f);
//        }
        
        LSideX =  (getWidth()/2) * (1 - imagerCoef);
        RSideX =  getWidth()/2 + getWidth() * imagerCoef/2;
        
        
        
//        float sideControlPointY = (CenterControlPoint.y - sidesY)/2 + sidesY;
//        float LControlPointX = (getWidth()/2 - LSideX)/2 + LSideX;
//        float RControlPointX = (RSideX - getWidth()/2)/2 + getWidth()/2;
//        Point<float> LSideControlPoint  = {static_cast<float>(LControlPointX),static_cast<float>(sideControlPointY * 1.212)};
//        Point<float> RSideControlPoint  = {static_cast<float>(RControlPointX),static_cast<float>(sideControlPointY * 1.212)};
        
        Point<float> LSidePoint         = {static_cast<float>(LSideX),static_cast<float>(sidesY)};
        Point<float> RSidePoint         = {static_cast<float>(RSideX),static_cast<float>(sidesY)};
        
        Point<float> CenterPoint        = {static_cast<float>(getWidth()/2),static_cast<float>(getHeight())};
        
        
        // Draw Side Path
        p.startNewSubPath(CenterPoint);
        p.lineTo(LSidePoint);
        g.strokePath(p, PathStrokeType(1.0,
        PathStrokeType::JointStyle::curved,
        PathStrokeType::EndCapStyle::rounded));
        
        p.startNewSubPath(CenterPoint);
        p.lineTo(RSidePoint);
        g.strokePath(p, PathStrokeType(1.0,
        PathStrokeType::JointStyle::curved,
        PathStrokeType::EndCapStyle::rounded));
        
        p.startNewSubPath(LSidePoint);
        p.quadraticTo(CenterControlPoint/* Control Point */,RSidePoint/* End Point */);
        g.strokePath(p, PathStrokeType(0.125,
        PathStrokeType::JointStyle::curved,
        PathStrokeType::EndCapStyle::rounded));
        
        
        /* Draw Points */
//        float ellipseSize = 2.0f;
//
//        g.drawEllipse (LSidePoint.getX() - ellipseSize/2, LSidePoint.getY() - ellipseSize/2, ellipseSize, ellipseSize, ellipseSize);
//        g.drawEllipse (RSidePoint.getX() - ellipseSize/2, RSidePoint.getY() - ellipseSize/2, ellipseSize, ellipseSize, ellipseSize);

        
//        p.startNewSubPath(LSidePoint);
//        p.quadraticTo(LSideControlPoint/* Control Point */,CenterControlPoint/* End Point */);
//        g.strokePath(p, PathStrokeType(1.0,
//        PathStrokeType::JointStyle::curved,
//        PathStrokeType::EndCapStyle::rounded));
//
//        p.startNewSubPath(RSidePoint);
//        p.quadraticTo(RSideControlPoint/* Control Point */,CenterControlPoint/* End Point */);
//        g.strokePath(p, PathStrokeType(1.0,
//        PathStrokeType::JointStyle::curved,
//        PathStrokeType::EndCapStyle::rounded));
    }
}

void ImagerMeter::resized()
{
    updateImager();
}

void ImagerMeter::updateImager()
{
    Path p;
    
    if(mode)// Mid/Side Mode
    {
        float sidesY;
        float LSideX = 0;
        float RSideX = getWidth();
        
        Point<float> CenterControlPoint;
        
        CenterControlPoint = {static_cast<float>(getWidth()/2),static_cast<float>(getHeight() - getHeight() * imagerCoef)};
        
        sidesY = getHeight() * imagerCoef;

        Point<float> LSidePoint         = {static_cast<float>(LSideX),static_cast<float>(sidesY)};
        Point<float> RSidePoint         = {static_cast<float>(RSideX),static_cast<float>(sidesY)};
        Point<float> CenterPoint        = {static_cast<float>(getWidth()/2),static_cast<float>(0.0f)};
        
        
        // Draw Side Path
        p.startNewSubPath(0,0);
        
        p.lineTo(LSidePoint);
        p.lineTo(CenterControlPoint);
        p.lineTo(RSidePoint);
        
        p.lineTo(getWidth(),0);
        
        
        float rate = jmap<float>(imagerSharpCoefficient[instrumetClickedSerial], 0.0075f, 0.1f, 0.7f,1.0f);
        DBG(rate);
        
        Colour shadowColorNew = lineColor;
        imagerPath->replaceColour(shadowColor,shadowColorNew);
        imagerPath->setAlpha(0.3);
        imagerPath->setPath(p);
        
        shadowColor = shadowColorNew;

    }
    else// Stereo<->Mono Mode
    {
        float sidesY = getHeight() * imagerCoef;
        float LSideX;
        float RSideX;
        
        Point<float> CenterControlPoint;
        CenterControlPoint = {static_cast<float>(getWidth()/2),static_cast<float>(getHeight()/4 * imagerCoef)};
        
//        if(imagerCoef >= 0.5f)
//        {
//            LSideX = 0;
//            RSideX = getWidth();
//
//        }
//        else
//        {
//            LSideX = (getWidth()/2) * jmap<float>(imagerCoef, 0.5f, 0.0f, 0.0f,1.0f);
//            RSideX =  getWidth()    * jmap<float>(imagerCoef, 0.5f, 0.0f, 1.0f, 0.5f);
//        }
        
        LSideX =  (getWidth()/2) * (1 - imagerCoef);
        RSideX =  getWidth()/2 + getWidth() * imagerCoef/2;

        Point<float> LSidePoint         = {static_cast<float>(LSideX),static_cast<float>(sidesY)};
        Point<float> RSidePoint         = {static_cast<float>(RSideX),static_cast<float>(sidesY)};
        Point<float> CenterPoint        = {static_cast<float>(getWidth()/2),static_cast<float>(getHeight())};
        
        
        // Draw Shadow
        p.startNewSubPath(CenterPoint);
        p.lineTo(LSidePoint);
        
        
//        p.startNewSubPath(CenterPoint);
//        p.lineTo(RSidePoint);
//        p.startNewSubPath(LSidePoint);
        p.quadraticTo(CenterControlPoint/* Control Point */,RSidePoint/* End Point */);
        
        
        float rate = jmap<float>(imagerSharpCoefficient[instrumetClickedSerial], 0.0075f, 0.1f, 0.6f,1.0f);
        DBG(rate);
        
        Colour shadowColorNew = Colour::fromRGB (10 * (1 - rate), 255 * rate, 255);
        imagerPath->replaceColour(shadowColor,shadowColorNew);
        //imagerPath->setColour(100, shadowColor2);
        imagerPath->setAlpha(0.3);
        imagerPath->setPath(p);
        
        shadowColor = shadowColorNew;

    }
    
    
    
    
}




//MARK:- Destructor
ImagerMeter::~ImagerMeter()
{
    
}
