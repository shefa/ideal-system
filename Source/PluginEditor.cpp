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

#include "PluginEditor.h"
#include "GrainContentComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MmcwAudioProcessorEditor::MmcwAudioProcessorEditor (MmcwAudioProcessor& ownerFilter, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(ownerFilter),
      processor(ownerFilter),
      m_valueTreeState(vts),
      m_spectComponent(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
	//m_grainComponent.setProcessor(processor.getGranularProcessor());
	//addAndMakeVisible(m_grainComponent);
    //[/Constructor_pre]

    inputSlider.reset (new Slider ("input"));
    addAndMakeVisible (inputSlider.get());
    inputSlider->setRange (-50, 50, 1);
    inputSlider->setSliderStyle (Slider::Rotary);
    inputSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    inputSlider->addListener (this);

    inputSlider->setBounds (64, 120, 88, 56);

    inputLabel.reset (new Label ("input",
                                 TRANS("Input")));
    addAndMakeVisible (inputLabel.get());
    inputLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    inputLabel->setJustificationType (Justification::centredLeft);
    inputLabel->setEditable (false, false, false);
    inputLabel->setColour (TextEditor::textColourId, Colours::black);
    inputLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    inputLabel->setBounds (16, 136, 48, 24);

    outputSlider.reset (new Slider ("output"));
    addAndMakeVisible (outputSlider.get());
    outputSlider->setRange (-100, 100, 10);
    outputSlider->setSliderStyle (Slider::Rotary);
    outputSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    outputSlider->addListener (this);

    outputSlider->setBounds (520, 120, 60, 56);

    outputLabel.reset (new Label ("output",
                                  TRANS("Output")));
    addAndMakeVisible (outputLabel.get());
    outputLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    outputLabel->setJustificationType (Justification::centredLeft);
    outputLabel->setEditable (false, false, false);
    outputLabel->setColour (TextEditor::textColourId, Colours::black);
    outputLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    outputLabel->setBounds (464, 136, 48, 24);

    noiseGateSlider.reset (new Slider ("noisegate"));
    addAndMakeVisible (noiseGateSlider.get());
    noiseGateSlider->setRange (0, 10, 0);
    noiseGateSlider->setSliderStyle (Slider::Rotary);
    noiseGateSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    noiseGateSlider->addListener (this);

    noiseGateSlider->setBounds (312, 120, 88, 56);

    noiseGateLabel.reset (new Label ("noisegate",
                                     TRANS("Noise Gate")));
    addAndMakeVisible (noiseGateLabel.get());
    noiseGateLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    noiseGateLabel->setJustificationType (Justification::centredLeft);
    noiseGateLabel->setEditable (false, false, false);
    noiseGateLabel->setColour (TextEditor::textColourId, Colours::black);
    noiseGateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    noiseGateLabel->setBounds (232, 136, 87, 24);

    tabbedComponent.reset (new TabbedComponent (TabbedButtonBar::TabsAtTop));
    addAndMakeVisible (tabbedComponent.get());
    tabbedComponent->setTabBarDepth (30);
    tabbedComponent->addTab (TRANS("Granular Synthesis"), Colours::lightgrey, new GrainContentComponent (processor, processor.getGranularProcessor(),vts), true);
    tabbedComponent->addTab (TRANS("Spectrogram"), Colours::lightgrey, new SpectrogramContentComponent (ownerFilter), true);
    tabbedComponent->addTab (TRANS("Convolution"), Colours::lightgrey, new ConvolutionDemo(), true);
    tabbedComponent->addTab (TRANS("Overdrive"), Colours::lightgrey, new OverdriveDemo(), true);
    tabbedComponent->setCurrentTabIndex (0);

    tabbedComponent->setBounds (0, 250, 600, 350);

    bpmSlider.reset (new Slider ("bpm"));
    addAndMakeVisible (bpmSlider.get());
    bpmSlider->setRange (20, 500, 10);
    bpmSlider->setSliderStyle (Slider::LinearHorizontal);
    bpmSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    bpmSlider->addListener (this);

    bpmSlider->setBounds (64, 200, 96, 40);

    bpmLabel.reset (new Label ("bpm",
                               TRANS("BPM")));
    addAndMakeVisible (bpmLabel.get());
    bpmLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    bpmLabel->setJustificationType (Justification::centredLeft);
    bpmLabel->setEditable (false, false, false);
    bpmLabel->setColour (TextEditor::textColourId, Colours::black);
    bpmLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    bpmLabel->setBounds (16, 200, 40, 24);

    bpmToggle.reset (new ToggleButton ("bpm"));
    addAndMakeVisible (bpmToggle.get());
    bpmToggle->setButtonText (TRANS("from DAW"));
    bpmToggle->addListener (this);

    bpmToggle->setBounds (432, 64, 104, 24);

    bpmDivSlider.reset (new Slider ("bpmdiv"));
    addAndMakeVisible (bpmDivSlider.get());
    bpmDivSlider->setRange (0.25, 16, 0.25);
    bpmDivSlider->setSliderStyle (Slider::LinearHorizontal);
    bpmDivSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    bpmDivSlider->addListener (this);

    bpmDivSlider->setBounds (488, 200, 96, 40);

    bpmDivLabel.reset (new Label ("bpmdiv",
                                  TRANS("Tempo Division")));
    addAndMakeVisible (bpmDivLabel.get());
    bpmDivLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    bpmDivLabel->setJustificationType (Justification::centredLeft);
    bpmDivLabel->setEditable (false, false, false);
    bpmDivLabel->setColour (TextEditor::textColourId, Colours::black);
    bpmDivLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    bpmDivLabel->setBounds (368, 200, 112, 24);

    ConvToggle.reset (new ToggleButton ("convToggle"));
    addAndMakeVisible (ConvToggle.get());
    ConvToggle->setButtonText (TRANS("Convolve"));
    ConvToggle->addListener (this);

    ConvToggle->setBounds (224, 200, 96, 24);

    fftToggle.reset (new ToggleButton ("ffttoggle"));
    addAndMakeVisible (fftToggle.get());
    fftToggle->setButtonText (TRANS("FFT2"));
    fftToggle->addListener (this);

    fftToggle->setBounds (432, 88, 96, 24);


    //[UserPreSize]
    //tabbedComponent->getTabContentComponent(1).setProcessor(processor.getGranularProcessor());
	bpmSlider->setValue(120.0f, NotificationType::dontSendNotification);
	bpmDivSlider->setValue(1.0f, NotificationType::dontSendNotification);
	m_inputSliderAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(m_valueTreeState, "inputGain", *inputSlider));
	m_outputSliderAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(m_valueTreeState, "outputGain", *outputSlider));
	m_noiseGateAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(m_valueTreeState, "noiseGate", *noiseGateSlider));
	m_bpmAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(m_valueTreeState, "masterTempo", *bpmSlider));
	m_bpmDivAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(m_valueTreeState, "tempoDivision", *bpmDivSlider));
	m_bpmToggleAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment(m_valueTreeState, "bpmToggle", *bpmToggle));
    m_convToggleAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment(m_valueTreeState, "convToggle", *ConvToggle));
    m_fftToggleAttachment.reset(new AudioProcessorValueTreeState::ButtonAttachment(m_valueTreeState, "fftToggle", *fftToggle));
    //[/UserPreSize]

    setSize (600, 600);


    //[Constructor] You can add your own custom stuff here..
	startTimer(40);
    //[/Constructor]
}

MmcwAudioProcessorEditor::~MmcwAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    inputSlider = nullptr;
    inputLabel = nullptr;
    outputSlider = nullptr;
    outputLabel = nullptr;
    noiseGateSlider = nullptr;
    noiseGateLabel = nullptr;
    tabbedComponent = nullptr;
    bpmSlider = nullptr;
    bpmLabel = nullptr;
    bpmToggle = nullptr;
    bpmDivSlider = nullptr;
    bpmDivLabel = nullptr;
    ConvToggle = nullptr;
    fftToggle = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MmcwAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 8, y = 16, width = 320, height = 30;
        String text (TRANS("Multimedia Coursework"));
        Colour fillColour = Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (Font::getDefaultMonospacedFontName(), 25.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 432, y = 8, width = 160, height = 30;
        String text (TRANS("By Georgi Marinov"));
        Colour fillColour = Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 432, y = 32, width = 152, height = 30;
        String text (TRANS("C1880922"));
        Colour fillColour = Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.00f, Font::plain).withTypefaceStyle ("Regular").withExtraKerningFactor (0.155f));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    {
        int x = 8, y = 56, width = 320, height = 30;
        String text (TRANS("Cool Real-time stuff"));
        Colour fillColour = Colours::aliceblue;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (Font (Font::getDefaultMonospacedFontName(), 25.00f, Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    Justification::centredLeft, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MmcwAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MmcwAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == inputSlider.get())
    {
        //[UserSliderCode_inputSlider] -- add your slider handling code here..
        //[/UserSliderCode_inputSlider]
    }
    else if (sliderThatWasMoved == outputSlider.get())
    {
        //[UserSliderCode_outputSlider] -- add your slider handling code here..
        //[/UserSliderCode_outputSlider]
    }
    else if (sliderThatWasMoved == noiseGateSlider.get())
    {
        //[UserSliderCode_noiseGateSlider] -- add your slider handling code here..
        //[/UserSliderCode_noiseGateSlider]
    }
    else if (sliderThatWasMoved == bpmSlider.get())
    {
        //[UserSliderCode_bpmSlider] -- add your slider handling code here..
        //[/UserSliderCode_bpmSlider]
    }
    else if (sliderThatWasMoved == bpmDivSlider.get())
    {
        //[UserSliderCode_bpmDivSlider] -- add your slider handling code here..
        //[/UserSliderCode_bpmDivSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MmcwAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bpmToggle.get())
    {
        //[UserButtonCode_bpmToggle] -- add your button handler code here..
        //[/UserButtonCode_bpmToggle]
    }
    else if (buttonThatWasClicked == ConvToggle.get())
    {
        //[UserButtonCode_ConvToggle] -- add your button handler code here..
        //[/UserButtonCode_ConvToggle]
    }
    else if (buttonThatWasClicked == fftToggle.get())
    {
        //[UserButtonCode_fftToggle] -- add your button handler code here..
        //[/UserButtonCode_fftToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MmcwAudioProcessorEditor::timerCallback() {
	if (*processor.m_bpmToggle==1.0f &&  processor.infobpm.bpm != (int)bpmSlider->getValue())
		bpmSlider->setValue(processor.infobpm.bpm);
	//m_valueTreeState.state.setProperty(Identifier("masterTempo"), x, nullptr);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MmcwAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="MmcwAudioProcessor&amp; ownerFilter, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="AudioProcessorEditor(ownerFilter),&#10;processor(ownerFilter),&#10;m_valueTreeState(vts),&#10;m_spectComponent(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="600">
  <BACKGROUND backgroundColour="ff323e44">
    <TEXT pos="8 16 320 30" fill="solid: fff0f8ff" hasStroke="0" text="Multimedia Coursework"
          fontname="Default monospaced font" fontsize="25.0" kerning="0.0"
          bold="0" italic="0" justification="33"/>
    <TEXT pos="432 8 160 30" fill="solid: fff0f8ff" hasStroke="0" text="By Georgi Marinov"
          fontname="Default monospaced font" fontsize="15.0" kerning="0.0"
          bold="0" italic="0" justification="33"/>
    <TEXT pos="432 32 152 30" fill="solid: fff0f8ff" hasStroke="0" text="C1880922"
          fontname="Default monospaced font" fontsize="15.0" kerning="0.155"
          bold="0" italic="0" justification="33"/>
    <TEXT pos="8 56 320 30" fill="solid: fff0f8ff" hasStroke="0" text="Cool Real-time stuff"
          fontname="Default monospaced font" fontsize="25.0" kerning="0.0"
          bold="0" italic="0" justification="33"/>
  </BACKGROUND>
  <SLIDER name="input" id="391c83354aa9630f" memberName="inputSlider" virtualName=""
          explicitFocusOrder="0" pos="64 120 88 56" min="-50.0" max="50.0"
          int="1.0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="input" id="41a347fc8ca0046e" memberName="inputLabel" virtualName=""
         explicitFocusOrder="0" pos="16 136 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="output" id="7b1b755b03aa2051" memberName="outputSlider"
          virtualName="" explicitFocusOrder="0" pos="520 120 60 56" min="-100.0"
          max="100.0" int="10.0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="output" id="745946be860c5b6a" memberName="outputLabel"
         virtualName="" explicitFocusOrder="0" pos="464 136 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="noisegate" id="1e3f717a0b22f86" memberName="noiseGateSlider"
          virtualName="" explicitFocusOrder="0" pos="312 120 88 56" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="noisegate" id="4513f721caa92a28" memberName="noiseGateLabel"
         virtualName="" explicitFocusOrder="0" pos="232 136 87 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Noise Gate" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TABBEDCOMPONENT name="new tabbed component" id="83779c27aaa075bd" memberName="tabbedComponent"
                   virtualName="" explicitFocusOrder="0" pos="0 250 600 350" orientation="top"
                   tabBarDepth="30" initialTab="0">
    <TAB name="Granular Synthesis" colour="ffd3d3d3" useJucerComp="1"
         contentClassName="GrainContentComponent" constructorParams="processor, processor.getGranularProcessor(),vts"
         jucerComponentFile="GrainContentComponent.cpp"/>
    <TAB name="Spectrogram" colour="ffd3d3d3" useJucerComp="0" contentClassName="SpectrogramContentComponent"
         constructorParams="ownerFilter" jucerComponentFile="SpectrogramContentComponent.h"/>
    <TAB name="Convolution" colour="ffd3d3d3" useJucerComp="0" contentClassName="ConvolutionDemo"
         constructorParams="" jucerComponentFile="Conv/ConvolutionDemo.h"/>
    <TAB name="Overdrive" colour="ffd3d3d3" useJucerComp="0" contentClassName="OverdriveDemo"
         constructorParams="" jucerComponentFile=""/>
  </TABBEDCOMPONENT>
  <SLIDER name="bpm" id="5e663459977c5cb" memberName="bpmSlider" virtualName=""
          explicitFocusOrder="0" pos="64 200 96 40" min="20.0" max="500.0"
          int="10.0" style="LinearHorizontal" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="bpm" id="87f8702e91e4af57" memberName="bpmLabel" virtualName=""
         explicitFocusOrder="0" pos="16 200 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="BPM" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="bpm" id="6cb132e911794ad9" memberName="bpmToggle" virtualName=""
                explicitFocusOrder="0" pos="432 64 104 24" buttonText="from DAW"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="bpmdiv" id="ca5762afce4c2194" memberName="bpmDivSlider"
          virtualName="" explicitFocusOrder="0" pos="488 200 96 40" min="0.25"
          max="16.0" int="0.25" style="LinearHorizontal" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="bpmdiv" id="7c10074f0a3561d0" memberName="bpmDivLabel"
         virtualName="" explicitFocusOrder="0" pos="368 200 112 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tempo Division" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="convToggle" id="9dbc7b718df424a6" memberName="ConvToggle"
                virtualName="" explicitFocusOrder="0" pos="224 200 96 24" buttonText="Convolve"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="ffttoggle" id="6fc1d6bee27c5fa3" memberName="fftToggle"
                virtualName="" explicitFocusOrder="0" pos="432 88 96 24" buttonText="FFT2"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

