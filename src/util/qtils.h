/*
  ==============================================================================

    qtils.h
    Created: 8 Sep 2019 9:59:40pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

namespace qtils
{
    float map(float val, float low1, float high1, float low2, float high2);

    void drawRoundedRectInside(Graphics &g, Rectangle<float> rect, float cornerSize, float thickness);
    
    void copyFromBufferAndWrap(AudioBuffer<float> buffer);
    void addFromBufferAndWrap(AudioBuffer<float> buffer);
}
