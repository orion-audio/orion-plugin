/*
  ==============================================================================

    compressor.h
    Created: 19 Jun 2019 12:00:25pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
class Compressor
{
private:
    
    float x_g, x_l,y_g, y_l,c;// input, output, control

    double sampleRate {44100};//gotta change later
    
    float alphaAttack,alphaRelease,yL_prev;
    
public:
    float tauAttack_ {0}; // Length of attack time, in ms
    float makeUpGain_ {0};      //
    float ratio_ {1};      // ratio of compression above threshold
    float tauRelease_ {0};    // Length of release time
    float threshold_ {0}; // threshold in terms of gain
    float x_g_r, y_g_r, x_l_r;

    Compressor()
    {
        alphaAttack= 0;
        alphaRelease = 0;
        yL_prev=0;
        x_g = 0;
        y_g = 0;
        x_l = 0;
        y_l = 0;
        c = 0;
    
    };
    
    void setup(double sr)
    {
        sampleRate = sr;
        
        
        alphaAttack = exp(-1/(0.001 * sampleRate * tauAttack_));
        alphaRelease= exp(-1/(0.001 * sampleRate * tauRelease_));
     
    };
    
    void update()
    {
        
        alphaAttack = exp(-1/(0.001 * sampleRate * tauAttack_));
        alphaRelease= exp(-1/(0.001 * sampleRate * tauRelease_));
        
    }
    
    void update_reference(float input)
    {
        x_g_r = 20*log10(fabs(input));
        if (x_g_r >= threshold_) y_g_r = threshold_ + (x_g_r - threshold_) / ratio_;
        else y_g_r = x_g_r;
        
        x_l_r = x_g_r - y_g_r;
    };
    
    //implement the compressor effects by samples
    float bysamples(float input)
    {
      
        if (fabs(input) < 0.000001) x_g =-120;
        else x_g =20*log10(fabs(input));
        //Gain computer- static apply input/output curve
        if (x_g >= threshold_) y_g = threshold_ + (x_g - threshold_) / ratio_;
        else y_g = x_g;
        x_l = x_g - y_g;
        //Ballistics- smoothing of the gain
        if (x_l_r > yL_prev)  y_l=alphaAttack * yL_prev+(1 - alphaAttack ) * x_l ;
        else                 y_l=alphaRelease* yL_prev+(1 - alphaRelease) * x_l ;
        //find control
        c = pow(10,(makeUpGain_ - y_l)/20);
        yL_prev=y_l;
        
        return c;
    };


};
