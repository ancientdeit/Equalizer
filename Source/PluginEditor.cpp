/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "LowPassFilter.h"

//==============================================================================
EqualizerAudioProcessorEditor::EqualizerAudioProcessorEditor (EqualizerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),
	lowLabel({}, processor.lowParam->name),
	gainlowLabel({}, processor.gainlowParam->name),
	topLabel({}, processor.topParam->name),
	gaintopLabel({}, processor.gaintopParam->name),
	peakLabel({}, processor.peakParam->name),
	bandpeakLabel({}, processor.bandpeakParam->name),
	gainpeakLabel({}, processor.gainpeakParam->name)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	addAndMakeVisible(lowSlider = new ParameterSlider(*processor.lowParam));
	addAndMakeVisible(gainlowSlider = new ParameterSlider(*processor.gainlowParam));
	addAndMakeVisible(topSlider = new ParameterSlider(*processor.topParam));
	addAndMakeVisible(gaintopSlider = new ParameterSlider(*processor.gaintopParam));
	addAndMakeVisible(peakSlider = new ParameterSlider(*processor.peakParam));
	addAndMakeVisible(bandpeakSlider = new ParameterSlider(*processor.bandpeakParam));
	addAndMakeVisible(gainpeakSlider = new ParameterSlider(*processor.gainpeakParam));

	addAndMakeVisible(lowLabel);
	lowLabel.setJustificationType(Justification::centredLeft);
	lowLabel.attachToComponent(lowSlider, true);

	addAndMakeVisible(gainlowLabel);
	gainlowLabel.setJustificationType(Justification::centredLeft);
	gainlowLabel.attachToComponent(gainlowSlider, true);

	addAndMakeVisible(topLabel);
	topLabel.setJustificationType(Justification::centredLeft);
	topLabel.attachToComponent(topSlider, true);

	addAndMakeVisible(gaintopLabel);
	gaintopLabel.setJustificationType(Justification::centredLeft);
	gaintopLabel.attachToComponent(gaintopSlider, true);

	addAndMakeVisible(peakLabel);
	peakLabel.setJustificationType(Justification::centredLeft);
	peakLabel.attachToComponent(peakSlider, true);

	addAndMakeVisible(bandpeakLabel);
	bandpeakLabel.setJustificationType(Justification::centredLeft);
	bandpeakLabel.attachToComponent(bandpeakSlider, true);

	addAndMakeVisible(gainpeakLabel);
	gainpeakLabel.setJustificationType(Justification::centredLeft);
	gainpeakLabel.attachToComponent(gainpeakSlider, true);

	setSize(600, 400);
}

EqualizerAudioProcessorEditor::~EqualizerAudioProcessorEditor()
{
}

//==============================================================================
void EqualizerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)

    //g.setFont (15.0f);
    //g.drawFittedText ("EQ test", getLocalBounds(), Justification::centred, 1);

	test.addXY(5, 5);

	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

	g.setColour(Colours::white);
}

void EqualizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	auto bounds = getLocalBounds().reduced(10);
	bounds.removeFromTop(10);
	bounds.removeFromLeft(125);

	//==============================================================================
	lowSlider->setBounds(bounds.removeFromTop(30));
	bounds.removeFromTop(5);

	gainlowSlider->setBounds(bounds.removeFromTop(30));
	bounds.removeFromTop(5);

	topSlider->setBounds(bounds.removeFromTop(30));
	bounds.removeFromTop(5);

	gaintopSlider->setBounds(bounds.removeFromTop(30));
	bounds.removeFromTop(5);

	peakSlider->setBounds(bounds.removeFromTop(30));
	bounds.removeFromTop(5);

	bandpeakSlider->setBounds(bounds.removeFromTop(30));
	bounds.removeFromTop(5);

	gainpeakSlider->setBounds(bounds.removeFromTop(30));
	bounds.removeFromTop(5);
}