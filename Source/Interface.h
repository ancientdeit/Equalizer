/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Interface  : public Component,
                   public Slider::Listener
{
public:
    //==============================================================================
    Interface ();
    ~Interface();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* metal_jpg;
    static const int metal_jpgSize;
    static const char* plate_png;
    static const int plate_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> label;
    std::unique_ptr<Label> label2;
    std::unique_ptr<Label> label3;
    std::unique_ptr<Slider> l_freq_slider;
    std::unique_ptr<Slider> m_freq_slider;
    std::unique_ptr<Slider> h_freq_slider;
    std::unique_ptr<Slider> l_gain_slider;
    std::unique_ptr<Slider> m_gain_slider;
    std::unique_ptr<Slider> h_gain_slider;
    std::unique_ptr<Label> label4;
    std::unique_ptr<Label> label5;
    std::unique_ptr<Label> label6;
    std::unique_ptr<Label> label7;
    std::unique_ptr<Label> label9;
    std::unique_ptr<Label> label10;
    std::unique_ptr<Slider> m_gain_slider2;
    Image cachedImage_metal_jpg_1;
    Image cachedImage_plate_png_2;
    Image cachedImage_plate_png_3;
    Image cachedImage_plate_png_4;
    Image cachedImage_plate_png_5;
    Image cachedImage_plate_png_6;
    Image cachedImage_plate_png_7;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Interface)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
