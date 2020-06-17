/*
 ==============================================================================
 
 OrionGlobalVars.h
 Created: 11 Jun 2019 11:02:17pm
 Author:  Lei Li
 
 ==============================================================================
 */

#pragma once

//--- Height/Width = 3/5 --- //
int const OrionGlobalWidth = 1080;
int const OrionGlobalHeight = 648;

static int OrionGlobalTabIndex = 3;

namespace orion
{
    const int defaultWidth = 1080;
    const int defaultHeight = 648;
    
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
        perc = 41,
        snap = 42,
        hhc = 43,
        hho = 44,
        crash = 46
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


//float masterVolumeCoefficient = 0.75f;
