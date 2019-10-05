/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "LookFeel.h"

struct ParameterSlider : public Slider,
	public Timer
{
	ParameterSlider(AudioProcessorParameter& p, std::unique_ptr<Slider> &slide)
		: s(slide), param(p)
	{
		setRange(0.0, 1.0, 0.0);
		startTimerHz(30);
		updateSliderPos();
	}

	void valueChanged() override
	{
		if (isMouseButtonDown())
			param.setValueNotifyingHost((float)s->getValue());
		else
			param.setValue((float)s->getValue());
	}

	void timerCallback() override { updateSliderPos(); }

	void startedDragging() override { param.beginChangeGesture(); }
	void stoppedDragging() override { param.endChangeGesture(); }

	double getValueFromText(const String& text) override { return param.getValueForText(text); }
	String getTextFromValue(double value) override { return param.getText((float)value, 1024) + " " + param.getLabel(); }

	void updateSliderPos()
	{
		const float newValue = param.getValue();

		if (newValue != (float)s->getValue() && !isMouseButtonDown())
			s->setValue(newValue);
	}

	AudioProcessorParameter& param;
    std::unique_ptr<Slider>& s;
};

//==============================================================================
/**
*/
class EqualizerAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener
{
public:
    EqualizerAudioProcessorEditor (EqualizerAudioProcessor&);
    ~EqualizerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* metal_jpg;
    static const int metal_jpgSize;
    static const char* plate_png;
    static const int plate_pngSize;


private:

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EqualizerAudioProcessor& processor;

    std::unique_ptr<Label> label;
    std::unique_ptr<Label> label2;
    std::unique_ptr<Label> label3;
    std::unique_ptr<Slider> l_freq_slider;
    std::unique_ptr<Slider> m_freq_slider;
    std::unique_ptr<Slider> h_freq_slider;
    std::unique_ptr<Slider> l_gain_slider;
    std::unique_ptr<Slider> m_gain_slider;
    std::unique_ptr<Slider> m_band_slider;
    std::unique_ptr<Slider> h_gain_slider;
    std::unique_ptr<Label> label4;
    std::unique_ptr<Label> label5;
    std::unique_ptr<Label> label6;
    std::unique_ptr<Label> label7;
    std::unique_ptr<Label> label9;
    std::unique_ptr<Label> label10;
    Image cachedImage_metal_jpg_1;
    Image cachedImage_plate_png_2;
    Image cachedImage_plate_png_3;
    Image cachedImage_plate_png_4;
    Image cachedImage_plate_png_5;
    Image cachedImage_plate_png_6;
    Image cachedImage_plate_png_7;

    OtherLookAndFeel otherLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerAudioProcessorEditor)
};