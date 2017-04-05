/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TimebasedAudioProcessor::TimebasedAudioProcessor()
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

TimebasedAudioProcessor::~TimebasedAudioProcessor()
{
	for (int delay = 0; delay < getNumInputChannels(); ++delay)
	{
		delayArray[delay].~SimpleDelay();
	}
}

//==============================================================================
const String TimebasedAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TimebasedAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TimebasedAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double TimebasedAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TimebasedAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TimebasedAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TimebasedAudioProcessor::setCurrentProgram (int index)
{
}

const String TimebasedAudioProcessor::getProgramName (int index)
{
    return String();
}

void TimebasedAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TimebasedAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	delayArray = new SimpleDelay[getNumInputChannels()];

	for (int delay = 0; delay < getNumInputChannels(); ++delay)
	{
		delayArray[delay].init(sampleRate);
	}
}

void TimebasedAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TimebasedAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void TimebasedAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	const int totalNumInputChannels  = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();

	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear (i, 0, buffer.getNumSamples());

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		float* channelData = buffer.getWritePointer(channel);

		for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
		{
			const float output = delayArray[channel].process(channelData[sample]);

			channelData[sample] = output;
		}
	}	
}

//==============================================================================
/*Delay Functions*/

void TimebasedAudioProcessor::updateDelayTime(double time)
{
	for (int delay = 0; delay < getNumInputChannels(); ++delay)
	{
		delayArray[delay].updateDelayTime(time);
	}
}

void TimebasedAudioProcessor::updateDelayFeedback(double feedback)
{
	for (int delay = 0; delay < getNumInputChannels(); ++delay)
	{
		delayArray[delay].updateFeedbackAmount(feedback);
	}
}

//==============================================================================

bool TimebasedAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TimebasedAudioProcessor::createEditor()
{
    return new TimebasedAudioProcessorEditor (*this);
}

//==============================================================================
void TimebasedAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TimebasedAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TimebasedAudioProcessor();
}
