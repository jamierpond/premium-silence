#pragma once

#include "PluginProcessor.h"
#include "BinaryData.h"

class PremiumSilenceAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit PremiumSilenceAudioProcessorEditor(PremiumSilenceAudioProcessor&);

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    // juce::GenericAudioProcessorEditor editor {processor};

    juce::Image background = juce::ImageCache::getFromMemory(BinaryData::bg_text_png, BinaryData::bg_text_pngSize);

    juce::Slider amountSlider;
    juce::ToggleButton silenceButton;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<SliderAttachment> sliderAttachment;
    std::unique_ptr<ButtonAttachment> buttonAttachment;
};
