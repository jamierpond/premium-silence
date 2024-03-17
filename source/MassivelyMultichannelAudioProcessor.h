#pragma once

#include "Parameters.h"

#ifndef JUCE_DEBUG
#define STEREO_DEBUGGING 0
#else
#define STEREO_DEBUGGING 1
#endif

// comment
#define ADD_BUS_PAIR(name, channelSet) \
    .withInput(name " Input", juce::AudioChannelSet::channelSet(), true) \
    .withOutput(name " Output", juce::AudioChannelSet::channelSet(), true)

class MassivelyMultichannelAudioProcessor : public PluginHelpers::ProcessorBase {
public:
    MassivelyMultichannelAudioProcessor()
        : PluginHelpers::ProcessorBase(BusesProperties()
                          ADD_BUS_PAIR("Stereo", stereo)
                          ADD_BUS_PAIR("Mono", mono)
                          ADD_BUS_PAIR("LCR", createLCR)
                          ADD_BUS_PAIR("LRS", createLRS)
                          ADD_BUS_PAIR("LCRS", createLCRS)
                          ADD_BUS_PAIR("5.0", create5point0)
                          ADD_BUS_PAIR("5.1", create5point1)
                          ADD_BUS_PAIR("6.0", create6point0)
                          ADD_BUS_PAIR("6.1", create6point1)
                          ADD_BUS_PAIR("6.0 Music", create6point0Music)
                          ADD_BUS_PAIR("6.1 Music", create6point1Music)
                          ADD_BUS_PAIR("7.0", create7point0)
                          ADD_BUS_PAIR("7.0 SDDS", create7point0SDDS)
                          ADD_BUS_PAIR("7.1", create7point1)
                          ADD_BUS_PAIR("7.1 SDDS", create7point1SDDS)
                          ADD_BUS_PAIR("5.0.2", create5point0point2)
                          ADD_BUS_PAIR("5.1.2", create5point1point2)
                          ADD_BUS_PAIR("5.0.4", create5point0point4)
                          ADD_BUS_PAIR("5.1.4", create5point1point4)
                          ADD_BUS_PAIR("7.0.2", create7point0point2)
                          ADD_BUS_PAIR("7.1.2", create7point1point2)
                          ADD_BUS_PAIR("7.0.4", create7point0point4)
                          ADD_BUS_PAIR("7.1.4", create7point1point4)
                          ADD_BUS_PAIR("7.0.6", create7point0point6)
                          ADD_BUS_PAIR("7.1.6", create7point1point6)
                          ADD_BUS_PAIR("9.0.4", create9point0point4)
                          ADD_BUS_PAIR("9.1.4", create9point1point4)
                          ADD_BUS_PAIR("9.0.6", create9point0point6)
                          ADD_BUS_PAIR("9.1.6", create9point1point6)
                          ADD_BUS_PAIR("Quadraphonic", quadraphonic)
                          ADD_BUS_PAIR("Pentagonal", pentagonal)
                          ADD_BUS_PAIR("Hexagonal", hexagonal)
                          ADD_BUS_PAIR("Octagonal", octagonal)
                         )
    {
    }

private:
    bool isBusesLayoutSupported(const BusesLayout&) const override {
        return true;
    }
};
