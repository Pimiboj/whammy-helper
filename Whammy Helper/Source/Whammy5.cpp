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
    // TODO Fill entire map
    m_settingsMap[-24] = Whammy5Settings(0, 0);
    m_settingsMap[-23] = Whammy5Settings(0, 0);
    m_settingsMap[-22] = Whammy5Settings(0, 0);
    m_settingsMap[-21] = Whammy5Settings(0, 0);
    m_settingsMap[-20] = Whammy5Settings(0, 0);
    m_settingsMap[-19] = Whammy5Settings(0, 0);
    m_settingsMap[-18] = Whammy5Settings(0, 0);
    m_settingsMap[-17] = Whammy5Settings(0, 0);
    m_settingsMap[-16] = Whammy5Settings(0, 0);
    m_settingsMap[-15] = Whammy5Settings(0, 0);
    m_settingsMap[-14] = Whammy5Settings(0, 0);
    m_settingsMap[-13] = Whammy5Settings(0, 0);

    m_settingsMap[-12] = Whammy5Settings(7, 127);   // TEST
    m_settingsMap[-11] = Whammy5Settings(7, 116);   // TEST
    m_settingsMap[-10] = Whammy5Settings(7, 106);   // TEST
    m_settingsMap[-9] = Whammy5Settings(7, 95);     // TEST
    m_settingsMap[-8] = Whammy5Settings(7, 85);     // TEST
    m_settingsMap[-7] = Whammy5Settings(6, 127);    // TEST
    m_settingsMap[-6] = Whammy5Settings(6, 109);    // TEST
    m_settingsMap[-5] = Whammy5Settings(5, 127);    // DONE
    m_settingsMap[-4] = Whammy5Settings(5, 101);    // TEST
    m_settingsMap[-3] = Whammy5Settings(5, 76);     // DONE
    m_settingsMap[-2] = Whammy5Settings(4, 127);    // DONE
    m_settingsMap[-1] = Whammy5Settings(4, 64);     // DONE

    m_settingsMap[0] = Whammy5Settings(0, 0);       // DONE

    m_settingsMap[1] = Whammy5Settings(3, 25);
    m_settingsMap[2] = Whammy5Settings(3, 50);
    m_settingsMap[3] = Whammy5Settings(3, 76);
    m_settingsMap[4] = Whammy5Settings(3, 101);
    m_settingsMap[5] = Whammy5Settings(3, 127);
    m_settingsMap[6] = Whammy5Settings(2, 109);
    m_settingsMap[7] = Whammy5Settings(2, 127);
    m_settingsMap[8] = Whammy5Settings(1, 85);
    m_settingsMap[9] = Whammy5Settings(1, 95);      // DONE
    m_settingsMap[10] = Whammy5Settings(1, 106);
    m_settingsMap[11] = Whammy5Settings(1, 116);
    m_settingsMap[12] = Whammy5Settings(1, 127);

    m_settingsMap[13] = Whammy5Settings(0, 0);
    m_settingsMap[14] = Whammy5Settings(0, 0);
    m_settingsMap[15] = Whammy5Settings(0, 0);
    m_settingsMap[16] = Whammy5Settings(0, 0);
    m_settingsMap[17] = Whammy5Settings(0, 0);
    m_settingsMap[18] = Whammy5Settings(0, 0);
    m_settingsMap[19] = Whammy5Settings(0, 0);
    m_settingsMap[20] = Whammy5Settings(0, 0);
    m_settingsMap[21] = Whammy5Settings(0, 0);
    m_settingsMap[22] = Whammy5Settings(0, 0);
    m_settingsMap[23] = Whammy5Settings(0, 0);
    m_settingsMap[24] = Whammy5Settings(0, 0);

}

void Whammy5::ChangeMidiChannel(uint8_t channel)
{
    if (channel < 16)
    {
        m_midiChannel = channel;
    }
}

juce::MidiBuffer Whammy5::Pitch(int8_t pitch, int sampleNumber)
{
    juce::MidiBuffer outputBuffer;

    outputBuffer.addEvent(juce::MidiMessage::programChange(m_midiChannel, m_settingsMap[pitch].programNumber), sampleNumber);
    outputBuffer.addEvent(juce::MidiMessage::controllerEvent(m_midiChannel, 11, m_settingsMap[pitch].pedalPosition), sampleNumber);

    return outputBuffer;
}