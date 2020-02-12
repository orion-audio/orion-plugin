/*
  ==============================================================================

    DragAndDropButton.h
    Created: 6 Feb 2020 4:34:15pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class DragAndDropButton : public ImageButton, public FileDragAndDropTarget
{
public:
    DragAndDropButton (const String& name = String()) : ImageButton(name)
    {
         
    }

    bool isInterestedInFileDrag(const juce::StringArray &files) override { return true; }
    
    void filesDropped(const juce::StringArray &files, int x, int y) override
    {
        onFilesDropped(files[0]);
    }
    
    std::function<void(File)> onFilesDropped;

    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DragAndDropButton)
};
