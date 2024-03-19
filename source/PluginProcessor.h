#pragma once

#include "MassivelyMultichannelAudioProcessor.h"
#include <cstdint>

static inline bool isApproxZero(float v) noexcept
{
      auto value = *reinterpret_cast<uint32_t*>(&v);
      constexpr uint32_t ifSetNotZero = 0b0'11000000'00000000'00000000'0000000;
      return (value & ifSetNotZero) == 0;
}



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
