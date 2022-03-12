/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

#include <atk_core/atk_core.h>
#include <atk_delay/atk_delay.h>

#include <memory>

//==============================================================================
/**
 */
class UniversalSyncDelayAudioProcessor : public juce::AudioProcessor
{
  public:
    //==============================================================================
    UniversalSyncDelayAudioProcessor();
    ~UniversalSyncDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioSampleBuffer&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool isMidiEffect() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

  private:
    ATK::InPointerFilter<float> inFilter;
    ATK::UniversalFixedDelayLineFilter<double> delayFilter;
    ATK::OutPointerFilter<float> outFilter;

    juce::AudioProcessorValueTreeState parameters;
    long sampleRate;
    int lastParameterSet;

    int old_numerator{0};
    int old_denominator{0};
    float old_tempo{120};
    float old_blend{100};
    float old_forward{0};
    float old_feedback{0};
};
