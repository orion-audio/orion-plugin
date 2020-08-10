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

    EQ.h
    Created: 3 Jul 2019 3:29:15pm
    Author:  Lily H

  ==============================================================================
*/

#pragma once
#include "GlobalCoefficients.h"
class EQ
{
private:
    double sampleRate {globalSampleRate};//gotta change later
    float* delayData;
    std::vector<double> frequencies;
    
  
    public:
    std::vector<IIRFilter>    filters{5};
    int activity[5];

    int serial;
    
    
    EQ(int index): serial(index)
    {
        for(int i = 0; i<5 ; i++)
        {
            activity[i] = 0;
        }
        frequencies.resize (300);
        for (size_t i=0; i < frequencies.size(); ++i)
        {
            frequencies [i] = 20.0 * std::pow (2.0, i / 30.0);
            
        }
        
    };
    

    enum FilterType
    {
        NoFilter = 0,
        HighPass,
        LowPass,
        LowShelf,
        HighShelf,
        Peak
        
    };
    

    struct Band {
        Band (const String& nameToUse, Colour colourToUse, FilterType typeToUse, float frequencyToUse, float qualityToUse, int serial, float gainToUse=1.0f, bool shouldBeActive=true)
        : name (nameToUse),
        colour (colourToUse),
        type (typeToUse),
        frequency (frequencyToUse),
        quality (qualityToUse),
        gain (gainToUse),
        active (shouldBeActive),
        index (serial)
        {}
        
        String      name;
        Colour      colour;
        FilterType  type      = NoFilter;
        float       frequency = 1000.0f;
        float       quality   = 1.0f;
        float       gain      = 1.0f;
        bool        active    = false;
        int         index;
        Path        frequencyResponse;
        std::vector<double> magnitudes;
        
    };
    
    std::vector<Band>   bands;
    
    std::vector<Band> createDefaultBands()
    {
        std::vector<Band> defaults;
        defaults.push_back (Band (TRANS ("Lowest"),    Colours::blue,   EQ::HighPass,    25.0f, 0.707f, serial));
        defaults.push_back (Band (TRANS ("Low"),       Colours::brown,  EQ::LowShelf,   250.0f, 0.707f, serial));
        defaults.push_back (Band (TRANS ("Low Mids"),  Colours::green,  EQ::Peak,       500.0f, 0.707f, serial));
        defaults.push_back (Band (TRANS ("High"),      Colours::orange, EQ::Peak,       5000.0f, 0.707f, serial));
        defaults.push_back (Band (TRANS ("Highest"),   Colours::red,    EQ::LowPass,    12000.0f, 0.707f, serial));
        return defaults;
    }
    
    
    
    
    Band* getBand (int index);
    
 

    
    

    float bysamples(float input)
    {
        float out = input;
        
        for(int i=0;i<filters.size();i++)
        {
            if(activity[i] != 0)
            {
                out = filters[i].processSingleSampleRaw(out);
            }
        }
       

        
        
        return out;
    };
    //extract magnitudes for each filter
    void updateBand(const size_t index)
    {
        if (sampleRate > 0)
        {
            dsp::IIR::Coefficients<float>::Ptr newCoefficients;
            juce::IIRCoefficients newCoef;
            switch (bands [index].type)
            {
                case NoFilter:
                    newCoefficients = new dsp::IIR::Coefficients<float> (1, 0, 1, 0);
                    activity[index] = 0;
                    
                    break;
                case LowPass:
                    newCoefficients = dsp::IIR::Coefficients<float>::makeLowPass (sampleRate, bands [index].frequency, bands [index].quality);
                    newCoef = juce::IIRCoefficients::makeLowPass (sampleRate, bands [index].frequency, bands [index].quality);
                    activity[index] = 1;
                    break;
                case LowShelf:
                    newCoefficients = dsp::IIR::Coefficients<float>::makeLowShelf (sampleRate, bands [index].frequency, bands [index].quality, bands [index].gain);
                    newCoef = juce::IIRCoefficients::makeLowShelf (sampleRate, bands [index].frequency, bands [index].quality, bands [index].gain);
                    activity[index] = 1;
                    break;
                case Peak:
                    newCoefficients = dsp::IIR::Coefficients<float>::makePeakFilter (sampleRate, bands [index].frequency, bands [index].quality, bands [index].gain);
                    newCoef = juce::IIRCoefficients::makePeakFilter (sampleRate, bands [index].frequency, bands [index].quality, bands [index].gain);
                    
                    activity[index] = 1;
                    break;
                case HighShelf:
                    newCoefficients = dsp::IIR::Coefficients<float>::makeHighShelf (sampleRate, bands [index].frequency, bands [index].quality, bands [index].gain);
                    newCoef = juce::IIRCoefficients::makeHighShelf (sampleRate, bands [index].frequency, bands [index].quality, bands [index].gain);
                    activity[index] = 1;
                    break;
                    
                case HighPass:
                    newCoefficients = dsp::IIR::Coefficients<float>::makeHighPass (sampleRate, bands [index].frequency, bands [index].quality);
                    newCoef = juce::IIRCoefficients::makeHighPass (sampleRate, bands [index].frequency, bands [index].quality);
                    activity[index] = 1;
                    
                    break;
                default:
                    break;
            }
            if (newCoefficients)
            {
                {
                    
                    // update filters
                    filters.at(index).setCoefficients(newCoef);
                    
                }
                //this step is for updating GUI plots
                newCoefficients->getMagnitudeForFrequencyArray (frequencies.data(),
                                                                bands [index].magnitudes.data(),
                                                                frequencies.size(), sampleRate);
                bands[index].active = true;
                //std::cout<<"who's ready "<<index<<"\n";
            }
            //updatePlots();
            
        }
    };
    
};


