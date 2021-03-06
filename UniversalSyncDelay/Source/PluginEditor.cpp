/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
UniversalSyncDelayAudioProcessorEditor::UniversalSyncDelayAudioProcessorEditor(
    UniversalSyncDelayAudioProcessor& p,
    juce::AudioProcessorValueTreeState& paramState)
    : juce::AudioProcessorEditor(&p), processor(p), paramState(paramState),
      syncDelay(paramState, "delaynum", "delaydenom", "blend", "forward",
                "feedback")

{
    addAndMakeVisible(syncDelay);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(550, 200);
}

UniversalSyncDelayAudioProcessorEditor::
    ~UniversalSyncDelayAudioProcessorEditor() = default;

void UniversalSyncDelayAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with
    // a solid colour)
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setFont(juce::Font("Times New Roman", 30.0f,
                         juce::Font::bold | juce::Font::italic));
    g.setColour(juce::Colours::whitesmoke);
    g.drawText("Universal Sync Delay", 20, 10, 400, 30,
               juce::Justification::verticallyCentred);
}

void UniversalSyncDelayAudioProcessorEditor::resized()
{
    syncDelay.setBoundsRelative(0, 1. / 4, 1, 3. / 4);
}
