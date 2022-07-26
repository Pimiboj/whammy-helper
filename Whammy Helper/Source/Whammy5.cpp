/*
  ==============================================================================

    Whammy5.cpp
    Created: 25 Jul 2022 4:54:15pm
    Author:  pimvl

  ==============================================================================
*/

#include "Whammy5.h"

Whammy5::Whammy5(uint8_t midiChannel)
    : m_midiChannel(midiChannel)
{

}

juce::MidiBuffer Whammy5::Pitch(int8_t pitch, int sampleNumber)
{
    juce::MidiBuffer outputBuffer;

    // TODO set correct values for the pitch parameter
    outputBuffer.addEvent(juce::MidiMessage::programChange(m_midiChannel, 60 + pitch), sampleNumber);
    outputBuffer.addEvent(juce::MidiMessage::controllerEvent(m_midiChannel, 11, 60 + pitch), sampleNumber);

    return outputBuffer;
}