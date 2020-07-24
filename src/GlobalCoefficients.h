/*
  ==============================================================================

    GlobalCoefficients.h
    Created: 16 Jun 2020 8:54:22pm
    Author:  Lei Li

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"

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

// Global Smaple Rate
double globalSampleRate = 44100;


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
File  instrumentSamplePathes       [8];

// Dropdown Type
int dropdownTabSerial = 0;

// Envelope
bool  envSwitches                  [8] = {false, false, false, false, false, false, false, false};

float envAttackCoefficient         [8] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};
float envDecayCoefficient          [8] = {1250.0f, 1250.0f, 1250.0f, 1250.0f, 1250.0f, 1250.0f, 1250.0f, 1250.0f};
float envSustainCoefficient        [8] = {750.0f, 750.0f, 750.0f, 750.0f, 750.0f, 750.0f, 750.0f, 750.0f};
float envReleaseCoefficient        [8] = {1250.0f, 1250.0f, 1250.0f, 1250.0f, 1250.0f, 1250.0f, 1250.0f, 1250.0f};

float envAttackBendCoefficient     [8] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
float envDecayBendCoefficient      [8] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
float envSustainBendCoefficient    [8] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
float envReleaseBendCoefficient    [8] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};


// FX Switch
bool  compSwitches                 [8] = {false, false, false, false, false, false, false, false};
bool  reverbSwitches               [8] = {false, false, false, false, false, false, false, false};
bool  delaySwitches                [8] = {false, false, false, false, false, false, false, false};

// Compressor
float compressorThreshCoefficient  [8] = {-60.0f, -60.0f, -60.0f, -60.0f, -60.0f, -60.0f, -60.0f, -60.0f};
float compressorRatioCoefficient   [8] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
float compressorAttackCoefficient  [8] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};
float compressorReleaseCoefficient [8] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};
float compressorGainCoefficient    [8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

// Reverb
float reverbDryCoefficient         [8] = {0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f};
float reverbPredelayCoefficient    [8] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
float reverbDecayCoefficient       [8] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
float reverbSizeCoefficient        [8] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
float reverbColorCoefficient       [8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

// Delay
float delayDryWetCoefficient       [8] = {0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f};
float delayTimeCoefficient         [8] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};
float delayFeedbackCoefficient     [8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float delayColorCoefficient        [8] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float delayPanCoefficient          [8] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f};


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

// Global Smaple Rate
extern double globalSampleRate;

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
extern File  instrumentSamplePathes[];

// Dropdown Type
extern int dropdownTabSerial;

// Envelope
extern bool  envSwitches                [];

extern float envAttackCoefficient       [];
extern float envDecayCoefficient        [];
extern float envSustainCoefficient      [];
extern float envReleaseCoefficient      [];

extern float envAttackBendCoefficient   [];
extern float envDecayBendCoefficient    [];
extern float envSustainBendCoefficient  [];
extern float envReleaseBendCoefficient  [];


// FX Switch
extern bool  compSwitches   [];
extern bool  reverbSwitches [];
extern bool  delaySwitches  [];

// Compressor
extern float compressorThreshCoefficient  [];
extern float compressorRatioCoefficient   [];
extern float compressorAttackCoefficient  [];
extern float compressorReleaseCoefficient [];
extern float compressorGainCoefficient    [];

// Reverb
extern float reverbDryCoefficient         [];
extern float reverbPredelayCoefficient    [];
extern float reverbDecayCoefficient       [];
extern float reverbSizeCoefficient        [];
extern float reverbColorCoefficient       [];

// Delay
extern float delayDryWetCoefficient       [];
extern float delayTimeCoefficient         [];
extern float delayFeedbackCoefficient     [];
extern float delayColorCoefficient        [];
extern float delayPanCoefficient          [];

#endif



