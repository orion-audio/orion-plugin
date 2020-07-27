#ifndef NOTE_SEQUENCE_H
#define NOTE_SEQUENCE_H

#include "Note.h"
#include <vector>
#include <iostream>
#include <array>
#include "JuceHeader.h"


class NoteSequence
{
public:
    
    enum SubDivision : int {
        half = 2,
        quarter = 4,
        eighth = 8,
        tripletEigth = 12,
        sixteenth = 16,
        tripletSixteenth = 24,
        thirtysecond = 32
    };
//    static int noteValues[8];
    static Array<int> noteValues;
    NoteSequence();
        
    int getTempo() { return tempo; }

    int getLength() { return notes.size(); }
    
    void addNote(Note n);
    void addNote(int pitch, double startTime, double endTime, int velocity = 100);
    void removeNote(int pitch, double time);
    
    bool isNotePresent(int pitch, double time);
    bool checkAndRemoveNote(int pitch, double time);
    
    
    std::vector<Note> getNotes();
        
    std::string toString();
    
    ValueTree toValueTree();
    void fromValueTree(ValueTree);

    
    SubDivision getSubdivisionForVoice(int voice) { return voiceSubdivisions[voice]; };
    void setSubdivisionForVoice(int voice, SubDivision subDivision) { voiceSubdivisions[voice] = subDivision; };
    static double ppqToSecs(double ppq, int tempo);
    static int ppqToSamples(double ppq, int tempo, SubDivision subdivision, double sampleRate);

    

private:
    int tempo = 120;
    std::vector<Note> notes;
    std::array<SubDivision, 6> voiceSubdivisions;

};
#endif
    
