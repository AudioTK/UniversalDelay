/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace
{
constexpr gsl::index FILTERSIZE = 384000+1;
}

//==============================================================================
UniversalSyncDelayAudioProcessor::UniversalSyncDelayAudioProcessor()
    :
#ifndef JucePlugin_PreferredChannelConfigurations
      AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
                         ),
#endif
      inFilter(nullptr, 1, 0, false), delayFilter(FILTERSIZE),
      outFilter(nullptr, 1, 0, false),
      parameters(*this, nullptr, juce::Identifier("ATKUniversalSyncDelay"),
                 {std::make_unique<juce::AudioParameterInt>(
                      "delaynum", "Delay numerator", 1, 64, 1),
                  std::make_unique<juce::AudioParameterInt>(
                      "delaydenom", "Delay denominator", 1, 64, 4),
                  std::make_unique<juce::AudioParameterFloat>(
                      "blend", "Blend", 0.f, 100.0f, 100.0f),
                  std::make_unique<juce::AudioParameterFloat>(
                      "forward", "Feed forward", -100.0f, 100.0f, 50.0f),
                  std::make_unique<juce::AudioParameterFloat>(
                      "feedback", "Feed backward", -90.f, 90.0f, .0f)})
{
    delayFilter.set_input_port(0, &inFilter, 0);
    outFilter.set_input_port(0, &delayFilter, 0);
}

UniversalSyncDelayAudioProcessor::~UniversalSyncDelayAudioProcessor() = default;

//==============================================================================
const juce::String UniversalSyncDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool UniversalSyncDelayAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool UniversalSyncDelayAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool UniversalSyncDelayAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double UniversalSyncDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int UniversalSyncDelayAudioProcessor::getNumPrograms() { return 4; }

int UniversalSyncDelayAudioProcessor::getCurrentProgram()
{
    return lastParameterSet;
}

void UniversalSyncDelayAudioProcessor::setCurrentProgram(int index)
{
    if (index != lastParameterSet)
    {
        lastParameterSet = index;
        if (index == 0)
        {
            const char* preset0 =
                "<UniversalSyncDelay><PARAM id=\"delay\" value=\"1\" /><PARAM "
                "id=\"blend\" value=\"100\" /><PARAM id=\"forward\" "
                "value=\"50\" /> "
                "<PARAM id=\"feedback\" value=\"0\" /></UniversalSyncDelay>";
            juce::XmlDocument doc(preset0);

            auto el = doc.getDocumentElement();
            parameters.state = juce::ValueTree::fromXml(*el);
        }
        else if (index == 1)
        {
            const char* preset1 =
                "<UniversalSyncDelay><PARAM id=\"delay\" value=\"1\" /><PARAM "
                "id=\"blend\" value=\"100\" /><PARAM id=\"forward\" "
                "value=\"50\" /> "
                "<PARAM id=\"feedback\" value=\"10\" /></UniversalSyncDelay>";
            juce::XmlDocument doc(preset1);

            auto el = doc.getDocumentElement();
            parameters.state = juce::ValueTree::fromXml(*el);
        }
        else if (index == 2)
        {
            const char* preset2 =
                "<UniversalSyncDelay><PARAM id=\"delay\" value=\"1\" /><PARAM "
                "id=\"blend\" value=\"100\" /><PARAM id=\"forward\" "
                "value=\"0\" /> "
                "<PARAM id=\"feedback\" value=\"0\" /></UniversalSyncDelay>";
            juce::XmlDocument doc(preset2);

            auto el = doc.getDocumentElement();
            parameters.state = juce::ValueTree::fromXml(*el);
        }
    }
}

const juce::String UniversalSyncDelayAudioProcessor::getProgramName(int index)
{
    if (index == 0)
    {
        return "FIR comb filter";
    }
    if (index == 1)
    {
        return "IIR comb filter";
    }
    if (index == 2)
    {
        return "All pass";
    }
    if (index == 3)
    {
        return "Delay";
    }
    return {};
}

void UniversalSyncDelayAudioProcessor::changeProgramName(
    int index, const juce::String& newName)
{
}

//==============================================================================
void UniversalSyncDelayAudioProcessor::prepareToPlay(double dbSampleRate,
                                                     int samplesPerBlock)
{
    sampleRate = std::lround(dbSampleRate);

    if (sampleRate != inFilter.get_output_sampling_rate())
    {
        inFilter.set_input_sampling_rate(sampleRate);
        inFilter.set_output_sampling_rate(sampleRate);
        delayFilter.set_input_sampling_rate(sampleRate);
        delayFilter.set_output_sampling_rate(sampleRate);
        outFilter.set_input_sampling_rate(sampleRate);
        outFilter.set_output_sampling_rate(sampleRate);
    }
    outFilter.dryrun(samplesPerBlock);
}

void UniversalSyncDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool UniversalSyncDelayAudioProcessor::isBusesLayoutSupported(
    const juce::BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void UniversalSyncDelayAudioProcessor::processBlock(
    juce::AudioSampleBuffer& buffer, juce::MidiBuffer& midiMessages)
{
    bool updateDelay = false;
    if (*parameters.getRawParameterValue("delaynum") != old_numerator)
    {
        old_numerator = *parameters.getRawParameterValue("delaynum");
        updateDelay = true;
    }
    if (*parameters.getRawParameterValue("delaydenom") != old_denominator)
    {
        old_denominator = *parameters.getRawParameterValue("delaydenom");
        updateDelay = true;
    }
    if (auto* head = getPlayHead())
    {
        juce::AudioPlayHead::CurrentPositionInfo info;
        if (head->getCurrentPosition(info) && info.bpm != 0 &&
            info.bpm != old_tempo)
        {
            old_tempo = info.bpm;
            updateDelay = true;
        }
    }
    if (updateDelay)
    {
        auto delay = static_cast<gsl::index>(
            delayFilter.get_input_sampling_rate() * (60 / old_tempo) * 4 *
            old_numerator / old_denominator);
        delayFilter.set_delay(std::min(delay, FILTERSIZE-1));
    }
    if (*parameters.getRawParameterValue("blend") != old_blend)
    {
        old_blend = *parameters.getRawParameterValue("blend");
        delayFilter.set_blend(old_blend / 100.);
    }
    if (*parameters.getRawParameterValue("forward") != old_forward)
    {
        old_forward = *parameters.getRawParameterValue("forward");
        delayFilter.set_feedforward(old_forward / 100.);
    }
    if (*parameters.getRawParameterValue("feedback") != old_feedback)
    {
        old_feedback = *parameters.getRawParameterValue("feedback");
        delayFilter.set_feedback(old_feedback / 100.);
    }

    const int totalNumInputChannels = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    assert(totalNumInputChannels == totalNumOutputChannels);
    assert(totalNumOutputChannels == 1);

    inFilter.set_pointer(buffer.getReadPointer(0), buffer.getNumSamples());
    outFilter.set_pointer(buffer.getWritePointer(0), buffer.getNumSamples());

    outFilter.process(buffer.getNumSamples());
}

//==============================================================================
bool UniversalSyncDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* UniversalSyncDelayAudioProcessor::createEditor()
{
    return new UniversalSyncDelayAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void UniversalSyncDelayAudioProcessor::getStateInformation(
    juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    xml->setAttribute("version", "1");
    copyXmlToBinary(*xml, destData);
}

void UniversalSyncDelayAudioProcessor::setStateInformation(const void* data,
                                                           int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(
        getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName(parameters.state.getType()))
        {
            if (xmlState->getStringAttribute("version") == "1")
            {
                parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
            }
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new UniversalSyncDelayAudioProcessor();
}
