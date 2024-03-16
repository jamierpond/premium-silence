#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>

struct Parameters
{
    void add(juce::AudioProcessor& processor) const
    {
        processor.addParameter(gain);
        processor.addParameter(silence_enabled);
    }

    //Raw pointers. They will be owned by either the processor or the APVTS (if you use it)
    juce::AudioParameterFloat* gain =
        new juce::AudioParameterFloat({"Amount", 1}, "Amount", 0.f, 1.f, 0.5f);

    juce::AudioParameterBool* silence_enabled =
        new juce::AudioParameterBool({"Silence", 1}, "Silence", true);
};
