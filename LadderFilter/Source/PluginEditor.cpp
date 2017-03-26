/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
LadderFilterAudioProcessorEditor::LadderFilterAudioProcessorEditor (LadderFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (500, 500);

	//Cutoff Dial
	cutoffDial.setSliderStyle(Slider::Rotary);
	cutoffDial.setRange(50.0, 20000.0);
	cutoffDial.setSkewFactorFromMidPoint(1000);
	cutoffDial.setTextValueSuffix(" Hz");
	cutoffDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
	cutoffDial.setTextBoxIsEditable(true);
	cutoffDial.addListener(this);

	addAndMakeVisible(cutoffDial);

	//Resonance Dial
	resonanceDial.setSliderStyle(Slider::Rotary);
	resonanceDial.setRange(0, 1.5);
	resonanceDial.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 100, 50);
	resonanceDial.setTextBoxIsEditable(true);
	resonanceDial.addListener(this);

	addAndMakeVisible(resonanceDial);

}

LadderFilterAudioProcessorEditor::~LadderFilterAudioProcessorEditor()
{
	
}

//==============================================================================
void LadderFilterAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(Colours::white);

	cutoffDial.setBoundsRelative(0.5f, 0.25f, .2f, .2f);
	resonanceDial.setBoundsRelative(0.5f, 0.75f, .2f, .2f);
}

void LadderFilterAudioProcessorEditor::resized()
{
}

/***********************Filter UI Interaction**********************/
void LadderFilterAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	if (slider == &cutoffDial)
	{
		processor.updateFilterCutoff(cutoffDial.getValue());
	}

	if (slider == &resonanceDial)
	{
		processor.updateFilterResonance(resonanceDial.getValue());
	}

}
