/*
  ==============================================================================

    EQ.h
    Created: 17 Aug 2017 1:05:53pm
    Author:  ancie

  ==============================================================================
*/

#pragma once

#ifndef EQ_CLASS
#define EQ_CLASS
#pragma once

#include<cmath>

#define PI 3.14159265359

enum FilterType
{
	LowShelf = 0,
	HighShelf = 1,
	Peak = 2
};

class EQ
{
public:
	inline EQ() { };

	inline EQ(FilterType type)
	{
		this->type = type;
	}

	inline ~EQ() { };

	inline void Update(float freq, float gain, float samFreq, int numSamples);
	inline void Update(float freq, float freqband, float gain, float samFreq, int numSamples);
	inline void CComp();
	inline float Tick(float input, int channel);

	float freq;	//cut-off frequency
	float freqband;	//bandwidth frequency for peak filters
	float gain;	//gain
	int numSamples;	//number of samples in buffor
	float samFreq;	//sampling frequency

	FilterType type;	// 0 - low, 1 - top, 2 - peak
private:
	float b0, b1, b2, a1, a2;	//coefficient
	float V0, K, Q;
	float xh[2] = { 0.f, 0.f };
	float xh1[2] = { 0.f, 0.f };
	float xh2[2] = { 0.f, 0.f };
};

inline void EQ::CComp()
{
	switch (type)
	{
	case LowShelf:
		if (gain >= 0.f)
		{
			b0 = (1 + sqrtf(2 * V0) * K + V0 *K*K) / (1 + sqrtf(2) * K + K*K);
			b1 = (2 * (V0 * K*K - 1)) / (1 + sqrtf(2) * K + K*K);
			b2 = (1 - sqrtf(2 * V0) * K + V0 *K*K) / (1 + sqrtf(2) * K + K*K);
			a1 = (2 * (K*K - 1)) / (1 + sqrtf(2) * K + K*K);
			a2 = (1 - sqrtf(2) * K + K*K) / (1 + sqrtf(2) * K + K*K);
		}
		else
		{
			b0 = (V0 * (1 + sqrtf(2) * K + K*K)) / (V0 + sqrtf(2 * V0) * K + K*K);
			b1 = (2 * V0 * (K*K - 1)) / (V0 + sqrtf(2 * V0) * K + K*K);
			b2 = (V0 * (1 - sqrtf(2) * K + K*K)) / (V0 + sqrtf(2 * V0) * K + K*K);
			a1 = (2 * (K*K - V0)) / (V0 + sqrtf(2 * V0) * K + K*K);
			a2 = (V0 - sqrtf(2 * V0) * K + K*K) / (V0 + sqrtf(2 * V0) * K + K*K);
		}
		break;
	case HighShelf:
		if (gain >= 0.f)
		{
			b0 = (V0 + sqrtf(2 * V0) * K + K*K) / (1 + sqrtf(2) * K + K*K);
			b1 = (2 * (K*K - V0)) / (1 + sqrtf(2) * K + K*K);
			b2 = (V0 - sqrtf(2 * V0) * K + K*K) / (1 + sqrtf(2) * K + K*K);
			a1 = (2 * (K*K - 1)) / (1 + sqrtf(2) * K + K*K);
			a2 = (1 - sqrtf(2) * K + K*K) / (1 + sqrtf(2) * K + K*K);
		}
		else
		{
			b0 = (V0 * (1 + sqrtf(2) * K + K*K)) / (1 + sqrtf(2 * V0) * K + V0 * K*K);
			b1 = (2 * V0 * (K*K - 1)) / (1 + sqrtf(2 * V0) * K + V0 * K*K);
			b2 = (V0 * (1 - sqrtf(2) * K + K*K)) / (1 + sqrtf(2 * V0) * K + V0 * K*K);
			a1 = (2 * (V0 * K*K - 1)) / (1 + sqrtf(2 * V0) * K + V0 * K*K);
			a2 = (1 - sqrtf(2 * V0) * K + V0 * K*K) / (1 + sqrtf(2 * V0) * K + V0 * K*K);
		}
		break;
	case Peak:
		if (gain >= 0.f)
		{
			b0 = (1 + (V0 / Q) * K + K*K) / (1 + (1 / Q) * K + K*K);
			b1 = (2 * (K*K - 1)) / (1 + (1 / Q) * K + K*K);
			b2 = (1 - (V0 / Q) * K + K*K) / (1 + (1 / Q) * K + K*K);
			a1 = b1;
			a2 = (1 - (1 / Q) * K + K*K) / (1 + (1 / Q) * K + K*K);
		}
		else
		{
			b0 = (1 + (1 / Q) * K + K*K) / (1 + (1 / (V0 * Q)) * K + K*K);
			b1 = (2 * (K*K - 1)) / (1 + (1 / (V0 * Q)) * K + K*K);
			b2 = (1 - (1 / Q) * K + K*K) / (1 + (1 / (V0 * Q)) * K + K*K);
			a1 = b1;
			a2 = (1 - (1 / (V0 * Q)) * K + K*K) / (1 + (1 / (V0 * Q)) * K + K*K);
		}
	default:
		break;
	}
}

inline void EQ::Update(float freq, float gain, float samFreq, int numSamples)
{
	this->freq = freq;
	this->gain = gain;
	this->samFreq = samFreq;
	this->numSamples = numSamples;

	K = tanf(PI*freq / samFreq);

	V0 = powf(10.f, gain / 20.f);

	CComp();
}

inline void EQ::Update(float freq, float freqband, float gain, float samFreq, int numSamples)
{
	this->freq = freq;
	this->freqband = freqband;
	this->gain = gain;
	this->samFreq = samFreq;
	this->numSamples = numSamples;

	K = tanf(PI*freq / samFreq);

	V0 = powf(10.f, gain / 20.f);

	Q = freq / freqband;

	CComp();
}

inline float EQ::Tick(float input, int channel)
{
	float output;

	xh[channel] = input - a1 * xh1[channel] - a2 * xh2[channel];
	output = b0 * xh[channel] + b1 * xh1[channel] + b2 * xh2[channel];

	xh2[channel] = xh1[channel];
	xh1[channel] = xh[channel];

	return output;
}

#endif  // EQ_CLASS