/*
==============================================================================

SimpleDelay.h
Created: 4 Apr 2017 12:01:56am
Author:  Ed

==============================================================================
*/


#ifndef SIMPLEDELAY_H_INCLUDED
#define SIMPLEDELAY_H_INCLUDED

class SimpleDelay {
public:
	SimpleDelay();
	~SimpleDelay();

	void init(double sampleRate);

	void updateDelayTime(double time);
	void updateFeedbackAmount(double feedback);
	void updateDryWet(double dryWet);

	void write(double input);
	double read();

	double calculateDryWetSignal(double dry, double wet);
	double process(double input);

	enum DelayTimeSmoothing {
		JUMP,
		CROSSFADE,
		PITCH
	};
	
	double smoothDelayTime(double input);
	void updateDelayTimeInterpolation(DelayTimeSmoothing);

private:
	double sampleRate;

	double dryWet;

	double delayTimeInMS;
	double delayTimeInSamples;
	const int MAX_DELAY_TIME_MS = 2000;

	double feedbackAmount;

	double* delayBuffer;
	int bufferSize;

	int currentPtr;
	int delayPtr;
	int targetDelayPtr;

	double interpolate();

	//One-Pole for parameter smoothing
	double a0;
	double b1;
	double z;
	double SMOOTHING_TIME_IN_SAMPLES;



	double lfo;
	DelayTimeSmoothing smoothing; 
};




#endif  // SIMPLEDELAY_H_INCLUDED
