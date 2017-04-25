/*
==============================================================================

SimpleDelay.cpp
Created: 4 Apr 2017 12:01:56am
Author:  Ed

==============================================================================
*/

#include "SimpleDelay.h"
#include <stdio.h>
#include <assert.h>


using namespace std; 

SimpleDelay::SimpleDelay()
{
	sampleRate = 0.0;

	delayTime = 0.0;
	feedbackAmount = 0.2;

	currentPtr = 0;
	delayPtr = 0;
	targetDelayPtr = 0;

	delayTimeInSamples = 0;

	smoothingBuffer = 0;
	smoothingPtr = 0;

	interpolation = DelayTimeInterpolation::CROSSFADE;
}

SimpleDelay::~SimpleDelay()
{

}

void SimpleDelay::init(double sr)
{
	sampleRate = sr;

	bufferSize = 2 * (sampleRate * MAX_DELAY_TIME_MS); //sampleRate * MAX_DELAY_TIME_MS = MAX_DELAY_TIME_SAMPLES
	delayBuffer = new double [bufferSize] ();

	updateDelayTime(delayTime);
	updateFeedbackAmount(feedbackAmount);

}

/*TODO: Parameter smoothing*/
void SimpleDelay::updateDelayTime(double time)
{
	delayTime = time;
	delayTimeInSamples = (delayTime / 1000) * sampleRate;
	switch (interpolation)
	{
	case JUMP:
		delayPtr = (currentPtr - (delayTimeInSamples));
		if (delayPtr < 0) delayPtr += bufferSize;
		targetDelayPtr = delayPtr;
		break;

	case PITCH:
		/*	delayTime = time;
		delayTimeInSamples = (delayTime / 1000) * sampleRate;

		delayPtr =
		break;*/

	case CROSSFADE:
		targetDelayPtr = (currentPtr - (delayTimeInSamples));
		if (targetDelayPtr < 0) targetDelayPtr += bufferSize;
		break;
	}
	

}
//=======================================================================================================
void SimpleDelay::updateFeedbackAmount(double feedback)
{
	feedbackAmount = feedback;
}

void SimpleDelay::updateDelayTimeInterpolation(SimpleDelay::DelayTimeInterpolation newInterpolation)
{
	interpolation = newInterpolation;
}

void SimpleDelay::updateDryWet(double amount)
{
	dryWet = amount;
}

//=======================================================================================================
double SimpleDelay::process(double input)
{

	const double wet = interpolateDelayTime(input);
	const double out = calculateDryWetSignal(input, wet);

	//const double out = delayBuffer[currentPtr] = input + (delayBuffer[delayPtr] * feedbackAmount);

	++currentPtr;
	currentPtr = currentPtr % bufferSize;

	return out;
}


double SimpleDelay::interpolateDelayTime(double input)
{
	assert(delayBuffer != NULL);

	switch (interpolation)
	{
		case JUMP:
			delayBuffer[currentPtr] = input + (delayBuffer[delayPtr] * feedbackAmount);	
			delayPtr++;
			delayPtr = delayPtr % bufferSize;
			break;

		case PITCH:
			/*	delayTime = time;
			delayTimeInSamples = (delayTime / 1000) * sampleRate;

			delayPtr =
			break;*/

		case CROSSFADE:
			if (targetDelayPtr != delayPtr) {
				/* Get crossfade value of samples*/

				const double crossFade = (delayBuffer[targetDelayPtr] - delayBuffer[delayPtr]) / 10;
				delayBuffer[currentPtr] = input + (crossFade * feedbackAmount);

				/*Update delay time based on interval multiples of difference*/
				const double delayIndexChangeInterval = (targetDelayPtr - delayPtr) / 10;
				delayPtr += delayIndexChangeInterval;

			}
			else {
				/*Output delay index if no change*/
				delayBuffer[currentPtr] = input + (delayBuffer[delayPtr] * feedbackAmount);

				delayPtr++;
				delayPtr = delayPtr % bufferSize;
			}

			/*Update target delay*/
			targetDelayPtr++;
			targetDelayPtr = targetDelayPtr % bufferSize;

			break;
	}

	return delayBuffer[delayPtr];
}

double SimpleDelay::calculateDryWetSignal(double dry, double wet)
{
	return (dry * (1 - dryWet)) + (wet * dryWet);
}

//=======================================================================================================
