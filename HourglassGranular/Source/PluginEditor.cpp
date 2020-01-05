/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
HourglassGranularAudioProcessorEditor::HourglassGranularAudioProcessorEditor(HourglassGranularAudioProcessor& p, AudioProcessorValueTreeState& vts)
	:
	AudioProcessorEditor(&p),
	processor(p),
	m_grainChannel1(p,vts),
	m_valueTreeState(vts)
{
	m_grainChannel1.assignGrainProcessor(processor.getGranularProcessor());
	addAndMakeVisible(m_grainChannel1);
	m_grainChannel1.setBounds (0, 150, 600, 350);

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
    noiseGateSlider->setRange (0, 100, 1);
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
    
    m_midiTrigAttach.reset(new ButtonAttachment(m_valueTreeState, "midiToggle", *bpmToggle.get()));
    m_convTrigAttach.reset(new ButtonAttachment(m_valueTreeState, "convToggle", *convToggle.get()));
    m_inputAttach.reset(new SliderAttachment(m_valueTreeState, "inputGain", *inputSlider.get()));
    m_outputAttach.reset(new SliderAttachment(m_valueTreeState, "outputGain", *outputSlider.get()));
    m_gateAttach.reset(new SliderAttachment(m_valueTreeState, "noiseGate", *noiseGateSlider.get()));
    m_tempoDivisionAttachment.reset(new SliderAttachment(m_valueTreeState, "tempoDivision", *bpmDivSlider.get()));
    m_masterTempoAttachment.reset(new SliderAttachment(m_valueTreeState, "masterTempo", *bpmSlider.get()));
    
    setSize (600, 500);
}

HourglassGranularAudioProcessorEditor::~HourglassGranularAudioProcessorEditor()
{

}

//==============================================================================
void HourglassGranularAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colour (0xff323e44));
}

void HourglassGranularAudioProcessorEditor::resized()
{	
}

void HourglassGranularAudioProcessorEditor::mouseUp(const MouseEvent& e){m_grainChannel1.mouseUp(e);}


void HourglassGranularAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
}

void HourglassGranularAudioProcessorEditor::buttonClicked(Button* button)
{
}




