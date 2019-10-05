/*
  ==============================================================================

    LookFeel.h
    Created: 5 Oct 2019 10:39:23am
    Author:  ancie

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class OtherLookAndFeel : public LookAndFeel_V4
{
public:
    static const char* knob_png;
    static const int knob_pngSize;

    static const char* slid_png;
    static const int slid_pngSize;

    Image cachedImage_knob_png_1;
    Image cachedImage_slid_png_1;

    OtherLookAndFeel()
    {
        setColour(Slider::thumbColourId, Colours::red);

        cachedImage_knob_png_1 = ImageCache::getFromMemory(knob_png, knob_pngSize);
        cachedImage_slid_png_1 = ImageCache::getFromMemory(slid_png, slid_pngSize);
    }

    void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override;

};