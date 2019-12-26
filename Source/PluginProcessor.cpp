/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

MmcwAudioProcessor::MmcwAudioProcessor() : 
	//AudioProcessor(BusesProperties().withOutput("Output", AudioChannelSet::stereo(), true)),
	m_parameters(*this, nullptr),
	m_grainProcessor(m_parameters),
	m_ampEnv(44100.0f, 0.0f, 1.0f, 1.0f, 1.0f),
	m_pitchShifter(m_parameters),
	parameters(*this)
	, paramFftSize(parameters, "FFT size", fftSizeItemsUI, fftSize512,
		[this](float value) {
	const ScopedLock sl(lock);
	value = (float)(1 << ((int)value + 5));
	paramFftSize.setCurrentAndTargetValue(value);
	stft.updateParameters((int)paramFftSize.getTargetValue(),
		(int)paramHopSize.getTargetValue(),
		(int)paramWindowType.getTargetValue());
	return value;
})
, paramHopSize(parameters, "Hop size", hopSizeItemsUI, hopSize8,
	[this](float value) {
	const ScopedLock sl(lock);
	value = (float)(1 << ((int)value + 1));
	paramHopSize.setCurrentAndTargetValue(value);
	stft.updateParameters((int)paramFftSize.getTargetValue(),
		(int)paramHopSize.getTargetValue(),
		(int)paramWindowType.getTargetValue());
	return value;
})
, paramWindowType(parameters, "Window", windowTypeItemsUI, STFT::windowTypeHann,
	[this](float value) {
	const ScopedLock sl(lock);
	paramWindowType.setCurrentAndTargetValue(value);
	stft.updateParameters((int)paramFftSize.getTargetValue(),
		(int)paramHopSize.getTargetValue(),
		(int)paramWindowType.getTargetValue());
	return value;
})
{
	parameters.valueTreeState.state = ValueTree(Identifier(getName().removeCharacters("- ")));
	m_parameters.createAndAddParameter(
		"bpmToggle",
		"BPM Toggle",
		"BPM Toggle",
		NormalisableRange<float>(0.0f, 1.0f, 1.0f),
		0.0f,
		nullptr, nullptr);

	m_parameters.createAndAddParameter(
		"convToggle",
		"conv Toggle",
		"conv Toggle",
		NormalisableRange<float>(0.0f, 1.0f, 1.0f),
		0.0f,
		nullptr, nullptr);

	m_parameters.createAndAddParameter(
		"fftToggle",
		"fft Toggle",
		"fft Toggle",
		NormalisableRange<float>(0.0f, 1.0f, 1.0f),
		0.0f,
		nullptr, nullptr);

	m_parameters.createAndAddParameter(
		"inputGain",
		"input gain",
		"input gain",
		NormalisableRange<float>(-50.0f, 50.0f, 1.0f),
		0.0f,
		nullptr, nullptr);
	m_parameters.createAndAddParameter(
		"outputGain",
		"output gain",
		"output gain",
		NormalisableRange<float>(-50.0f, 50.0f, 1.0f),
		0.0f,
		nullptr, nullptr);
	inputGain = m_parameters.getRawParameterValue("inputGain");
	outputGain = m_parameters.getRawParameterValue("outputGain");
	m_bpmToggle = m_parameters.getRawParameterValue("bpmToggle");

	m_convToggle = m_parameters.getRawParameterValue("convToggle");
	m_fftToggle = m_parameters.getRawParameterValue("fftToggle");

	m_parameters.state = ValueTree(Identifier("Mmcw"));
	infobpm.bpm = 120;
	convolve = false;
	distortion = false;
	samplesPerBlockSaved=0;
}

MmcwAudioProcessor::~MmcwAudioProcessor(){}

//==============================================================================
GrainContentProcessor* MmcwAudioProcessor::getGranularProcessor() {return &m_grainProcessor;}

const String MmcwAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MmcwAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MmcwAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MmcwAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MmcwAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MmcwAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MmcwAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MmcwAudioProcessor::setCurrentProgram (int index)
{
}

const String MmcwAudioProcessor::getProgramName (int index)
{
    return {};
}

void MmcwAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================

void MmcwAudioProcessor::updateMagic (float start, float size)
{

	const int x=m_grainProcessor.getBufferSize();
	float* buffer;
	buffer = new float[x];
	//float buffer[x];
	m_grainProcessor.fillBuffer(buffer);
	magic.init(samplesPerBlockSaved, buffer, x);
}

void MmcwAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	samplesPerBlockSaved=samplesPerBlock;
	m_grainProcessor.setSampleRate(sampleRate);
	m_ampEnv.setSampleRate(sampleRate);
	m_pitchShifter.prepareToPlay(sampleRate, samplesPerBlock);
	const double smoothTime = 1e-3;
	paramFftSize.reset(sampleRate, smoothTime);
	paramHopSize.reset(sampleRate, smoothTime);
	paramWindowType.reset(sampleRate, smoothTime);

	//======================================

	stft.setup(getTotalNumInputChannels());
	stft.updateParameters((int)paramFftSize.getTargetValue(),
		(int)paramHopSize.getTargetValue(),
		(int)paramWindowType.getTargetValue());
}

void MmcwAudioProcessor::releaseResources()
{
	m_pitchShifter.releaseResources();
	magic.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MmcwAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MmcwAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	const int numInputChannels = getTotalNumInputChannels();
	const int numOutputChannels = getTotalNumOutputChannels();
	const int numSamples = buffer.getNumSamples();

	AudioPlayHead* playhead = nullptr;
	//======================================

	//stft.processBlock(buffer);

	//======================================

	for (int channel = numInputChannels; channel < numOutputChannels; ++channel)
		buffer.clear(channel, 0, numSamples);

	if (*m_bpmToggle == 1.0) {
		
		MidiMessage msg;
		int time = 0;
		for (MidiBuffer::Iterator it(midiMessages); it.getNextEvent(msg, time); )
		{
			if (msg.isNoteOn())
			{
				m_ampEnv.trigger();

				int midiNote = msg.getNoteNumber();
				m_grainProcessor.setGrainPitch(midiNote);

			}
			else if (msg.isNoteOff())
			{
				m_ampEnv.release();
			}
		}
		playhead = getPlayHead();
		playhead->getCurrentPosition(infobpm);
	}

	

	if (*m_convToggle == 1.0f)
	{
		magic.process(buffer.getReadPointer(0), buffer.getWritePointer(0), buffer.getNumSamples());
		magic.process(buffer.getReadPointer(1), buffer.getWritePointer(1), buffer.getNumSamples());
	}

	m_grainProcessor.process(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples(), playhead);
	m_pitchShifter.processBlock(buffer, midiMessages);
	if(*m_fftToggle == 1.0f) stft.processBlock(buffer);

	if (*m_bpmToggle == 1.0f)
	{
		for (int n = 0; n < buffer.getNumSamples(); ++n)
		{
			float* left = buffer.getWritePointer(0);
			float *right = buffer.getWritePointer(1);

			left[n] *= m_ampEnv.getValue();
			right[n] *= m_ampEnv.getValue();
		}
	}

	/*
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
		if(convolve) magic.process(buffer.getReadPointer(channel), channelData, buffer.getNumSamples());
    }*/
}

//==============================================================================
bool MmcwAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MmcwAudioProcessor::createEditor()
{
    return new MmcwAudioProcessorEditor (*this, m_parameters);
}

//==============================================================================
void MmcwAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	auto state = m_parameters.state;
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);

	/*auto state = parameters.valueTreeState.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);*/
}

void MmcwAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
	if (xmlState.get() != nullptr)
		m_parameters.state = ValueTree::fromXml(*xmlState);
	String s = m_parameters.state.getProperty("SampleFile");
	s = s + " ";
	m_parameters.state.setProperty(Identifier("SampleFile"), s, nullptr);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MmcwAudioProcessor();
}
