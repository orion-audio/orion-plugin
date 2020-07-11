/*
 Copyright (c) 2018, Daniel Walz - Foleys Finest Audio UG All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
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
#include "EQ.h"
#include "GlobalCoefficients.h"



class OrionSamplerVoice : public SamplerVoice
, public AudioProcessorValueTreeState::Listener
{
    
private:
    BigInteger midiNote;
    EnvelopeGenerator env;

    //float* masterVolume = &masterVolumeCoefficient;

    //Sidechain sidechain;
    
    
    //
    int index = 0;
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
    bool sidechain_on {true}; 
    int sidechain_from, sidechain_to;
    bool initialized {false};
    
    // dsp::Gain<float> overallgain;
    std::vector<double> magnitudes;
    
    
    

public:
 
    //---------- Pan ----------/
    PanPos pan;
    //------- Effect Switches -------/
    bool delayswitch {false}, compressorswitch {false}, reverbswitch {false};
    
    //-------- Compressor --------/
    Compressor compressor;
    
    //---------- Reverb ----------/
    Reverb reverb;
    Reverb::Parameters reverb_param;
    /* color for reverb */
    IIRFilter reverb_lowpass;
    IIRFilter reverb_highpass;
    IIRCoefficients lowcoef,highcoef;
    double reverb_lowfreq {3000};
    double reverb_highfreq {1000};
    float reverbColor {0};
    
    //---------- Delay ----------/
    Delay delay;
    
    //---------- EQ ----------/
    EQ eq;
    
    EQ::FilterType getTypefromindex(int index)
    {
        switch (index)
        {
            case 0:
                return EQ::NoFilter;
                break;
            case 1:
                return EQ::HighPass;
                break;
            case 2:
                return EQ::LowPass;
                break;
            case 3:
                return EQ::LowShelf;
                break;
            case 4:
                return EQ::HighShelf;
                break;
            case 5:
                return EQ::Peak;
                break;
        }
        
    };

    std::vector<double> frequencies;
    
    OrionSamplerVoice(double sr, int i) : pitchVal(0), currSampRate(48000), sampleRate(sr), index(i), delay(Delay(i)), eq(EQ(i))
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
        
        eq.bands = eq.createDefaultBands();
        frequencies.resize (300);
        for (size_t i=0; i < frequencies.size(); ++i)
        {
            frequencies [i] = 20.0 * std::pow (2.0, i / 30.0);
            
        }
        magnitudes.resize (frequencies.size());
       
       
        for (size_t i = 0; i < eq.bands.size(); ++i)
        {
            eq.bands [i].magnitudes.resize (frequencies.size(), 1.0);
            eq.updateBand(i);
          
        }
        updatePlots();
    };

    void setactivity(int index, int active)
    {
        eq.activity[index] = active;
    }
    
    static StringArray getFilterTypeNames()
    {
        return {
            TRANS ("No Filter"),
            TRANS ("High Pass"),
            TRANS ("Low Pass"),
            TRANS ("Low Shelf"),
            TRANS ("High Shelf"),
            TRANS ("Peak")
        };

    };
    
    const std::vector<double>& getMagnitudes ()
    {
        return magnitudes;
    };
    
    

    void updatePlots ()
    {
        //auto gain = overallgain.getGainLinear();
        std::fill (magnitudes.begin(), magnitudes.end(), 1.0f);
        
        for (size_t i = 0; i < eq.bands.size() ; ++i)
        {
        if(eq.bands[i].active)
            //std::cout<<"what's wrong "<<i<<" "<<eq.activity[i]<<" "<<"\n";
           FloatVectorOperations::multiply (magnitudes.data(), eq.bands [i].magnitudes.data(), static_cast<int> (magnitudes.size()));
        }
           //overallgain.setGainLinear(magnitudes.data());
    
    }
    
    double getSampleRate()
    {
        return sampleRate;
    }
    
    
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
                clearCurrentNote();
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
            int safelength =(int) 10 * sampleRate;// Previous Value: 2 * sampleRate
            safelength = std::max(playingSound->length,safelength);
            //std::cout<<"playing "<<playingSound->length<<" 2 sec "<<safelength<<"\n";
            
            while (--numSamples >= 0)
            {
             
                float envVal,compVal,sideVal, l, r;
                if (sourceSamplePosition <= playingSound->length)
                {
                    auto pos = (int)sourceSamplePosition;
                    auto alpha = (float)(sourceSamplePosition - pos);
                    auto invAlpha = 1.0f - alpha;
                    envVal = 0.0f;
                    compVal = 0.0f;
                    sideVal = 0.0f;
                
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
                
                
                //MARK:- Apply Instruments Pan
                pan.setPosition(instrumentsPanCoefficient[instrumetSerial]);
                l = pan.processLeftChannel(l);
                r = pan.processRightChannel(r);
                
                //MARK:- Apply EQ
                l = eq.bysamples(l);
                r = l;
                
                //MARK:- Apply Envelope
                envVal = env.doEnvelope();
                // std::cout<<"what envelope"<<" "<<env.getAttackTime()<<" "<<env.getDecayTime()<<" "<<env.getSustainTime()<<" "<<env.getReleaseTime()<<"\n";
                l *= envVal;
                r *= envVal;
              
                //MARK:- Apply Compressor
                if(compressorswitch)
                {
                    compVal = compressor.bysamples(l);
                    l *= compVal;
                    r *= compVal;
                }
                
                //MARK:- Apply Reverb
                if(reverbswitch)
                {
                    reverb.processStereo(&l, &r, 1);
                    l = reverb_highpass.processSingleSampleRaw(reverb_lowpass.processSingleSampleRaw(l));
                    r = reverb_highpass.processSingleSampleRaw(reverb_lowpass.processSingleSampleRaw(l));
                    //r = l;
                }
                

                //MARK:- Apply Delay
                if(delayswitch)
                {
                    //Apply Delay
                    l = delay.bysamples(l,true);
                    r = delay.bysamples(r,false);
                
                    //Apply Pan
                    //pan.setPosition(pan.position);
                    //l = pan.processLeftChannel(l);
                    //r = pan.processRightChannel(r);
                }
                
                
                
                //MARK:- Apply Instruments Volume
                l = l * instrumentsVolumeCoefficient[instrumetSerial];
                r = r * instrumentsVolumeCoefficient[instrumetSerial];

                //MARK:- Apply Master Volume
                l = l * masterVolumeCoefficient;
                r = r * masterVolumeCoefficient;
                
                //MARK:- Apply Solo & Mute
                if(!instrumentsSoloStates[instrumetSerial] && instrumentsMuteStates[instrumetSerial])
                {
                    l = l * 0.0f;
                    r = r * 0.0f;
                }
                

                if (outR != nullptr)
                {
                    *outL++ += l;
                    *outR++ += r;
                }
                else
                {
                    *outL++ += (l + r) * 0.5f;
                }
                

                //MARK:- Master Meters
                globalOutputMeterL = outputBuffer.getRMSLevel(0, 0, outputBuffer.getNumSamples());
                if (outputBuffer.getNumChannels() > 1)
                    globalOutputMeterR = outputBuffer.getRMSLevel(1, 0, outputBuffer.getNumSamples());
                else
                    globalOutputMeterR = outputBuffer.getRMSLevel(0, 0, outputBuffer.getNumSamples());
                

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
        /* ON-OFF SWITCHES */
        //DBG("parameterChanged");
        if (parameterID == String("delaySwitch" + String(index))){delayswitch = newValue;}
        if (parameterID == String("compressorSwitch" + String(index))){compressorswitch = newValue;}
        if (parameterID == String("reverbSwitch" + String(index))){reverbswitch = newValue;}
        
        /* Delay */
        if (parameterID == String("delayTime" + String(index))){delay.delayLength_ = newValue;}
        if (parameterID == String("delayFeedback" + String(index))){delay.feedback_ = newValue;}
        if (parameterID == String("delayColor" + String(index))){delay.color_ = newValue;}
        if (parameterID == String("delayPan" + String(index))){pan.setPosition(newValue);}
        if (parameterID == String("delayDryWet" + String(index)))
        {
            delay.dryMix_ = newValue;
            delay.wetMix_ = 1.0f - delay.dryMix_;
        }
        
        delay.update();
        
        /*Envelope*/
        if (parameterID == String("envAttack" + String(index))){env.setAttackTime_mSec(newValue);}
        if (parameterID == String("envHold" + String(index))){env.setSustainTime_mSec(newValue);}// problematic!!
        if (parameterID == String("envDecay" + String(index))){env.setDecayTime_mSec(newValue);}
        if (parameterID == String("envRelease" + String(index))){env.setReleaseTime_mSec(newValue);}
       
        //if (parameterID == String("envAttackBend" + String(index))){compressor.ratio_ = newValue;}
        if (parameterID == String("envSustain" + String(index))){env.setSustainLevel(newValue);}
        //if (parameterID == String("envDecayBend" + String(index))){compressor.tauRelease_ = newValue;}
        //if (parameterID == String("envReleaseBend" + String(index))){compressor.threshold_ = newValue;}
        
         //std::cout<<"what envelope22222"<<" "<<env.getAttackTime()<<" "<<env.getDecayTime()<<" "<<env.getSustainTime()<<" "<<env.getReleaseTime()<<"\n";
        
        /* Comp */
        if (parameterID == String("compThresh" + String(index))){compressor.threshold_ = newValue;}
        if (parameterID == String("compRatio" + String(index))){compressor.ratio_ = newValue;}
        if (parameterID == String("compAttack" + String(index))){compressor.tauAttack_ = newValue;}
        if (parameterID == String("compRelease" + String(index))){compressor.tauRelease_ = newValue;}
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
           
            
        }
        if (parameterID == String("reverbDecay" + String(index))){reverb_param.damping = newValue;}//0 to 1
        if (parameterID == String("reverbDry" + String(index)))//0 to 1
        {
            reverb_param.dryLevel = newValue;
            reverb_param.wetLevel = 1.0f - newValue;
        }
        
        
        
        reverb.setParameters(reverb_param);
        for(size_t i=0;i<5;i++)
        {
            eq.updateBand(i);
        }
        
        /*Envelope*/
        
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
    
    
    void createFrequencyPlot (Path& p, const std::vector<double>& mags, const Rectangle<int> bounds, float pixelsPerDouble)
    {
        p.startNewSubPath (bounds.getX(), roundToInt (bounds.getCentreY()));
        p.lineTo(bounds.getX(), roundToInt (bounds.getCentreY() - pixelsPerDouble * std::log (mags [0]) / std::log (2)));
        //p.startNewSubPath (bounds.getX(), roundToInt (bounds.getCentreY() - pixelsPerDouble * std::log (mags [0]) / std::log (2)));
       
        const double xFactor = static_cast<double> (bounds.getWidth()) / frequencies.size();
        for (size_t i=1; i < frequencies.size(); ++i)
        {
            if(i == 0)
            {
                p.lineTo (bounds.getX(),
                roundToInt (bounds.getCentreY() - pixelsPerDouble * std::log (mags [i]) / std::log (2)));
            }
            else if(i == frequencies.size() - 1)
            {
                p.lineTo (bounds.getWidth(),
                roundToInt (bounds.getCentreY() - pixelsPerDouble * std::log (mags [i]) / std::log (2)));
            }
            else
            {
                p.lineTo (roundToInt (bounds.getX() + i * xFactor),
                roundToInt (bounds.getCentreY() - pixelsPerDouble * std::log (mags [i]) / std::log (2)));
            }
        }
        p.lineTo(bounds.getWidth(), roundToInt (bounds.getCentreY()));
    }

};
