#include "SpectrumAnalizer.h"

SpectrumAnalizer::SpectrumAnalizer() : forwardFFT(fftOrder), window(fftSize, dsp::WindowingFunction<float>::hann)
{
    setOpaque(true);
    startTimerHz(30);
    setSize(600, 400);

    spectrum_button.reset(new TextButton("spectrum_button"));
    addAndMakeVisible(spectrum_button.get());
    spectrum_button->setButtonText(TRANS("Equalizer"));
    spectrum_button->addListener(this);

    spectrum_button->setBounds(434, 16, 150, 24);
}

void SpectrumAnalizer::paint(Graphics& g)
{
    g.fillAll(Colours::white);

    g.setOpacity(1.0f);
    g.setColour(Colours::black);

    drawFrame(g);
}

void SpectrumAnalizer::timerCallback()
{
    if (nextFFTBlockReady)
    {
        drawNextFrameOfSpectrum();
        nextFFTBlockReady = false;
        repaint();
    }
}

void SpectrumAnalizer::pushNextSampleIntoFifo(float sample) noexcept
{
    // if the fifo contains enough data, set a flag to say
    // that the next frame should now be rendered..
    if (fifoIndex == fftSize)
    {
        if (!nextFFTBlockReady)
        {
            zeromem(fftData, sizeof(fftData));
            memcpy(fftData, fifo, sizeof(fifo));
            nextFFTBlockReady = true;
        }

        fifoIndex = 0;
    }

    fifo[fifoIndex++] = sample;
}

void SpectrumAnalizer::drawNextFrameOfSpectrum()
{
    // first apply a windowing function to our data
    window.multiplyWithWindowingTable(fftData, fftSize);

    // then render our FFT data..
    forwardFFT.performFrequencyOnlyForwardTransform(fftData);

    auto mindB = -100.0f;
    auto maxdB = 0.0f;

    for (int i = 0; i < scopeSize; ++i)
    {
        auto skewedProportionX = 1.0f - std::exp(std::log(1.0f - i / (float)scopeSize) * 0.2f);
        auto fftDataIndex = jlimit(0, fftSize / 2, (int)(skewedProportionX * fftSize / 2));
        auto level = jmap(jlimit(mindB, maxdB, Decibels::gainToDecibels(fftData[fftDataIndex])
            - Decibels::gainToDecibels((float)fftSize)),
            mindB, maxdB, 0.0f, 1.0f);

        scopeData[i] = level;
    }
}

void SpectrumAnalizer::drawFrame(Graphics& g)
{
    auto bounds = getLocalBounds().reduced(10);

    g.setOpacity(0.3);
    g.setColour(Colours::grey);
    //grid painting
    for (int i = -15; i < 15; i++)
        g.drawHorizontalLine(jmap(0.33784f + i * 0.01120f, 0.0f, 1.0f, (float)400, 0.0f), 0.f, 600.f);

    g.setOpacity(1.0);
    g.setColour(Colours::black);
    for (int i = 1; i < scopeSize; ++i)
    {
        auto width = bounds.getWidth();
        auto height = bounds.getHeight();

        g.drawLine({ (float)jmap(i - 1, 0, scopeSize - 1, 0, width),
                              jmap(scopeData[i - 1], 0.0f, 1.0f, (float)height, 0.0f),
                      (float)jmap(i,     0, scopeSize - 1, 0, width),
                              jmap(scopeData[i],     0.0f, 1.0f, (float)height, 0.0f) });
    }
}

void SpectrumAnalizer::buttonClicked(Button* buttonThatWasClicked)
{
    this->setVisible(false);
}