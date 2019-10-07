/*
  ==============================================================================

    OrionSamplerSound.h
    Created: 5 Jun 2019 9:57:33pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
class OrionSamplerSound : public SamplerSound
{
private:
    int midiRootNote = 0;
    int length = 0;
    double sourceSampleRate;
public:
    friend class OrionSamplerVoice;
    OrionSamplerSound(const String &name, AudioFormatReader &source, const BigInteger &midiNotes, int midiNoteForNormalPitch, double attackTimeSecs, double releaseTimeSecs, double maxSampleLengthSeconds) : SamplerSound(name, source, midiNotes, midiNoteForNormalPitch, attackTimeSecs, releaseTimeSecs, maxSampleLengthSeconds),
    sourceSampleRate(source.sampleRate), length(source.lengthInSamples), midiRootNote(midiNoteForNormalPitch){}
    
};
