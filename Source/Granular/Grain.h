/*
  ==============================================================================

	Grain.h
	Created: 15 Jan 2018 9:13:08am
	Author:  George Dean

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "GrainTable.h"
#include "Phasor.h"

//https://devblogs.nvidia.com/lerp-faster-cuda/
template <class T>
T lerp(T v0, T v1, T t)
{
	return fma(t, v1, fma(-t, v0, v0));
}

struct WindowShapes
{
	GrainTable* hanning;
	GrainTable* blendWindow;
	GrainTable* sineWindow;
};

class Grain
{
	bool m_alive, m_running;
	int m_lifeTimeSamples, m_timeAliveSamples;
	float m_startPosition, m_currentOutput, m_gain;
	float m_panning;
	float m_pitch;
	float m_rPitch;

	WindowShapes m_windows;

	GrainTable* m_hannWindow, *m_triWindow, *m_sineWindow, *m_audio;
	Phasor m_phasor;

public:
	Grain() :
		m_alive(false),
		m_running(false),
		m_startPosition(0),
		m_currentOutput(0),
		m_phasor(44100),
		m_gain(0.3f),
		m_panning(0.5f),
		m_pitch(1.0f),
		m_rPitch(0.0f)
	{
		m_hannWindow = 0;
		m_triWindow = 0;
		m_sineWindow = 0;
		m_audio = 0;
	}
	bool alive()
	{
		return m_alive;
	}

	void spawn(GrainTable* audio,
		GrainTable* hann,
		GrainTable* triw,
		GrainTable* sinew,
		float sampleRate,
		int durationSamples,
		float startPosition = 0,
		float pitch = 1, 
		float gain = 0.3f)
	{
		m_lifeTimeSamples = durationSamples;
		m_timeAliveSamples = 0;
		m_startPosition = startPosition;
		m_phasor.setSampleRate(sampleRate);
		m_phasor.setPhase(0);
		m_gain = gain;

		
		m_phasor.setFrequency(m_pitch);

		if (audio != nullptr && hann != nullptr)
		{
			if (audio->isReady() == true && audio->getSize() > 0 &&
				hann->isReady() == true && hann->getSize() > 0)
			{

				m_audio = audio;
				m_hannWindow = hann;
				m_triWindow = triw;
				m_sineWindow = sinew;



				m_alive = true;
				m_running = true;
			}
			else
			{
				m_alive = false;
				m_running = false;
			}
		}
		else
		{
			m_alive = false;
			m_running = false;
		}
		/*
		static int grainNum(0);
		++grainNum;

		DBG(grainNum);*/
	}

	void fillBuffer(float* buf)
	{
		for (int i=0;i<m_lifeTimeSamples;i++){
			float grainPos01=(float)i / (float)m_lifeTimeSamples;
			float amp(0);
			float hann = m_hannWindow->getSample(grainPos01* (float)m_hannWindow->getSize());
			float sine = m_sineWindow->getSample(grainPos01* (float)m_sineWindow->getSize());
			amp = lerp(hann, sine, 2.0f);
			m_currentOutput = m_audio->getSample(m_startPosition + float(m_phasor.getPhase() * m_audio->getSize())) * amp;
			m_phasor.tick();
			m_currentOutput *= m_gain;
			buf[i]=m_currentOutput;
		}
	}

	void updatePitch(float p)
	{
		m_pitch = p + m_rPitch;
		m_phasor.setFrequency(m_pitch);
	}

	void process(float* left, float* right, int position)
	{
		if (m_alive == false || m_running == false || m_audio == nullptr) return;

		// write to audio buffers here...
		float grainPos01 = (float)m_timeAliveSamples / (float)m_lifeTimeSamples;

		float amp(0);
		
		float hann = m_hannWindow->getSample(grainPos01 * (float)m_hannWindow->getSize());
		float sine = m_sineWindow->getSample(grainPos01 * (float)m_sineWindow->getSize());

		amp = lerp(hann, sine, 2.0f);

		m_currentOutput = m_audio->getSample(m_startPosition + float(m_phasor.getPhase() * m_audio->getSize())) * amp;
		m_phasor.tick();

		m_currentOutput *= m_gain;

		left[position] += m_currentOutput;
		right[position] += m_currentOutput;

		++m_timeAliveSamples;

		if (m_timeAliveSamples >= m_lifeTimeSamples)
		{
			m_running = false;
			m_alive = false;
		}

	}
};