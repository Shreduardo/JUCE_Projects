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
	double b1, b2;
	double z1_1, z1_2, z2_1, z2_2, z_buff;

};



#endif  // FILTER_H_INCLUDED
