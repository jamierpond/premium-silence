#pragma once

#include "MassivelyMultichannelAudioProcessor.h"

class PremiumSilenceAudioProcessor : public MassivelyMultichannelAudioProcessor
{
public:
    PremiumSilenceAudioProcessor();

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:

    juce::AudioProcessorValueTreeState parameters;
};
