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
const int HHCPitch   = 42;
const int HHOPitch   = 46;
const int CrashPitch = 48;

// Master Meters
float globalOutputMeterL = 0.0f;
float globalOutputMeterR = 0.0f;

// Instruments
int   instrumetSerial = 0;
int   instrumetOffSerial = 0;
float masterVolumeCoefficient = 0.75f;
bool  instrumentsSoloStates        [8] = {false, false, false, false, false, false, false, false};
bool  instrumentsMuteStates        [8] = {false, false, false, false, false, false, false, false};
float instrumentsVolumeCoefficient [8] = {0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f};
float instrumentsPanCoefficient    [8] = {0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f};

// FX Switch
bool  compSwitches                 [8] = {false, false, false, false, false, false, false, false};
bool  reverbSwitches               [8] = {false, false, false, false, false, false, false, false};
bool  delaySwitches                [8] = {false, false, false, false, false, false, false, false};

// Reverb
float reverbDryCoefficient         [8] = {0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f};
float reverbPredelayCoefficient    [8] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
float reverbDecayCoefficient       [8] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
float reverbSizeCoefficient        [8] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
float reverbColorCoefficient       [8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};


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

// Master Meters
extern float globalOutputMeterL;
extern float globalOutputMeterR;

// Instruments
extern int   instrumetSerial;
extern int   instrumetOffSerial;
extern float masterVolumeCoefficient;
extern bool  instrumentsSoloStates[];
extern bool  instrumentsMuteStates[];
extern float instrumentsVolumeCoefficient[];
extern float instrumentsPanCoefficient[];

// FX Switch
extern bool  compSwitches   [];
extern bool  reverbSwitches [];
extern bool  delaySwitches  [];

// Reverb
extern float reverbDryCoefficient         [];
extern float reverbPredelayCoefficient    [];
extern float reverbDecayCoefficient       [];
extern float reverbSizeCoefficient        [];
extern float reverbColorCoefficient       [];

#endif



