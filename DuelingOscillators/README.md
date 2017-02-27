# Dueling Oscillators

Hello! This is a README guide for the v0.02 version oscillator generator.

## Purpose

This project was mostly intended to get a better feel of the JUCE environment
and workflow. I took what I learned from a few of the JUCE online tutorials and
applied it to a self-assigned "homework" project.

There are a few issues with this project (that I will explain shortly). For
clarification, this does NOT serve as one of my intended final projects for the
independent study. It is only a way to put the things I have learned thus far
into practice. Though, this will not be the only iteration of this project. It
will most likely serve as an on-going assignment to put the learned principles
to work.

## Rundown
	1. This is a dual oscillator generator. Two oscillators, running
	simultaneously with completely independent controls, are added together and
	sent to the output buffer to be played.
	  * I understand because the oscillators are added together, calling them
	  "dueling" is a bit of a misnomer. However, dueling sounds better than
	  hugging (:

	2. It is quite quiet as I introduced a pretty extreme level-safety
	multiplier to ensure no speakers are blown by accident.

	3. The sliders, when clicked and released, produce a percussive "knock"
	sound. I originally thought these were artefacts when working on the single
	oscillator. However, I have come to realize it is just the sound effect.
	Very annoying, in my opinion, and working on turning that off.

## Updates

	1. v0.03
	  1. Added a biquad lowpass filter and slider to control cutoff
	    * Very simple implementation as this was practice for my midterm project
		which will be a more feature filled, robust and 24dB/octave lowpass

	  2. Still ugly :,(
		  
	2. v0.02
	  1. Introduced object oriented paradigms to create better SoC and emphasize
	  DRY principles. All around, the project is much less monolithic than the
	  first version.
	    * Created Oscillator class to handle and update data of Oscillators.
		* Set up structure for GUI to be laid out with OO principles.

	  2. Artefacts produced by moving the second oscillators frequency sliders
	  has been fixed. This is mostly due to the update on separating concerns.



Give it a whirl!
