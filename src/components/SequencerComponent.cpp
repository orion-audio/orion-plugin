/*
  ==============================================================================

    SequencerComponent.cpp
    Created: 8 Nov 2019 1:53:21am
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SequencerComponent.h"
#include "qtils.h"

#define NUM_VOICES 6

//==============================================================================
SequencerComponent::SequencerComponent(Sequencer &s) : sequencer(s)
{
    sequencer.addListener(this);
    
    setOpaque(true);
    
    this->shouldFlip = shouldFlip;
    
    startTimerHz(15);
    
    voiceNames.add("KICK");
    voiceNames.add("SNARE");
    voiceNames.add("HH-CLOSED");
    voiceNames.add("HH-OPEN");
    voiceNames.add("CRASH");
    voiceNames.add("CLAP");

    setColour(ColourIds::backgroundColourId, Colours::black);
    setColour(ColourIds::beatColourOffId, Colours::magenta);
    setColour(ColourIds::beatColourOnId, Colours::magenta);

    lengthSlider.reset(new Slider());
    lengthSlider->setSliderStyle(Slider::SliderStyle::Rotary);
    lengthSlider->setColour(Slider::ColourIds::rotarySliderFillColourId, findColour(ColourIds::beatColourOffId));
    lengthSlider->setColour(Slider::ColourIds::backgroundColourId, Colours::white);
}

SequencerComponent::~SequencerComponent()
{
}

void SequencerComponent::paint (Graphics& g)
{
    g.fillAll(findColour(ColourIds::backgroundColourId));
    paintGrid(g);
    
//    g.fillAll(Colours::black.withAlpha((.7f)));
}

void SequencerComponent::paintGrid(Graphics& g)
{
    SequencerComponent::LookAndFeelMethods* laf = dynamic_cast<SequencerComponent::LookAndFeelMethods*>(&getLookAndFeel());
    if (laf == nullptr)
        jassertfalse; // your look and feel must include the sequencer methods
    
    NoteSequence* sequence = sequencer.getNoteSequence();
    int totalLength = sequencer.getTotalLength();
    float xDist = (float)getWidth() / (totalLength + 1);
    float yDist = (float)getHeight() / NUM_VOICES;
    Rectangle<float> area(xDist, 0, xDist, yDist);
    
    for (int rows = 0; rows < NUM_VOICES; rows++)
    {
        
        for (int cols = 0; cols < totalLength; cols++)
        {
            bool active = false;
            g.setColour(findColour(ColourIds::beatColourOffId));
            if (sequence->isNotePresent(NoteSequence::noteValues[rows], cols))
                active = true;
            if (notesToBePlayed)
            laf->drawNoteBox(g, *this, area.withSizeKeepingCentre(xDist * .9, yDist * .9), active, false);

            area.translate(xDist, 0);
        }
        
        area.translate(0, yDist);
        area.setX(xDist);
    }
    Rectangle<float> selectedRowArea(0, 0, getWidth(), getHeight() / 8);
    
    selectedRowArea.translate(0, yDist * selectedRow);
    g.setColour(Colours::white.withAlpha(.4f));

    area.setBounds(0, 0, xDist, yDist);

    if (isSelected)
    {
        for (int i = 0; i < NUM_VOICES; i++)
        {
            g.setColour(Colours::white);
            g.drawFittedText(voiceNames[i], area.toNearestInt(), Justification::right, 1);
            g.setColour(Colours::white.withAlpha(gridPhase));
            g.drawRect(0.0, area.getY(), float(getWidth()), 1.f);
            area.translate(0, yDist);
        }
        
        g.drawRect(0.0, area.getY() - 1.f, float(getWidth()), 1.f);
        
        if (gridPhase + .05 * gridDirection >= 1 || gridPhase + .05 * gridDirection <= 0)
        {
            gridDirection *= -1;
        }
        
        gridPhase += gridDirection * .05;
        
        area.setBounds(xDist * 5, 0, 1, getHeight());
        
        for (int i = 1; i <= 3; i++)
        {
            g.setColour(Colours::white);
            g.drawRect(area);
            area.translate(xDist * 4, 0);
        }
    }
}

void SequencerComponent::resized()
{
    auto area = getLocalBounds();
    if (shouldFlip)
        area.removeFromBottom(getHeight() / 2);
    else
        area.removeFromTop(getHeight() / 2);
    
    area = area.withSizeKeepingCentre(area.getHeight(), area.getHeight());
//    lengthSlider->setBounds(area);
}


void SequencerComponent::mouseUp(const MouseEvent& e)
{
    Component::mouseUp(e);
    std::pair<int, int> result = checkClick(e.getMouseDownPosition().toFloat());

    if (result.first !=-1)
    {
        
        int pitch = NoteSequence::noteValues[result.first];
        int startTime = result.second;

        NoteSequence* sequence = sequencer.getNoteSequence();
        if (sequence->checkAndRemoveNote(pitch, startTime))
            DBG("removed");
        else
        {
            sequence->addNote(Note(pitch, 100, startTime, startTime + 1));
        }
    }
    
    repaint();
}


std::pair<int, int> SequencerComponent::checkClick(Point<float> p)
{
    int totalLength = sequencer.getTotalLength();
    float xDist = getWidth() / (totalLength + 1);
    float yDist = getHeight() / NUM_VOICES;
    
    Rectangle<float> area(xDist, 0, xDist, yDist);

    for (int rows = 0; rows < NUM_VOICES; rows++)
    {
        if (p.getY() > area.getBottom())
        {
            area.translate(0, yDist);
            continue;
        }
        for (int cols = 0; cols < totalLength; cols++){

            if (p.getX() > area.getRight())
            {
                area.translate(xDist, 0);
                continue;
            }

            if (area.contains(p))
            {
                selectedRow = rows;
                return std::pair<int, int>(rows, cols);
            }
        }
    }
    return std::pair<int, int>(-1, -1);
    
}

void SequencerComponent::colourChanged()
{
    if (isColourSpecified(ColourIds::beatColourOffId && lengthSlider != nullptr))
        lengthSlider->setColour(Slider::ColourIds::rotarySliderFillColourId, findColour(ColourIds::beatColourOffId));
}

void SequencerComponent::timerCallback()
{
    std::queue<Note>* noteQueue = &sequencer.lastNotesPlayed;
    for (int i = 0; i < noteQueue->size(); i++) {
        notesToBePlayed.push_back(noteQueue->front());
        noteQueue->pop();
    }
    lastBeat = notesToBePlayed.front().startTime;
    repaint();
}

void SequencerComponent::buttonClicked(Button* b)
{
    
}

void SequencerComponent::buttonStateChanged(Button* b)
{
    if (b->getToggleStateValue() == true)
        isSelected = true;
    else
        isSelected = false;
}

void SequencerComponent::notePlayed(int part, int beat) {
    
}
    
