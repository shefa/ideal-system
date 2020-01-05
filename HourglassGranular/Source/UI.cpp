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

#include "UI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
UI::UI (HourglassGranularAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p),
      processor(p),
      m_valueTreeState(vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    bpmSlider.reset (new Slider ("bpm"));
    addAndMakeVisible (bpmSlider.get());
    bpmSlider->setRange (20, 500, 10);
    bpmSlider->setSliderStyle (Slider::LinearHorizontal);
    bpmSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    bpmSlider->addListener (this);

    bpmSlider->setBounds (64, 100, 96, 40);

    bpmLabel.reset (new Label ("bpm",
                               TRANS("BPM")));
    addAndMakeVisible (bpmLabel.get());
    bpmLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    bpmLabel->setJustificationType (Justification::centredLeft);
    bpmLabel->setEditable (false, false, false);
    bpmLabel->setColour (TextEditor::textColourId, Colours::black);
    bpmLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    bpmLabel->setBounds (16, 100, 40, 24);

    bpmDivSlider.reset (new Slider ("bpmdiv"));
    addAndMakeVisible (bpmDivSlider.get());
    bpmDivSlider->setRange (0.25, 16, 0.25);
    bpmDivSlider->setSliderStyle (Slider::LinearHorizontal);
    bpmDivSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    bpmDivSlider->addListener (this);

    bpmDivSlider->setBounds (488, 100, 96, 40);

    bpmDivLabel.reset (new Label ("bpmdiv",
                                  TRANS("Tempo Division")));
    addAndMakeVisible (bpmDivLabel.get());
    bpmDivLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    bpmDivLabel->setJustificationType (Justification::centredLeft);
    bpmDivLabel->setEditable (false, false, false);
    bpmDivLabel->setColour (TextEditor::textColourId, Colours::black);
    bpmDivLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    bpmDivLabel->setBounds (368, 100, 112, 24);

    convToggle.reset (new ToggleButton ("convToggle"));
    addAndMakeVisible (convToggle.get());
    convToggle->setButtonText (TRANS("Convolve"));
    convToggle->addListener (this);

    convToggle->setBounds (224, 104, 96, 24);

    bpmToggle.reset (new ToggleButton ("bpm"));
    addAndMakeVisible (bpmToggle.get());
    bpmToggle->setButtonText (TRANS("from DAW"));
    bpmToggle->addListener (this);

    bpmToggle->setBounds (224, 72, 104, 24);

    inputSlider.reset (new Slider ("input"));
    addAndMakeVisible (inputSlider.get());
    inputSlider->setRange (-50, 50, 1);
    inputSlider->setSliderStyle (Slider::Rotary);
    inputSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    inputSlider->addListener (this);

    inputSlider->setBounds (60, 9, 88, 56);

    inputLabel.reset (new Label ("input",
                                 TRANS("Input")));
    addAndMakeVisible (inputLabel.get());
    inputLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    inputLabel->setJustificationType (Justification::centredLeft);
    inputLabel->setEditable (false, false, false);
    inputLabel->setColour (TextEditor::textColourId, Colours::black);
    inputLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    inputLabel->setBounds (12, 25, 48, 24);

    outputSlider.reset (new Slider ("output"));
    addAndMakeVisible (outputSlider.get());
    outputSlider->setRange (-100, 100, 10);
    outputSlider->setSliderStyle (Slider::Rotary);
    outputSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    outputSlider->addListener (this);

    outputSlider->setBounds (516, 9, 60, 56);

    outputLabel.reset (new Label ("output",
                                  TRANS("Output")));
    addAndMakeVisible (outputLabel.get());
    outputLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    outputLabel->setJustificationType (Justification::centredLeft);
    outputLabel->setEditable (false, false, false);
    outputLabel->setColour (TextEditor::textColourId, Colours::black);
    outputLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    outputLabel->setBounds (460, 25, 48, 24);

    noiseGateSlider.reset (new Slider ("noisegate"));
    addAndMakeVisible (noiseGateSlider.get());
    noiseGateSlider->setRange (0, 10, 0);
    noiseGateSlider->setSliderStyle (Slider::Rotary);
    noiseGateSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    noiseGateSlider->addListener (this);

    noiseGateSlider->setBounds (308, 9, 88, 56);

    noiseGateLabel.reset (new Label ("noisegate",
                                     TRANS("Noise Gate")));
    addAndMakeVisible (noiseGateLabel.get());
    noiseGateLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    noiseGateLabel->setJustificationType (Justification::centredLeft);
    noiseGateLabel->setEditable (false, false, false);
    noiseGateLabel->setColour (TextEditor::textColourId, Colours::black);
    noiseGateLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    noiseGateLabel->setBounds (228, 25, 87, 24);

    component.reset (new Component());
    addAndMakeVisible (component.get());
    component->setBounds (0, 200, 600, 330);


    //[UserPreSize]
    m_midiTrigAttach.reset(new ButtonAttachment(m_valueTreeState, "midiToggle", *bpmToggle.get()));
    m_convTrigAttach.reset(new ButtonAttachment(m_valueTreeState, "midiToggle", *convToggle.get()));
    m_tempoDivisionAttachment.reset(new SliderAttachment(m_valueTreeState, "tempoDivision", *bpmDivSlider.get()));
    m_masterTempoAttachment.reset(new SliderAttachment(m_valueTreeState, "masterTempo", *bpmSlider.get()));
    //[/UserPreSize]

    setSize (600, 450);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

UI::~UI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    bpmSlider = nullptr;
    bpmLabel = nullptr;
    bpmDivSlider = nullptr;
    bpmDivLabel = nullptr;
    convToggle = nullptr;
    bpmToggle = nullptr;
    inputSlider = nullptr;
    inputLabel = nullptr;
    outputSlider = nullptr;
    outputLabel = nullptr;
    noiseGateSlider = nullptr;
    noiseGateLabel = nullptr;
    component = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void UI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == bpmSlider.get())
    {
        //[UserSliderCode_bpmSlider] -- add your slider handling code here..
        //[/UserSliderCode_bpmSlider]
    }
    else if (sliderThatWasMoved == bpmDivSlider.get())
    {
        //[UserSliderCode_bpmDivSlider] -- add your slider handling code here..
        //[/UserSliderCode_bpmDivSlider]
    }
    else if (sliderThatWasMoved == inputSlider.get())
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

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void UI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == convToggle.get())
    {
        //[UserButtonCode_convToggle] -- add your button handler code here..
        //[/UserButtonCode_convToggle]
    }
    else if (buttonThatWasClicked == bpmToggle.get())
    {
        //[UserButtonCode_bpmToggle] -- add your button handler code here..
        //[/UserButtonCode_bpmToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void UI::timerCallback() {
	//if (*processor.m_bpmToggle==1.0f &&  processor.infobpm.bpm != (int)bpmSlider->getValue())
		//bpmSlider->setValue(processor.infobpm.bpm);
	//m_valueTreeState.state.setProperty(Identifier("masterTempo"), x, nullptr);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UI" componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="HourglassGranularAudioProcessor&amp; p, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="AudioProcessorEditor(&amp;p),&#10;&#9;processor(p),&#10;&#9;m_valueTreeState(vts)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="450">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="bpm" id="5e663459977c5cb" memberName="bpmSlider" virtualName=""
          explicitFocusOrder="0" pos="64 100 96 40" min="20.0" max="500.0"
          int="10.0" style="LinearHorizontal" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="bpm" id="87f8702e91e4af57" memberName="bpmLabel" virtualName=""
         explicitFocusOrder="0" pos="16 100 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="BPM" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="bpmdiv" id="ca5762afce4c2194" memberName="bpmDivSlider"
          virtualName="" explicitFocusOrder="0" pos="488 100 96 40" min="0.25"
          max="16.0" int="0.25" style="LinearHorizontal" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="bpmdiv" id="7c10074f0a3561d0" memberName="bpmDivLabel"
         virtualName="" explicitFocusOrder="0" pos="368 100 112 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tempo Division" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="convToggle" id="9dbc7b718df424a6" memberName="convToggle"
                virtualName="" explicitFocusOrder="0" pos="224 104 96 24" buttonText="Convolve"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="bpm" id="6cb132e911794ad9" memberName="bpmToggle" virtualName=""
                explicitFocusOrder="0" pos="224 72 104 24" buttonText="from DAW"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="input" id="391c83354aa9630f" memberName="inputSlider" virtualName=""
          explicitFocusOrder="0" pos="60 9 88 56" min="-50.0" max="50.0"
          int="1.0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="input" id="41a347fc8ca0046e" memberName="inputLabel" virtualName=""
         explicitFocusOrder="0" pos="12 25 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="output" id="7b1b755b03aa2051" memberName="outputSlider"
          virtualName="" explicitFocusOrder="0" pos="516 9 60 56" min="-100.0"
          max="100.0" int="10.0" style="Rotary" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="output" id="745946be860c5b6a" memberName="outputLabel"
         virtualName="" explicitFocusOrder="0" pos="460 25 48 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="noisegate" id="1e3f717a0b22f86" memberName="noiseGateSlider"
          virtualName="" explicitFocusOrder="0" pos="308 9 88 56" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="noisegate" id="4513f721caa92a28" memberName="noiseGateLabel"
         virtualName="" explicitFocusOrder="0" pos="228 25 87 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Noise Gate" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <JUCERCOMP name="" id="b4921d1a7df57236" memberName="component" virtualName=""
             explicitFocusOrder="0" pos="0 200 600 330" sourceFile="" constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

