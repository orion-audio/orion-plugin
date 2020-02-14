/*
  ==============================================================================

    SequencerComponent.h
    Created: 8 Nov 2019 1:53:21am
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sequencer.h"

//==============================================================================
/*
*/
class SequencerComponent : public Component, public Timer, public Button::Listener, public Sequencer::Listener
{
public:
    
    struct LookAndFeelMethods
    {
    public:
        virtual void drawNoteBox(Graphics &g, SequencerComponent& s, Rectangle<float> bounds, bool isActive)
        {
            if (isActive)
                g.drawRect(bounds);
            else
                g.fillRect(bounds);
        }
    };
    
    enum ColourIds : int
    {
        backgroundColourId = 1,
        dividerColourId,
        beatColourOffId,
        beatColourOnId,
        playheadColourId
    };
    
    SequencerComponent(Sequencer &s);
    ~SequencerComponent();

    
    void paint (Graphics&) override;
    void paintGrid(Graphics&);
    
    void resized() override;
    
    virtual void colourChanged() override;
    
    void mouseUp(const MouseEvent& e) override;
    
    std::pair<int, int> checkClick(Point<float> p);

    void timerCallback() override;
    
    // button listener
    void buttonClicked(Button* b) override;
    void buttonStateChanged(Button* b) override;
    
    bool isSelected = true;
    
    virtual void sequenceChanged() override { repaint(); }
    
private:
    Sequencer &sequencer;
    std::unique_ptr<Slider> lengthSlider;
    
    int selectedRow = 0;
    
    bool shouldFlip = false;
    
    StringArray voiceNames;
    
    float gridPhase = 0;
    float gridDirection = 1;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SequencerComponent)
};
