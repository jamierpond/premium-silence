#pragma once

#include "PluginProcessor.h"

class PremiumSilenceAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit PremiumSilenceAudioProcessorEditor(PremiumSilenceAudioProcessor&);

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    juce::GenericAudioProcessorEditor editor {processor};
};
