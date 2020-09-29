/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SirenePlugAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Button::Listener

//, private juce::Slider::Listener
{
public:
    SirenePlugAudioProcessorEditor (SirenePlugAudioProcessor&);
    ~SirenePlugAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //==============================================================================

    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SirenePlugAudioProcessor& audioProcessor;
    
    // slider volume
    /*
    void sliderValueChanged (juce::Slider* slider) override;
    juce::Slider midiVolume;
     */
    
    void buttonClicked (juce::Button* button) override
    {
        if (button == &resetButton)
        {
            std::cout << "Reset"<<std::endl;

        }
    }
    
    juce::TextButton resetButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SirenePlugAudioProcessorEditor)
};
