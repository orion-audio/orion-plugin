/*
  ==============================================================================

    Sequencer.cpp
    Created: 8 Nov 2019 1:53:40am
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "Sequencer.h"

Sequencer::Sequencer(std::vector<Layout> layouts)
{
    formatManager.registerBasicFormats();

    sequence.reset(new NoteSequence());
    
    unsigned long numVoices = layouts.size();
    
    sampler.clearVoices();
    for (int i = 0; i < numVoices; i++)
    {
        sampler.addVoice(new SamplerVoice());
        createSynthesizerSound(layouts[i]);
        sampler.addSound(samplerSounds[i]);
    }
    
}

void Sequencer::prepareToPlay(double sampleRate)
{
    lastSampleRate = sampleRate;
    sampler.setCurrentPlaybackSampleRate(sampleRate);
}

void Sequencer::processBlock(AudioPlayHead* p, AudioBuffer<float> &buffer, MidiBuffer &midiBuffer)
{
    playhead = p;
    
    int numSamples = buffer.getNumSamples();
    if (playhead == nullptr)
        return;
    

    addToBufferIfNeeded(0, numSamples, midiBuffer);
    
    sampler.renderNextBlock(buffer, midiBuffer, 0, buffer.getNumSamples());
}
            
void Sequencer::addToBufferIfNeeded(int which, int samplesPerBlock, MidiBuffer &midiBuffer)
{
    // get current position
    AudioPlayHead::CurrentPositionInfo currentPos;
    playhead->getCurrentPosition(currentPos);
    if (!currentPos.isPlaying)
        return;
    long long posInSamples = currentPos.timeInSamples;
    posInSamples %= NoteSequence::ppqToSamples(totalLength, 120, lastSampleRate);
    auto notes = sequence->getNotes();
    
    int loopEnd = NoteSequence::ppqToSamples(totalLength, sequence->getTempo(), lastSampleRate);
    
    // iterate through all notes
    for (int i = 0; i < notes.size(); i++){
        int beatInSamples = NoteSequence::ppqToSamples(notes[i].startTime, sequence->getTempo(), lastSampleRate);
        
        // check first beat
        if (posInSamples + samplesPerBlock >= loopEnd && posInSamples <= loopEnd && notes[i].startTime == 0)
        {
            DBG("beat 1");
            long long offset = loopEnd - posInSamples;
            midiBuffer.addEvent(MidiMessage::noteOn(1, notes[i].pitch, .8f), offset);
        }
        
        // check all other beats
        else if (beatInSamples > posInSamples &&
            beatInSamples < posInSamples + samplesPerBlock)
        {
            long long offset = beatInSamples - posInSamples;
            midiBuffer.addEvent(MidiMessage::noteOn(1, notes[i].pitch, .8f), offset);
        }
    }
}

ValueTree Sequencer::getStateInformation()
{
    return sequence->toValueTree();
}

void Sequencer::setStateInformation(ValueTree tree)
{
    sequence->fromValueTree(tree);
}

void Sequencer::setNewSequence(NoteSequence* newSequence)
{
    sequence.reset(newSequence);
//    for (int i = 0; i < listeners.size(); i++)
//    {
//        MessageManager::callAsync([&]{ listeners[i]->sequenceChanged(); });
//
//    }
    for (int i = 0; i < listeners.size(); i++){
        listeners[i]->sequenceChanged();
    }

}

void Sequencer::swapSequences(Sequencer &otherSequencer, bool clearOther)
{
    sequence.swap(otherSequencer.getSequenceForSwap());
    if (clearOther)
        otherSequencer.clearSequence();
    for (int i = 0; i < listeners.size(); i++){
        listeners[i]->sequenceChanged();
    }
}

void Sequencer::clearSequence()
{
    sequence.reset(new NoteSequence());
    for (int i = 0; i < listeners.size(); i++){
        listeners[i]->sequenceChanged();
    }

}

std::unique_ptr<NoteSequence>& Sequencer::getSequenceForSwap()
{
    return sequence;
}

void Sequencer::addListener(Listener* l)
{
    listeners.push_back(l);
}

void Sequencer::removeListener(Listener* l)
{
    for (int i = 0; i < listeners.size(); i++)
    {
        if (listeners[i] == l)
            listeners.erase(listeners.begin()+i);
    }
}

void Sequencer::addNote(Note n)
{
    sequence->addNote(n);
}

void Sequencer::removeNote(Note n)
{

}

void Sequencer::createSynthesizerSound(Sequencer::Layout layout)
{
    std::unique_ptr<AudioFormatReader> reader;
    BigInteger range;
    range.setBit(layout.midiNote);
    reader.reset(formatManager.createReaderFor (new MemoryInputStream(layout.data, layout.size, false)));
    samplerSounds.push_back(new SamplerSound(layout.name, *reader.get(), range, layout.midiNote, 0, 10, 10.0));
}


