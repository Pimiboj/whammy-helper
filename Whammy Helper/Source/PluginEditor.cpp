/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


WhammyHelperAudioProcessorEditor::WhammyHelperAudioProcessorEditor (WhammyHelperAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
    addAndMakeVisible(midiOutputSelector);
    fillMidiOutputSelector();

    addAndMakeVisible(realTuningSelector);
    fillTuningSelector();

    addAndMakeVisible(midiChannelSelector);
    fillMidiChannelSelector();

    addAndMakeVisible(whammyVersionSelector);
    fillWhammyVersionSelector();
}

WhammyHelperAudioProcessorEditor::~WhammyHelperAudioProcessorEditor()
{
}

void WhammyHelperAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Whammy Midi Helper", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText(audioProcessor.getNoteDifference(), getLocalBounds(), juce::Justification::centredBottom, 1);
}

void WhammyHelperAudioProcessorEditor::resized()
{
    const int margin = 10;
    const int height = 40;
    midiOutputSelector.setBounds(margin, margin, getWidth() - 2 * margin, height);
    realTuningSelector.setBounds(margin, height + (2 * margin), (getWidth() - 3 * margin) / 2, height);
    midiChannelSelector.setBounds((getWidth() + margin) / 2, height + (2 * margin), (getWidth() - 3 * margin) / 2, height);
    whammyVersionSelector.setBounds(margin, (2 * height) + (3 * margin), (getWidth() - 3 * margin) / 2, height);
}

void WhammyHelperAudioProcessorEditor::fillMidiOutputSelector()
{
    midiOutputSelector.clear();
    midiOutputSelector.setTextWhenNoChoicesAvailable("No MIDI Outputs Enabled");
    midiOutputSelector.addItemList(audioProcessor.getMidiOutputList(), 1);
}

void WhammyHelperAudioProcessorEditor::fillTuningSelector()
{
    realTuningSelector.clear();

    juce::StringArray tuningStringArray;
    for (int i = 21; i < 48; i++)
    {
        tuningStringArray.add(juce::MidiMessage::getMidiNoteName(i, true, true, 4));
    }

    realTuningSelector.addItemList(tuningStringArray, 1);
}

void WhammyHelperAudioProcessorEditor::fillMidiChannelSelector()
{
    midiChannelSelector.clear();

    juce::StringArray channelStringArray;
    for (int i = 1; i <= 16; i++)
    {
        channelStringArray.add(std::to_string(i));
    }

    midiChannelSelector.addItemList(channelStringArray, 1);
}

void WhammyHelperAudioProcessorEditor::fillWhammyVersionSelector()
{
    whammyVersionSelector.clear();

    juce::StringArray versionStringArray;
    versionStringArray.add("Whammy 4");
    versionStringArray.add("Whammy 5");
    versionStringArray.add("Whammy DT");

    whammyVersionSelector.addItemList(versionStringArray, 1);
}
