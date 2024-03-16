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

    auto initialWidth = 800.0f;
    auto initialHeight = initialWidth / ratio;

    setResizeLimits(400, 400.0/ratio, 1200, 1200.0/ratio);
    getConstrainer()->setFixedAspectRatio(ratio);
    setSize(800.0,800.0/ratio);
}

void PremiumSilenceAudioProcessorEditor::paint(juce::Graphics& g)
{
    // draw the image to fit the available space
    auto bound = getLocalBounds();
    g.drawImage(background, bound.toFloat());
}

void PremiumSilenceAudioProcessorEditor::resized()
{
    // editor.setBounds(getLocalBounds());
}
