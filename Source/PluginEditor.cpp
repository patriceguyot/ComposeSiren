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
}

SirenePlugAudioProcessorEditor::~SirenePlugAudioProcessorEditor()
{
}

//==============================================================================
void SirenePlugAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Sirene plugin", 0, 0, getWidth(), 30, juce::Justification::centred, 1);}


void SirenePlugAudioProcessorEditor::resized()
{
    
    //midiVolume.setBounds (40, 30, 20, getHeight() - 60);
}

/*
void SirenePlugAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.noteOnVel = midiVolume.getValue();
}
*/

