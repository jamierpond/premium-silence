#include "PluginProcessor.h"
#include "PluginEditor.h"

PremiumSilenceAudioProcessor::PremiumSilenceAudioProcessor()
    : parameters(*this,
                 nullptr,
                 juce::Identifier("APVTSTutorial"),
                 {
                     std::make_unique<juce::AudioParameterFloat>(
                         juce::ParameterID("Amount", 1), // parameterID
                         "Amount", // parameter name
                         0.0f, // minimum value
                         1.0f, // maximum value
                         0.5f), // default value
                     std::make_unique<juce::AudioParameterBool>(
                         juce::ParameterID("Silence", 1), // parameterID
                         "Silence", // parameter name
                         false) // default value
                 })
{
    parameters.addParameterListener("Silence", this);
}

void PremiumSilenceAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(sampleRate, samplesPerBlock);
    smoothGain.reset(sampleRate, 0.2);
}

void PremiumSilenceAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                                juce::MidiBuffer&)
{
    const auto currentValue = smoothGain.getCurrentValue();
    auto isOne = juce::approximatelyEqual(currentValue, 1.0f);
    if (isOne)
    {
        smoothGain.skip(buffer.getNumSamples());
        return;
    }

    auto isZero = juce::approximatelyEqual(currentValue, 0.0f);
    if (isZero)
    {
        buffer.clear();
        smoothGain.skip(buffer.getNumSamples());
        return;
    }

    smoothGain.applyGain(buffer, buffer.getNumSamples());
    smoothGain.skip(buffer.getNumSamples());
}

juce::AudioProcessorEditor* PremiumSilenceAudioProcessor::createEditor()
{
    return new PremiumSilenceAudioProcessorEditor(*this);
}

void PremiumSilenceAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PremiumSilenceAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PremiumSilenceAudioProcessor();
}
