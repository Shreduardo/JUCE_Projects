Week 2 Independent Study: Double oscillator generator =========================
======================================================================================================================================
Hello! This is a README guide for the v0.01 version additive oscillator generator.
--------------------------------------------------------------------------------------------------------------------------------------
This project was mostly intended to get a better feel of the JUCE environment and workflow. I took what I learned from 
the first half of the JUCE online tutorials and applied it to a self-assigned "homework" project. 

There are a few issues with this project (that I will explain shortly). For clarification, this does NOT serve as one of my 
intended final projects for the independent study. It is only a way to put the things I have learned thus far into practice.
Though, this will not be the only iteration of this project. It will most likely serve as an on-going assignment to put the 
learned principles to work. 
--------------------------------------------------------------------------------------------------------------------------------------
With that being said, here is a general run down of the project:

	i) This is a dual "additive" oscillator generator. Two oscillators, running simultanesouly with completely independent 
	   controls, are added together and sent to the output buffer to be played.

	ii) It is quite quiet as I introduced a pretty extreme level-safety multiplier to ensure no speakers are blown by accident.

	iii) There are artefacts that come out during frequency parameter changing. Though my basic smoothing algorithm works with
	     a single oscillator, I have not been able to get it right (with my knowledge thus far) using two oscillators. Two 
	     oscialltors, one output buffer-tricky! 

		a) Aside: The next tutorial is on polyphony and I am sure the issues will be cleared up then.

	iv) The sliders, when clicked and released, also produce a percusive "knock" sound. I originally thought these were artefacts
	    when working on the single oscillator. However, I have come to realize it is just the sound effect. Very annoying, in my
	    opinion, and working on turning that off. 
--------------------------------------------------------------------------------------------------------------------------------------
That is all for now! Go ahead and give it a whirl. 
======================================================================================================================================

	