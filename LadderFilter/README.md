# Ladder Filter

This project serves as my midterm project as well as the first of the final
three projects I plan on completing this semester.

## Rundown

This ladder filter is based off the tradition Moog ladder filters. Basically,
it is a 24db/Octave, non-resonance limiting lowpass filter. It is build as a VST
plugin to be hosted by audio software programs.

The 24db/Octave feature is created by cascading four one-pole filters. The
coefficients are calculated by formulas I obtained from the musicdsp.org filter
archive.

Shoutout to Nigel Redmon and RBJ, your tutorials are amazing!

## Features

1. Dynamic cutoff selection
2. Dynamic resonance selection
4. 4 Poles, 24 db/Octave

## Update v.02

1. Decoupling of Q and cutoff by using 4 pole, Moog VCF design.
  * Biquad has harsh coupling of these two parameters
2. Fixed distortion and strange phasing at low frequencies.
3. Unlimited resonance

## In progress

1. A better GUI (;
2. Buffer holds output with high resonance and changing cutoff
