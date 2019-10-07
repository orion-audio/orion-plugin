/*
  ==============================================================================

    panpos.h
    Created: 4 Jun 2019 10:58:54am
    Author:  Lily H

  ==============================================================================
*/

#pragma once
#include <cmath>
#include "../JuceLibraryCode/JuceHeader.h"
#define PI 3.14159265358979323846264338327950288

class PanPos
{
    float position;
    
    float angle;
    const float piovr2;
    const float root2ovr2;
    
public:
    PanPos() : piovr2(PI * 0.5), root2ovr2(sqrt(2.0) * 0.5) { setPosition(0.0); }
    
    float getPosition() { return position; }
    
    void setPosition(float _position)
    {
        position = _position * piovr2;
        angle = position * 0.5;
    };
    
    
    float processLeftChannel(float leftChannel)
    {
        leftChannel *= root2ovr2 * (cos(angle) - sin(angle));
        return leftChannel;
    };
    
    
    float processRightChannel(float rightChannel)
    {
        rightChannel *= root2ovr2 * (cos(angle) + sin(angle));
        return rightChannel;
    };
    
    
};
