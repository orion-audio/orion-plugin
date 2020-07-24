#include "Envelope.h"
#include "GlobalCoefficients.h"

using namespace std;
EnvelopeGenerator::EnvelopeGenerator(void)
{
    sampleRate = globalSampleRate;
    msPerSample = 1000/sampleRate;
    attackTime = 0.1f;//Attack
    decayTime = 1250.0f;//Decay
    sustainTime = 750.0f;//Hold
    releaseTime = 1250.0f;//Release
    
    sustainLevel = 0.5f;//Bend - Sustain
    
    envelopeOutput = 0.0;//output is between 0 to 1
    incValueShutdown = 0.0;
    currentTime = 0.0;
    
    shutdownTime = 10.0;
    
    envelopeState = off;
    isControllingDCA = true;
    envelopeMode = digital;
    setEGMode(envelopeMode);
    resetToZeroMode = true;
    legatoMode = false;
}


void EnvelopeGenerator::setEGMode(int envelopeMode)
{
    
    this->envelopeMode = envelopeMode;
    
    
    if (envelopeMode == analog)
    {
        /* TCO quantifies the curvature of envelope ? */
        attackTCO = exp(-1.5);//exp(x) = pow(e,x);
        decayTCO = exp(-4.95);
        releaseTCO = decayTCO;
    }
    else// preset init
    {
        attackTCO = 0.99999;
        decayTCO = exp(-11.05);//负无穷->0,越趋近于0,下降越平缓
        releaseTCO = exp(-11.05);
    }
    
    
    calculateAttackTime();
    calculateDecayTime();
    calculateReleaseTime();
}


void EnvelopeGenerator::reset()
{
    
    envelopeState = off;
    
    //DBG("reset");
    //setEGMode(envelopeMode);
    
    calculateReleaseTime();
    
    
    if (resetToZeroMode)
    {
        envelopeOutput = 0.0;
    }
}

void EnvelopeGenerator::calculateAttackTime()
{
    double samples = sampleRate * (attackTime / 1000.0);
    
    attackCoeff = exp(-log((1.0 + attackTCO) / attackTCO) / samples);//TCO is what determines the bend, range ?
    attackOffset = (1.0 + attackTCO)*(1.0 - attackCoeff);
}


void EnvelopeGenerator::calculateDecayTime()
{
    
    double samples = sampleRate * (decayTime / 1000.0);
    
    decayCoeff = exp(-log((1.0 + decayTCO) / decayTCO) / samples);
    decayOffset = (sustainLevel - decayTCO)*(1.0 - decayCoeff);
}

void EnvelopeGenerator::calculateReleaseTime()
{
    double samples = sampleRate * (releaseTime / 1000.0);

    releaseCoeff = exp(-log((1.0f + releaseTCO) / releaseTCO) / samples);
    
    releaseOffset = (- releaseTCO) * (1.0f - releaseCoeff);
}


void EnvelopeGenerator::noteOff()
{
    if(envelopeOutput > 0)
        envelopeState = release;
    else
        envelopeState = off;
}


void EnvelopeGenerator::shutDown()
{
    if(legatoMode)
    return;
    incValueShutdown = -(1000.0 * envelopeOutput) / shutdownTime / sampleRate;
    envelopeState = shutdown;
}





