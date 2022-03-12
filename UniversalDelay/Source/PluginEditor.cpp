/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
UniversalDelayAudioProcessorEditor::UniversalDelayAudioProcessorEditor(
    UniversalDelayAudioProcessor& p,
    juce::AudioProcessorValueTreeState& paramState)
    : juce::AudioProcessorEditor(&p), processor(p), paramState(paramState),
      knobSym(juce::ImageFileFormat::loadFrom(BinaryData::KNB02uni43_png,
                                              BinaryData::KNB02uni43_pngSize),
              43, 43, 43),
      knobAsym(juce::ImageFileFormat::loadFrom(BinaryData::KNB02bi43_png,
                                               BinaryData::KNB02bi43_pngSize),
               43, 43, 43),
      delayLevel(paramState, "delay", "Delay", &knobSym),
      blendLevel(paramState, "blend", "Blend", &knobSym),
      forwardLevel(paramState, "forward", "Forward", &knobAsym),
      feedbackLevel(paramState, "feedback", "Feedback", &knobAsym)

{
    addAndMakeVisible(delayLevel);
    addAndMakeVisible(blendLevel);
    addAndMakeVisible(forwardLevel);
    addAndMakeVisible(feedbackLevel);

    bckgndImage = juce::ImageFileFormat::loadFrom(
        BinaryData::Background_png, BinaryData::Background_pngSize);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(300, 100);
}

UniversalDelayAudioProcessorEditor::~UniversalDelayAudioProcessorEditor() =
    default;

void UniversalDelayAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.drawImageAt(bckgndImage, 0, 0);
}

void UniversalDelayAudioProcessorEditor::resized()
{
    delayLevel.setBounds(25, 26, 43, 43);
    blendLevel.setBounds(94, 26, 43, 43);
    forwardLevel.setBounds(163, 26, 43, 43);
    feedbackLevel.setBounds(232, 26, 43, 43);
}
