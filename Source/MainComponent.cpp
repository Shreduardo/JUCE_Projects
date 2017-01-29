/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


class MainContentComponent   : public AudioAppComponent, public Slider::Listener
{
public:
    //==============================================================================
	MainContentComponent()
		: currentSampleRate(0.0),
		currentAngle_1(0.0),
		currentAngle_2(0.0),
		angleDelta_1(0.0),
		angleDelta_2(0.0),
		currentFreq_1(0.0),
		currentFreq_2(0.0),
		targetFreq_1(0.0),
		targetFreq_2(0.0)
		
    {
        setSize (800, 600);

        setAudioChannels (2, 2);

		/***Initialize all components***/

		//Frequency Slider of Oscillator 1
		addAndMakeVisible(freqOsc_1);
		freqOsc_1.setRange(50, 5000);
		freqOsc_1.setSkewFactorFromMidPoint(500);
		freqOsc_1.setTextValueSuffix(" Hz");
		freqOsc_1.addListener(this); 

		//Frequency Slider of Oscillator 2
		addAndMakeVisible(freqOsc_2);
		freqOsc_2.setRange(50, 5000);
		freqOsc_2.setSkewFactorFromMidPoint(500);
		freqOsc_2.setTextValueSuffix(" Hz");
		freqOsc_2.addListener(this);


		//Level of Oscillator 1
		addAndMakeVisible(levelOsc_1);
		levelOsc_1.setRange(0, 0.125);
		levelOsc_1.addListener(this);
		levelOsc_1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
		levelOsc_1.setSliderStyle(Slider::SliderStyle::LinearVertical);

		//Level of Oscillator 2
		addAndMakeVisible(levelOsc_2);
		levelOsc_2.setRange(0, 0.125);
		levelOsc_2.addListener(this);
		levelOsc_2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
		levelOsc_2.setSliderStyle(Slider::SliderStyle::LinearVertical);

		//Frequency Slider 1 Label
		addAndMakeVisible(freqOscLabel_1);
		freqOscLabel_1.setText("Freq Osc 1", dontSendNotification);
		freqOscLabel_1.attachToComponent(&freqOsc_1, false);

		//Freqency Slider 2 Label
		addAndMakeVisible(freqOscLabel_2);
		freqOscLabel_2.setText("Freq Osc 2", dontSendNotification);
		freqOscLabel_2.attachToComponent(&freqOsc_2, false);

		//Level Slider 1 Label
		addAndMakeVisible(levelOscLabel_1);
		levelOscLabel_1.setText("Level Osc 1", dontSendNotification);
		levelOscLabel_1.attachToComponent(&levelOsc_1, false);

		//Level Slider 2 Label
		addAndMakeVisible(levelOscLabel_2);
		levelOscLabel_2.setText("Level Osc 2", dontSendNotification);
		levelOscLabel_2.attachToComponent(&levelOsc_2, false);

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
		updateAngleDelta(&angleDelta_1);
		updateAngleDelta(&angleDelta_2);
    }

	//TODO: DRY
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
		const float level_1 = (float)levelOsc_1.getValue();
		const float level_2 = (float)levelOsc_2.getValue();

		const double LEVEL_SAFETY_BLOCK = 0.8f;

		float* const buffer = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);

		const double localTargetFrequency_1 = targetFreq_1;
		const double localTargetFrequency_2 = targetFreq_2;

		//Update frequency of oscillator 1
		if (localTargetFrequency_1 != currentFreq_1)
		{
			const double freqIncrement_1 = (localTargetFrequency_1 - currentFreq_1) / bufferToFill.numSamples;

			for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
			{
				const float currentSample = (float)std::sin(currentAngle_1);

				currentFreq_1 += freqIncrement_1;
				updateAngleDelta(&angleDelta_1);

				currentAngle_1 += angleDelta_1;
				buffer[sample] = ((currentSample * level_1) + (std::sin(currentAngle_2) * level_2)) * LEVEL_SAFETY_BLOCK; 
			}
			currentFreq_1 = localTargetFrequency_1;
		}

		//Update frequency of oscillator 2
		else if (localTargetFrequency_2 != currentFreq_2)
		{
			const double freqIncrement_2 = (localTargetFrequency_2 - currentFreq_2) / bufferToFill.numSamples;

			for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
			{
				const float currentSample = (float)std::sin(currentAngle_2);

				currentFreq_2 += freqIncrement_2;
				updateAngleDelta(&angleDelta_2);

				currentAngle_2 += angleDelta_2;
				buffer[sample] = ((currentSample * level_2) + (std::sin(currentAngle_1) * level_1)) * LEVEL_SAFETY_BLOCK;
			}
			currentFreq_2 = localTargetFrequency_2;
		}

		//Play both oscillators if no updating needs to be done
		else
		{
			for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
			{
				const float currentSample = (float)std::sin(currentAngle_1)*level_1 + (float)std::sin(currentAngle_2)*level_2;
				currentAngle_1 += angleDelta_1;
				currentAngle_2 += angleDelta_2;
				buffer[sample] = currentSample * LEVEL_SAFETY_BLOCK;
			}
		}
  
    }

    void releaseResources() override
    {
		freqOsc_1.removeListener(this);
		freqOsc_2.removeListener(this);

		levelOsc_1.removeListener(this);
		levelOsc_2.removeListener(this);

    }

    //==============================================================================
	void sliderValueChanged(Slider* slider) override
	{
		if (slider = &freqOsc_1) 
		{
			targetFreq_1 = freqOsc_1.getValue();
		}

		if (slider = &freqOsc_2)
		{
			targetFreq_2 = freqOsc_2.getValue();
		}

		if (slider = &levelOsc_1)
		{
			currentLevel_1 = levelOsc_1.getValue();
		}

		if (slider = &levelOsc_2)
		{
			currentLevel_2 = levelOsc_2.getValue();
		}
	}

	void updateAngleDelta(double* angle)
	{
		if (angle == &angleDelta_1)
		{
			const double cyclesPerSample = freqOsc_1.getValue() / currentSampleRate;
			angleDelta_1 = cyclesPerSample * 2.0 * double_Pi;
		}

		if (angle == &angleDelta_2)
		{
			const double cyclesPerSample = freqOsc_2.getValue() / currentSampleRate;
			angleDelta_2 = cyclesPerSample * 2.0 * double_Pi;
		}
	}
	//==============================================================================
    void paint (Graphics& g) override
    {

        //g.fillAll (Colours::black);
		freqOsc_1.setBoundsRelative(0.0125f, 0.25f, 0.4f, 0.125f);
		
		freqOsc_2.setBoundsRelative(0.5125f, 0.25f, 0.4f, 0.125f);

		levelOsc_1.setBoundsRelative(0.25f, 0.5f, 0.125f, 0.4f);

		levelOsc_2.setBoundsRelative(0.75f, 0.5f, 0.125f, 0.4f);

		title.setBoundsRelative(0.4f, 0.01f, 0.5f, 0.2f);
    }

    void resized() override
    {


    }


private:
    //==============================================================================

	/*Components*/
	Slider freqOsc_1;
	Slider freqOsc_2;

	Slider levelOsc_1;
	Slider levelOsc_2;

	Label freqOscLabel_1;
	Label freqOscLabel_2;
	Label levelOscLabel_1;
	Label levelOscLabel_2;

	Label title;

	/*Audio Related Member Variables*/
	double currentSampleRate;

	//For Oscillator 1
	double currentAngle_1, angleDelta_1;
	double currentFreq_1, targetFreq_1;

	double currentLevel_1;

	//For Oscillator 2
	double currentAngle_2, angleDelta_2;
	double currentFreq_2, targetFreq_2;

	double currentLevel_2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
