/*
  ==============================================================================

    OrionSamplerVoice.h
    Created: 3 Jun 2019 3:57:29pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "panpos.h"
#include "delay.h"
#include "OrionSamplerSound.h"
#include "Envelope.h"
#include "compressor.h"

class OrionSamplerVoice : public SamplerVoice
, public AudioProcessorValueTreeState::Listener
{
private:
    BigInteger midiNote;
    PanPos pan;
    Delay delay;
    EnvelopeGenerator env;
    Compressor compressor;
    Reverb reverb;
    Reverb::Parameters reverb_param;
    //color for reverb
    IIRFilter reverb_lowpass;
    IIRFilter reverb_highpass;
    IIRCoefficients lowcoef,highcoef;
    double reverb_lowfreq {3000};
    double reverb_highfreq {1000};
    float reverbColor {0};
    //
    int index;
    int pitchVal;
    double currSampRate;
    //Variables from SamplerVoice Base Class
    double pitchRatio = 0;
    double sourceSamplePosition = 0;
    float lgain = 0, rgain = 0;
    double filterCutoff;
    double levelSlider;
    int iterator=0;
    double sampleRate;
    
   
    
public:
    OrionSamplerVoice(double sr, int i) : pitchVal(0), currSampRate(44100), sampleRate(sr), index(i), delay(Delay(i))
    {
        pan.setPosition(0.0);
        delay.setup(sr);
        compressor.setup(sr);
        reverb.setSampleRate(sr);
        reverb_param.roomSize = 0.5;
        reverb_param.damping = 0.4;
        reverb_param.wetLevel = 0.3;
        reverb_param.dryLevel = 0.7;
        reverb_param.width = 0.5;
        reverb_param.freezeMode = 0.0f;
        reverb.setParameters(reverb_param);
        reverb_highfreq = 50;
        reverb_lowfreq = 20000;
        
        
        reverb_lowpass.setCoefficients(lowcoef.makeLowPass(sampleRate, reverb_lowfreq));
        reverb_highpass.setCoefficients(highcoef.makeHighPass(sampleRate, reverb_highfreq));
    };

    
    /**
     
     Gets the envelope attached to the voice.
     */
    
    EnvelopeGenerator & getEnvelope() { return env; }

    void setEnvelopeAttack(double time) { env.setAttackTime_mSec(time); }
    
    /**
     
     Sets the envelope decay time in msec.
     */
    
    void setEnvelopeDecay(double time) { env.setDecayTime_mSec(time); }
    
    /**
     
     Sets the envelope sustain value.
     */
    
    void setEnvelopeSustain(double sus) { env.setSustainLevel(sus); }
    
    /**
     
     Sets the envelope release time in msec.
     */
    
    void setEnvelopeRelease(double time) { env.setReleaseTime_mSec(time); }
    
 

    void setMidiNote(int note)
    {
        midiNote.setBit(note);
    };

    bool canPlaySound(SynthesiserSound* sampSound) override
    {
        return ((dynamic_cast<OrionSamplerSound*>(sampSound)) != nullptr);
    };
    
    bool canPlayOrionSound(int note) const
    {
        
        return midiNote[note];
        
    };


    void startNote(int midiNoteNumber, float velocity, SynthesiserSound * sampSound, int pitchWheel) override
    {
        
        
        if (auto* sound = dynamic_cast<OrionSamplerSound*> (sampSound))
        {
            
            pitchRatio = std::pow(2.0, ((midiNoteNumber - sound->midiRootNote) + pitchVal) / 12.0)
            * sound->sourceSampleRate / getSampleRate();
            
            sourceSamplePosition = 0.0;
            lgain = velocity;
            rgain = velocity;
            env.startEG();
        }
        else
        {
            jassertfalse; // this object can only play SamplerSounds!
        }
        
    };
    
    
    void stopNote(float velocity, bool allowTailOff) override
    {
        
        
        if (allowTailOff)
        {
            if (env.canNoteOff())
                env.noteOff();
                //clearCurrentNote();
        }
        else if(!allowTailOff && velocity == 0.0f)
        {
            env.shutDown();
            clearCurrentNote();
           
        }
        
        else if (!allowTailOff && velocity == 1.0f)
        {
            
            if (env.canNoteOff())
                env.noteOff();
           
        }
        
        
    };
    
 
    void renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override
    {
       
        int ns = numSamples;
        
        if (auto* playingSound = dynamic_cast<OrionSamplerSound*> (getCurrentlyPlayingSound().get()))
        {
            
            auto& data = *playingSound->getAudioData();
            const float* const inL = data.getReadPointer(0);
            const float* const inR = data.getNumChannels() > 1 ? data.getReadPointer(1) : nullptr;
            //add delay effect by blocks or should i change sample by sample? i think by block
            //resulting in updating the inL/inR
           
            
            float* outL = outputBuffer.getWritePointer(0, startSample);
            float* outR = outputBuffer.getNumChannels() > 1 ? outputBuffer.getWritePointer(1, startSample) : nullptr;
            int safelength =(int) 2 * sampleRate;
            safelength = std::max(playingSound->length,safelength);
            //std::cout<<"playing "<<playingSound->length<<" 2 sec "<<safelength<<"\n";
            
            while (--numSamples >= 0)
            {
             
               
                float envVal,compVal,l,r;
                if (sourceSamplePosition <= playingSound->length)
                {

                auto pos = (int)sourceSamplePosition;
                auto alpha = (float)(sourceSamplePosition - pos);
                auto invAlpha = 1.0f - alpha;
                envVal = 0.0f;
                compVal = 0.0f;
                
                // just using a very simple linear interpolation here..
                l = (inL[pos] * invAlpha + inL[pos + 1] * alpha);
                r = (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha): l;
                
                
                }
                else
                {
                    l = 0;
                    r = 0;
                }
                
                if(ns == numSamples - 1)
                {
                    compressor.update_reference(l);
                }
                
                //Apply Delay
                //std::cout<<"before delay "<<l<<"\n";
                l = delay.bysamples(l);
                r = l;
                //std::cout<<"after delay "<<l<<"\n";
                
                //Apply Reverb
                reverb.processStereo(&l, &r, 1);
                l = reverb_highpass.processSingleSampleRaw(reverb_lowpass.processSingleSampleRaw(l));
                r = l;
                
                //Apply Compressor
                compVal = compressor.bysamples(l);
                l *= compVal;
                r *= compVal;
                
                //Envelope
                envVal = env.doEnvelope();
                //std::cout<<"envVal "<<envVal<<"\n";
                l *= envVal;
                r *= envVal;
                
                //std::cout<<"delaytime "<<delay.delayLength_<<" index "<<delay.serial<<" \n";//!!!!!!!!!!!
                //std::cout<<"delay info "<<delay.serial<<" "<<delay.delayLength_<<" "<<delay.feedback_<<"\n";
           
                //Apply Pan
                //pan.setPosition(pan.position);
                l = pan.processLeftChannel(l);
                r = pan.processRightChannel(r);
           
                if (outR != nullptr)
                {
                    *outL++ += l;
                    *outR++ += r;
            
                    
                    
                }
                else
                {
                    *outL++ += (l + r) * 0.5f;
                }
                
                sourceSamplePosition += pitchRatio;
               
                
                if (sourceSamplePosition > safelength)
                {
                   
                    clearCurrentNote();
                    break;
                }
            }
        }
         
    };
    
    void parameterChanged(const String &parameterID, float newValue) override
    {
        /* Delay */
        if (parameterID == String("delayTime" + String(index))){delay.delayLength_ = newValue;}
        //std::cout<<"index "<<index<<" new value "<<newValue<<"delayLenth "<<delay.delayLength_<<" index "<<delay.serial<<"\n";
        if (parameterID == String("delayFeedback" + String(index))){delay.feedback_ = newValue;}
        if (parameterID == String("delayColor" + String(index))){delay.color_ = newValue;}
        if (parameterID == String("delayPan" + String(index))){pan.setPosition(newValue);}
        if (parameterID == String("delayDryWet" + String(index)))
        {
            delay.dryMix_ = newValue;
            delay.wetMix_ = 1.0f - delay.dryMix_;
        }
        
        delay.update();
        
        /* Comp */
        if (parameterID == String("compRatio" + String(index))){compressor.ratio_ = newValue;}
        if (parameterID == String("compAttack" + String(index))){compressor.tauAttack_ = newValue;}
        if (parameterID == String("compRelease" + String(index))){compressor.tauRelease_ = newValue;}
        if (parameterID == String("compThresh" + String(index))){compressor.threshold_ = newValue;}
        if (parameterID == String("compGain" + String(index))){compressor.makeUpGain_ = newValue;}
        
        compressor.update();
        
        /*Reverb*/
        if (parameterID == String("reverbPredelay" + String(index))){ reverb_param.width = newValue;}//0 to 1
        if (parameterID == String("reverbSize" + String(index))){reverb_param.roomSize = newValue;}//0 to 1
        if (parameterID == String("reverbColor" + String(index)))
        {
            reverbColor =  newValue;
            //tweak reverb color
            if(reverbColor == 0)
            {
                reverb_highfreq = 50;
                reverb_lowfreq = 20000;
            }
            else if (reverbColor > 0)
            {
                reverb_highfreq = (float) 50 * pow(2, (6.6 * reverbColor));//color = 1, 5000; color = 0.01, 50
                reverb_lowfreq = 20000;
            }
            else if(reverbColor < 0)
            {
                reverb_highfreq = 50;
                reverb_lowfreq = (float) 200000 * pow(2, (6.6 * reverbColor));
            }
            //safety belt for low and high freq
            if(reverb_lowfreq >= 20000)
            {
                reverb_lowfreq = 20000;
            }
            else if(reverb_lowfreq <= 200)
            {
                reverb_lowfreq = 200;
            }
            if(reverb_highfreq >= 5000)
            {
                reverb_highfreq = 5000;
            }
            else if(reverb_highfreq <= 50)
            {
                reverb_highfreq = 50;
            }
            
            reverb_lowpass.setCoefficients(lowcoef.makeLowPass(sampleRate, reverb_lowfreq));
            reverb_highpass.setCoefficients(highcoef.makeHighPass(sampleRate, reverb_highfreq));
            //
           
            
        }
        if (parameterID == String("reverbDecay" + String(index))){reverb_param.damping = newValue;}//0 to 1
        if (parameterID == String("reverbDry" + String(index)))//0 to 1
        {
            reverb_param.dryLevel = newValue;
            reverb_param.wetLevel = 1.0f - newValue;
            
        }
        
        reverb.setParameters(reverb_param);
        
        
        
        
    };
    
    



    void setCurrentPlaybackSampleRate(double newRate) override
    {
        SamplerVoice::setCurrentPlaybackSampleRate(newRate);
        if (currSampRate != newRate && newRate != 0)
        {
            currSampRate = newRate;
            
        }
    };
    
    void setPitchVal(int pitch) { pitchVal = pitch; };
    
    int getPitchVal() { return pitchVal; };
    

    
};
