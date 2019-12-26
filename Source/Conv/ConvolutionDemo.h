#pragma once

#include "DemoUtilities.h"
#include "DSPDemos_Common.h"

using namespace dsp;

//==============================================================================
struct ConvolutionReverbDSP
{
	void prepare(const ProcessSpec& spec)
	{
		sampleRate = spec.sampleRate;
		convolution.prepare(spec);
		updateParameters();
	}

	void process(ProcessContextReplacing<float> context)
	{
		context.isBypassed = bypass;
		convolution.process(context);
	}

	void reset()
	{
		convolution.reset();
	}

	void updateParameters()
	{
		if (auto* cabinetTypeParameter = dynamic_cast<ChoiceParameter*> (parameters[0]))
		{
			if (cabinetTypeParameter->getCurrentSelectedID() == 1)
			{
				bypass = true;
			}
			else
			{
				bypass = false;

				auto maxSize = static_cast<size_t> (roundToInt(sampleRate * (8192.0 / 44100.0)));
				auto selectedType = cabinetTypeParameter->getCurrentSelectedID();
				auto assetName = (selectedType == 2 ? "Impulse1.wav" : "Impulse2.wav");

				std::unique_ptr<InputStream> assetInputStream(createAssetInputStream(assetName));
				if (assetInputStream != nullptr)
				{
					currentCabinetData.reset();
					assetInputStream->readIntoMemoryBlock(currentCabinetData);

					convolution.loadImpulseResponse(currentCabinetData.getData(), currentCabinetData.getSize(),
						false, true, maxSize);
				}
			}
		}
	}

	//==============================================================================
	double sampleRate = 0.0;
	bool bypass = false;

	MemoryBlock currentCabinetData;
	Convolution convolution;

	ChoiceParameter cabinetParam{ { "Bypass", "Impulse1", "Impulse2" }, 1, "Reverb Type" };

	std::vector<DSPDemoParameterBase*> parameters{ &cabinetParam };
};


struct ConvolutionDemoDSP
{
    void prepare (const ProcessSpec& spec)
    {
        sampleRate = spec.sampleRate;
        convolution.prepare (spec);
        updateParameters();
    }

    void process (ProcessContextReplacing<float> context)
    {
        context.isBypassed = bypass;
        convolution.process (context);
    }

    void reset()
    {
        convolution.reset();
    }

    void updateParameters()
    {
        if (auto* cabinetTypeParameter = dynamic_cast<ChoiceParameter*> (parameters[0]))
        {
            if (cabinetTypeParameter->getCurrentSelectedID() == 1)
            {
                bypass = true;
            }
            else
            {
                bypass = false;

                auto maxSize = static_cast<size_t> (roundToInt (sampleRate * (8192.0 / 44100.0)));
                auto selectedType = cabinetTypeParameter->getCurrentSelectedID();
                auto assetName = (selectedType == 2 ? "guitar_amp.wav" : "cassette_recorder.wav");

                std::unique_ptr<InputStream> assetInputStream (createAssetInputStream (assetName));
                if (assetInputStream != nullptr)
                {
                    currentCabinetData.reset();
                    assetInputStream->readIntoMemoryBlock (currentCabinetData);

                    convolution.loadImpulseResponse (currentCabinetData.getData(), currentCabinetData.getSize(),
                                                     false, true, maxSize);
                }
            }
        }
    }

    //==============================================================================
    double sampleRate = 0.0;
    bool bypass = false;

    MemoryBlock currentCabinetData;
    Convolution convolution;

    ChoiceParameter cabinetParam { { "Bypass", "Guitar amplifier 8''", "Cassette recorder" }, 1, "Cabinet Type" };

    std::vector<DSPDemoParameterBase*> parameters { &cabinetParam };
};

struct ConvolutionReverb : public Component
{
	ConvolutionReverb()
	{
		addAndMakeVisible(fileReaderComponent);
		setSize(750, 500);
	}

	void resized() override
	{
		fileReaderComponent.setBounds(getLocalBounds());
	}

	AudioFileReaderComponent<ConvolutionReverbDSP> fileReaderComponent;
};

struct ConvolutionDemo    : public Component
{
    ConvolutionDemo()
    {
        addAndMakeVisible (fileReaderComponent);
        setSize (750, 500);
    }

    void resized() override
    {
        fileReaderComponent.setBounds (getLocalBounds());
    }

    AudioFileReaderComponent<ConvolutionDemoDSP> fileReaderComponent;
};

struct OverdriveDemoDSP
{
	void prepare(const ProcessSpec& spec)
	{
		sampleRate = spec.sampleRate;

		auto& gainUp = overdrive.get<0>();
		gainUp.setGainDecibels(24);

		auto& bias = overdrive.get<1>();
		bias.setBias(0.4f);

		auto& wavShaper = overdrive.get<2>();
		wavShaper.functionToUse = std::tanh;

		auto& dcFilter = overdrive.get<3>();
		dcFilter.state = IIR::Coefficients<float>::makeHighPass(sampleRate, 5.0);

		auto& gainDown = overdrive.get<4>();
		gainDown.setGainDecibels(-18.0f);

		overdrive.prepare(spec);
	}

	void process(const ProcessContextReplacing<float>& context)
	{
		overdrive.process(context);
	}

	void reset()
	{
		overdrive.reset();
	}

	void updateParameters()
	{
		if (sampleRate != 0.0)
		{
			overdrive.get<0>().setGainDecibels(static_cast<float> (inGainParam.getCurrentValue()));
			overdrive.get<4>().setGainDecibels(static_cast<float> (outGainParam.getCurrentValue()));
		}
	}

	//==============================================================================
	using GainProcessor = Gain<float>;
	using BiasProcessor = Bias<float>;
	using DriveProcessor = WaveShaper<float>;
	using DCFilter = ProcessorDuplicator<IIR::Filter<float>,
		IIR::Coefficients<float>>;

	ProcessorChain<GainProcessor, BiasProcessor, DriveProcessor, DCFilter, GainProcessor> overdrive;

	SliderParameter inGainParam{ { -100.0, 60.0 }, 3, 24.0,  "Input Gain",  "dB" };
	SliderParameter outGainParam{ { -100.0, 20.0 }, 3, -18.0, "Output Gain", "dB" };

	std::vector<DSPDemoParameterBase*> parameters{ &inGainParam, &outGainParam };
	double sampleRate = 0.0;
};

struct OverdriveDemo : public Component
{
	OverdriveDemo()
	{
		addAndMakeVisible(fileReaderComponent);
		setSize(750, 500);
	}

	void resized() override
	{
		fileReaderComponent.setBounds(getLocalBounds());
	}

	AudioFileReaderComponent<OverdriveDemoDSP> fileReaderComponent;
};