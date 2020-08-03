/*
  ==============================================================================

    EnvelopeMeter.h
    Created: 16 Jul 2020 11:41:29am
    Author:  Lei Li

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GlobalCoefficients.h"

class EnvelopeMeter  : public Component
{
public:
    EnvelopeMeter();
    ~EnvelopeMeter() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void loadAudioFile();
    void initAudioFile();
    
    void updateEnvelope();
    
    //void setSustainBendCoefficient(float SBC){sustainBendCoef = SBC;};
    
    AudioBuffer<float>& getWaveForm(){return mWaveForm;};
    
    std::vector<float> getmAudioPoints();
        
    float getAttackCoef(){return attackCoef;};
    float getDecayCoef(){return decayCoef;};
    float getSustainCoef(){return sustainCoef;};
    float getReleaseCoef(){return releaseCoef;};
    
    void setAttackCoef(float inputVal){attackCoef = inputVal;};
    void setDecayCoef(float inputVal){decayCoef = inputVal;};
    void setSustainCoef(float inputVal){sustainCoef = inputVal;};
    void setReleaseCoef(float inputVal){releaseCoef = inputVal;};
    
    void setAttackBendCoef(float inputVal){attackBendCoef = inputVal;};
    void setDecayBendCoef(float inputVal){decayBendCoef = inputVal;};
    void setSustainBendCoef(float inputVal){sustainBendCoef = inputVal;};
    void setReleaseBendCoef(float inputVal){releaseBendCoef = inputVal;};
    
    float getSampleLength()
    {
        float sampleLengthInMS = 1000 * mWaveForm.getNumSamples()/globalSampleRate;
        return sampleLengthInMS;
    };

private:
    //File* audioFile;
    AudioBuffer<float> mWaveForm;
    AudioFormatManager  mFormatManager;
    //AudioFormatReader*  mFormatReader {nullptr};
    //std::vector<float> mAudioPoints;
    
    Colour waveColor;
    Colour EnvelopeColor;
    
    std::unique_ptr<DrawablePath> envelopePath;
    
    float attackCoef  = 0.1f;//0.0f <= attackCoef < decayCoef
    float decayCoef   = 0.2f;//attackCoef < decayCoef < sustainCoef
    float sustainCoef = 0.5f;//decayCoef < sustainCoef < releaseCoef
    float releaseCoef = 1.0f;//sustainCoef < releaseCoef <= 1.0f

    float attackBendCoef  = 0.5f;
    float decayBendCoef   = 0.5f;
    float sustainBendCoef = 0.5f;
    float releaseBendCoef = 0.5f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeMeter)
};
