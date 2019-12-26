/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "GrainContentComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GrainContentComponent::GrainContentComponent (MmcwAudioProcessor& proc, GrainContentProcessor* x, AudioProcessorValueTreeState& vts)
    : m_processor(proc),m_grainProcessor(x),m_thumbnailCache(5),m_sampleThumbnail(512,m_formatManager,m_thumbnailCache),m_valueTreeState(vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    playButton.reset (new TextButton ("play"));
    addAndMakeVisible (playButton.get());
    playButton->setButtonText (TRANS("Play"));
    playButton->addListener (this);
    playButton->setColour (TextButton::buttonColourId, Colours::cadetblue);

    playButton->setBounds (224, 16, 150, 24);

    stopButton.reset (new TextButton ("stop"));
    addAndMakeVisible (stopButton.get());
    stopButton->setButtonText (TRANS("Stop"));
    stopButton->addListener (this);
    stopButton->setColour (TextButton::buttonColourId, Colours::cadetblue);

    stopButton->setBounds (416, 16, 150, 24);

    sliderGrainSize.reset (new Slider ("grainsize"));
    addAndMakeVisible (sliderGrainSize.get());
    sliderGrainSize->setRange (0, 10, 0);
    sliderGrainSize->setSliderStyle (Slider::Rotary);
    sliderGrainSize->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderGrainSize->addListener (this);

    sliderGrainSize->setBounds (104, 240, 63, 80);

    loadSampleButton.reset (new TextButton ("samplebtn"));
    addAndMakeVisible (loadSampleButton.get());
    loadSampleButton->setButtonText (TRANS("Load Sample"));
    loadSampleButton->addListener (this);
    loadSampleButton->setColour (TextButton::buttonColourId, Colours::cadetblue);

    loadSampleButton->setBounds (24, 16, 150, 24);

    silderGrainStart.reset (new Slider ("grainstart"));
    addAndMakeVisible (silderGrainStart.get());
    silderGrainStart->setRange (0, 10, 0);
    silderGrainStart->setSliderStyle (Slider::Rotary);
    silderGrainStart->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    silderGrainStart->addListener (this);

    silderGrainStart->setBounds (304, 240, 63, 80);

    sliderGrainPitch.reset (new Slider ("grainpitch"));
    addAndMakeVisible (sliderGrainPitch.get());
    sliderGrainPitch->setRange (0, 10, 0);
    sliderGrainPitch->setSliderStyle (Slider::Rotary);
    sliderGrainPitch->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderGrainPitch->addListener (this);

    sliderGrainPitch->setBounds (504, 240, 63, 80);

    labelGrainSize.reset (new Label ("grainsize",
                                     TRANS("Grain Size")));
    addAndMakeVisible (labelGrainSize.get());
    labelGrainSize->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelGrainSize->setJustificationType (Justification::centredLeft);
    labelGrainSize->setEditable (false, false, false);
    labelGrainSize->setColour (TextEditor::textColourId, Colours::black);
    labelGrainSize->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    labelGrainSize->setBounds (16, 264, 95, 24);

    labelGrainStart.reset (new Label ("grainstart",
                                      TRANS("Grain Start")));
    addAndMakeVisible (labelGrainStart.get());
    labelGrainStart->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelGrainStart->setJustificationType (Justification::centredLeft);
    labelGrainStart->setEditable (false, false, false);
    labelGrainStart->setColour (TextEditor::textColourId, Colours::black);
    labelGrainStart->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    labelGrainStart->setBounds (208, 264, 95, 24);

    labelGrainPitch.reset (new Label ("grainpitch",
                                      TRANS("Grain Pitch")));
    addAndMakeVisible (labelGrainPitch.get());
    labelGrainPitch->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelGrainPitch->setJustificationType (Justification::centredLeft);
    labelGrainPitch->setEditable (false, false, false);
    labelGrainPitch->setColour (TextEditor::textColourId, Colours::black);
    labelGrainPitch->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    labelGrainPitch->setBounds (424, 264, 95, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 330);


    //[Constructor] You can add your own custom stuff here..
	m_startPositionAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(m_valueTreeState, "grainStartPosition", *silderGrainStart));
	m_grainSizeAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(m_valueTreeState, "grainSizeMultiplier", *sliderGrainSize));
	m_mainPitchAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(m_valueTreeState, "pitchShiftFrequency", *sliderGrainPitch));
	m_formatManager.registerBasicFormats();
	m_sampleThumbnail.addChangeListener(this);
	m_valueTreeState.state.addListener(this);
	startTimer(40);
    //[/Constructor]
}

GrainContentComponent::~GrainContentComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    playButton = nullptr;
    stopButton = nullptr;
    sliderGrainSize = nullptr;
    loadSampleButton = nullptr;
    silderGrainStart = nullptr;
    sliderGrainPitch = nullptr;
    labelGrainSize = nullptr;
    labelGrainStart = nullptr;
    labelGrainPitch = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GrainContentComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
	auto thumb = getLocalBounds();
	thumb.removeFromTop(getHeight() * 0.15f);
	thumb.removeFromBottom(getHeight() * 0.25f);
	g.setColour(getLookAndFeel().findColour(Slider::backgroundColourId));
	g.fillRect(thumb.reduced(3));

	if (m_sampleThumbnail.getTotalLength() > 0.0)
	{
		int x = thumb.getRelativePoint(((float)silderGrainStart->getValue()), 1.0f).x;
		float tmpx = (float)silderGrainStart->getValue() + sliderGrainSize->getValue()*0.22f;

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
    //[/UserPaint]
}

void GrainContentComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GrainContentComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == playButton.get())
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
		m_grainProcessor->setPlayState(true);
        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == stopButton.get())
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
		m_grainProcessor->setPlayState(false);
    m_processor.updateMagic(silderGrainStart->getValue(),sliderGrainSize->getValue());
        //[/UserButtonCode_stopButton]
    }
    else if (buttonThatWasClicked == loadSampleButton.get())
    {
        //[UserButtonCode_loadSampleButton] -- add your button handler code here..
		browseSample();
        //[/UserButtonCode_loadSampleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void GrainContentComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderGrainSize.get())
    {
        //[UserSliderCode_sliderGrainSize] -- add your slider handling code here..
        //m_processor.updateMagic(silderGrainStart->getValue(),sliderGrainSize->getValue());
        //[/UserSliderCode_sliderGrainSize]
    }
    else if (sliderThatWasMoved == silderGrainStart.get())
    {
        //[UserSliderCode_silderGrainStart] -- add your slider handling code here..
        //m_processor.updateMagic(silderGrainStart->getValue(),sliderGrainSize->getValue());
        //[/UserSliderCode_silderGrainStart]
    }
    else if (sliderThatWasMoved == sliderGrainPitch.get())
    {
        //[UserSliderCode_sliderGrainPitch] -- add your slider handling code here..
        //[/UserSliderCode_sliderGrainPitch]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void GrainContentComponent::mouseDown(const MouseEvent& e)
{

}
void GrainContentComponent::mouseUp(const MouseEvent& e)
{
	if (m_sampleThumbnail.isFullyLoaded())
	{
		//const ScopedLock sl(m_grainProcessor.getAudioCallbackLock());
		auto thumb = getLocalBounds();
		thumb.removeFromTop(getHeight() * 0.15f);
		thumb.removeFromBottom(getHeight() * 0.25f);
		thumb=thumb.reduced(3);

		if (thumb.contains(e.x, e.y)) {
			silderGrainStart->setValue((double)(e.x - thumb.getTopLeft().x) / (double)thumb.getWidth());
		}
	}
}
void GrainContentComponent::timerCallback(){repaint();}
void GrainContentComponent::setProcessor(GrainContentProcessor* processor) {m_grainProcessor = processor;}
void GrainContentComponent::browseSample()
{
	if (m_grainProcessor == 0) return;

	m_grainProcessor->setPlayState(false);
	FileChooser fileSelector("Load sample", File(), "*.wav");

	if (fileSelector.browseForFileToOpen())
	{
		File selectedFile = fileSelector.getResult();
		m_valueTreeState.state.setProperty(Identifier("SampleFile"), selectedFile.getFullPathName(), nullptr);


		//loadSample(selectedFile);
	}
}

void GrainContentComponent::loadSample(File file)
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

}

void GrainContentComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &m_sampleThumbnail) repaint();
}

void GrainContentComponent::valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged,const Identifier& property)
{
	if (property == Identifier("SampleFile"))
	{
		String s = m_valueTreeState.state.getProperty(property);
		File f(s.trim());
		if (f.exists()) loadSample(f);
		else AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "MMCW", ("Could not locate sample " + s.trim()), "OK", this);
	}
}

void GrainContentComponent::valueTreeChildRemoved(ValueTree& parentTree,ValueTree& childWhichHasBeenRemoved,int indexFromWhichChildWasRemoved){}
void GrainContentComponent::valueTreeChildOrderChanged(ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) {}
void GrainContentComponent::valueTreeParentChanged(ValueTree& treeWhoseParentHasChanged){}
void GrainContentComponent::valueTreeChildAdded(ValueTree& parentTree,ValueTree& childWhichHasBeenAdded){}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GrainContentComponent" componentName=""
                 parentClasses="public Component, public ChangeListener, public Timer, public ValueTree::Listener"
                 constructorParams="MmcwAudioProcessor&amp; proc, GrainContentProcessor* x, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="m_processor(proc),m_grainProcessor(x),m_thumbnailCache(5),m_sampleThumbnail(512,m_formatManager,m_thumbnailCache),m_valueTreeState(vts)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="330">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="play" id="3cff215db977012" memberName="playButton" virtualName=""
              explicitFocusOrder="0" pos="224 16 150 24" bgColOff="ff5f9ea0"
              buttonText="Play" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="stop" id="f29fedec5f72c60a" memberName="stopButton" virtualName=""
              explicitFocusOrder="0" pos="416 16 150 24" bgColOff="ff5f9ea0"
              buttonText="Stop" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="grainsize" id="76a13b107dbbd720" memberName="sliderGrainSize"
          virtualName="" explicitFocusOrder="0" pos="104 240 63 80" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <TEXTBUTTON name="samplebtn" id="a4c8faf43346eb1" memberName="loadSampleButton"
              virtualName="" explicitFocusOrder="0" pos="24 16 150 24" bgColOff="ff5f9ea0"
              buttonText="Load Sample" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <SLIDER name="grainstart" id="56e14d271ca80ac3" memberName="silderGrainStart"
          virtualName="" explicitFocusOrder="0" pos="304 240 63 80" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="grainpitch" id="6f2d9dde86bf0511" memberName="sliderGrainPitch"
          virtualName="" explicitFocusOrder="0" pos="504 240 63 80" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="grainsize" id="d93203ff314e7e67" memberName="labelGrainSize"
         virtualName="" explicitFocusOrder="0" pos="16 264 95 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Grain Size" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="grainstart" id="7a0f9385d28d4e92" memberName="labelGrainStart"
         virtualName="" explicitFocusOrder="0" pos="208 264 95 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Grain Start" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="grainpitch" id="5a334bbc3602666d" memberName="labelGrainPitch"
         virtualName="" explicitFocusOrder="0" pos="424 264 95 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Grain Pitch" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

