/*
  ==============================================================================

    SimpleSynth.cpp
    Created: 29 May 2019 9:07:54am
    Author:  Lily H

  ==============================================================================
*/

#include "SimpleSynth.h"
#include "GlobalCoefficients.h"
#define MAX_VOICES 8



void SimpleSynth::setup(double sr)
{
    sampleRate = sr;
    // add voices to our sampler

    for (int i = 0; i < MAX_VOICES; i++)
    {
        auto* voice = new OrionSamplerVoice(sampleRate,i);
        //auto* voice = new SamplerVoice();
        switch(i)
        {
            case KICK:
                voice->setMidiNote(36);
                break;
            case SNARE:
                voice->setMidiNote(38);
                break;
            case CLAP:
                voice->setMidiNote(39);
                break;
            case PERC:
                voice->setMidiNote(41);
                break;
            case SNAP:
                voice->setMidiNote(42);
                break;
            case HHC:
                voice->setMidiNote(43);
                break;
            case HHO:
                voice->setMidiNote(44);
                break;
            case CRASH:
                voice->setMidiNote(46);
                break;
            default:
                break;
        }
        addVoice(voice);

    }
    audioFormatManager.registerBasicFormats();
    loadSamples();

}

void SimpleSynth::loadSamples()
{


    
    if(getNumSounds() != 0)
    {
        for(int i = 0; i < getNumSounds(); i++)
        {
            removeSound(i);
        }
    }
    int MidiNote;
    audiofolder = File("/Library/Application\ Support/Orion/Orion\ Plugin/Samples");
    
    String dir;
    String filename;
    for(int i = 0; i < MAX_VOICES; i++)
    {
        switch(i)
        {
            case KICK:
                MidiNote = 36;
                dir = "Kicks";
                filename = "trell_kick.wav";
                break;
            case SNARE:
                MidiNote = 38;
                dir = "Snares";
                filename = "Snare.wav";
                break;
            case CLAP:
                MidiNote = 39;
                dir = "Claps";
                filename = "Clap2.wav";
                break;
            case PERC:
                 MidiNote = 41;
                 dir = "Percs";
                 filename = "basic-perc.wav";
                break;
            case SNAP:
                 MidiNote = 42;
                dir = "Snaps";
                filename = "HHPSNP1.wav";
                break;
            case HHC:
                 MidiNote = 43;
                dir = "HHC";
                filename = "MetroHihat.wav";
                break;
            case HHO:
                 MidiNote = 44;
                dir = "HHO";
                filename = "HiHatOp(10).WAV";
                break;
            case CRASH:
                MidiNote = 46;
                dir = "Crash";
                filename = "Crash_01.WAV";
                break;
            default:
                break;

        }
        File file(audiofolder.getChildFile(dir).getChildFile(filename));
        std::unique_ptr<AudioFormatReader> reader;
        reader.reset(audioFormatManager.createReaderFor(file));
        if (reader == nullptr)
            return;
        BigInteger note;
        note.setBit(MidiNote);
        OrionSamplerSound *sampler = new OrionSamplerSound(String(i), *reader.get(), note, MidiNote, 0.0f, 10.0f, 10.0f);
        addSound(sampler);
    }



}

void SimpleSynth::changeSamples(int index,const String &f,int midi)//index should imply which instrument it is, but in this case index is the sequence
{

    if(getNumSounds() != 0 and index < getNumSounds())
    {
        //std::cout<<"who did you lose "<<getNumSounds()<<" "<<index<<"\n";
        removeSound(index);
    }
    //const String f = files[0];
    file = new File(f);
    std::unique_ptr<AudioFormatReader> reader;
    reader.reset(audioFormatManager.createReaderFor(*file));
    
    if (reader.get() == nullptr)
    {
        auto alert = [&]
        {
            AlertWindow::showNativeDialogBox("Invalid file", "The selected file is not a valid file", false);
        };
        
        MessageManager::callAsync(alert);
        return;    
    }
    
    
    BigInteger note;
    note.setBit(midi);
    OrionSamplerSound *sampler = new OrionSamplerSound(String(index), *reader, note, midi, 0.0f, 10.0f, 10.0f);
    addSound(sampler);
    delete file;



}


void SimpleSynth::noteOn(int midiChannel,
                         int midiNoteNumber,
                         float velocity)
{
    //const ScopedLock sl(lock);
    //std::cout<<"number of sounds"<<getNumSounds();
    DBG("Hey");
    for(int j = 0; j < getNumSounds(); j++)
    {
        auto sound = getSound(j);
        if(sound->appliesToNote(midiNoteNumber) && sound->appliesToChannel(midiChannel))
        {
            for(int i = 0; i < getNumVoices(); i++)
            {
                if(auto* voice = dynamic_cast<OrionSamplerVoice*>(getVoice(i)))
                {
                    //std::cout<<"can play sound "<<voice->canPlayOrionSound(midiNoteNumber);
                    //std::cout<<"current sound " << voice->getCurrentlyPlayingSound();
                    if(voice->canPlayOrionSound(midiNoteNumber) && voice->getCurrentlyPlayingSound())
                    {
                        //std::cout<<"stopped voice"<<midiNoteNumber<<voice->canPlayOrionSound(midiNoteNumber);
                        stopVoice(voice, 0.0f, false);
                    }
                }
            }

            for(int i = 0; i < getNumVoices(); i++)
            {
                if(auto* voice = dynamic_cast<OrionSamplerVoice*> (getVoice(i)))
                {
                    if(voice->canPlayOrionSound(midiNoteNumber) && !voice->getCurrentlyPlayingSound())
                    {
                        //Logger::outputDebugString("Start Voice: " + std::to_string(i) + " with Sound: " + std::to_string(j));
                        startVoice(voice, sound.get(), midiChannel, midiNoteNumber, velocity);
                    }
                }
            }
            
            /* Set Solo Button Image */
            if(instrumentsSoloStates[instrumetSerial])
            {
                //primaryPane->setInstrumetsSoloButtonImage(true);
            }
            else
            {
               //primaryPane->setInstrumetsSoloButtonImage(false);
            }
            
        }
    }
}


//void SimpleSynth::renderNextBlock (AudioBuffer<float>& outputAudio, const MidiBuffer& inputMidi,
//                                   int startSample, int numSamples)
//{
//
//}
