/*
 ==============================================================================
 
 OrionGlobalVars.h
 Created: 11 Jun 2019 11:02:17pm
 Author:  Lei Li
 
 ==============================================================================
 */

#pragma once

int const OrionGlobalWidth = 900;
int const OrionGlobalHeight = 675;

static int OrionGlobalTabIndex = 3;

namespace orion
    {
    const int defaultWidth = 900;
    const int defaultHeight = 675;
    
    enum DrumPart : int
    {
        Kick = 0,
        Snare,
        HHC,
        HHO,
        Clap
    };
}
