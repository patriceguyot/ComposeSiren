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
    setSize (300, 200);

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

    addAndMakeVisible (labelPluginTitle);
    labelPluginTitle.setColour (juce::Label::textColourId, juce::Colours::black);
    labelPluginTitle.setText("COMPOSE SIREN", juce::dontSendNotification);
    labelPluginTitle.setFont (juce::Font (15.0f, juce::Font::italic));
    labelPluginTitle.setJustificationType (juce::Justification::centred);

    addAndMakeVisible (resetButton);
    resetButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    // resetButton.setColour(juce::TextButton::buttonOnColourId , juce::Colours::grey);
    resetButton.setColour(juce::TextButton::textColourOffId , juce::Colours::black);
    resetButton.setButtonText ("Reset");
    //resetButton.setFont (juce::Font (14.0f, juce::Font::bold)); // no set font for textbutton :-(
    //resetButton.setColour(juce::Label::textColourId, juce::Colours::black);
    resetButton.addListener (this);
    
    addAndMakeVisible(sirenMenu);
    sirenMenu.setText("Siren selector", juce::dontSendNotification);
    sirenMenu.addItem("Siren 1 - alto", 1);
    sirenMenu.addItem("Siren 2 - alto", 2);
    sirenMenu.addItem("Siren 3 - bass", 3);
    sirenMenu.addItem("Siren 4 - tenor", 4);
    sirenMenu.addItem("Siren 5 - soprano", 5);
    sirenMenu.addItem("Siren 6 - soprano", 6);
    sirenMenu.addItem("Siren 7 - picollo", 7);


}

SirenePlugAudioProcessorEditor::~SirenePlugAudioProcessorEditor()
{
    resetButton.removeListener (this);

}

//==============================================================================
void SirenePlugAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.fillAll (juce::Colour (255, 153, 0)); // background color

    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("COMPOSE SIREN", 0, 0, getWidth(), 30, juce::Justification::centred, 1);

}


void SirenePlugAudioProcessorEditor::resized()
{

    // void Component::setBounds  (int x, int y, int width, int height) - top left
    labelPluginTitle.setBounds (20, 10, getWidth() - 40, 20);
    sirenMenu.setBounds (30, 40, 130, 40);
    resetButton.setBounds (30, 90, 60, 40);

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
