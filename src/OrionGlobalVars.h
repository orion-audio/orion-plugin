/*
 ==============================================================================
 
 OrionGlobalVars.h
 Created: 11 Jun 2019 11:02:17pm
 Author:  Lei Li
 
 ==============================================================================
 */
#include "GlobalCoefficients.h"
#pragma once

//--- Height/Width = 3/5 --- //
int const OrionGlobalWidth = 1080;//1080//800
int const OrionGlobalHeight = 648;//648//480

static int OrionGlobalTabIndex = 3;

namespace orion
{
    const int defaultWidth = 1080;
    const int defaultHeight = 648;
    
//    enum DrumPart : int
//    {
//        Kick = 0,
//        Snare,
//        HHC,
//        HHO,
//        Clap
//    };
    
    enum MidiNotes : int
    {
        kick  = 36,
        snare = 38,
        clap  = 40,
        perc  = 41,
        snap  = 43,
        hhc   = 45,
        hho   = 47,
        crash = 48
    };
    
    enum Tabs : int
    {
        kickTab  = 0,
        snareTab = 1,
        clapTab  = 2,
        percTab  = 3,
        snapTab  = 4,
        hhoTab   = 5,
        hhcTab   = 6,
        crashTab = 7
    };
    

}


//float masterVolumeCoefficient = 0.75f;
