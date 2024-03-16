project(PremiumSilence VERSION 0.0.1)

set (BaseTargetName PremiumSilence)

juce_set_aax_sdk_path("/Users/jamiepond/projects/aax-sdk")

# add binary data
juce_add_binary_data(BinaryData
      SOURCES
      ./assets/button_off.png
      ./assets/bg_text.png
      ./assets/knob.png
      ./assets/logo.png
      ./assets/button_on.png
)


juce_add_plugin("${BaseTargetName}"
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME "PresentDayProduction"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_MANUFACTURER_CODE Pdp1
        PLUGIN_CODE prmS
        FORMATS AU VST3 AAX Standalone
        PRODUCT_NAME "PremiumSilence")

target_sources(${BaseTargetName} PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp)

target_compile_definitions(${BaseTargetName}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${BaseTargetName} PRIVATE
        shared_plugin_helpers
        BinaryData
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags)
