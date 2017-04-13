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

	delayTimeInSamples = 0;
	
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

void SimpleDelay::updateDelayTime(double time)
{
	delayTime = time;
	delayTimeInSamples = (delayTime / 1000) * sampleRate;

	delayPtr = (currentPtr - (delayTimeInSamples));
	if (delayPtr < 0) delayPtr += bufferSize;
}

void SimpleDelay::updateFeedbackAmount(double feedback)
{
	feedbackAmount = feedback;
}

double SimpleDelay::process(double input)
{

	write(input);
	double out = read();

	++currentPtr;
	currentPtr = currentPtr % bufferSize;

	++delayPtr;
	delayPtr = delayPtr % bufferSize;

	return out;
}

double SimpleDelay::read()
{
	return delayBuffer[delayPtr];
}

void SimpleDelay::write(double input)
{
	assert(delayBuffer != NULL);
	delayBuffer[currentPtr] = input + (delayBuffer[delayPtr] * feedbackAmount);
}