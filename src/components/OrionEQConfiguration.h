/*
  ==============================================================================

    OrionEQConfiguration.h
    Created: 11 Jun 2019 9:44:35pm
    Author:  Lei Li

  ==============================================================================
*/

#pragma once
#include "PluginProcessor.h"

//==============================================================================
class OrionEQConfiguration : public Component
                            // public ChangeListener
{
public:
    OrionEQConfiguration(OrionaudioAudioProcessor& p, int serial);
    ~OrionEQConfiguration();
    
    void paint(Graphics& g) override;
    void resized() override;

    
    //void mouseDown (const MouseEvent& e) override;
    void mouseDown (const MouseEvent& e) override;
    void mouseMove (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseWheelMove (const MouseEvent& e,const MouseWheelDetails & wheel) override;
    void mouseDoubleClick (const MouseEvent& e) override;
   
     int EQserial;
     GroupComponent          frame;
private:
    void updateFrequencyResponses ();
    static float getPositionForFrequency (float freq);
    static float getFrequencyForPosition (float pos);
    static float getPositionForGain (float gain, float top, float bottom);
    static float getGainForPosition (float pos, float top, float bottom);
    File* eqbackground;
    OrionaudioAudioProcessor& processor;
    Rectangle<int>          plotFrame;
    Path                    analyserPath;
    Path                    frequencyResponse;
    int                     draggingBand = -1;
    int                     wheelBand = -1;
    int                     wheelQ = false;
    bool                    draggingGain = false;
    PopupMenu               contextMenu;
    std::array<std::unique_ptr<Label>, 10> freqLabels;
    String freqLabelStrings[10] = {"30", "50", "100", "200", "500", "1K", "2K", "5K", "10K", "20K"};
    Colour freqLabelColor = Colour(0xff3AE6D1);
};
