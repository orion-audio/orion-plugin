/*
  ==============================================================================

    delay.h
    Created: 7 Jun 2019 12:20:03pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
#include <math.h>
class Delay
{
private:
    AudioSampleBuffer delayBuffer_;
    int delayBufferLength_ {1};
    int delayReadPosition_ {0};
    int delayWritePosition_ {0};
    double sampleRate {44100};//gotta change later
    int dpr {0};
    int dpw {0};
    float* delayData;
    IIRFilter lowpass;
    IIRFilter highpass;
    IIRCoefficients lowcoef,highcoef;
    double lowfreq {3000};
    double highfreq {1000};
    bool on {1};
    
public:
    
    float delayLength_ {0.1}; // Length of delay line in seconds
    float dryMix_ {0.3};      // Mix level of original signal (0-1)
    float wetMix_ {0.7};      // Mix level of delayed signal (0-1)
    float feedback_ {0.0};    // Feedback level (0-just less than 1)
    float color_ {0.0}; //low pass filter - high pass filter (-1-1)
    int serial;
    //constructor: set size, set read and write pointer
    Delay(int index): serial(index)
    {
        //what is the range for low pass and high pass filter
       
        //highfreq = 275 + color_ * 225;//cut off high pass is 50 to 500; cut off low pass is 1k to 20k
        //lowfreq = 10500 + color_ * 9500;// how to discern knob is turning left or right
        
      
        highfreq = 50;
        lowfreq = 20000;
        
        
        lowpass.setCoefficients(lowcoef.makeLowPass(sampleRate, lowfreq));
        highpass.setCoefficients(highcoef.makeHighPass(sampleRate, highfreq));
        
    };
    
    //setup should initialize delay buffer, read/write positions
    void setup(double sr)
    {
        sampleRate = sr;
        delayBufferLength_ = (int)(1.0*sampleRate);
        if(delayBufferLength_ < 1)
            delayBufferLength_ = 1;
        delayBuffer_.setSize(1, delayBufferLength_);
        delayBuffer_.clear();
        
        // This method gives us the sample rate. Use this to figure out what the delay position
        // offset should be (since it is specified in seconds, and we need to convert it to a number
        // of samples)
        delayReadPosition_ = (int)(delayWritePosition_ - (delayLength_ * sampleRate)
                                   + delayBufferLength_) % delayBufferLength_;
        delayData = delayBuffer_.getWritePointer (0);
        
        dpr = delayReadPosition_;
        dpw = delayWritePosition_;
        
        //delayReadPosition_ = dpr;
        //delayWritePosition_ = dpw;
        //std::cout<<"beginning "<<dpr<<" "<<dpw<<" "<<delayReadPosition_<<"\n";
    };
    
    void update()
    {
        dpr = (int)(dpw - (delayLength_ * sampleRate)
                                   + delayBufferLength_) % delayBufferLength_;
        if(color_ == 0)
        {
            highfreq = 50;
            lowfreq = 20000;
        }
        else if (color_ > 0)
        {
            highfreq = (float) 50 * pow(2, (6.6 * color_));//color = 1, 5000; color = 0.01, 50
            lowfreq = 20000;
        }
        else if(color_ < 0)
        {
            highfreq = 50;
            lowfreq = (float) 200000 * pow(2, (6.6 * color_));
        }
        //safety belt for low and high freq
        if(lowfreq >= 20000)
        {
            lowfreq = 20000;
        }
        else if(lowfreq <= 200)
        {
            lowfreq = 200;
        }
        if(highfreq >= 5000)
        {
            highfreq = 5000;
        }
        else if(highfreq <= 50)
        {
            highfreq = 50;
        }
       
        lowpass.setCoefficients(lowcoef.makeLowPass(sampleRate, lowfreq));
        highpass.setCoefficients(highcoef.makeHighPass(sampleRate, highfreq));
        if(delayLength_ == 0)
        {
            on = 0;
        }
        else
        {
            on = 1;
        }
    };
    
    //bysamples should output the final signal value at each time step
    float bysamples(float input)
    {
        //dpr = delayReadPosition_;
        //dpw = delayWritePosition_;
       
        float out = 0.0;
        if(on==1)
        {
            out = (dryMix_ * input + highpass.processSingleSampleRaw(lowpass.processSingleSampleRaw(wetMix_ * delayData[dpr])));
        }
        else
        {
            out = dryMix_ * input;
        }

        delayData[dpw] = input + (delayData[dpr] * feedback_);
        
        if (++dpr >= delayBufferLength_)
            dpr = 0;
        if (++dpw >= delayBufferLength_)
            dpw = 0;
    
    
        return out;
    };
    
    
    //apply delay time
    //apply dry/wet
    //apply feedback
    //apply color
    
    
    //feedback
    //pan
    //color
    
    //dry or wet - y(t)= a x(t) + b x(t-m) ; a+b=1; dry: a=1
   
    
};
