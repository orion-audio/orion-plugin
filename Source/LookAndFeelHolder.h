/*
  ==============================================================================

    LookAndFeelHolder.h
    Created: 20 Oct 2019 2:43:47pm
    Author:  Quin Scacheri

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

template< typename T>
class LookAndFeelHolder
{
public:
    LookAndFeelHolder()
    {
        LookAndFeel::setDefaultLookAndFeel(&laf);
    }
    
private:
    T laf;
};
