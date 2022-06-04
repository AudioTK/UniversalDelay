/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

#include <ATKJUCEComponents/Delay/SyncUniversalFixedDelayFilter.h>

//==============================================================================
/**
 */
class UniversalSyncDelayAudioProcessorEditor : public juce::AudioProcessorEditor
{
  public:
    UniversalSyncDelayAudioProcessorEditor(
        UniversalSyncDelayAudioProcessor& p,
        juce::AudioProcessorValueTreeState& paramState);
    ~UniversalSyncDelayAudioProcessorEditor();

    //==============================================================================
    void resized() override;
    void paint(juce::Graphics& g) override;

  private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    UniversalSyncDelayAudioProcessor& processor;
    juce::AudioProcessorValueTreeState& paramState;

    ATK::juce::SyncUniversalFixedDelayFilterComponent syncDelay;
};
