/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include "../JuceLibraryCode/JuceHeader.h"
#include "FFT/FFTConvolver.h"
#include "STFT.h"
#include "FFT/PluginParameter.h"
#include "Granular/GrainContentProcessor.h"
#include "Granular/EnvelopeGenerator.h"
#include "Granular/PitchShifter.h"

//==============================================================================
/**
*/
class MmcwAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MmcwAudioProcessor();
    ~MmcwAudioProcessor();

    //==============================================================================
    void updateMagic(float start, float size);
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
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

	GrainContentProcessor* getGranularProcessor();
	AudioPlayHead::CurrentPositionInfo infobpm;
	float* m_bpmToggle = nullptr;
	float* m_convToggle = nullptr;
	float* m_fftToggle = nullptr;

	//==============================================================================
	//==============================================================================
	//==============================================================================

	StringArray fftSizeItemsUI = {
		"32",
		"64",
		"128",
		"256",
		"512",
		"1024",
		"2048",
		"4096",
		"8192"
	};

	enum fftSizeIndex {
		fftSize32 = 0,
		fftSize64,
		fftSize128,
		fftSize256,
		fftSize512,
		fftSize1024,
		fftSize2048,
		fftSize4096,
		fftSize8192,
	};

	//======================================

	StringArray hopSizeItemsUI = {
		"1/2 Window",
		"1/4 Window",
		"1/8 Window",
	};

	enum hopSizeIndex {
		hopSize2 = 0,
		hopSize4,
		hopSize8,
	};

	//======================================

	StringArray windowTypeItemsUI = {
		"Rectangular",
		"Bartlett",
		"Hann",
		"Hamming",
	};

	//======================================

	class PassThrough : public STFT
	{
	public:
		PassThrough()
		{
			fifoIndex = 0;
			nextFFTBlockReady = 0;
		}
		bool getnextFFTBlockReady() {
			if (nextFFTBlockReady) {
				nextFFTBlockReady = 0;
				return true;
			}
			return false;
		}

		int getfftSize() { return fftSize; }
		float* getfftData() { return fftData.get(); }

	protected:
		virtual void updateFftSize(const int newFftSize) override
		{
			STFT::updateFftSize(newFftSize);
			fifo.realloc(fftSize);
			fifo.clear(fftSize);
			fftData.realloc(fftSize);
			fftData.clear(fftSize);
			fifoIndex = 0;
			nextFFTBlockReady = 0;
		}
		virtual void modification() override
		{
			fft->perform(timeDomainBuffer, frequencyDomainBuffer, false);

			for (int index = 0; index < fftSize / 2 + 1; ++index) {
				float magnitude = abs(frequencyDomainBuffer[index]);
				float phase = arg(frequencyDomainBuffer[index]);
				fftData[index] = magnitude;
				frequencyDomainBuffer[index].real(magnitude * cosf(phase));
				frequencyDomainBuffer[index].imag(magnitude * sinf(phase));
				if (index > 0 && index < fftSize / 2) {
					frequencyDomainBuffer[fftSize - index].real(magnitude * cosf(phase));
					frequencyDomainBuffer[fftSize - index].imag(magnitude * sinf(-phase));
				}
			}
			nextFFTBlockReady = true;
			fft->perform(frequencyDomainBuffer, timeDomainBuffer, true);
		}
		HeapBlock<float> fifo;
		HeapBlock<float> fftData;
		int fifoIndex = 0;
		bool nextFFTBlockReady = false;
	};

	//======================================

	CriticalSection lock;
	PassThrough stft;

	//======================================

	PluginParametersManager parameters;

	PluginParameterComboBox paramFftSize;
	PluginParameterComboBox paramHopSize;
	PluginParameterComboBox paramWindowType;

private:
    //==============================================================================
    int samplesPerBlockSaved;
	fftconvolver::FFTConvolver magic;
	AudioProcessorValueTreeState m_parameters;
	GrainContentProcessor m_grainProcessor;
	bool convolve;
	bool distortion;
	float* inputGain;
	float* outputGain;
	PitchShifter m_pitchShifter;
	EnvelopeGenerator m_ampEnv;
	

	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MmcwAudioProcessor)
};
