/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WhammyHelperAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    WhammyHelperAudioProcessorEditor (WhammyHelperAudioProcessor&);
    ~WhammyHelperAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WhammyHelperAudioProcessor& audioProcessor;

    juce::ComboBox midiOutputSelector;
    juce::ComboBox realTuningSelector;
    juce::ComboBox midiChannelSelector;
    juce::ComboBox whammyVersionSelector;

    void fillMidiOutputSelector();
    void fillTuningSelector();
    void fillMidiChannelSelector();
    void fillWhammyVersionSelector();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WhammyHelperAudioProcessorEditor)
};
