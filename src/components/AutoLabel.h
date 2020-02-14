/*
  ==============================================================================

    AutoLabel.h
    Created: 13 Feb 2020 12:54:21pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class AutoLabel : public Label
{
public:
    static const String propertyName;
    
    AutoLabel(const String&, const String&);
    ~AutoLabel();
    
    void setBoundsBasedOnText(int x, int y, bool anchorRight = false);

private:     
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AutoLabel)
};
