/*
  ==============================================================================

    AutoLabel.cpp
    Created: 13 Feb 2020 12:54:21pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "AutoLabel.h"

const String AutoLabel::propertyName("AUTO_LABEL");

//==============================================================================
AutoLabel::AutoLabel(const String& name, const String& text) : Label(name, text)
{
    getProperties().set(AutoLabel::propertyName, true);
    
}

AutoLabel::~AutoLabel()
{
    
}


void AutoLabel::setBoundsBasedOnText(int x, int y, bool anchorRight)
{
    Font f = getLookAndFeel().getLabelFont(*this);
    float width = 1.5 * f.getStringWidthFloat(getText());
    float height = 1.5 * f.getHeight();
    
    if (anchorRight)
        setBounds(x - width, y, width, height);
    else
        setBounds(x, y, width, height);

    
}
