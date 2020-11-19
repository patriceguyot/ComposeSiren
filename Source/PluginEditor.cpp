/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
// Component on the top of the main window
headComponent::headComponent()
{
    addAndMakeVisible (labelPluginTitle);
}

void headComponent::paint (juce::Graphics& g)
{
    //g.fillAll (juce::Colour (155, 153, 100)); // background color to see the component

    labelPluginTitle.setColour (juce::Label::textColourId, juce::Colours::black);
    labelPluginTitle.setText("COMPOSE SIREN", juce::dontSendNotification);

    labelPluginTitle.setFont (juce::Font (24.0f, juce::Font::italic));
    labelPluginTitle.setJustificationType (juce::Justification::centred);
    
    
    imgLogo = juce::ImageFileFormat::loadFrom(BinaryData::Picto_Siren_40x37_png, BinaryData::Picto_Siren_40x37_pngSize);
    //g.drawImageAt(imgLogo, labelPluginTitle.getX() + labelPluginTitle.getWidth(), 0);
    g.drawImageAt(imgLogo, getWidth()/2 + 90, 5);

    
}


void headComponent::resized()
{
    labelPluginTitle.setBounds (getLocalBounds());
}
//==============================================================================



//==============================================================================
// Component on the top of the main window
MainCommandsComponent::MainCommandsComponent()
{
    addAndMakeVisible (resetButton);
    
   
}

MainCommandsComponent::~MainCommandsComponent()
{

}

void MainCommandsComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(getLocalBounds().toFloat().reduced(1), 10);
    g.setColour(juce::Colour (71, 71, 71));
    g.fillRoundedRectangle(getLocalBounds().toFloat().reduced(2), 10);
    
   
    resetButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    // resetButton.setColour(juce::TextButton::buttonOnColourId , juce::Colours::grey);
    resetButton.setColour(juce::TextButton::textColourOffId , juce::Colours::black);
    resetButton.setButtonText ("Reset");
    //resetButton.setFont (juce::Font (14.0f, juce::Font::bold)); // no set font for textbutton :-(
    //resetButton.setColour(juce::Label::textColourId, juce::Colours::black);

}


void MainCommandsComponent::resized()
{
    resetButton.setBounds (20, 5, 60, 30);
}
//==============================================================================




//==============================================================================
SirenePlugAudioProcessorEditor::SirenePlugAudioProcessorEditor (SirenePlugAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    setSize (300, 200);
    addAndMakeVisible (head);
    addAndMakeVisible (mainCommands);
    mainCommands.resetButton.addListener(this);




}

SirenePlugAudioProcessorEditor::~SirenePlugAudioProcessorEditor()
{
    mainCommands.resetButton.removeListener(this);
}

//==============================================================================
void SirenePlugAudioProcessorEditor::paint (juce::Graphics& g)
{

    g.fillAll (juce::Colour (255, 153, 0)); // background color (orange)
   
}


void SirenePlugAudioProcessorEditor::resized()
{

    // void Component::setBounds  (int x, int y, int width, int height) - top left
    head.setBounds(0, 0, getWidth(), 50);
    mainCommands.setBounds (10, 50, 100, 40);

}


