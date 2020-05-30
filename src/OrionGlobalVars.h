/*
 ==============================================================================
 
 OrionGlobalVars.h
 Created: 11 Jun 2019 11:02:17pm
 Author:  Lei Li
 
 ==============================================================================
 */

#pragma once

//--- Height/Width = 3/5 --- //
int const OrionGlobalWidth = 830;
int const OrionGlobalHeight = 498;

static int OrionGlobalTabIndex = 3;

namespace orion
    {
    const int defaultWidth = 830;
    const int defaultHeight = 498;
    
    enum DrumPart : int
    {
        Kick = 0,
        Snare,
        HHC,
        HHO,
        Clap
    };
    
    enum MidiNotes : int
    {
        kick = 36,
        snare = 38,
        clap = 39,
        snap = 46,
        perc = 41,
        hhc = 42,
        hho = 43,
        crash = 50
    };
    
    enum Tabs : int
    {
        kickTab = 0,
        snareTab,
        clapTab,
        percTab,
        snapTab,
        hhcTab,
        hhoTab,
        crashTab
    };

}
