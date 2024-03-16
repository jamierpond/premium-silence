#include "PluginProcessor.h"
#include "PluginEditor.h"

PremiumSilenceAudioProcessorEditor::PremiumSilenceAudioProcessorEditor(
    PremiumSilenceAudioProcessor& p)
    : AudioProcessorEditor(&p)
{
    addAndMakeVisible(editor);
    setSize(400, 300);
}

void PremiumSilenceAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PremiumSilenceAudioProcessorEditor::resized()
{
    editor.setBounds(getLocalBounds());
}
