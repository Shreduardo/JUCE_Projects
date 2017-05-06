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
	//delayFeedbackDial.setTextValueSuffix(" %");
	delayFeedbackDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
	delayFeedbackDial.setTextBoxIsEditable(true);
	delayFeedbackDial.addListener(this);

	addAndMakeVisible(delayFeedbackDial);

	//Dry/Wet Dial
	dryWetDial.setSliderStyle(Slider::Rotary);
	dryWetDial.setRange(0.0, 1.0);
	//dryWetDial.setTextValueSuffix(" %");
	dryWetDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
	dryWetDial.setTextBoxIsEditable(true);
	dryWetDial.addListener(this);

	addAndMakeVisible(dryWetDial);

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
	delayFeedbackDial.setBoundsRelative(0.7f, 0.25f, .2f, .2f);
	dryWetDial.setBoundsRelative(0.7f, 0.5f, .2f, .2f);

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

	if (slider == &dryWetDial)
	{
		processor.updateDryWet(dryWetDial.getValue());
	}
}

void TimebasedAudioProcessorEditor::buttonClicked(Button* button)
{
	if (button == &jumpInterpolationButton)
	{
		processor.updateInterpolation(SimpleDelay::DelayTimeSmoothing::JUMP);
	}

	if (button == &crossfadeInterpolationButton)
	{
		processor.updateInterpolation(SimpleDelay::DelayTimeSmoothing::CROSSFADE);
	}
}
