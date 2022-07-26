/*
  ==============================================================================

    Whammy5.h
    Created: 25 Jul 2022 4:43:41pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "IPitchShifter.h"

class Whammy5 : public IPitchShifter
{
public:
    Whammy5(uint8_t midiChannel);

    juce::MidiBuffer Pitch(int8_t pitch, int sampleNumber);

private:
    uint8_t m_midiChannel;
};