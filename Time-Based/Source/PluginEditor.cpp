/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TimebasedAudioProcessorEditor::TimebasedAudioProcessorEditor (TimebasedAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	setSize (800, 600);

	//Delay Time Dial
	delayTimeDial.setSliderStyle(Slider::Rotary);
	delayTimeDial.setRange(0, 2000);
	delayTimeDial.setTextValueSuffix(" ms");
	delayTimeDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
	delayTimeDial.setTextBoxIsEditable(true);
	delayTimeDial.addListener(this);

	addAndMakeVisible(delayTimeDial);

	//Delay Feedback Dial
	delayFeedbackDial.setSliderStyle(Slider::Rotary);
	delayFeedbackDial.setRange(0, 1.0);
	delayFeedbackDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
	delayFeedbackDial.setTextBoxIsEditable(true);
	delayFeedbackDial.addListener(this);

	addAndMakeVisible(delayFeedbackDial);
}

TimebasedAudioProcessorEditor::~TimebasedAudioProcessorEditor()
{

}

//==============================================================================
void TimebasedAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(Colours::white);

	delayTimeDial.setBoundsRelative(0.5f, 0.25f, .2f, .2f);
	delayFeedbackDial.setBoundsRelative(0.5f, 0.75f, .2f, .2f);
}

void TimebasedAudioProcessorEditor::resized()
{

}


/*Delay Interaction*/
void TimebasedAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	if (slider == &delayTimeDial)
	{
		processor.updateDelayTime(delayTimeDial.getValue());
	}

	if (slider == &delayFeedbackDial)
	{

		processor.updateDelayFeedback(delayFeedbackDial.getValue());
	}
}
