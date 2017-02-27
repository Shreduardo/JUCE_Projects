/*
  ==============================================================================

    Filter.cpp
    Created: 25 Feb 2017 10:49:19pm
    Author:  Ed

  ==============================================================================
*/
#define _USE_MATH_DEFINES

#include "Filter.h"

#include <math.h>


Filter :: Filter()
{
	cutoff = 20000;
	Q = 0.707;

	//Turn into pointer arrays and store in registers
	a0 = a1 = a2 = 0.0;
	b1 = b2 = 0.0;

	//Store these in registers
	z1_1 = z1_2 = 0;
	z2_1 = z2_2 = 0;
	z_buff = 0.0;
}

Filter :: ~Filter()
{

}

void Filter :: init(float sampleRate)
{
	currentSampleRate = sampleRate;
	calculateBiquad();
}

void Filter :: updateCutoff(double freq)
{
	cutoff = freq;
	calculateBiquad();
}

void Filter :: updateResonance(double res)
{
	Q = res;
	calculateBiquad();
}


//Coefficient formulas provided by Earlevelengineering.com
void Filter :: calculateBiquad()
{
	double norm;

	float K = tan(M_PI * (cutoff / currentSampleRate));
	norm = 1 / (1 + K / Q + (K * K));
	
	a0 = K * K * norm;
	a1 = 2 * a0;
	a2 = a0;

	b1 = 2 * (K * K - 1) * norm;
	b2 = (1 - K / Q + K * K) * norm;
}

float Filter::applyFilter(float in)
{
	//Biquad 1
	double out = in * a0 + z1_1;

	z1_1 = in * a1 + z1_2 - b1 * out;
	z1_2 = in * a2 - b2 * out;

	//Cascade into Biquad 2
	z_buff = out;

	out = z_buff * a0 + z2_1;
	z2_1 = z_buff * a1 + z2_2 - b1 * out;
	z2_2 = z_buff * a2 - b2 * out;

	return out;
}


