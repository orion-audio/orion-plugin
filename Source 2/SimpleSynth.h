/*
  ==============================================================================

    SimpleSynth.h
    Created: 29 May 2019 9:07:54am
    Author:  Lily H

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "OrionSamplerVoice.h"
#include "OrionSamplerSound.h"

class SimpleSynth : public Synthesiser
//,public AudioProcessorValueTreeState::Listener
{
public:
    void setup(double sr);
    void loadSamples();
    void noteOn(int midiChannel,
                int midiNoteNumber,
                float velocity) override;
    typedef enum Sounds{KICK=0, SNARE, CLAP, PERC, HIHAT, CYMBAL, SNAP}Sounds_t;
    double sampleRate;
private:

    AudioFormatManager audioFormatManager;
    File* file;
    ScopedPointer<AudioFormatReader> reader;
    bool isChokeGroupActive;
    
    
};
