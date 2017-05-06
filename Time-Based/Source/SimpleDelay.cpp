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

#define _USE_MATH_DEFINES
#include <cmath>




using namespace std; 

SimpleDelay::SimpleDelay()
{
	sampleRate = 0.0;

	delayTimeInMS = 0.0;
	feedbackAmount = 0.2;

	currentPtr = 0;
	delayPtr = 0;
	targetDelayPtr = 0;

	delayTimeInSamples = 0.0;

	dryWet = 0;

	double feedbackAmount;

	smoothing = DelayTimeSmoothing::CROSSFADE;

	b1 = exp(-2.0 * M_PI * 5); //5 Hz Frequency cutoff for smoothing
	a0 = 1 - b1;
	z = 0.0;
}

SimpleDelay::~SimpleDelay()
{

}

void SimpleDelay::init(double sr)
{
	sampleRate = sr;

	bufferSize = 2 * (sampleRate * MAX_DELAY_TIME_MS); //sampleRate * MAX_DELAY_TIME_MS = MAX_DELAY_TIME_SAMPLES
	delayBuffer = new double [bufferSize] ();

	updateDelayTime(delayTimeInMS);
	updateFeedbackAmount(feedbackAmount);


}

/*TODO: Parameter smoothing*/
void SimpleDelay::updateDelayTime(double time)
{

	//Set new delay times
	delayTimeInMS = smoothDelayTime(time);
	delayTimeInSamples = (delayTimeInMS / 1000.0) * sampleRate;

	delayPtr = (currentPtr - ((int)delayTimeInSamples));
	if (delayPtr < 0) delayPtr += bufferSize;

	//Update necessary variables for interpolation type
	//switch (smoothing)
	//{
	//case JUMP:
	//	delayPtr = (currentPtr - (delayTimeInSamples));
	//	if (delayPtr < 0) delayPtr += bufferSize;
	//	targetDelayPtr = delayPtr;
	//	break;

	//case PITCH:
	//	/*	delayTime = time;
	//	delayTimeInSamples = (delayTime / 1000) * sampleRate;

	//	delayPtr =
	//	break;*/

	//case CROSSFADE:
	//	targetDelayPtr = (currentPtr - delayTimeInSamples);
	//	if (targetDelayPtr < 0) targetDelayPtr += bufferSize;
	//	break;
	//}
	//

}

//Update Functions========================================================================================
void SimpleDelay::updateFeedbackAmount(double feedback)
{
	feedbackAmount = feedback;
}

void SimpleDelay::updateDelayTimeInterpolation(SimpleDelay::DelayTimeSmoothing newInterpolation)
{
	smoothing = newInterpolation;
}

void SimpleDelay::updateDryWet(double amount)
{
	dryWet = amount;
}

//Audio Thread===========================================================================================
double SimpleDelay::process(double input)
{
	const double fractionalDelay = interpolate();
	//const double wet = smoothDelayTime(input);
	const double out = calculateDryWetSignal(input, fractionalDelay);

	delayBuffer[currentPtr] = input + (delayBuffer[delayPtr] * feedbackAmount);

	++delayPtr;
	delayPtr = delayPtr % bufferSize;

	++currentPtr;
	currentPtr = currentPtr % bufferSize;

	return out;
}

double SimpleDelay::interpolate()
{
	const double interpolationAmount = delayTimeInSamples - (int)delayTimeInSamples;

	return (delayBuffer[delayPtr] * (1 - interpolationAmount)) + (delayBuffer[delayPtr - 1] * interpolationAmount);

}
double SimpleDelay::smoothDelayTime(double input)
{
	//Smoothing;
	return z = input * a0 + z * b1;

	//delayBuffer[currentPtr] = input + (delayBuffer[delayPtr] * feedbackAmount);

	//return delayBuffer[delayPtr];
	//assert(delayBuffer != NULL);

	//switch (interpolation)
	//{
	//	case JUMP:
	//		delayBuffer[currentPtr] = input + (delayBuffer[delayPtr] * feedbackAmount);	
	//		delayPtr++;
	//		delayPtr = delayPtr % bufferSize;
	//		break;

	//	case PITCH:
	//		/*	delayTime = time;
	//		delayTimeInSamples = (delayTime / 1000) * sampleRate;

	//		delayPtr =
	//		break;*/

	//	case CROSSFADE:
	//		//Only interpolate if difference is greater than interpolation interval (10)
	//		if (targetDelayPtr != delayPtr) {

	//			/* Get crossfade value of samples*/
	//			const double crossFade = (delayBuffer[targetDelayPtr] - delayBuffer[delayPtr]) / 10;
	//			delayBuffer[currentPtr] = input + (crossFade * feedbackAmount);

	//			/*Update delay time based on interval multiples of difference*/
	//			const double delayIndexChangeInterval = (targetDelayPtr - delayPtr) / 10;
	//			delayPtr += delayIndexChangeInterval;

	//		}
	//		else {
	//			targetDelayPtr = delayPtr;
	//			/*Output delay index if no change*/
	//			delayBuffer[currentPtr] = input + (delayBuffer[delayPtr] * feedbackAmount);

	//			delayPtr++;
	//			delayPtr = delayPtr % bufferSize;
	//		}

	//		/*Update target delay*/
	//		targetDelayPtr++;
	//		targetDelayPtr = targetDelayPtr % bufferSize;

	//		break;
	//}

	//return delayBuffer[delayPtr];
}

double SimpleDelay::calculateDryWetSignal(double dry, double wet)
{
	return (dry * (1 - dryWet)) + (wet * dryWet);
}

//=======================================================================================================
