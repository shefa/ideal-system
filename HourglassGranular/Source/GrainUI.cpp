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

#include "GrainUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
GrainUI::GrainUI (HourglassGranularAudioProcessor& proc, JuicyClouds* x, AudioProcessorValueTreeState& vts)
    : m_processor(proc),m_grainProcessor(x),m_thumbnailCache(5),m_sampleThumbnail(512,m_formatManager,m_thumbnailCache),m_valueTreeState(vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    loadButton.reset (new TextButton ("load btn"));
    addAndMakeVisible (loadButton.get());
    loadButton->setButtonText (TRANS("Load Sample"));
    loadButton->addListener (this);
    loadButton->setColour (TextButton::buttonColourId, Colours::cadetblue);

    loadButton->setBounds (16, 16, 150, 24);

    playButton.reset (new TextButton ("play btn"));
    addAndMakeVisible (playButton.get());
    playButton->setButtonText (TRANS("Play"));
    playButton->addListener (this);
    playButton->setColour (TextButton::buttonColourId, Colours::cadetblue);

    playButton->setBounds (216, 16, 150, 24);

    stopButton.reset (new TextButton ("stop btn"));
    addAndMakeVisible (stopButton.get());
    stopButton->setButtonText (TRANS("Stop"));
    stopButton->addListener (this);
    stopButton->setColour (TextButton::buttonColourId, Colours::cadetblue);

    stopButton->setBounds (424, 16, 150, 24);

    sliderGrainSize.reset (new Slider ("grainsize"));
    addAndMakeVisible (sliderGrainSize.get());
    sliderGrainSize->setRange (0, 10, 0);
    sliderGrainSize->setSliderStyle (Slider::Rotary);
    sliderGrainSize->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderGrainSize->addListener (this);

    sliderGrainSize->setBounds (110, 304, 63, 80);

    silderGrainStart.reset (new Slider ("grainstart"));
    addAndMakeVisible (silderGrainStart.get());
    silderGrainStart->setRange (0, 10, 0);
    silderGrainStart->setSliderStyle (Slider::Rotary);
    silderGrainStart->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    silderGrainStart->addListener (this);

    silderGrainStart->setBounds (310, 304, 63, 80);

    sliderGrainPitch.reset (new Slider ("grainpitch"));
    addAndMakeVisible (sliderGrainPitch.get());
    sliderGrainPitch->setRange (0, 10, 0);
    sliderGrainPitch->setSliderStyle (Slider::Rotary);
    sliderGrainPitch->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderGrainPitch->addListener (this);

    sliderGrainPitch->setBounds (510, 304, 63, 80);

    labelGrainSize.reset (new Label ("grainsize",
                                     TRANS("Grain Size")));
    addAndMakeVisible (labelGrainSize.get());
    labelGrainSize->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelGrainSize->setJustificationType (Justification::centredLeft);
    labelGrainSize->setEditable (false, false, false);
    labelGrainSize->setColour (TextEditor::textColourId, Colours::black);
    labelGrainSize->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    labelGrainSize->setBounds (22, 328, 95, 24);

    labelGrainStart.reset (new Label ("grainstart",
                                      TRANS("Grain Start")));
    addAndMakeVisible (labelGrainStart.get());
    labelGrainStart->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelGrainStart->setJustificationType (Justification::centredLeft);
    labelGrainStart->setEditable (false, false, false);
    labelGrainStart->setColour (TextEditor::textColourId, Colours::black);
    labelGrainStart->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    labelGrainStart->setBounds (214, 328, 95, 24);

    labelGrainPitch.reset (new Label ("grainpitch",
                                      TRANS("Grain Pitch")));
    addAndMakeVisible (labelGrainPitch.get());
    labelGrainPitch->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelGrainPitch->setJustificationType (Justification::centredLeft);
    labelGrainPitch->setEditable (false, false, false);
    labelGrainPitch->setColour (TextEditor::textColourId, Colours::black);
    labelGrainPitch->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    labelGrainPitch->setBounds (430, 328, 95, 24);

    sliderGrainSize2.reset (new Slider ("grainsize"));
    addAndMakeVisible (sliderGrainSize2.get());
    sliderGrainSize2->setRange (0, 10, 0);
    sliderGrainSize2->setSliderStyle (Slider::Rotary);
    sliderGrainSize2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderGrainSize2->addListener (this);

    sliderGrainSize2->setBounds (113, 213, 63, 80);

    silderGrainStart2.reset (new Slider ("grainstart"));
    addAndMakeVisible (silderGrainStart2.get());
    silderGrainStart2->setRange (0, 10, 0);
    silderGrainStart2->setSliderStyle (Slider::Rotary);
    silderGrainStart2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    silderGrainStart2->addListener (this);

    silderGrainStart2->setBounds (313, 213, 63, 80);

    sliderGrainPitch2.reset (new Slider ("grainpitch"));
    addAndMakeVisible (sliderGrainPitch2.get());
    sliderGrainPitch2->setRange (0, 10, 0);
    sliderGrainPitch2->setSliderStyle (Slider::Rotary);
    sliderGrainPitch2->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sliderGrainPitch2->addListener (this);

    sliderGrainPitch2->setBounds (513, 213, 63, 80);

    labelGrainSize2.reset (new Label ("grainsize",
                                      TRANS("Grain Size")));
    addAndMakeVisible (labelGrainSize2.get());
    labelGrainSize2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelGrainSize2->setJustificationType (Justification::centredLeft);
    labelGrainSize2->setEditable (false, false, false);
    labelGrainSize2->setColour (TextEditor::textColourId, Colours::black);
    labelGrainSize2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    labelGrainSize2->setBounds (25, 237, 95, 24);

    labelGrainStart2.reset (new Label ("grainstart",
                                       TRANS("Grain Start")));
    addAndMakeVisible (labelGrainStart2.get());
    labelGrainStart2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelGrainStart2->setJustificationType (Justification::centredLeft);
    labelGrainStart2->setEditable (false, false, false);
    labelGrainStart2->setColour (TextEditor::textColourId, Colours::black);
    labelGrainStart2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    labelGrainStart2->setBounds (217, 237, 95, 24);

    labelGrainPitch2.reset (new Label ("grainpitch",
                                       TRANS("Grain Pitch")));
    addAndMakeVisible (labelGrainPitch2.get());
    labelGrainPitch2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    labelGrainPitch2->setJustificationType (Justification::centredLeft);
    labelGrainPitch2->setEditable (false, false, false);
    labelGrainPitch2->setColour (TextEditor::textColourId, Colours::black);
    labelGrainPitch2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    labelGrainPitch2->setBounds (433, 237, 95, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 300);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

GrainUI::~GrainUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    loadButton = nullptr;
    playButton = nullptr;
    stopButton = nullptr;
    sliderGrainSize = nullptr;
    silderGrainStart = nullptr;
    sliderGrainPitch = nullptr;
    labelGrainSize = nullptr;
    labelGrainStart = nullptr;
    labelGrainPitch = nullptr;
    sliderGrainSize2 = nullptr;
    silderGrainStart2 = nullptr;
    sliderGrainPitch2 = nullptr;
    labelGrainSize2 = nullptr;
    labelGrainStart2 = nullptr;
    labelGrainPitch2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void GrainUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void GrainUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void GrainUI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == loadButton.get())
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
        //[/UserButtonCode_loadButton]
    }
    else if (buttonThatWasClicked == playButton.get())
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == stopButton.get())
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
        //[/UserButtonCode_stopButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void GrainUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderGrainSize.get())
    {
        //[UserSliderCode_sliderGrainSize] -- add your slider handling code here..
        //[/UserSliderCode_sliderGrainSize]
    }
    else if (sliderThatWasMoved == silderGrainStart.get())
    {
        //[UserSliderCode_silderGrainStart] -- add your slider handling code here..
        //[/UserSliderCode_silderGrainStart]
    }
    else if (sliderThatWasMoved == sliderGrainPitch.get())
    {
        //[UserSliderCode_sliderGrainPitch] -- add your slider handling code here..
        //[/UserSliderCode_sliderGrainPitch]
    }
    else if (sliderThatWasMoved == sliderGrainSize2.get())
    {
        //[UserSliderCode_sliderGrainSize2] -- add your slider handling code here..
        //[/UserSliderCode_sliderGrainSize2]
    }
    else if (sliderThatWasMoved == silderGrainStart2.get())
    {
        //[UserSliderCode_silderGrainStart2] -- add your slider handling code here..
        //[/UserSliderCode_silderGrainStart2]
    }
    else if (sliderThatWasMoved == sliderGrainPitch2.get())
    {
        //[UserSliderCode_sliderGrainPitch2] -- add your slider handling code here..
        //[/UserSliderCode_sliderGrainPitch2]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void GrainUI::filesDropped (const StringArray& filenames, int mouseX, int mouseY)
{
    //[UserCode_filesDropped] -- Add your code here...
    //[/UserCode_filesDropped]
}

void GrainUI::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    //[/UserCode_mouseUp]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void GrainUI::timerCallback() {
}
void GrainUI::browseSample(){}

void GrainUI::loadSample(File file){}

void GrainUI::changeListenerCallback(ChangeBroadcaster* source){}

void GrainUI::valueTreePropertyChanged(ValueTree& treeWhosePropertyHasChanged, const Identifier& property)
{
}

void GrainUI::valueTreeChildRemoved(ValueTree& parentTree,ValueTree& childWhichHasBeenRemoved,int indexFromWhichChildWasRemoved) {}
void GrainUI::valueTreeChildOrderChanged(ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) {}
void GrainUI::valueTreeParentChanged(ValueTree& treeWhoseParentHasChanged) {}
void GrainUI::valueTreeChildAdded(ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) {}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="GrainUI" componentName=""
                 parentClasses="public Component, public ChangeListener, public Timer, public ValueTree::Listener"
                 constructorParams="HourglassGranularAudioProcessor&amp; proc, JuicyClouds* x, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="m_processor(proc),m_grainProcessor(x),m_thumbnailCache(5),m_sampleThumbnail(512,m_formatManager,m_thumbnailCache),m_valueTreeState(vts)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="300">
  <METHODS>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
    <METHOD name="filesDropped (const StringArray&amp; filenames, int mouseX, int mouseY)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="load btn" id="b54c54bc5d8e15d9" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="16 16 150 24" bgColOff="ff5f9ea0"
              buttonText="Load Sample" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="play btn" id="1bb370e1bfd24dac" memberName="playButton"
              virtualName="" explicitFocusOrder="0" pos="216 16 150 24" bgColOff="ff5f9ea0"
              buttonText="Play" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="stop btn" id="fa98d3b8f945b706" memberName="stopButton"
              virtualName="" explicitFocusOrder="0" pos="424 16 150 24" bgColOff="ff5f9ea0"
              buttonText="Stop" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="grainsize" id="76a13b107dbbd720" memberName="sliderGrainSize"
          virtualName="" explicitFocusOrder="0" pos="110 304 63 80" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="grainstart" id="56e14d271ca80ac3" memberName="silderGrainStart"
          virtualName="" explicitFocusOrder="0" pos="310 304 63 80" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="grainpitch" id="6f2d9dde86bf0511" memberName="sliderGrainPitch"
          virtualName="" explicitFocusOrder="0" pos="510 304 63 80" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="grainsize" id="d93203ff314e7e67" memberName="labelGrainSize"
         virtualName="" explicitFocusOrder="0" pos="22 328 95 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Grain Size" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="grainstart" id="7a0f9385d28d4e92" memberName="labelGrainStart"
         virtualName="" explicitFocusOrder="0" pos="214 328 95 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Grain Start" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="grainpitch" id="5a334bbc3602666d" memberName="labelGrainPitch"
         virtualName="" explicitFocusOrder="0" pos="430 328 95 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Grain Pitch" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="grainsize" id="9395795607a27fdc" memberName="sliderGrainSize2"
          virtualName="" explicitFocusOrder="0" pos="113 213 63 80" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="grainstart" id="3617b1f8a078f584" memberName="silderGrainStart2"
          virtualName="" explicitFocusOrder="0" pos="313 213 63 80" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="grainpitch" id="f486c91dc2db3156" memberName="sliderGrainPitch2"
          virtualName="" explicitFocusOrder="0" pos="513 213 63 80" min="0.0"
          max="10.0" int="0.0" style="Rotary" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="grainsize" id="9f9ef3b86d7d7874" memberName="labelGrainSize2"
         virtualName="" explicitFocusOrder="0" pos="25 237 95 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Grain Size" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="grainstart" id="42361bdf8298570b" memberName="labelGrainStart2"
         virtualName="" explicitFocusOrder="0" pos="217 237 95 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Grain Start" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="grainpitch" id="6b3840ff064d84fb" memberName="labelGrainPitch2"
         virtualName="" explicitFocusOrder="0" pos="433 237 95 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Grain Pitch" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

