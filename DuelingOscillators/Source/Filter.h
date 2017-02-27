/*
  ==============================================================================

    Filter.h
    Created: 23 Feb 2017 1:57:00am
    Author:  Ed

  ==============================================================================
*/

#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#define _USE_MATH_DEFINES

#include <math.h>


class Filter
{
public:

	Filter();
	~Filter();

	void init(float sampleRate);

	void updateCutoff(float freq);
	void updateResonance(float Q);


	void calculateCoefficients();
	float applyFilter(float in);


private:

	float res;
	float cutoff;
	float currentSampleRate;

	float a0, a1, a2;
	float b1, b2;
	float z1, z2, z11, z22;
	float z_buff;
	float norm;
	
	const float pi = M_PI;

};


#endif  // FILTER_H_INCLUDED
