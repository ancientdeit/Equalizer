/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "LowPassFilter.h"
#include "EQ.h"
#include<string>

//==============================================================================
/**
*/
class EqualizerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    EqualizerAudioProcessor();
    ~EqualizerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void updateParameters(int numSamples);
	//==============================================================================
	AudioParameterFloat* lowParam;
	AudioParameterFloat* gainlowParam;
	AudioParameterFloat* topParam;
	AudioParameterFloat* gaintopParam;
	AudioParameterFloat* peakParam;
	AudioParameterFloat* bandpeakParam;
	AudioParameterFloat* gainpeakParam;

private:
	EQ *basseq;
	EQ *peakeq;
	EQ *topeq;

	
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerAudioProcessor)
};
