#pragma once

#include "MassivelyMultichannelAudioProcessor.h"

class PremiumSilenceAudioProcessor
  : public MassivelyMultichannelAudioProcessor
{
public:
    PremiumSilenceAudioProcessor();

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState parameters;
private:
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear>
      smoothGain{1.0f};
};
