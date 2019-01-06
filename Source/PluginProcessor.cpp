/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
EqualizerAudioProcessor::EqualizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	addParameter(lowParam = new AudioParameterFloat("LOWEQ", "Bass Freq", { 0.f, 500.f, 0.f, 0.5f }, 0.5f, "Hz"));
	addParameter(gainlowParam = new AudioParameterFloat("LOWEQG", "Bass Level", { -15.f, 15.f, 0.f, 0.5f }, 0.f, "dB"));
	addParameter(topParam = new AudioParameterFloat("TOPEQ", "Treble Freq", { 1000.f, 5000.f, 0.f, 0.5f }, 1000.f, "Hz"));
	addParameter(gaintopParam = new AudioParameterFloat("TOPEQG", "Treble Level", { -15.f, 15.f, 0.f, 0.5f }, 0.f, "dB"));
	addParameter(peakParam = new AudioParameterFloat("PEAKEQ", "Peak Freq", { 500.f, 1000.f, 0.f, 0.5f }, 500.f, "Hz"));
	addParameter(bandpeakParam = new AudioParameterFloat("PEAKEQB", "Peak Band Freq", { 10.f, 300.f, 0.f, 0.5f }, 10.f, "Hz"));
	addParameter(gainpeakParam = new AudioParameterFloat("PEAKEQG", "Peak Level", { -15.f, 15.f, 0.f, 0.5f }, 0.f, "dB"));

	basseq = new EQ(LowShelf);
	peakeq = new EQ(Peak);
	topeq = new EQ(HighShelf);
}

EqualizerAudioProcessor::~EqualizerAudioProcessor()
{
}

//==============================================================================
const String EqualizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EqualizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EqualizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double EqualizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EqualizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EqualizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EqualizerAudioProcessor::setCurrentProgram (int index)
{
}

const String EqualizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void EqualizerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void EqualizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void EqualizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EqualizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EqualizerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...

	updateParameters(buffer.getNumSamples());

	float* leftChannel = buffer.getWritePointer(0);
	float* rightChannel = buffer.getWritePointer(1);

	for (int i = 0; i < buffer.getNumSamples(); i++)
	{
		leftChannel[i] = topeq->Tick(peakeq->Tick(basseq->Tick(leftChannel[i], 0), 0), 0);
		rightChannel[i] = topeq->Tick(peakeq->Tick(basseq->Tick(rightChannel[i], 1), 1), 1);
	}
}

void EqualizerAudioProcessor::updateParameters(int numSamples)
{
	//bass
	auto templowfreq = lowParam->get();
	auto templowgain = gainlowParam->get();
	
	if (basseq->gain != templowgain || basseq->freq != templowfreq || basseq->samFreq != getSampleRate() || basseq->numSamples != numSamples)
		basseq->Update(lowParam->get(), gainlowParam->get(), getSampleRate(), numSamples);
	
	//peak
	auto temppeakfreq = peakParam->get();
	auto temppeakgain = gainpeakParam->get();
	auto temppeakband = bandpeakParam->get();

	if (peakeq->gain != temppeakgain || peakeq->freqband != temppeakband || peakeq->freq != temppeakfreq || peakeq->samFreq != getSampleRate() || peakeq->numSamples != numSamples)
		peakeq->Update(peakParam->get(), bandpeakParam->get(), gainpeakParam->get(), getSampleRate(), numSamples);

	//treble
	auto temptopfreq = topParam->get();
	auto temptopgain = gaintopParam->get();

	if (topeq->gain != temptopgain || topeq->freq != temptopfreq || topeq->samFreq != getSampleRate() || topeq->numSamples != numSamples)
		topeq->Update(topParam->get(), gaintopParam->get(), getSampleRate(), numSamples);
}

//==============================================================================
bool EqualizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* EqualizerAudioProcessor::createEditor()
{
    return new EqualizerAudioProcessorEditor (*this);
}

//==============================================================================
void EqualizerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void EqualizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EqualizerAudioProcessor();
}
