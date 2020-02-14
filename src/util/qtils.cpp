/*
 ==============================================================================
 
 qtils.cpp
 Created: 8 Sep 2019 11:25:11pm
 Author:  Quin Scacheri
 
 ==============================================================================
 */

#include "qtils.h"
namespace qtils
{
    float map(float val, float low1, float high1, float low2, float high2)
    {
        return ((val - low1) / (high1 - low1)) * (high2 - low2) + low2;
    }

    void drawRoundedRectInside(Graphics &g, Rectangle<float> rect, float cornerSize, float thickness)
    {
        Path p;
        p.addRoundedRectangle(rect, cornerSize, cornerSize);
        p.applyTransform(AffineTransform::scale(1.f - thickness / rect.getWidth(), 1.f - thickness / rect.getHeight(), rect.getCentreX(), rect.getCentreY()));
        g.strokePath(p, PathStrokeType(thickness));
        
    }
void copyFromBufferAndWrap(AudioBuffer<float> destination, int destChannel, int destStartSample, const AudioBuffer<float> &source, int sourceChannel, int sourceStartSample, int numSamples)
{
    // Not dealing with this now
    jassert(sourceStartSample + numSamples < source.getNumSamples());
    
    int destSamples = destination.getNumSamples();
    if (destStartSample + numSamples > destSamples)
    {
        int diff = destSamples - destStartSample;
        destination.copyFrom(destChannel, destStartSample, source, sourceChannel, sourceStartSample, diff);
        destination.copyFrom(destChannel, 0, source, sourceChannel, sourceStartSample, numSamples - diff);
    }
    else
        destination.copyFrom(destChannel, destStartSample, source, sourceChannel, sourceStartSample, numSamples);
}

void addFromBufferAndWrap(AudioBuffer<float> destination, int destChannel, int destStartSample, const AudioBuffer<float> &source, int sourceChannel, int sourceStartSample, int numSamples)
{
    // Not dealing with this now
    jassert(sourceStartSample + numSamples < source.getNumSamples());

    int destSamples = destination.getNumSamples();
    if (destStartSample + numSamples > destSamples)
    {
        int diff = destSamples - destStartSample;
        destination.addFrom(destChannel, destStartSample, source, sourceChannel, sourceStartSample, diff);
        destination.addFrom(destChannel, 0, source, sourceChannel, sourceStartSample, numSamples - diff);
    }
    else
        destination.addFrom(destChannel, destStartSample, source, sourceChannel, sourceStartSample, numSamples);
}


}
