/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
UniversalDelayAudioProcessorEditor::UniversalDelayAudioProcessorEditor(UniversalDelayAudioProcessor& p, juce::AudioProcessorValueTreeState& paramState)
  : juce::AudioProcessorEditor(&p)
  , processor(p)
  , paramState(paramState)
, knobSym(juce::ImageFileFormat::loadFrom(BinaryData::KNB02uni43_png, BinaryData::KNB02uni43_pngSize), 43, 43, 43)
, knobAsym(juce::ImageFileFormat::loadFrom(BinaryData::KNB02bi43_png, BinaryData::KNB02bi43_pngSize), 43, 43, 43)
, delayLevel(paramState, "delay", "Delay", &knobAsym)
  , blendLevel(paramState, "blend", "Blend", &knobAsym)
  , forwardLevel(paramState, "forward", "Forward", &knobSym)
  , feedbackLevel(paramState, "feedback", "Feedback", &knobSym)

{
  addAndMakeVisible(delayLevel);
  addAndMakeVisible(blendLevel);
  addAndMakeVisible(forwardLevel);
  addAndMakeVisible(feedbackLevel);

  bckgndImage = juce::ImageFileFormat::loadFrom(BinaryData::Background_png, BinaryData::Background_pngSize);

  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(300, 200);
}

UniversalDelayAudioProcessorEditor::~UniversalDelayAudioProcessorEditor() = default;

void UniversalDelayAudioProcessorEditor::paint(juce::Graphics& g)
{
  g.drawImageAt(bckgndImage, 0, 0);
}

void UniversalDelayAudioProcessorEditor::resized()
{
  delayLevel.setBounds(20, 80, 55, 55);
  blendLevel.setBounds(120, 40, 55, 55);
  forwardLevel.setBounds(120, 120, 55, 55);
  feedbackLevel.setBounds(220, 40, 55, 55);
}
