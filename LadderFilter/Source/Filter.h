/*
  ==============================================================================

    Filter.h
    Created: 25 Feb 2017 10:49:19pm
    Author:  Ed

  ==============================================================================
*/

#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

class Filter {
public:
	Filter();
	~Filter();

	void init(float sampleRate);

	void updateCutoff(double freq);
	void updateResonance(double res);

	void calculateBiquad();
	
	float applyFilter(float in);

private:

	double Q;
	double cutoff;
	double currentSampleRate;

	double a0, a1, a2;
	double b0, b1, b2;
	double z1_1, z1_2, z2_1, z2_2, z_buff;

	/*Moog VCF*/
	//Coefficients
	float f, k, p, scale, r = 0;
	//One pole filters
	float p1, p2, p3, p4 = 0;
	//Buffers to hold previous value of pole filters
	double z0, z1, z2, z3 = 0;

	//Inverted feedback
	float inputFeedback = 0;
};



#endif  // FILTER_H_INCLUDED
