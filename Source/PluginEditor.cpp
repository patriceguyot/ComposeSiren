/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SirenePlugAudioProcessorEditor::SirenePlugAudioProcessorEditor (SirenePlugAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);
    
    // volume slider
    /*
    midiVolume.setSliderStyle (juce::Slider::LinearBarVertical);
    midiVolume.setRange (0.0, 127.0, 1.0);
    midiVolume.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    midiVolume.setPopupDisplayEnabled (true, false, this);
    midiVolume.setTextValueSuffix (" Volume");
    midiVolume.setValue(1.0);
    
    addAndMakeVisible (&midiVolume);
    
    midiVolume.addListener (this);
    */
    
    
    resetButton.setButtonText ("Reset");
    //resetButton.setColour(juce::Label::backgroundColourId, juce::Colours::red);
    //resetButton.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible (resetButton);
    resetButton.addListener (this);
    
    
}

SirenePlugAudioProcessorEditor::~SirenePlugAudioProcessorEditor()
{
    resetButton.removeListener (this);

}

//==============================================================================
void SirenePlugAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Sirene plugin", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
    
}


void SirenePlugAudioProcessorEditor::resized()
{
    
    resetButton.setBounds (30, 30, 50, 50);
}

/*
void SirenePlugAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.noteOnVel = midiVolume.getValue();
}
*/

/*
void buttonClicked (juce::Button* button)
{
    if (button == &resetButton)
    {
        std::cout << "Reset"<<std::endl;

    }
}
*/

