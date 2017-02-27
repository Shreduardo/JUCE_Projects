/*
  ==============================================================================

    Filter.cpp
    Created: 23 Feb 2017 1:57:00am
    Author:  Ed

  ==============================================================================
*/

#include "Filter.h"
#include "../JuceLibraryCode/JuceHeader.h"

#include <math.h>

Filter :: Filter()
{
	cutoff = 20000;
	res = 0.707;

	a0 = a1 = a2 = 0.0;
	b1 = b2 = 0.0;

	z1 = z2 = z11 = z22 = 0.0;
	z_buff = 0.0;


}

Filter :: ~Filter()
{

}

void Filter :: init(float sampleRate)
{
	currentSampleRate = sampleRate;
	calculateCoefficients();
}

void Filter :: updateCutoff(float freq)
{
	cutoff = freq;
	calculateCoefficients();
}

void Filter::updateResonance(float Q)
{
	res = Q;
	calculateCoefficients();
}

void Filter::calculateCoefficients()
{
	double norm;
	//float V = pow(10, 1 / 20);    //1 is peak gain for bandpass
	float K = tan(pi * (cutoff / currentSampleRate));

	norm = 1 / (1 + K / res + (K * K));
	a0 = K * K * norm;
	a1 = 2 * a0;
	a2 = a0;

	b1 = 2 * (K * K - 1) * norm;
	b2 = (1 - K / res + K * K) * norm;
}

float Filter::applyFilter(float in)
{
	double out = in * a0 + z1;
	z1 = in * a1 + z2 - b1 * out;
	z2 = in * a2 - b2 * out;

	z_buff = out; 

	out = z_buff * a0 + z11;
	z11 = z_buff * a1 + z22 - b1 * out;
	z22 = z_buff * a2 - b2 * out;

	return out;
}

