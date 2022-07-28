/*
  ==============================================================================

    Whammy5.h
    Created: 25 Jul 2022 4:43:41pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "IPitchShifter.h"

typedef struct Whammy5Settings
{
    uint8_t programNumber;
    uint8_t pedalPosition;
};

class Whammy5 : public IPitchShifter
{
public:
    Whammy5(uint8_t midiChannel);

    void ChangeMidiChannel(uint8_t channel);
    juce::MidiBuffer Pitch(int8_t pitch, int sampleNumber);

private:
    uint8_t m_midiChannel;
    std::unordered_map<int8_t, Whammy5Settings> m_settingsMap;
};