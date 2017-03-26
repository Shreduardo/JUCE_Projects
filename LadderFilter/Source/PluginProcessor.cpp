/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "Filter.h"


//==============================================================================
LadderFilterAudioProcessor::LadderFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

LadderFilterAudioProcessor::~LadderFilterAudioProcessor()
{
	delete[] lowPassFilterArray;
}

//==============================================================================
const String LadderFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LadderFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LadderFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double LadderFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LadderFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LadderFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LadderFilterAudioProcessor::setCurrentProgram (int index)
{
}

const String LadderFilterAudioProcessor::getProgramName (int index)
{
    return String();
}

void LadderFilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void LadderFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	lowPassFilterArray = new Filter[getNumInputChannels()];

	for (int filterNumber = 0; filterNumber < getNumInputChannels(); ++filterNumber) {
		lowPassFilterArray[filterNumber] = Filter();
		lowPassFilterArray[filterNumber].init(sampleRate);
		lowPassFilterArray[filterNumber].calculateBiquad();
	}

	//lowPassFilter.init(sampleRate);
	//lowPassFilter.calculateBiquad();

}

void LadderFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LadderFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void LadderFilterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();


    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	

	//Process Audio
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			const float inSample = channelData[sample];

			const float output = lowPassFilterArray[channel].applyFilter(inSample);

			channelData[sample] = output;
		}
        
    }
}

//==============================================================================
bool LadderFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* LadderFilterAudioProcessor::createEditor()
{
    return new LadderFilterAudioProcessorEditor (*this);
}

//==============================================================================
void LadderFilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LadderFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

/*Filter Functions=============================================================*/
void LadderFilterAudioProcessor::updateFilterCutoff(double freq)
{

	for (int filterNumber = 0; filterNumber < getNumInputChannels(); ++filterNumber) {
		lowPassFilterArray[filterNumber].updateCutoff(freq);
		lowPassFilterArray[filterNumber].calculateBiquad();
	}

}

void LadderFilterAudioProcessor::updateFilterResonance(double Q)
{

	for (int filterNumber = 0; filterNumber < getNumInputChannels(); ++filterNumber) {
		lowPassFilterArray[filterNumber].updateResonance(Q);
		lowPassFilterArray[filterNumber].calculateBiquad();
	}

}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LadderFilterAudioProcessor();
}
