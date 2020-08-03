/*
  ==============================================================================

    SimpleSynth.cpp
    Created: 29 May 2019 9:07:54am
    Author:  Lily H

  ==============================================================================
*/

#include "SimpleSynth.h"
#include "GlobalCoefficients.h"
#include "MirrorViews.h"
#define MAX_VOICES 8


int PitchToInstrumentSerial(int pitch)
{
    int instrumentSerial = 0;
  
    switch (pitch)
    {
        case 36:
            instrumentSerial = 0;
            break;
        case 38:
            instrumentSerial = 1;
            break;
        case 40:
            instrumentSerial = 2;
            break;
        case 41:
            instrumentSerial = 3;
            break;
        case 39:
            instrumentSerial = 4;
            break;
        case 46:
            instrumentSerial = 5;
            break;
        case 42:
            instrumentSerial = 6;
            break;
        case 48:
            instrumentSerial = 7;
            break;
        default:
            std::cout << "Invalid Pitch: "<< pitch << std::endl;
    }
         
    return instrumentSerial;
  
}


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
                voice->setMidiNote(KickPitch);
                break;
            case SNARE:
                voice->setMidiNote(SnarePitch);
                break;
            case CLAP:
                voice->setMidiNote(ClapPitch);
                break;
            case PERC:
                voice->setMidiNote(PercPitch);
                break;
            case SNAP:
                voice->setMidiNote(SnapPitch);
                break;
            case HHO:
                voice->setMidiNote(HHOPitch);
                break;
            case HHC:
                voice->setMidiNote(HHCPitch);
                break;
            case CRASH:
                voice->setMidiNote(CrashPitch);
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
                MidiNote = KickPitch;
                dir = "Kicks";
                filename = "trell_kick.wav";
                break;
            case SNARE:
                MidiNote = SnarePitch;
                dir = "Snares";
                filename = "Snare.wav";
                break;
            case CLAP:
                MidiNote = ClapPitch;
                dir = "Claps";
                filename = "Clap2.wav";
                break;
            case PERC:
                 MidiNote = PercPitch;
                 dir = "Percs";
                 filename = "basic-perc.wav";
                break;
            case SNAP:
                 MidiNote = SnapPitch;
                 dir = "Snaps";
                 filename = "HHPSNP1.wav";
                 break;
            case HHO:
                 MidiNote = HHOPitch;
                 dir = "HHO";
                 filename = "HiHatOp(10).WAV";
                 break;
            case HHC:
                 MidiNote = HHCPitch;
                 dir = "HHC";
                 filename = "MetroHihat.wav";
                 break;
            case CRASH:
                MidiNote = CrashPitch;
                dir = "Crash";
                filename = "Crash_01.WAV";
                //filename = "testWhiteNoise5sec.wav";
                break;
            default:
                break;

        }
        File file(audiofolder.getChildFile(dir).getChildFile(filename));
        instrumentSamplePathes[i] = file;
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
    //DBG("Hey");
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
                        startVoice(voice, sound.get(), midiChannel, midiNoteNumber, velocity);
                    }
                }
            }
            
            /* Set PrimaryPane Images */
            if(!instrumentsMuteStates[instrumetSerial])
            {
                PrimaryPaneMirror->waveWiggle->waveColor = Colour(0xff3AE6D1);
                
                if(!dropDownVisible)
                {
                  PrimaryPaneMirror->waveWiggle->startAnimation();
                }
            }
            DBG("KeyboardPress!!!!!!!!!!!");
        }
    }
}

void SimpleSynth::noteOff(int midiChannel,
                         int midiNoteNumber,
                         float velocity,
                         bool allowTailOff)
{
    /* Set PrimaryPane Images */
    //if(!instrumentsMuteStates[instrumetSerial])
    //{
        //instrumetOffSerial = PitchToInstrumentSerial(midiNoteNumber);
        //noteOffPNGChange();
    //}
    
    std::cout<< "Note Off"<<std::endl;

}


void SimpleSynth::noteOnPNGChange()
{
    //const MessageManagerLock mmLock;//????????????????
    //PrimaryPaneMirror->drumButtonCoverImageViews[instrumetSerial]->setVisible(true);
    //PrimaryPaneMirror->drumButtons[instrumetSerial]->setImages(false, true, true, upImage, 1.f, Colours::transparentBlack, upImage, 1.f, Colours::transparentBlack, downImage, 1.f, Colours::transparentBlack);
}


void SimpleSynth::noteOffPNGChange()
{
    //const MessageManagerLock mmLock;// ????????????????
    //PrimaryPaneMirror->drumButtonCoverImageViews[instrumetOffSerial]->setVisible(false);
}
