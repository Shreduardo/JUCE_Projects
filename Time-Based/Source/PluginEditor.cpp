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
	delayFeedbackDial.setRange(0, .99);
	delayFeedbackDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
	delayFeedbackDial.setTextBoxIsEditable(true);
	delayFeedbackDial.addListener(this);

	addAndMakeVisible(delayFeedbackDial);

	//Interpolation Label
	interpolationLabel.setText("Interpolation Type", dontSendNotification); 
	interpolationLabel.setJustificationType(Justification::centred);

	addAndMakeVisible(interpolationLabel);

	//Interpolation Buttons
	jumpInterpolationButton.setButtonText("Jump");
	crossfadeInterpolationButton.setButtonText("Crossfade");

	addAndMakeVisible(jumpInterpolationButton);
	addAndMakeVisible(crossfadeInterpolationButton);
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

	jumpInterpolationButton.setBoundsRelative(.1f, .25f, .1f, .1f);
	crossfadeInterpolationButton.setBoundsRelative(.1f, .35f, .1f, .1f);

	interpolationLabel.attachToComponent(&jumpInterpolationButton, false);
	interpolationLabel.setBoundsRelative(.05f, .15f, .2f, .1f);
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

void TimebasedAudioProcessorEditor::buttonClicked(Button* button)
{
	if (button == &jumpInterpolationButton)
	{
		processor.updateInterpolation(SimpleDelay::DelayTimeInterpolation::JUMP);
	}

	if (button == &crossfadeInterpolationButton)
	{
		processor.updateInterpolation(SimpleDelay::DelayTimeInterpolation::CROSSFADE);
	}
}
