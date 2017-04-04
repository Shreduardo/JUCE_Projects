/*
  ==============================================================================

    SimpleDelay.cpp
    Created: 4 Apr 2017 12:01:56am
    Author:  Ed

  ==============================================================================
*/

#include "SimpleDelay.h"

SimpleDelay::SimpleDelay()
{
	sampleRate = 0.0;
	
	delayTime = 0.0;
	feedbackAmount = 0.0;

	delayBuffer = nullptr; 

	currentIndex = 0;
	delayIndex = 0;
}

SimpleDelay::~SimpleDelay()
{
	delete[] delayBuffer;
}

void SimpleDelay::init(double sr)
{
	sampleRate = sr;

	bufferSize = 2 * (sampleRate * MAX_DELAY_TIME_MS); //sampleRate * MAX_DELAY_TIME_MS = MAX_DELAY_TIME_SAMPLES
	delayBuffer = new double[bufferSize];

}

void SimpleDelay::updateDelayTime(double time)
{
	delayTime = time;
	delayTimeInSamples = delayTime * sampleRate;
}

void SimpleDelay::updateFeedbackAmount(double feedback)
{
	feedbackAmount = feedback;
}

double SimpleDelay::process(double input)
{
	//i = i % bufferSize
	if (currentIndex >= bufferSize)
	{
		currentIndex = 0;
	}

	delayIndex = currentIndex - (delayTimeInSamples);

	if (delayIndex < 0)
	{
		++delayIndex;
	}

	delayBuffer[currentIndex] = input + (delayBuffer[delayIndex] * feedbackAmount);

	return delayBuffer[currentIndex];
}