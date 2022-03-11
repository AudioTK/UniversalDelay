/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

#include <ATKJUCEComponents/JUCE/ImageLookAndFeel.h>
#include <ATKJUCEComponents/JUCE/Slider.h>

//==============================================================================
/**
 */
class UniversalDelayAudioProcessorEditor: public juce::AudioProcessorEditor
{
public:
  UniversalDelayAudioProcessorEditor(UniversalDelayAudioProcessor& p, juce::AudioProcessorValueTreeState& paramState);
  ~UniversalDelayAudioProcessorEditor();

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  UniversalDelayAudioProcessor& processor;
  juce::AudioProcessorValueTreeState& paramState;

    ATK::juce::ImageLookAndFeel knobSym;
    ATK::juce::ImageLookAndFeel knobAsym;
  juce::Image bckgndImage;

  ATK::juce::SliderComponent delayLevel;
  ATK::juce::SliderComponent blendLevel;
  ATK::juce::SliderComponent forwardLevel;
  ATK::juce::SliderComponent feedbackLevel;
};
