/*
  ==============================================================================

    Oscillator.h
    Created: 11 Feb 2017 6:28:32pm
    Author:  Ed

  ==============================================================================
*/

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED

//Should probably start a thread

class Oscillator
{
public:

	Oscillator();
	~Oscillator();

	/***Functions not called on audio thread***/

	//Sets SR and angles to begin updating oscillator
	void init(double sampleRate);

	//Set functions to be called after user interaction
	void setTargetFrequency(double target);
	void setLevel(double level);


	/***Functions that will be called on audio thread***/

	//Called as oscialltor is being put into buffer to play
	void updateFrequency(int numberOfSamples);

	//Retrieve current oscillator data to be put into sample
	float getCurrentSample();

	


private:
	
	//Internal update of oscialltor phase
	void updateAngleDelta();
	void updateAngle();
	
	
	/*State Variables*/

	//Phase variables
	double currentAngle, angleDelta;

	//Frequency variables
	double currentFrequency, targetFrequency;

	//Level variables
	double currentLevel;

	//SR variable
	double currentSampleRate;
};



#endif  // OSCILLATOR_H_INCLUDED
