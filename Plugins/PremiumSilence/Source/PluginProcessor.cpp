#include "PluginProcessor.h"
#include "PluginEditor.h"

PremiumSilenceAudioProcessor::PremiumSilenceAudioProcessor()
          : parameters (*this, nullptr, juce::Identifier ("APVTSTutorial"),
                      {
                          std::make_unique<juce::AudioParameterFloat> (juce::ParameterID("Amount", 1), // parameterID
                                                                       "Amount",            // parameter name
                                                                       0.0f,              // minimum value
                                                                       1.0f,              // maximum value
                                                                       0.5f),             // default value
                          std::make_unique<juce::AudioParameterBool> (juce::ParameterID("Silence", 1), // parameterID
                                                                      "Silence",     // parameter name
                                                                      false)              // default value
                      })
{
}

void PremiumSilenceAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                                juce::MidiBuffer& midiMessages)

{
    auto amount = parameters.getRawParameterValue ("Amount");
    juce::ignoreUnused(midiMessages, amount);
    auto silent = parameters.getRawParameterValue ("Silence");
    bool shouldBeSilent = silent->load() > 0.5f;

    if (shouldBeSilent)
        buffer.clear();
}

juce::AudioProcessorEditor* PremiumSilenceAudioProcessor::createEditor()
{
    return new PremiumSilenceAudioProcessorEditor(*this);
}

void PremiumSilenceAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void PremiumSilenceAudioProcessor::setStateInformation(const void* data,
                                                          int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PremiumSilenceAudioProcessor();
}
