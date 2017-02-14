/*
  ==============================================================================

    ~~~~~~~~~~~~~~~~~~~~~~~~~~Dueling Sine Waves!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	Very Simple program that runs two, parallel, sine wave oscialltors. 
	Will be constantly updating over the course of my independent study. 

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"


class MainContentComponent   : public AudioAppComponent, public Slider::Listener
{
public:
    //==============================================================================
	MainContentComponent()
		: currentSampleRate(0.0)
		
    {
        setSize (800, 600);
        setAudioChannels (0, 2);

		/***Initialize all components***/

		//Frequency Slider of Oscillator 1
		addAndMakeVisible(freqSliderOsc_1);
		freqSliderOsc_1.setRange(50, 5000);
		freqSliderOsc_1.setSkewFactorFromMidPoint(500);
		freqSliderOsc_1.setTextValueSuffix(" Hz");
		freqSliderOsc_1.addListener(this); 

		//Frequency Slider of Oscillator 2
		addAndMakeVisible(freqSliderOsc_2);
		freqSliderOsc_2.setRange(50, 5000);
		freqSliderOsc_2.setSkewFactorFromMidPoint(500);
		freqSliderOsc_2.setTextValueSuffix(" Hz");
		freqSliderOsc_2.addListener(this);


		//Level of Oscillator 1
		addAndMakeVisible(levelSliderOsc_1);
		levelSliderOsc_1.setRange(0, 0.125);
		levelSliderOsc_1.addListener(this);
		levelSliderOsc_1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
		levelSliderOsc_1.setSliderStyle(Slider::SliderStyle::LinearVertical);

		//Level of Oscillator 2
		addAndMakeVisible(levelSliderOsc_2);
		levelSliderOsc_2.setRange(0, 0.125);
		levelSliderOsc_2.addListener(this);
		levelSliderOsc_2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
		levelSliderOsc_2.setSliderStyle(Slider::SliderStyle::LinearVertical);

		//Frequency Slider 1 Label
		addAndMakeVisible(freqOscLabel_1);
		freqOscLabel_1.setText("Freq Osc 1", dontSendNotification);
		freqOscLabel_1.attachToComponent(&freqSliderOsc_1, false);

		//Freqency Slider 2 Label
		addAndMakeVisible(freqOscLabel_2);
		freqOscLabel_2.setText("Freq Osc 2", dontSendNotification);
		freqOscLabel_2.attachToComponent(&freqSliderOsc_2, false);

		//Level Slider 1 Label
		addAndMakeVisible(levelOscLabel_1);
		levelOscLabel_1.setText("Level Osc 1", dontSendNotification);
		levelOscLabel_1.attachToComponent(&levelSliderOsc_1, false);

		//Level Slider 2 Label
		addAndMakeVisible(levelOscLabel_2);
		levelOscLabel_2.setText("Level Osc 2", dontSendNotification);
		levelOscLabel_2.attachToComponent(&levelSliderOsc_2, false);

		//Title
		addAndMakeVisible(title);
		title.setText("Ed-itive Synth", dontSendNotification);
    }

    ~MainContentComponent()
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override
    {
		currentSampleRate = sampleRate;

		/*Initialize Oscillators*/
		oscillator_1.init(sampleRate);
		oscillator_2.init(sampleRate);

    }


    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {

		const double LEVEL_SAFETY_BLOCK = 0.8f;

		float* const buffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);	
	
		for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
		{
			const float currentSample = oscillator_1.getCurrentSample() + oscillator_2.getCurrentSample();

			oscillator_1.updateFrequency(bufferToFill.numSamples - sample);
			oscillator_2.updateFrequency(bufferToFill.numSamples - sample);

			buffer[sample] = currentSample * LEVEL_SAFETY_BLOCK;
		}

    }

    void releaseResources() override
    {
		freqSliderOsc_1.removeListener(this);
		freqSliderOsc_2.removeListener(this);

		levelSliderOsc_1.removeListener(this);
		levelSliderOsc_2.removeListener(this);

    }

    //==============================================================================

	//TODO: Too static
	void sliderValueChanged(Slider* slider) override
	{
		if (slider = &freqSliderOsc_1) 
		{
			oscillator_1.setTargetFrequency(freqSliderOsc_1.getValue());
		}

		if (slider = &freqSliderOsc_2)
		{
			oscillator_2.setTargetFrequency(freqSliderOsc_2.getValue());
		}

		if (slider = &levelSliderOsc_1)
		{
			oscillator_1.setLevel(levelSliderOsc_1.getValue());
		}

		if (slider = &levelSliderOsc_2)
		{
			oscillator_2.setLevel(levelSliderOsc_2.getValue());
		}
	}


	//==============================================================================
    void paint (Graphics& g) override
    {

        //g.fillAll (Colours::black);
		freqSliderOsc_1.setBoundsRelative(0.0125f, 0.25f, 0.4f, 0.125f);
		
		freqSliderOsc_2.setBoundsRelative(0.5125f, 0.25f, 0.4f, 0.125f);

		levelSliderOsc_1.setBoundsRelative(0.25f, 0.5f, 0.125f, 0.4f);

		levelSliderOsc_2.setBoundsRelative(0.75f, 0.5f, 0.125f, 0.4f);

		title.setBoundsRelative(0.4f, 0.01f, 0.5f, 0.2f);
    }

    void resized() override
    {


    }


private:
    //==============================================================================

	/*Components*/
	Slider freqSliderOsc_1;
	Slider freqSliderOsc_2;

	Slider levelSliderOsc_1;
	Slider levelSliderOsc_2;

	Label freqOscLabel_1;
	Label freqOscLabel_2;
	Label levelOscLabel_1;
	Label levelOscLabel_2;

	Label title;


	/*Audio Related Member Variables*/
	double currentSampleRate;


	/*Oscillators*/
	Oscillator oscillator_1;
	Oscillator oscillator_2;
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
