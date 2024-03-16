#include "PluginProcessor.h"
#include "PluginEditor.h"

PremiumSilenceAudioProcessorEditor::PremiumSilenceAudioProcessorEditor(
    PremiumSilenceAudioProcessor& p)
    : AudioProcessorEditor(&p)
{
    addAndMakeVisible(editor);
    auto bgSize = background.getBounds();
    setSize(bgSize.getWidth(), bgSize.getHeight());
}

void PremiumSilenceAudioProcessorEditor::paint(juce::Graphics& g)
{
  g.drawImageAt(background, 0, 0);
}

void PremiumSilenceAudioProcessorEditor::resized()
{
    editor.setBounds(getLocalBounds());
}
