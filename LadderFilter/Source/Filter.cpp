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
	b0 = b1 = b2 = 0.0;

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



void Filter :: calculateBiquad()
{

	/*Stilson Smith Moog 24dB*/
	//These should be done in calculate coefficients
	f = 2 * (cutoff / currentSampleRate);
	k = 3.6 * f - 1.6 * f * f - 1;
	p = (k + 1) * 0.5;
	scale = pow(M_E, ((1 - p) * 1.386249));
	r = Q * scale;
	

	/*RBJ formulas*/
	//double w0 = 2 * M_PI * (cutoff / currentSampleRate);

	//double alpha = sin(w0) / (2 * Q);

	//b0 = (1 - cos(w0)) / 2;
	//b1 = 1 - cos(w0);
	//b2 = (1 - cos(w0)) / 2;

	//a0 = 1 + alpha;
	//a1 = -2 * cos(w0);
	//a2 = 1 - alpha;

	/*Earlevel Formulas*/
//	double norm;
//
//	float K = tan(M_PI * (cutoff / currentSampleRate));
//	norm = 1 / (1 + K / Q + (K * K));
//	
//	a0 = K * K * norm;
//	a1 = 2 * a0;
//	a2 = a0;
//
//	b1 = 2 * (K * K - 1) * norm;
//	b2 = (1 - K / Q + K * K) * norm;
}

float Filter::applyFilter(float in)
{

	/*Moog VCF*/

	//Invert feedback
	inputFeedback = in - r * p4;

	//Cascade onepoles
	p1 = inputFeedback*p + z0*p  - k*p1;
	p2 = p1*p            + z1*p - k*p2;
	p3 = p2*p            + z2*p - k*p3;
	p4 = p3*p            + z3*p - k*p4;

	z0 = inputFeedback;
	z1 = p2;
	z2 = p3;
	z3 = p4;

	//Band limited sigmoid
	p4 = p4 - (pow(p4, 3) / 6);

	float out = p4;

	/*RBJ*/
	/*double out = in * (b0 / a0) + z1_1;

	z1_1 = (in * (b1 / a0) - out * (a1 / a0)) + z1_2;
	z1_2 = (in * (b2 / a0) - out * (a2 / a0));
	*/

	/*Earlevel*/
	////Biquad 1
	//double out = in * a0 + z1_1;

	//z1_1 = in * a1 + z1_2 - b1 * out;
	//z1_2 = in * a2 - b2 * out;

	////Cascade into Biquad 2
	//z_buff = out;

	//out = z_buff * a0 + z2_1;
	//z2_1 = z_buff * a1 + z2_2 - b1 * out;
	//z2_2 = z_buff * a2 - b2 * out;

	return out;
}


