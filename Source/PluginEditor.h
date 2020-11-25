/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"



//==============================================================================
// class headComponent : head of the main window
class headComponent   : public juce::Component
{
public:
    headComponent();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Label labelPluginTitle;
    juce::Image imgLogo;
};

//==============================================================================


//==============================================================================
// class MainCommandsComponent : main commands
class MainCommandsComponent   : public juce::Component
{
public:
    MainCommandsComponent(SirenePlugAudioProcessor&);
    ~MainCommandsComponent();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    juce::TextButton resetButton;

private:
    SirenePlugAudioProcessor& audioProcessor;
    
   
    
};

//==============================================================================


class SirenePlugAudioProcessorEditor  : public juce::AudioProcessorEditor//, public juce::Button::Listener

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
    
    headComponent head;
    MainCommandsComponent mainCommands;
    
    /*
    void buttonClicked (juce::Button* button) override
    {
        //juce::String buttonName = button->getComponentID();
        //if (buttonName == "reset")
        if (button == &mainCommands.resetButton)
        {
            std::cout << "Reset"<<std::endl;
            audioProcessor.myMidiInHandler -> resetSireneCh(1);
            audioProcessor.myMidiInHandler -> resetSireneCh(2);
            audioProcessor.myMidiInHandler -> resetSireneCh(3);
            audioProcessor.myMidiInHandler -> resetSireneCh(4);
            audioProcessor.myMidiInHandler -> resetSireneCh(5);
            audioProcessor.myMidiInHandler -> resetSireneCh(6);
            audioProcessor.myMidiInHandler -> resetSireneCh(7);

        }
    }
     */

    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SirenePlugAudioProcessorEditor)
};
