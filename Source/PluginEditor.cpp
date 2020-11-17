/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
headComponent::headComponent()
{
    addAndMakeVisible (labelPluginTitle);
    labelPluginTitle.setText("COMPOSE SIREN", juce::dontSendNotification);
}

void headComponent::paint (juce::Graphics& g)
{
    //g.fillAll (juce::Colour (155, 153, 100)); // background color to see the head
    addAndMakeVisible (labelPluginTitle);

    labelPluginTitle.setColour (juce::Label::textColourId, juce::Colours::black);
    labelPluginTitle.setText("COMPOSE SIREN", juce::dontSendNotification);

    labelPluginTitle.setFont (juce::Font (15.0f, juce::Font::italic));
    labelPluginTitle.setJustificationType (juce::Justification::centred);
}


void headComponent::resized()
{
    labelPluginTitle.setBounds (getLocalBounds());
}




//==============================================================================
SirenePlugAudioProcessorEditor::SirenePlugAudioProcessorEditor (SirenePlugAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize (300, 200);

   
    
    addAndMakeVisible (head);
    

    addAndMakeVisible (resetButton);
    resetButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    // resetButton.setColour(juce::TextButton::buttonOnColourId , juce::Colours::grey);
    resetButton.setColour(juce::TextButton::textColourOffId , juce::Colours::black);
    resetButton.setButtonText ("Reset");
    //resetButton.setFont (juce::Font (14.0f, juce::Font::bold)); // no set font for textbutton :-(
    //resetButton.setColour(juce::Label::textColourId, juce::Colours::black);
    resetButton.addListener (this);

   

}

SirenePlugAudioProcessorEditor::~SirenePlugAudioProcessorEditor()
{
    resetButton.removeListener (this);

}

//==============================================================================
void SirenePlugAudioProcessorEditor::paint (juce::Graphics& g)
{

    g.fillAll (juce::Colour (255, 153, 0)); // background color (orange)

   
}


void SirenePlugAudioProcessorEditor::resized()
{

    // void Component::setBounds  (int x, int y, int width, int height) - top left
    head.setBounds(0, 0, getWidth(), 30);
    resetButton.setBounds (30, 90, 60, 40);

}


