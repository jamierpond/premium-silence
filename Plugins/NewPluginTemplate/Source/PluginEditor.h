#pragma once
#include "BinaryData.h"

#include "PluginProcessor.h"
#include "BinaryData.h"

struct ButtonLf : juce::LookAndFeel_V4
{
  void drawToggleButton(juce::Graphics &g,
      juce::ToggleButton &button,
      bool ,
      bool ) override {
    auto bound = button.getLocalBounds();
    if (button.getToggleState()) {
      g.drawImage(buttonOn, bound.toFloat());
    } else {
      g.drawImage(buttonOff, bound.toFloat());
    }
  }

  juce::Image buttonOn = juce::ImageCache::getFromMemory(BinaryData::button_on_png, BinaryData::button_on_pngSize);
  juce::Image buttonOff = juce::ImageCache::getFromMemory(BinaryData::button_off_png, BinaryData::button_off_pngSize);
};


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

    ButtonLf buttonLf;
};
