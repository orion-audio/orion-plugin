/*
  ==============================================================================

    WaveWiggle.h
    Created: 8 Oct 2019 10:38:58pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <array>
//==============================================================================
/*
*/
struct ControlPoint
{
    float y = 0;
    float startingY = 0;
    float targetY = 0;
    float direction = 1;
    void update()
    {
        if (direction < 0)
        {
            if (y > targetY)
                y += direction;
            else
                y = targetY;
        }
        else
        {
            if (y < targetY)
                y += direction;
            else
                y = targetY;
        }
        
    }
    
    void reset()
    {
        y = startingY;
        //std::cout<<"y: "<<y<<std::endl;
        //std::cout<<"startingY: "<<startingY<<std::endl;
    }
};

class WaveWiggle : public Component, public Timer
{
public:
    WaveWiggle()
    {
        setOpaque(false);
    }
    

    Colour waveColor = Colour(0xff3AE6D1);
    

    ~WaveWiggle()
    {
    }
    
    void resized() override
    {
        float height = getHeight() * .1;
        float middle = getHeight() / 2;
        for (int i = 0; i < 24; i+=2){
            controlPoints[i].startingY = middle - height;
            controlPoints[i].targetY = middle;
            controlPoints[i].direction = (controlPoints[i].targetY - controlPoints[i].startingY) / 6 ;
            controlPoints[i].y = controlPoints[i].targetY;
            
            controlPoints[i + 1].startingY = middle + height;
            controlPoints[i + 1].targetY = middle;
            controlPoints[i + 1].direction = (controlPoints[i + 1].targetY - controlPoints[i + 1].startingY) / 6 ;
            controlPoints[i + 1].y = controlPoints[i + 1].targetY;
            height *= 1.2;
            
        }
        
        std::cout<<"resize"<<std::endl;
        
       
    }

    void paint (Graphics& g) override
    {
        g.setColour(waveColor);
        Path p;
        p.startNewSubPath(0, getHeight() / 2);
        
        int x = 0;
        int w = getWidth() * 0.020;
        
        for (int i = 0; i < 23; i++){
            p.quadraticTo(x - w / 2,
                          controlPoints[i].y,
                          x,
                          controlPoints[i].targetY);
            x += w;

        }
        
        for (int i = 23; i > 0; i--){
            p.quadraticTo(x - w / 2,
                          controlPoints[i].y,
                          x,
                          controlPoints[i].targetY);
            x += w;
            
        }
        
        
        g.strokePath(p, PathStrokeType(1.f));
        

    }
    
    void startAnimation()
    {
        //std::cout<<"activate"<<std::endl;
        //float height = getHeight() * .1;
        //float middle = getHeight() / 2;
        //std::cout<<"height: "<< height <<std::endl;
        //std::cout<<"middle: "<< middle <<std::endl;
        
        for (int i = 0; i < 24; i++){
            controlPoints[i].reset();
        }
        startTimerHz(30);
    }
    
    void timerCallback() override
    {
        //std::cout<<"called"<<std::endl;
        
        bool shouldStop = true;
        for (int i = 0; i < 24; i++){
            controlPoints[i].update();
            if (controlPoints[i].y != controlPoints[i].targetY)
                shouldStop = false;
        }
        
        repaint();
        
        if (shouldStop)
        {
            waveColor = Colour(146, 148, 150);
            //setVisible(false);
            stopTimer();
        }
    }

private:
    std::array<ControlPoint, 24> controlPoints;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveWiggle)
};
