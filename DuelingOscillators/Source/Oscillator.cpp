/*
  ==============================================================================

    Oscillator.cpp
    Created: 11 Feb 2017 6:28:32pm
    Author:  Ed

  ==============================================================================
*/

#include "Oscillator.h"

#include "../JuceLibraryCode/JuceHeader.h"


Oscillator :: Oscillator()
{
	currentAngle = 0.0;
	angleDelta = 0.0;

	currentFrequency = 0.0;
	targetFrequency = 0.0;

	currentLevel = 0.0;
	currentSampleRate = 0.0;
}

Oscillator :: ~Oscillator()
{

}

/*Basic Setter*/
void Oscillator :: init(double sampleRate)
{
	currentSampleRate = sampleRate;
	updateAngleDelta();
}


/*UI callback Setters*/
void Oscillator::setTargetFrequency(double target)
{
	targetFrequency = target;
}

void Oscillator::setLevel(double level)
{
	currentLevel = level;
}


/*Data retrievers and updaters that are called on the audio thread*/
void Oscillator :: updateFrequency(int numberOfSamples)
{
	const double localTargetFrequency = targetFrequency;

	//Change to while???
	if (localTargetFrequency != currentFrequency)
	{
		const double frequencyIncrement = (localTargetFrequency - currentFrequency) / numberOfSamples;
		
		currentFrequency += frequencyIncrement;
		updateAngleDelta();
		updateAngle();
	}

	else
	{
		updateAngleDelta();
		updateAngle();
	}
}

float Oscillator::getCurrentSample()
{
	return (float)std::sin(currentAngle) * currentLevel;
}




/*Private methods*/
void Oscillator :: updateAngleDelta()
{
	const double cyclesPerSample = targetFrequency / currentSampleRate;
	angleDelta = cyclesPerSample * 2.0 * double_Pi;
}

void Oscillator :: updateAngle()
{
	currentAngle += angleDelta;
}
