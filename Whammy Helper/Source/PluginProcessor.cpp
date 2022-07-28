/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Whammy5.h"

//==============================================================================
WhammyHelperAudioProcessor::WhammyHelperAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // TODO change to create the correct implementation of a pitch shifter
    // TODO change the channel selection to be correct

    m_shifter = std::make_unique<Whammy5>(1);
}

WhammyHelperAudioProcessor::~WhammyHelperAudioProcessor()
{
}

//==============================================================================
const juce::String WhammyHelperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WhammyHelperAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WhammyHelperAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WhammyHelperAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WhammyHelperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WhammyHelperAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WhammyHelperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WhammyHelperAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WhammyHelperAudioProcessor::getProgramName (int index)
{
    return {};
}

void WhammyHelperAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WhammyHelperAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void WhammyHelperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WhammyHelperAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void WhammyHelperAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    if (!midiMessages.isEmpty() && m_shifter)
    {
        double sampleRate = getSampleRate();
        juce::MidiBuffer midiOutputBuffer;
        int rootNote = static_cast<int>(apvts.getRawParameterValue("Root Note")->load()) + 21;
        int midiChannel = static_cast<int>(apvts.getRawParameterValue("Midi Channel")->load()) + 1;
        m_shifter->ChangeMidiChannel(midiChannel);

        for (const juce::MidiBufferIterator::reference meta : midiMessages)
        {
            const juce::MidiMessage msg = meta.getMessage();

            if (msg.isNoteOn())
            {
                int noteDifference = msg.getNoteNumber() - rootNote;
                juce::MidiBuffer output = m_shifter->Pitch(noteDifference, msg.getTimeStamp());
                midiOutputBuffer.addEvents(output, 0, -1, 0);
            }
        }

        midiMessages.swapWith(midiOutputBuffer);
    }
}

int GetNoteNumberFromNoteName(juce::String name)
{
    static const char* const noteNames[] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B", "", "Db", "", "Eb", "", "", "Gb", "", "Ab", "", "Bb" };

    int keyNumber, octave = 0, numPos = name.indexOfAnyOf("01234567890-");

    if (numPos == 0)
        keyNumber = name.getIntValue();	//apparently already a number!

    else
    {
        if (numPos > 0)
        {
            octave = name.substring(numPos).getIntValue() + 1;
        }
        else
        {
            octave = 5;		//default to octave of middle C if none found
            numPos = name.length();
        }

        juce::String name(name.substring(0, numPos).trim().toUpperCase());

        keyNumber = juce::StringArray(noteNames, 12).indexOf(name) % 12;
    }

    return keyNumber + octave * 12;
}

//==============================================================================
bool WhammyHelperAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WhammyHelperAudioProcessor::createEditor()
{
    //return new WhammyHelperAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void WhammyHelperAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void WhammyHelperAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout WhammyHelperAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    juce::StringArray channelStringArray;
    for (int i = 1; i <= 16; i++)
    {
        channelStringArray.add(std::to_string(i));
    }
    layout.add(std::make_unique<juce::AudioParameterChoice>("Midi Channel", "Midi Channel", channelStringArray, 0));

    juce::StringArray tuningStringArray;
    for (int i = 21; i < 48; i++)
    {
        tuningStringArray.add(juce::MidiMessage::getMidiNoteName(i, true, true, 4));
    }
    layout.add(std::make_unique<juce::AudioParameterChoice>("Root Note", "Root Note", tuningStringArray, 0));

    return layout;
}

juce::StringArray WhammyHelperAudioProcessor::getMidiOutputList()
{
    juce::StringArray outList;

    juce::Array<juce::MidiDeviceInfo> devices = juce::MidiOutput::getAvailableDevices();

    for (auto output : devices)
    {
        outList.add(output.name);
    }

    return outList;
}

std::string WhammyHelperAudioProcessor::getNoteDifference()
{
    return std::to_string(m_noteDifference);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WhammyHelperAudioProcessor();
}
