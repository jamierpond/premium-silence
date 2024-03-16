#pragma once
#include "BinaryData.h"
#include "PluginProcessor.h"
#include "BinaryData.h"

struct ButtonLf : juce::LookAndFeel_V4
{
    void drawToggleButton(juce::Graphics& g,
                          juce::ToggleButton& button,
                          bool,
                          bool) override
    {
        auto bound = button.getLocalBounds();
        if (button.getToggleState())
        {
            g.drawImage(buttonOn, bound.toFloat());
        }
        else
        {
            g.drawImage(buttonOff, bound.toFloat());
        }
    }

    void drawRotarySlider(juce::Graphics& g,
                          int /* x */,
                          int /* y */,
                          int width,
                          int height,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override
    {
        auto sliderBounds = slider.getLocalBounds().toFloat();
        auto imageBounds = knob.getBounds().toFloat();

        auto scaleFactors =
            juce::jmin(sliderBounds.getWidth() / imageBounds.getWidth(),
                       sliderBounds.getHeight() / imageBounds.getHeight());

        auto rotation = rotaryStartAngle
                        + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

        // Center of the knob image within the slider bounds
        auto imageCenterX = sliderBounds.getCentreX();
        auto imageCenterY =
            sliderBounds.getY() + (imageBounds.getHeight() * scaleFactors * 0.5f)
            + (sliderBounds.getHeight() - imageBounds.getHeight() * scaleFactors) * 0.5f;

        // Apply scaling, translation, and rotation to the AffineTransform
        auto affine =
            juce::AffineTransform()
                .scaled(scaleFactors)
                .translated(sliderBounds.getX(),
                            imageCenterY
                                - (imageBounds.getHeight() * scaleFactors * 0.5f))
                .rotated(rotation, imageCenterX, imageCenterY);

        // Draw the image with the transformation applied
        g.drawImageTransformed(knob, affine);
    }

    juce::Image buttonOn = juce::ImageCache::getFromMemory(BinaryData::button_on_png,
                                                           BinaryData::button_on_pngSize);
    juce::Image buttonOff = juce::ImageCache::getFromMemory(
        BinaryData::button_off_png, BinaryData::button_off_pngSize);
    juce::Image knob =
        juce::ImageCache::getFromMemory(BinaryData::knob_png, BinaryData::knob_pngSize);
};

class PremiumSilenceAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit PremiumSilenceAudioProcessorEditor(PremiumSilenceAudioProcessor&);

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    // juce::GenericAudioProcessorEditor editor {processor};

    juce::Image background = juce::ImageCache::getFromMemory(BinaryData::bg_text_png,
                                                             BinaryData::bg_text_pngSize);

    juce::Slider amountSlider;
    juce::ToggleButton silenceButton;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<SliderAttachment> sliderAttachment;
    std::unique_ptr<ButtonAttachment> buttonAttachment;

    ButtonLf buttonLf;
};
