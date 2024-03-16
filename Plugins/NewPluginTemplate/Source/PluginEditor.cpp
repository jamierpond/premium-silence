#include "BinaryData.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"

PremiumSilenceAudioProcessorEditor::PremiumSilenceAudioProcessorEditor(
    PremiumSilenceAudioProcessor& p)
    : AudioProcessorEditor(&p)
{
    // addAndMakeVisible(editor);
    auto bgSize = background.getBounds().toFloat();
    auto bgWidth = bgSize.getWidth();
    auto bgHeight = bgSize.getHeight();

    auto ratio = bgWidth / bgHeight;

//     auto initialWidth = 800.0f;
//     auto initialHeight = initialWidth / ratio;

    setResizeLimits(400, int(400.0 / ratio), 1200, int(1200.0 / ratio));
    getConstrainer()->setFixedAspectRatio(ratio);
    setSize(800.0, int(800.0 / ratio));

    addAndMakeVisible(amountSlider);
    amountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);

    addAndMakeVisible(silenceButton);
    silenceButton.setButtonText("Silence");

    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        p.parameters, "Amount", amountSlider);

    buttonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        p.parameters, "Silence", silenceButton);


    setLookAndFeel(&buttonLf);
}

void PremiumSilenceAudioProcessorEditor::paint(juce::Graphics& g)
{
    // draw the image to fit the available space
    auto bound = getLocalBounds();
    g.drawImage(background, bound.toFloat());
}

void PremiumSilenceAudioProcessorEditor::resized()
{
    {
        auto bounds = getLocalBounds().toFloat();
        auto sliderBounds = bounds.removeFromRight(bounds.getWidth() / 4);
        amountSlider.setBounds(sliderBounds.toNearestInt());
    }

    {
        auto bounds = getLocalBounds().toFloat();
        auto buttonBounds = bounds.removeFromLeft(bounds.getWidth() / 4);
        silenceButton.setBounds(buttonBounds.toNearestInt());
    }
}
