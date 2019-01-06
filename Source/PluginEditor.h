/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

struct ParameterSlider : public Slider,
	public Timer
{
	ParameterSlider(AudioProcessorParameter& p)
		: Slider(p.getName(256)), param(p)
	{
		setRange(0.0, 1.0, 0.0);
		startTimerHz(30);
		updateSliderPos();
	}

	void valueChanged() override
	{
		if (isMouseButtonDown())
			param.setValueNotifyingHost((float)Slider::getValue());
		else
			param.setValue((float)Slider::getValue());
	}

	void timerCallback() override { updateSliderPos(); }

	void startedDragging() override { param.beginChangeGesture(); }
	void stoppedDragging() override { param.endChangeGesture(); }

	double getValueFromText(const String& text) override { return param.getValueForText(text); }
	String getTextFromValue(double value) override { return param.getText((float)value, 1024) + " " + param.getLabel(); }

	void updateSliderPos()
	{
		const float newValue = param.getValue();

		if (newValue != (float)Slider::getValue() && !isMouseButtonDown())
			Slider::setValue(newValue);
	}

	AudioProcessorParameter& param;
};

//==============================================================================
/**
*/
class EqualizerAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    EqualizerAudioProcessorEditor (EqualizerAudioProcessor&);
    ~EqualizerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EqualizerAudioProcessor& processor;

	ScopedPointer<ParameterSlider> lowSlider;
	ScopedPointer<ParameterSlider> gainlowSlider;
	ScopedPointer<ParameterSlider> topSlider;
	ScopedPointer<ParameterSlider> gaintopSlider;
	ScopedPointer<ParameterSlider> peakSlider;
	ScopedPointer<ParameterSlider> bandpeakSlider;
	ScopedPointer<ParameterSlider> gainpeakSlider;

	Label lowLabel;
	Label gainlowLabel;
	Label topLabel;
	Label gaintopLabel;
	Label peakLabel;
	Label bandpeakLabel;
	Label gainpeakLabel;

	Point<int> test;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerAudioProcessorEditor)
};
