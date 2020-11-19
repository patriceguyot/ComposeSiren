/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SirenePlugAudioProcessor::SirenePlugAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    startTimer(1);
    myMidiInHandler = new MidiIn;
    
    
    
}

SirenePlugAudioProcessor::~SirenePlugAudioProcessor()
{
}

//==============================================================================
const juce::String SirenePlugAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SirenePlugAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SirenePlugAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SirenePlugAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SirenePlugAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SirenePlugAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SirenePlugAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SirenePlugAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SirenePlugAudioProcessor::getProgramName (int index)
{
    return {};
}

void SirenePlugAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SirenePlugAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    /*
    int totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    std::cout << "total number of Input Channels: " << totalNumInputChannels << "\n";
    std::cout << "total nomber of Output Channels: " << totalNumOutputChannels << "\n";
     */
}

void SirenePlugAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SirenePlugAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SirenePlugAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
        
    buffer.clear();

    // process midi message
    for (const auto meta : midiMessages)
    {
        const auto msg = meta.getMessage();
        midiMessageIntArray = getIntFromMidiMessage(msg.getRawData(), msg.getRawDataSize());
        std::cout << "Message reçu ----------------------------------------------------------------------" << std::endl;
        std::cout << "Message: " << midiMessageIntArray[0] << "-" << midiMessageIntArray[1] << "-" << midiMessageIntArray[2] << "\n";
        myMidiInHandler -> handleMIDIMessage2(midiMessageIntArray[0], midiMessageIntArray[1], midiMessageIntArray[2]);
    }
 
    
    float sampleS1 = 0;
    float sampleS2 = 0;
    float sampleS3 = 0;
    float sampleS4 = 0;
    float sampleS5 = 0;
    float sampleS6 = 0;
    float sampleS7 = 0;
    
    
    myMidiInHandler -> timerAudio();
    
    //Pat: original code of the audio plug in template
    juce::ScopedNoDenormals noDenormals;
    //auto totalNumInputChannels  = getTotalNumInputChannels();
    //auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    //for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        
        //buffer.clear (i, 0, buffer.getNumSamples());

        // This is the place where you'd normally do the guts of your plugin's
        // audio processing...
        // Make sure to reset the state if your inner loop is processing
        // the samples and the outer loop is handling the channels.
        // Alternatively, you can process the samples with the channels
        // interleaved by keeping the same state.
        
        //int channel = 0;
        //for (int channel = 0; channel < totalNumOutputChannels; ++channel)
        //{
            
        auto* channelLeft = buffer.getWritePointer (0);
        auto* channelRight = buffer.getWritePointer (1);
            
            
            for (auto sample = 0; sample < buffer.getNumSamples(); sample++)
            {
                
                // ..do something to the data...
                sampleS1 = myMidiInHandler -> mySynth -> s1 -> calculwave();
                sampleS2 = myMidiInHandler -> mySynth -> s2 -> calculwave();
                sampleS3 = myMidiInHandler -> mySynth -> s3 -> calculwave();
                sampleS4 = myMidiInHandler -> mySynth -> s4 -> calculwave();
                sampleS5 = myMidiInHandler -> mySynth -> s5 -> calculwave();
                sampleS6 = myMidiInHandler -> mySynth -> s6 -> calculwave();
                sampleS7 = myMidiInHandler -> mySynth -> s7 -> calculwave();
                 
                
                channelLeft[sample]  = sampleS1 * myMidiInHandler -> mySynth->getPan(1,0) + sampleS2 * myMidiInHandler -> mySynth->getPan(2,0) + sampleS3 * myMidiInHandler -> mySynth->getPan(3,0) + sampleS4 * myMidiInHandler -> mySynth->getPan(4,0) + sampleS5 * myMidiInHandler -> mySynth->getPan(5,0) + sampleS6 * myMidiInHandler -> mySynth->getPan(6,0) + sampleS7 * myMidiInHandler -> mySynth->getPan(7,0);
                channelRight[sample]  = sampleS1 * myMidiInHandler -> mySynth->getPan(1,1) + sampleS2 * myMidiInHandler -> mySynth->getPan(2,1) + sampleS3 * myMidiInHandler -> mySynth->getPan(3,1) + sampleS4 * myMidiInHandler -> mySynth->getPan(4,1) + sampleS5 * myMidiInHandler -> mySynth->getPan(5,1) + sampleS6 * myMidiInHandler -> mySynth->getPan(6,1) + sampleS7 * myMidiInHandler -> mySynth->getPan(7,1);
            //}
    }
    
}

//==============================================================================
bool SirenePlugAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SirenePlugAudioProcessor::createEditor()
{
    return new SirenePlugAudioProcessorEditor (*this);
}

//==============================================================================
void SirenePlugAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SirenePlugAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}



int* SirenePlugAudioProcessor::getIntFromMidiMessage(const void * data, int size)
// From a midi message and its size, output the midi message as an array of 3 integers
{
    static int arr[3];
    unsigned int x;

    juce::String hexaMessage =  juce::String::toHexString (data, size); // convert message to hexadecimal string

    juce::String value;
    int begin, end;
    // loop to split the string in 3 and convert each part in integer
    for (int i = 0; i < 3; ++i)
    {
        std::stringstream ss;
        begin = i*3;
        end = begin + 2;
        value = hexaMessage.substring(begin, end);
        ss << std::hex << value;
        ss >> x;
        arr[i] = static_cast<int>(x);
    }
    return arr;
}

void SirenePlugAudioProcessor::timerCallback()
{
    
    myMidiInHandler -> mySynth -> s1 -> setnote();
    myMidiInHandler -> mySynth -> s2 -> setnote();
    myMidiInHandler -> mySynth -> s3 -> setnote();
    myMidiInHandler -> mySynth -> s4 -> setnote();
    myMidiInHandler -> mySynth -> s5 -> setnote();
    myMidiInHandler -> mySynth -> s6 -> setnote();
    myMidiInHandler -> mySynth -> s7 -> setnote();
     
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SirenePlugAudioProcessor();
}
