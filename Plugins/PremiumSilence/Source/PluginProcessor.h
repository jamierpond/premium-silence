#pragma once

#include "MassivelyMultichannelAudioProcessor.h"

class PremiumSilenceAudioProcessor
    : public MassivelyMultichannelAudioProcessor
    , public juce::AudioProcessorValueTreeState::Listener
{
public:
    PremiumSilenceAudioProcessor();

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    void parameterChanged(const juce::String& parameterID, float newValue) override
    {
        if (parameterID == "Silence")
        {
            bool shouldBeSilent = newValue > 0.5f;
            if (shouldBeSilent)
            {
                smoothGain.setTargetValue(0.0f);
            }
            else
            {
                smoothGain.setTargetValue(1.0f);
            }
        }
    }

    juce::AudioProcessorValueTreeState parameters;

private:
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> smoothGain {1.0f};
};
