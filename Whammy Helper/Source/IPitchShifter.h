/*
  ==============================================================================

    IPitchShifter.h
    Created: 25 Jul 2022 4:46:13pm
    Author:  pimvl

  ==============================================================================
*/

#pragma once

#include "stdint.h"
#include <JuceHeader.h>

class IPitchShifter
{
public:
    virtual ~IPitchShifter() {};

    virtual juce::MidiBuffer Pitch(int8_t pitch, int sampleNumber) = 0;
};