#include "GrainContentProcessor.h"

GrainContentProcessor::GrainContentProcessor(AudioProcessorValueTreeState& parameters, float sampleRate) :
	m_parameters(parameters),
	m_sampleRate(sampleRate),
	m_childGrains(64),
	m_samplesPerSpawn(4410),
	m_samplesUntilSpawn(0),
	m_hannTable(512),
	m_triwTable(512),
	m_sineTable(512),
	m_audioTable((int)sampleRate),
	m_running(false),
	m_phasorSpeed(1),
	m_masterPitch(0),
	m_pitchOffset(0)
{

	parameters.createAndAddParameter(
		"grainSizeMultiplier",
		"Grain Size Multiplier",
		"grain size",
		NormalisableRange<float>(0.01, 2.0, 0.001),
		1.0,
		nullptr, nullptr);

	parameters.createAndAddParameter(
		"grainStartPosition",
		"Grain Start Position",
		"start",
		NormalisableRange<float>(0.0, 1.0, 0.001),
		0,
		nullptr, nullptr);

	parameters.createAndAddParameter(
		"masterTempo",
		"Master Tempo",
		"bpm",
		NormalisableRange<float>(60.0f, 200.0f, 0.5f),
		120.0f,
		nullptr, nullptr);

	parameters.createAndAddParameter(
		"tempoDivision",
		"Tempo Division",
		"div",
		NormalisableRange<float>(0.25, 16.0, 0.25),
		1.0f,
		nullptr, nullptr);

	parameters.addParameterListener("masterTempo", this);
	parameters.addParameterListener("tempoDivision", this);

	//parameters.state = ValueTree(Identifier("HourglassGranular"));

	m_grainSizeMultiplier = parameters.getRawParameterValue("grainSizeMultiplier");
	m_startPosition = parameters.getRawParameterValue("grainStartPosition");

	m_bpm = parameters.getRawParameterValue("masterTempo");
	m_division = parameters.getRawParameterValue("tempoDivision");

	//m_windowTable.printData();
	m_audioTable.fillSine(440);
	m_triwTable.fillTriangleWindow();
	m_sineTable.fillSineWindow();
	m_playbackPhasor.setFrequency(0.01);
	setGrainPitch(1);
	calculateSamplesPerStep();
}



void GrainContentProcessor::setSampleRate(float sampleRate)
{
	if (sampleRate <= 0) sampleRate = 44100.0f;
	m_sampleRate = sampleRate;
	m_playbackPhasor.setSampleRate(sampleRate);
}

int GrainContentProcessor::getBufferSize()
{
	return (int)(m_sampleRate * *m_grainSizeMultiplier);
}

void GrainContentProcessor::fillBuffer(float* buf)
{
	float start((*m_startPosition) * m_audioTable.getSize());
	Grain x;
	x.spawn(&m_audioTable,&m_hannTable,&m_triwTable,&m_sineTable,m_sampleRate,m_sampleRate * *m_grainSizeMultiplier,start,m_masterPitch,0.3f);
	x.fillBuffer(buf);
}

void GrainContentProcessor::process(float* leftChannel, float* rightChannel, int blockSize, AudioPlayHead* playhead)
{
	if (m_running)
	{
		float start((*m_startPosition) * m_audioTable.getSize());

		if (playhead != nullptr)
		{
			AudioPlayHead::CurrentPositionInfo info;
			playhead->getCurrentPosition(info);

			if (info.bpm != 0)
				setBPM(info.bpm);

		}

		for (int n = 0; n < blockSize; ++n)
		{
			if (m_samplesUntilSpawn <= 0)
			{
				//spawn here
				bool spawned(false);

				for (int child = 0; child < m_childGrains.size(); ++child)
				{
					
					if (m_childGrains[child].alive() == false && spawned == false)
					{
						m_childGrains[child].spawn(&m_audioTable,
							&m_hannTable,
							&m_triwTable,
							&m_sineTable,
							m_sampleRate,
							m_sampleRate * *m_grainSizeMultiplier, // duration samples
							start, //m_playbackPhasor.getPhase() * m_audioTable.getSize() , // start position (phasor this?)
							m_masterPitch, // pitch
							0.3f); // Gain
						
						spawned = true;
						m_samplesUntilSpawn = m_samplesPerSpawn;
					}
				}
			} 

			for (int child = 0; child < m_childGrains.size(); ++child)
			{
				if (m_childGrains[child].alive() == true)
				{
					m_childGrains[child].updatePitch(m_phasorSpeed + m_masterPitch);
					m_childGrains[child].process(leftChannel, rightChannel, n);
				}
				m_playbackPhasor.tick();
			}
			--m_samplesUntilSpawn;
		}
	}
}

void GrainContentProcessor::setPlayState(bool state)
{
	m_running = state;
}

void GrainContentProcessor::setAudioSize(int size)
{
	m_audioTable.setSize(size);
	calculatePhasorSpeed();
}

void GrainContentProcessor::setAudioSample(int index, float value)
{
	m_audioTable.setSample(index, value);
	calculatePhasorSpeed();
}

void GrainContentProcessor::calculatePhasorSpeed()
{
	m_phasorSpeed = m_sampleRate / m_audioTable.getSize();
}


void GrainContentProcessor::setPitch(float pitch)
{
	m_pitchOffset = pitch;
}

void GrainContentProcessor::calculateSamplesPerStep()
{
	m_samplesPerSpawn = (m_sampleRate * 60.0f / *m_bpm) / *m_division;
	//DBG(m_samplesPerSpawn);
}

void GrainContentProcessor::setBPM(float bpm)
{
	*m_bpm = bpm;
	calculateSamplesPerStep();
}

void GrainContentProcessor::setDivision(float div)
{
	*m_division = div;
	calculateSamplesPerStep();
}

void GrainContentProcessor::setGrainPitch(float midiValue)
{
	float phasorSpeed = m_sampleRate / m_audioTable.getSize();

	phasorSpeed *= exp2f((midiValue - 69) / 11);

	m_masterPitch = phasorSpeed;

}

void GrainContentProcessor::parameterChanged(const String& parameterID, float newValue)
{
	if (parameterID == "masterTempo")
	{
		calculateSamplesPerStep();
	}
	else if (parameterID == "tempoDivision")
	{
		calculateSamplesPerStep();
	}
}