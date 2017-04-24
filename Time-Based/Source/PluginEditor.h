/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class TimebasedAudioProcessorEditor  : public AudioProcessorEditor, public Slider :: Listener, public Button :: Listener
{
public:
    TimebasedAudioProcessorEditor (TimebasedAudioProcessor&);
    ~TimebasedAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void sliderValueChanged(Slider* slider) override;
	void buttonClicked(Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TimebasedAudioProcessor& processor;

	Slider delayTimeDial;
	Slider delayFeedbackDial;

	Label interpolationLabel;
	TextButton jumpInterpolationButton;
	TextButton crossfadeInterpolationButton; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimebasedAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
