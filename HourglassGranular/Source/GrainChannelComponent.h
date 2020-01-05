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
#include "PluginProcessor.h"

class WavetableWidget : public Component
{
	std::vector<float> m_hannWindow, m_triWindow, m_sineWindow;
	int m_resolutionFactor;
	bool m_filled;
	float m_blendAmount;

public:
	WavetableWidget() :
		m_hannWindow(64),
		m_triWindow(64),
		m_sineWindow(64),
		m_filled(false),
		m_blendAmount(0)
	{
		fillHann(m_hannWindow);
		fillTriangle(m_triWindow);
		fillSine(m_sineWindow);
	}
	~WavetableWidget()
	{

	}

	void paint(Graphics& g) override
	{
		g.fillAll(getLookAndFeel().findColour(Slider::backgroundColourId));

		g.setColour(getLookAndFeel().findColour(Slider::rotarySliderFillColourId));
		Path windowPath;

		int inc = m_hannWindow.size() / getWidth();

		for (int i = 0; i < m_hannWindow.size() / inc; i++)
		{
			float v(0);

			if (m_blendAmount <= 0.25f)
			{
				float hann = m_hannWindow[i * inc];
				float sine = m_sineWindow[i*inc];
				v = lerp(hann, sine, m_blendAmount * 4.0f);
			}
			else if (m_blendAmount > 0.25f && m_blendAmount <= 0.5f)
			{
				float sine = m_sineWindow[i*inc];
				float triw = m_triWindow[i*inc];
				v = lerp(sine, triw, (m_blendAmount * 4.0f) - 1);
			}
			else if (m_blendAmount > 0.5f && m_blendAmount <= 0.75f)
			{
				float triw = m_triWindow[i*inc];
				v = lerp(triw, 1.0f, (m_blendAmount * 4.0f) - 2);
			}
			else
			{
				float hann = m_hannWindow[i * inc];
				v = lerp(1.0f, hann, (m_blendAmount * 4.0f) - 3);
			}

			//float v = lerp(m_windowTable[i * inc], m_blendTable[i * inc], m_blendAmount);

			Point<float> p(i, getHeight() - (v * (getHeight() * 0.98f)));
			if (i == 0)
			{
				windowPath.startNewSubPath(p);
			}
			else 
			{
				windowPath.lineTo(p);
			}

			//g.fillPath(i, getHeight() - (m_windowTable[i] * (getHeight() * 0.99f)), 1, 1, 1);
		}
	
		g.strokePath(windowPath, PathStrokeType(2.0f));
	}

	void fillWaveshape(std::vector<float> wavetable)
	{
		m_hannWindow.clear();
		m_hannWindow = wavetable;


		repaint();
	}

	void fillHann(std::vector<float>& table)
	{
		for (int n = 0; n < table.size(); ++n)
		{
			table[n] = 0.5f * (1.0f - cos((6.28318530718 * n) / (float)table.size()));
		}
	}

	void fillSine(std::vector<float>& table)
	{
		for (int n = 0; n < table.size(); ++n)
		{
			table[n] = (sinf((6.28318530718 * n * 0.5 * 1.0) / (float)table.size()));
		}
	}

	void fillTriangle(std::vector<float>& table)
	{
		auto size = table.size() - 1;
		auto f = (1.0 / (size));
		for (int n = 0; n < size; ++n)
		{
			if (n <= size / 2)
			{
				//m_blendTable[n] = (((size - n) * f) - 1.0);
				table[n] = scaleRange((((size - n) * f) - 1.0), 0.0, -0.5, 0.0, 1.0);
			}
			else
			{
				//m_blendTable[n] = ((n*f) - 1.0);
				table[n] = scaleRange(((n * f) - 1.0), 0.0, -0.5, 0.0, 1.0);
			}
		}
	}

	void setBlendAmount(float amount)
	{
		m_blendAmount = amount;
		repaint();
	}

	void resized() override
	{

	}

};

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

	GrainChannelComponent (HourglassGranularAudioProcessor& p, AudioProcessorValueTreeState& vts) :
		GroupComponent("grainChannel", "Grain Channel"),
		m_processor(p),
		m_grainProcessor(0),
		m_thumbnailCache(5),
		m_sampleThumbnail(512, m_formatManager, m_thumbnailCache),
		m_valueTreeState(vts)
    {

		m_loadSampleButton.reset(new TextButton("Load Sample"));
		m_loadSampleButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
		addAndMakeVisible(m_loadSampleButton.get());
		m_loadSampleButton->addListener(this);

		playButton.reset (new TextButton ("play"));
	    addAndMakeVisible (playButton.get());
	    playButton->setButtonText (TRANS("Play"));
	    playButton->addListener (this);
	    playButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
	    

	    stopButton.reset (new TextButton ("stop"));
	    addAndMakeVisible (stopButton.get());
	    stopButton->setButtonText (TRANS("Stop"));
	    stopButton->addListener (this);
	    stopButton->setColour (TextButton::buttonColourId, Colours::cadetblue);
		

		m_startPositionSlider.reset(new Slider(Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::TextBoxBelow));
		m_startPositionSlider->setName("Start Position");
		m_startPositionSlider->setRange(0.0, 1.0, 0.001);
		m_startPositionSlider->addListener(this);
		m_startPositionSlider->setTextBoxIsEditable(true);
		addAndMakeVisible(m_startPositionSlider.get());
		m_startPositionSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
		
		m_startPosLabel.reset(new Label("lblStartPos", "start"));
		m_startPosLabel->setJustificationType(Justification::centred);
		addAndMakeVisible(m_startPosLabel.get());
		m_startPosLabel->attachToComponent(m_startPositionSlider.get(), false);
		m_startPositionAttachment.reset(new SliderAttachment(m_valueTreeState, "grainStartPosition", *m_startPositionSlider));

		m_grainSizeSlider.reset(new Slider(Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::TextBoxBelow));
		
		m_grainSizeSlider->setName("Grain Size");
		m_grainSizeSlider->setRange(0.01, 2.0, 0.001);
		m_grainSizeSlider->addListener(this);
		m_grainSizeSlider->setTextBoxIsEditable(true);
		m_grainSizeSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
		addAndMakeVisible(m_grainSizeSlider.get());
		
		m_grainSizeLabel.reset(new Label("lblGrainSize", "size"));
		m_grainSizeLabel->setJustificationType(Justification::centred);
		addAndMakeVisible(m_grainSizeLabel.get());
		m_grainSizeLabel->attachToComponent(m_grainSizeSlider.get(), false);
		
		m_grainSizeAttachment.reset(new SliderAttachment(m_valueTreeState, "grainSizeMultiplier", *m_grainSizeSlider));

		m_mainPitchSlider.reset(new Slider(Slider::SliderStyle::RotaryVerticalDrag, Slider::TextEntryBoxPosition::TextBoxBelow));
		m_mainPitchSlider->setName("Pitch");
		m_mainPitchSlider->setRange(-12.0f, 12.0f, 0.1f);
		m_mainPitchSlider->addListener(this);
		m_mainPitchSlider->setTextBoxIsEditable(true);
		addAndMakeVisible(m_mainPitchSlider.get());
		m_mainPitchSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
        
		m_mainPitchLabel.reset(new Label("lblMainPitch", "pitch"));
		m_mainPitchLabel->setJustificationType(Justification::centred);
		addAndMakeVisible(m_mainPitchLabel.get());
		m_mainPitchLabel->attachToComponent(m_mainPitchSlider.get(), false);
		m_mainPitchAttachment.reset(new SliderAttachment(m_valueTreeState, "pitchShiftFrequency", *m_mainPitchSlider));


		m_windowBlendSlider.reset(new Slider(Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox));
		m_windowBlendSlider->setName("Window Blend");
		m_windowBlendSlider->setRange(0.0, 1.0, 0.001);
		m_windowBlendSlider->addListener(this);
		m_windowBlendSlider->setTextBoxIsEditable(true);
		addAndMakeVisible(m_windowBlendSlider.get());
		m_windowBlendLabel.reset(new Label("lblWindowBlend", "blend"));
		m_windowBlendLabel->setJustificationType(Justification::centred);
		addAndMakeVisible(m_windowBlendLabel.get());
		m_windowBlendLabel->attachToComponent(m_windowBlendSlider.get(), false);
		m_blendAttachment.reset(new SliderAttachment(m_valueTreeState, "windowBlend", *m_windowBlendSlider));

        
		// Audio Thumbnail
		m_formatManager.registerBasicFormats();
		m_sampleThumbnail.addChangeListener(this);

		// Window shape widget
		m_waveWidget.reset(new WavetableWidget());
		addAndMakeVisible(m_waveWidget.get());

		m_valueTreeState.state.addListener(this);

    }

    ~GrainChannelComponent()
    {
    }

	void assignGrainProcessor(JuicyClouds* processor)
	{
		m_grainProcessor = processor;
	}

    void paint (Graphics& g) override
    {

		g.fillAll (Colour (0xff323e44));

	    //[UserPaint] Add your own custom painting code here..
		auto thumb = getLocalBounds();
		thumb.removeFromTop(getHeight() * 0.2f);
		thumb.removeFromBottom(getHeight() * 0.25f);
		g.setColour(getLookAndFeel().findColour(Slider::backgroundColourId));
		g.fillRect(thumb.reduced(3));

		if (m_sampleThumbnail.getTotalLength() > 0.0)
		{
			int x = thumb.getRelativePoint(((float)m_startPositionSlider->getValue()), 1.0f).x;
			float tmpx = (float)m_startPositionSlider->getValue() + m_grainSizeSlider->getValue()*0.22f;

			int x2 = thumb.getRelativePoint(tmpx>1.0f ? tmpx-1.0f:tmpx, 1.0f).x;

			g.setColour(Colours::darkslateblue);
			if (tmpx <= 1.0f) g.fillRect(thumb.withTrimmedLeft(x - thumb.getTopLeft().x).withTrimmedRight(thumb.getWidth() - x2).reduced(3));
			else {
				g.fillRect(thumb.withTrimmedLeft(x - thumb.getTopLeft().x).reduced(3));
				g.fillRect(thumb.withTrimmedRight(thumb.getWidth() - x2).reduced(3));
			}

			g.setColour(getLookAndFeel().findColour(Slider::ColourIds::thumbColourId));
			m_sampleThumbnail.drawChannel(g, thumb.reduced(3), 0.0f, m_sampleThumbnail.getTotalLength(), 0, 1.0f);

			g.setColour(Colours::seagreen);
			g.drawRect(x, thumb.getY() , 1, thumb.getHeight() - 5, 1);


			g.setColour(Colours::crimson);
			g.drawRect(x2, thumb.getY(), 1, thumb.getHeight() - 5, 1);
		}
		else
		{
			g.setColour(Colours::grey);
			g.drawText("No Sample Loaded", thumb, Justification::centred, false);
		}

    }

    void resized() override
    {
    	int reduce2=40;
    	playButton->setBounds (281, 16, 130, 24);
	    stopButton->setBounds (446, 16, 130, 24);
		m_loadSampleButton->setBounds (116, 16, 130, 24);
		m_startPositionSlider->setBounds (310, 304-reduce2, 63, 80);
		m_startPosLabel->setBounds (214, 328-reduce2, 95, 24);
		m_grainSizeSlider->setBounds (110, 304-reduce2, 63, 80);
		m_grainSizeLabel->setBounds (22, 328-reduce2, 95, 24);
        m_mainPitchSlider->setBounds (510, 304-reduce2, 63, 80);
		m_mainPitchLabel->setBounds (430, 328-reduce2, 95, 24);
		m_windowBlendSlider->setBounds(54, 5, 64, 64);
		//m_windowBlendLabel->setBounds(64, 69, 64, 20);
		m_waveWidget->setBounds(5, 5, 64, 64);
    }

	void browseSample()
	{
		if (m_grainProcessor == 0) return;

		FileChooser fileSelector("Load sample", File(), "*.wav");

		if (fileSelector.browseForFileToOpen())
		{
			File selectedFile = fileSelector.getResult();
			
			//ValueTree v(Identifier("SampleFile"));
			//v.setProperty(Identifier("Path"), selectedFile.getFullPathName(), nullptr);

			//m_valueTreeState.state.addChild(v, 0, nullptr);
			//
			m_valueTreeState.state.setProperty(Identifier("SampleFile"), selectedFile.getFullPathName(), nullptr);


			//m_grainProcessor->setPlayState(true);

			//loadSample(selectedFile);
		}


	}

	void loadSample(File file)
	{
		std::unique_ptr<AudioFormatReader> reader;
		reader.reset(m_formatManager.createReaderFor(file));
		AudioSampleBuffer buffer(reader->numChannels, reader->lengthInSamples);

		reader->read(&buffer, 0, reader->lengthInSamples, 0, true, false);
		m_grainProcessor->setAudioSize(buffer.getNumSamples());
		for (int i = 0; i < buffer.getNumSamples(); ++i)
		{
			m_grainProcessor->setAudioSample(i, buffer.getSample(0, i));
		}

		m_sampleThumbnail.setSource(new FileInputSource(file));

		//m_grainProcessor->setPlayState(true);
	}


	void buttonClicked(Button* button) override
	{
		if (m_grainProcessor == 0) return; 
		if (button == playButton.get())
	    {
	        //[UserButtonCode_playButton] -- add your button handler code here..
			m_grainProcessor->setPlayState(true);
	        //[/UserButtonCode_playButton]
	    }
	    else if (button == stopButton.get())
	    {
	        //[UserButtonCode_stopButton] -- add your button handler code here..
			m_grainProcessor->setPlayState(false);
	   	 	m_processor.updateMagic(m_startPositionSlider->getValue(),m_grainSizeSlider->getValue());
	        //[/UserButtonCode_stopButton]
	    }
		else if (button == m_loadSampleButton.get())
		{
			browseSample();
		}
	}

	void sliderValueChanged(Slider* slider) override
	{
		if (m_grainProcessor == 0) return; 

		else if (slider == m_windowBlendSlider.get())
		{
			m_waveWidget->setBlendAmount(m_windowBlendSlider->getValue());
		}

		else if (slider == m_grainSizeSlider.get()) repaint();
		else if (slider == m_startPositionSlider.get()) repaint();
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

	void mouseUp(const MouseEvent& e) override
	{
		if (m_sampleThumbnail.isFullyLoaded())
		{
			//DBG("sample is ok");
			//const ScopedLock sl(m_grainProcessor.getAudioCallbackLock());
			auto thumb = getLocalBounds();
			thumb.removeFromTop(getHeight() * 0.2f);
			thumb.removeFromBottom(getHeight() * 0.25f);
			thumb=thumb.reduced(3);

			if (thumb.contains(e.x, e.y-150)) {
				m_startPositionSlider->setValue((double)(e.x - thumb.getTopLeft().x) / (double)thumb.getWidth());
				//DBG("inside");
			}
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
	HourglassGranularAudioProcessor& m_processor;
	JuicyClouds* m_grainProcessor;

	// UI Components
	std::unique_ptr<TextButton> playButton;
    std::unique_ptr<TextButton> stopButton;

	std::unique_ptr<TextButton> m_loadSampleButton;

	std::unique_ptr<Slider> m_startPositionSlider;
	std::unique_ptr<SliderAttachment> m_startPositionAttachment;

	std::unique_ptr<Slider> m_grainSizeSlider;
	std::unique_ptr<SliderAttachment> m_grainSizeAttachment;

	std::unique_ptr<Slider> m_mainPitchSlider;
	std::unique_ptr<SliderAttachment> m_mainPitchAttachment;

	std::unique_ptr<Slider> m_windowBlendSlider;
	std::unique_ptr<SliderAttachment> m_blendAttachment;

	std::unique_ptr<Label> m_startPosLabel;
	std::unique_ptr<Label> m_grainSizeLabel;
	std::unique_ptr<Label> m_mainPitchLabel;
	std::unique_ptr<Label> m_windowBlendLabel;

	AudioFormatManager m_formatManager;

	AudioThumbnailCache m_thumbnailCache;
	AudioThumbnail m_sampleThumbnail;

	std::unique_ptr<WavetableWidget> m_waveWidget;

	AudioProcessorValueTreeState& m_valueTreeState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrainChannelComponent)
};
