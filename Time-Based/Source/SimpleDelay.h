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

	void write(double input);
	double read();

	double process(double input);


private:
	double sampleRate;

	double delayTime;
	int delayTimeInSamples;
	double feedbackAmount;

	const int MAX_DELAY_TIME_MS = 2000;

	double* delayBuffer;
	int bufferSize;

	int currentPtr;
	int delayPtr;
};




#endif  // SIMPLEDELAY_H_INCLUDED
