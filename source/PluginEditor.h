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
        auto bounds = button.getLocalBounds().toFloat(); // Get the button's bounds

        // Determine which image to use based on the toggle state
        const auto& image = button.getToggleState() ? buttonOn : buttonOff;

        // Calculate the scale factor to fit the image within the button's bounds while maintaining its aspect ratio
        auto scaleFactor = juce::jmin(bounds.getWidth() / image.getWidth(),
                                      bounds.getHeight() / image.getHeight());

        // Calculate the centered position for the image
        float imageX =
            bounds.getX() + (bounds.getWidth() - image.getWidth() * scaleFactor) / 2.0f;
        float imageY =
            bounds.getY() + (bounds.getHeight() - image.getHeight() * scaleFactor) / 2.0f;

        // Create an AffineTransform for scaling and translation to the centered position
        auto transform =
            juce::AffineTransform::scale(scaleFactor).translated(imageX, imageY);

        // Draw the image centered within the button
        g.drawImageTransformed(image, transform);
    }

    void drawRotarySlider(juce::Graphics& g,
                          int /* x */,
                          int /* y */,
                          int ,
                          int ,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override
    {
        auto sliderBounds = slider.getLocalBounds().toFloat();
        auto imageBounds = knob.getBounds().toFloat();

        auto scaleFactor = juce::jmin(sliderBounds.getWidth() / imageBounds.getWidth(),
                                      sliderBounds.getHeight() / imageBounds.getHeight())
                           * 0.7f; // Adjusted scale factor

        auto rotation = rotaryStartAngle
                        + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

        // Calculate the center of the image after scaling
        auto scaledImageWidth = imageBounds.getWidth() * scaleFactor;
        auto scaledImageHeight = imageBounds.getHeight() * scaleFactor;
        auto imageCenterX = sliderBounds.getCentreX();
        auto imageCenterY = sliderBounds.getCentreY();

        // Apply scaling, then translation to center, then rotation
        auto affine = juce::AffineTransform::scale(scaleFactor)
                          .translated(imageCenterX - scaledImageWidth / 2,
                                      imageCenterY - scaledImageHeight / 2)
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

struct PdpLogoButton : juce::HyperlinkButton
{
    PdpLogoButton()
    {
        setURL(juce::URL("https://www.presentdayproduction.com"));
        setTooltip("Support the developer on Patreon");
    }

    void paintButton(juce::Graphics &g, bool, bool) override {
      // Draw the image to fit the available space
        auto bounds = getLocalBounds().toFloat(); // Get the button's bounds

        // Determine which image to use based on the toggle state
        const auto& image = pdpLogo;

        // Calculate the scale factor to fit the image within the button's bounds while maintaining its aspect ratio
        auto scaleFactor = juce::jmin(bounds.getWidth() / image.getWidth(),
                                      bounds.getHeight() / image.getHeight());

        // Calculate the centered position for the image
        float imageX =
            bounds.getX() + (bounds.getWidth() - image.getWidth() * scaleFactor) / 2.0f;
        float imageY =
            bounds.getY() + (bounds.getHeight() - image.getHeight() * scaleFactor) / 2.0f;

        // Create an AffineTransform for scaling and translation to the centered position
        auto transform =
            juce::AffineTransform::scale(scaleFactor).translated(imageX, imageY);

        // Draw the image centered within the button
        g.drawImageTransformed(image, transform);
    }

    juce::Image pdpLogo = juce::ImageCache::getFromMemory(BinaryData::logo_png,
                                                          BinaryData::logo_pngSize);
};

class PremiumSilenceAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit PremiumSilenceAudioProcessorEditor(PremiumSilenceAudioProcessor&);

    ~PremiumSilenceAudioProcessorEditor() override {
        setLookAndFeel(nullptr);
    }

private:
    void paint(juce::Graphics&) override;
    void resized() override;

    // juce::GenericAudioProcessorEditor editor {processor};

    juce::Image background = juce::ImageCache::getFromMemory(BinaryData::bg_text_png,
                                                             BinaryData::bg_text_pngSize);

    juce::Slider amountSlider;
    juce::ToggleButton silenceButton;

    juce::HyperlinkButton pdpLogoButton;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<SliderAttachment> sliderAttachment;
    std::unique_ptr<ButtonAttachment> buttonAttachment;

    PdpLogoButton pdpButton;

    ButtonLf buttonLf;
};
