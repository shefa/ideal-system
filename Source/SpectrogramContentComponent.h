/*
  ==============================================================================

    SpectrogramContentComponent.h
    Created: 11 Dec 2019 8:37:20am
    Author:  shefa

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FFT/PluginParameter.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class SpectrogramContentComponent    : public Component, private Timer
{
public:
    SpectrogramContentComponent(MmcwAudioProcessor& ownerFilter) : processor(ownerFilter), spectrogramImage(Image::RGB, 500, 300, true)
    {
		const Array<AudioProcessorParameter*> parameters = processor.getParameters();
		int comboBoxCounter = 0;

		editorHeight = 2 * editorMargin;
		for (int i = 0; i < parameters.size(); ++i) {
			if (const AudioProcessorParameterWithID* parameter =
				dynamic_cast<AudioProcessorParameterWithID*> (parameters[i])) {

				if (processor.parameters.parameterTypes[i] == "Slider") {
					Slider* aSlider;
					sliders.add(aSlider = new Slider());
					aSlider->setTextValueSuffix(parameter->label);
					aSlider->setTextBoxStyle(Slider::TextBoxLeft,
						false,
						sliderTextEntryBoxWidth,
						sliderTextEntryBoxHeight);

					SliderAttachment* aSliderAttachment;
					sliderAttachments.add(aSliderAttachment =
						new SliderAttachment(processor.parameters.valueTreeState, parameter->paramID, *aSlider));

					components.add(aSlider);
					editorHeight += sliderHeight;
				}

				//======================================

				else if (processor.parameters.parameterTypes[i] == "ToggleButton") {
					ToggleButton* aButton;
					toggles.add(aButton = new ToggleButton());
					aButton->setToggleState(parameter->getDefaultValue(), dontSendNotification);

					ButtonAttachment* aButtonAttachment;
					buttonAttachments.add(aButtonAttachment =
						new ButtonAttachment(processor.parameters.valueTreeState, parameter->paramID, *aButton));

					components.add(aButton);
					editorHeight += buttonHeight;
				}

				//======================================

				else if (processor.parameters.parameterTypes[i] == "ComboBox") {
					ComboBox* aComboBox;
					comboBoxes.add(aComboBox = new ComboBox());
					aComboBox->setEditableText(false);
					aComboBox->setJustificationType(Justification::left);
					aComboBox->addItemList(processor.parameters.comboBoxItemLists[comboBoxCounter++], 1);

					ComboBoxAttachment* aComboBoxAttachment;
					comboBoxAttachments.add(aComboBoxAttachment =
						new ComboBoxAttachment(processor.parameters.valueTreeState, parameter->paramID, *aComboBox));

					components.add(aComboBox);
					editorHeight += comboBoxHeight;
				}

				//======================================

				Label* aLabel;
				labels.add(aLabel = new Label(parameter->name, parameter->name));
				aLabel->attachToComponent(components.getLast(), true);
				addAndMakeVisible(aLabel);

				components.getLast()->setName(parameter->name);
				components.getLast()->setComponentID(parameter->paramID);
				addAndMakeVisible(components.getLast());
			}
		}

		//======================================

		editorHeight += components.size() * editorPadding;
		spectrogramHeight = 200;
		startTimerHz(60);
		setSize(editorWidth, editorHeight + spectrogramHeight);

    }

    ~SpectrogramContentComponent()
    {
    }


    void paint (Graphics& g) override
    {
		g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
		g.setOpacity(1.0f);
		g.drawImage(spectrogramImage, getLocalBounds().removeFromBottom(spectrogramHeight).toFloat());
    }

    void resized() override
    {
		Rectangle<int> r = getLocalBounds().reduced(editorMargin);
		r = r.removeFromRight(r.getWidth() - labelWidth);

		for (int i = 0; i < components.size(); ++i) {
			if (Slider* aSlider = dynamic_cast<Slider*> (components[i]))
				components[i]->setBounds(r.removeFromTop(sliderHeight));

			if (ToggleButton* aButton = dynamic_cast<ToggleButton*> (components[i]))
				components[i]->setBounds(r.removeFromTop(buttonHeight));

			if (ComboBox* aComboBox = dynamic_cast<ComboBox*> (components[i]))
				components[i]->setBounds(r.removeFromTop(comboBoxHeight));

			r = r.removeFromBottom(r.getHeight() - editorPadding);
		}

    }

	void timerCallback() override {
		if (processor.stft.getnextFFTBlockReady())
		{
			drawNextLineOfSpectrogram();
			repaint();
		}

	}

	void drawNextLineOfSpectrogram()
	{
		auto rightHandEdge = spectrogramImage.getWidth() - 1;
		auto imageHeight = spectrogramImage.getHeight();

		// first, shuffle our image leftwards by 1 pixel..
		spectrogramImage.moveImageSection(0, 0, 1, 0, rightHandEdge, imageHeight);

		// then render our FFT data..

		float* fftData = processor.stft.getfftData();
		int fftSize = processor.stft.getfftSize();

		// find the range of values produced, so we can scale our rendering to
		// show up the detail clearly
		auto maxLevel = FloatVectorOperations::findMinAndMax(fftData, fftSize / 2);

		for (auto y = 1; y < imageHeight; ++y)
		{
			auto skewedProportionY = 1.0f - std::exp(std::log(y / (float)imageHeight) * 0.2f);
			auto fftDataIndex = jlimit(0, fftSize / 2, (int)(skewedProportionY * fftSize / 2));
			auto level = jmap(fftData[fftDataIndex], 0.0f, jmax(maxLevel.getEnd(), 1e-5f), 0.0f, 1.0f);

			spectrogramImage.setPixelAt(rightHandEdge, y, Colour::fromHSV(level, 1.0f, level, 1.0f));
		}
	}

private:
	MmcwAudioProcessor& processor;

	enum {
		editorWidth = 500,
		editorMargin = 10,
		editorPadding = 10,

		sliderTextEntryBoxWidth = 100,
		sliderTextEntryBoxHeight = 25,
		sliderHeight = 25,
		buttonHeight = 25,
		comboBoxHeight = 25,
		labelWidth = 100,
	};

	//======================================

	OwnedArray<Slider> sliders;
	OwnedArray<ToggleButton> toggles;
	OwnedArray<ComboBox> comboBoxes;

	OwnedArray<Label> labels;
	Array<Component*> components;

	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
	typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

	OwnedArray<SliderAttachment> sliderAttachments;
	OwnedArray<ButtonAttachment> buttonAttachments;
	OwnedArray<ComboBoxAttachment> comboBoxAttachments;

	int editorHeight;
	int spectrogramHeight;
	Image spectrogramImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrogramContentComponent)
};
