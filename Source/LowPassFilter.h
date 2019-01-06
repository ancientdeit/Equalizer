/*
  ==============================================================================

    LowPassFilter.h
    Created: 10 Aug 2017 1:49:36pm
    Author:  ancie

  ==============================================================================
*/
#ifndef LOWPASSFILTER_CLASS
#define LOWPASSFILTER_CLASS
#pragma once

#include<cmath>

#define PI 3.14159265359

class Convolution
{
public:
	inline Convolution() {};	//default constructor
	inline ~Convolution() {};	//default destructor

	inline void LoadAudioFile(AudioSampleBuffer *fileBuffer);
	inline void Process(float *input, float *output, int numSamples);

private:
	const float *audio;
	int size;
	int help;
};

inline void Convolution::LoadAudioFile(AudioSampleBuffer *fileBuffer)
{
	audio = fileBuffer->getReadPointer(0);
	size = fileBuffer->getNumSamples();
}

inline void Convolution::Process(float *input, float *output, int numSamples)
{	
	for (int i = 0; i < numSamples; i++)
	{
		float temp = 0.f;
		for (int k = 0; k <= i; k++)
		{
			if (k >= size) return;
			temp += input[k] * audio[i - k];
		}
		output[i] = temp;
	}
}


#endif  // LOWPASSFILTER_CLASS