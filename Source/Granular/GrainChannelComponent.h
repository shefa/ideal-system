/*
  ==============================================================================

    GrainChannelComponent.h
    Created: 16 Apr 2018 4:03:04pm
    Author:  George Dean

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "JuicyClouds.h"



//==============================================================================
/*
*/
class GrainChannelComponent : 
	public GroupComponent, public Button::Listener, public Slider::Listener,
	public ChangeListener, public Label::Listener, public ValueTree::Listener
{


public:
	
	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

	GrainChannelComponent(AudioProcessorValueTreeState& vts) :
		GroupComponent("grainChannel", "Grain Channel"),
		m_grainProcessor(0),
		m_thumbnailCache(5),
		m_sampleThumbnail(512, m_formatManager, m_thumbnailCache),
		m_valueTreeState(vts)
    {

		// UI
		m_loadSampleButton = new TextButton("Load Sample");
		addAndMakeVisible(m_loadSampleButton);
		m_loadSampleButton->addListener(this);

		m_startPositionSlider = new Slider(Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::TextBoxBelow);
		m_startPositionSlider->setName("Start Position");
		m_startPositionSlider->setRange(0.0, 1.0, 0.001);
		m_startPositionSlider->addListener(this);
		m_startPositionSlider->setTextBoxIsEditable(true);
		addAndMakeVisible(m_startPositionSlider);
		m_startPosLabel = new Label("lblStartPos", "start");
		m_startPosLabel->setJustificationType(Justification::centred);
		addAndMakeVisible(m_startPosLabel);
		m_startPosLabel->attachToComponent(m_startPositionSlider, false);
		m_startPositionAttachment.reset(new SliderAttachment(m_valueTreeState, "grainStartPosition", *m_startPositionSlider));

		m_grainSizeSlider = new Slider(Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::TextBoxBelow);
		m_grainSizeSlider->setName("Grain Size");
		m_grainSizeSlider->setRange(0.01, 2.0, 0.001);
		m_grainSizeSlider->addListener(this);
		m_grainSizeSlider->setTextBoxIsEditable(true);
		addAndMakeVisible(m_grainSizeSlider);
		m_grainSizeLabel = new Label("lblGrainSize", "size");
		m_grainSizeLabel->setJustificationType(Justification::centred);
		addAndMakeVisible(m_grainSizeLabel);
		m_grainSizeLabel->attachToComponent(m_grainSizeSlider, false);
	    m_grainSizeAttachment.reset(new SliderAttachment(m_valueTreeState, "grainSizeMultiplier", *m_grainSizeSlider));

		m_mainPitchSlider = new Slider(Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::TextBoxBelow);
		m_mainPitchSlider->setName("Pitch");
		m_mainPitchSlider->setRange(-12.0f, 12.0f, 0.1f);
		m_mainPitchSlider->addListener(this);
		m_mainPitchSlider->setTextBoxIsEditable(true);
		addAndMakeVisible(m_mainPitchSlider);
		m_mainPitchLabel = new Label("lblMainPitch", "pitch");
		m_mainPitchLabel->setJustificationType(Justification::centred);
		addAndMakeVisible(m_mainPitchLabel);
		m_mainPitchLabel->attachToComponent(m_mainPitchSlider, false);
		m_mainPitchAttachment.reset(new SliderAttachment(m_valueTreeState, "pitchShiftFrequency", *m_mainPitchSlider));


		// Audio Thumbnail
		m_formatManager.registerBasicFormats();
		m_sampleThumbnail.addChangeListener(this);


		m_valueTreeState.state.addListener(this);
    }

    ~GrainChannelComponent()
    {
    }

	void assignGrainProcessor(GrainContentProcessor* processor)
	{
		m_grainProcessor = processor;
	}

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        //g.setColour (Colours::grey);
        //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        //g.setColour (Colours::white);
        //g.setFont (14.0f);
        //g.drawText ("GrainChannelComponent", getLocalBounds(),
        //            Justification::centred, true);   // draw some placeholder text

		// Draw waveform
		auto thumb = getLocalBounds();
		thumb.removeFromTop(getHeight() * 0.65f);
		g.setColour(getLookAndFeel().findColour(Slider::backgroundColourId));
		g.fillRect(thumb.reduced(3));

		if (m_sampleThumbnail.getTotalLength() > 0.0)
		{
			g.setColour(getLookAndFeel().findColour(Slider::rotarySliderFillColourId));
			m_sampleThumbnail.drawChannel(g, thumb.reduced(3), 0.0f, m_sampleThumbnail.getTotalLength(), 0, 1.0f);
			auto x = thumb.getRelativePoint(((float)m_startPositionSlider->getValue() * 0.5f), 1.0f).x;
			g.drawRect(x, thumb.getY() + thumb.getHeight(), 1, thumb.getHeight() - 5, 1);
			//g.drawRect((thumb.getRelativePoint((m_startPositionSlider->getValue() * 0.5f), 1.0f). 
		}
		else
		{
			g.setColour(Colours::grey);
			g.drawText("No Sample Loaded", thumb, Justification::centred, false);
		}

    }

    void resized() override
    {
		auto bounds = getLocalBounds();

		auto sliderBar = bounds.removeFromTop(getHeight() * 0.65f);
		auto sliderBarWidth = getWidth() * 0.8f;
		auto sliderRight = sliderBar.removeFromRight(sliderBarWidth);
		auto labelbar = sliderRight.removeFromTop(sliderRight.getHeight() * 0.15f);

		m_startPositionSlider->setBounds(sliderRight.removeFromLeft(sliderBarWidth *	0.2f));
		m_grainSizeSlider->setBounds(sliderRight.removeFromLeft(sliderBarWidth *		0.2f));
		m_mainPitchSlider->setBounds(sliderRight.removeFromLeft(sliderBarWidth *		0.2f));
		

		m_startPosLabel->setBounds(labelbar.removeFromLeft(sliderBarWidth * 0.2f));
		m_grainSizeLabel->setBounds(labelbar.removeFromLeft(sliderBarWidth * 0.2f));
		m_mainPitchLabel->setBounds(labelbar.removeFromLeft(sliderBarWidth * 0.2f));
		

		m_loadSampleButton->setBounds(5, getHeight() * 0.5f, 100, 25);

    }

	void browseSample()
	{
		if (m_grainProcessor == 0) return;

		m_grainProcessor->setPlayState(false);

		//do loading...

		FileChooser fileSelector("Load sample", File(), "*.wav");

		if (fileSelector.browseForFileToOpen())
		{
			File selectedFile = fileSelector.getResult();
			
			//ValueTree v(Identifier("SampleFile"));
			//v.setProperty(Identifier("Path"), selectedFile.getFullPathName(), nullptr);

			//m_valueTreeState.state.addChild(v, 0, nullptr);
			//
			m_valueTreeState.state.setProperty(Identifier("SampleFile"), selectedFile.getFullPathName(), nullptr);


			m_grainProcessor->setPlayState(true);

			//loadSample(selectedFile);
		}


	}

	void loadSample(File file)
	{
		ScopedPointer<AudioFormatReader> reader = m_formatManager.createReaderFor(file);
		AudioSampleBuffer buffer(reader->numChannels, reader->lengthInSamples);

		reader->read(&buffer, 0, reader->lengthInSamples, 0, true, false);
		m_grainProcessor->setAudioSize(buffer.getNumSamples());
		for (int i = 0; i < buffer.getNumSamples(); ++i)
		{
			m_grainProcessor->setAudioSample(i, buffer.getSample(0, i));
		}

		m_sampleThumbnail.setSource(new FileInputSource(file));

		m_grainProcessor->setPlayState(true);
	}


	void buttonClicked(Button* button) override
	{
		if (button == m_loadSampleButton)
		{
			browseSample();
		}
	}

	void sliderValueChanged(Slider* slider) override
	{
	}

	void labelTextChanged(Label* labelThatHasChanged) override
	{

	}

	void changeListenerCallback(ChangeBroadcaster* source) override
	{
		if (source == &m_sampleThumbnail)
		{
			repaint();
		}
	}



	void valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged,
		const Identifier& property) override
	{

		//DBG(s);
	
		if (property == Identifier("SampleFile"))
			{
				String s = m_valueTreeState.state.getProperty(property);
				File f(s.trim());
				if (f.exists())
				{
					loadSample(f);
				}
				else
				{
					AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "hourglass", ("Could not locate sample " + s.trim()), "OK", this);
				}
			}
		//}
	}

	void valueTreeChildRemoved(ValueTree& parentTree,
		ValueTree& childWhichHasBeenRemoved,
		int indexFromWhichChildWasRemoved) override
	{

	}

	void valueTreeChildOrderChanged(ValueTree& parentTreeWhoseChildrenHaveMoved,
		int oldIndex, int newIndex) override
	{

	}

	void valueTreeParentChanged(ValueTree& treeWhoseParentHasChanged) override
	{

	}
	void valueTreeChildAdded(ValueTree& parentTree,
		ValueTree& childWhichHasBeenAdded) override
	{

	}

private:
	GrainContentProcessor* m_grainProcessor;

	// UI Components
	ScopedPointer<TextButton> m_loadSampleButton;

	ScopedPointer<Slider> m_startPositionSlider;
	std::unique_ptr<SliderAttachment> m_startPositionAttachment;

	ScopedPointer<Slider> m_grainSizeSlider;
	std::unique_ptr<SliderAttachment> m_grainSizeAttachment;

	ScopedPointer<Slider> m_mainPitchSlider;
	std::unique_ptr<SliderAttachment> m_mainPitchAttachment;

	ScopedPointer<Label> m_startPosLabel;
	ScopedPointer<Label> m_grainSizeLabel;
	ScopedPointer<Label> m_mainPitchLabel;

	AudioFormatManager m_formatManager;

	AudioThumbnailCache m_thumbnailCache;
	AudioThumbnail m_sampleThumbnail;

	AudioProcessorValueTreeState& m_valueTreeState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrainChannelComponent)
};
