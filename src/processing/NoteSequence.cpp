

#include "NoteSequence.h"


Array<int> NoteSequence::noteValues({36, 38, 40, 41, 43, 45, 47, 48});

int noteSort(const Note &n1, const Note &n2)
{
    return n1.startTime < n2.startTime;
}

NoteSequence::NoteSequence()
{
    
}

std::string NoteSequence::toString()
{
    std::string s;
    for (int i = 0; i < notes.size(); i++)
    {
        s += notes[i].toString();
    }

    return s;
}

void NoteSequence::addNote(Note n)
{
    notes.push_back(n);
}

void NoteSequence::addNote(int pitch, double startTime, double endTime, int velocity)
{
    notes.push_back(Note(pitch, velocity, startTime, endTime));
}

void NoteSequence::removeNote(int pitch, double time)
{
    for (int i = 0; i < notes.size(); i++){
        if (notes[i].pitch == pitch && notes[i].startTime == time)
        {
            notes.erase(notes.begin()+i);
        }
    }
}

bool NoteSequence::checkAndRemoveNote(int pitch, double time)
{
    for (int i = 0; i < notes.size(); i++)
    {
        if (notes[i].pitch == pitch && notes[i].startTime == time)
        {
            notes.erase(notes.begin() + i);
            return true;
        }
    }
    return false;
}

bool NoteSequence::isNotePresent(int pitch, double time)
{
    for (int i = 0; i < notes.size(); i++)
    {
        if (notes[i].pitch == pitch && notes[i].startTime == time)
        {
            return true;
        }
    }
    return false;
}

std::vector<Note> NoteSequence::getNotes()
{
    return notes;
}

ValueTree NoteSequence::toValueTree()
{
    ValueTree tree { "note_sequence", {{ "length", getLength() }},
      {
      }
    };
    
    for (int i = 0; i < getLength(); i++){
        ValueTree noteTree { "Note", {{ "pitch", notes[i].pitch}, { "start_time", notes[i].startTime}, { "velocity", notes[i].velocity}},
          {
          }
        };
        
        tree.addChild(noteTree, -1, nullptr);
    }
    
    return tree;
}

void NoteSequence::fromValueTree(ValueTree tree)
{
    for (int i = 0; i < tree.getNumChildren(); i++){
        
        int pitch = tree.getChild(i).getPropertyAsValue("pitch", nullptr).getValue();
        int velocity = tree.getChild(i).getPropertyAsValue("velocity", nullptr).getValue();
        int startTime = tree.getChild(i).getPropertyAsValue("start_time", nullptr).getValue();
        
        notes.push_back(Note(pitch, velocity, startTime, startTime + 1));
    }
}


double NoteSequence::ppqToSecs(double ppq, int tempo)
{
    return (double)ppq * (15.f / double(tempo));
}

int NoteSequence::ppqToSamples(double ppq, int tempo, double sampleRate)
{
    double secsPerMeasure = 4 * (60.0 / double(tempo));
    return sampleRate * ppq * secsPerMeasure;
}

