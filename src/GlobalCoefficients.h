/*
  ==============================================================================

    GlobalCoefficients.h
    Created: 16 Jun 2020 8:54:22pm
    Author:  Lei Li

  ==============================================================================
*/


#ifdef __COEFFICIENTSMAIN__

const int instrumentAmount = 8;

const int KickPitch  = 36;
const int SnarePitch = 38;
const int ClapPitch  = 40;
const int PercPitch  = 41;
const int SnapPitch  = 39;
const int HHOPitch   = 46;
const int HHCPitch   = 42;
const int CrashPitch = 48;

// SOLO & MUTE BUTTONS
int   instrumetSerial = 0;
float masterVolumeCoefficient = 0.75f;
bool  instrumentsSoloStates        [8] = {false, false, false, false, false, false, false, false};
bool  instrumentsMuteStates        [8] = {false, false, false, false, false, false, false, false};
float instrumentsVolumeCoefficient [8] = {0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f};
float instrumentsPanCoefficient    [8] = {0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f};

float globalOutputMeterL = 0.0f;
float globalOutputMeterR = 0.0f;

#else
extern const int instrumentAmount;

extern const int KickPitch;
extern const int SnarePitch;
extern const int ClapPitch;
extern const int PercPitch;
extern const int SnapPitch;
extern const int HHCPitch;
extern const int HHOPitch;
extern const int CrashPitch;



extern int   instrumetSerial;
extern float masterVolumeCoefficient;
extern bool  instrumentsSoloStates[];
extern bool  instrumentsMuteStates[];
extern float instrumentsVolumeCoefficient[];
extern float instrumentsPanCoefficient[];

extern float globalOutputMeterL;
extern float globalOutputMeterR;
#endif



