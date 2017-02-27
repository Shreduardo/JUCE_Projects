# Ladder Filter

This project serves as my midterm project as well as the first of the final
three projects I plan on completing this semester.

## Rundown

This ladder filter is based off the tradition Moog ladder filters. Basically,
it is a 24db/Octave, non-resonance limiting lowpass filter. It is build as a VST
plugin to be hosted by audio software programs.

The 24db/Octave feature is created by cascading two biquad filters. The
coefficients are calculated by formulas I obtained from earlevelengineering.com
Shoutout to Nigel Redmon, your tutorials are amazing!

## Features

1. Dynamic cutoff selection
2. Dynamic resonance selection

## In progress

1. A better GUI (;
2. Parameter smoothing
3. Resonance effect is minimal
4. Fixing of a strange phasing effect at low cutoffs
