/*
  ==============================================================================

    GlobalCoefficients.h
    Created: 16 Jun 2020 8:54:22pm
    Author:  Lei Li

  ==============================================================================
*/

#ifdef __COEFFICIENTSMAIN__

    // SOLO & MUTE BUTTONS
    const int instrumentAmount = 8;
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
    extern int   instrumetSerial;
    extern float masterVolumeCoefficient;
    extern bool  instrumentsSoloStates[];
    extern bool  instrumentsMuteStates[];
    extern float instrumentsVolumeCoefficient[];
    extern float instrumentsPanCoefficient[];

    extern float globalOutputMeterL;
    extern float globalOutputMeterR;
#endif


