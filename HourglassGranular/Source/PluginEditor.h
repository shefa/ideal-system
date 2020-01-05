/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GrainChannelComponent.h"

//==============================================================================
/**
*/
class HourglassGranularAudioProcessorEditor : public AudioProcessorEditor, public Slider::Listener, public Button::Listener
{
public:
    HourglassGranularAudioProcessorEditor (HourglassGranularAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~HourglassGranularAudioProcessorEditor();

    //==============================================================================

	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

	void mouseUp(const MouseEvent& e) override;
	void paint (Graphics&) override;
    void resized() override;
	void sliderValueChanged(Slider* slider) override; 
	void buttonClicked(Button* button) override;
private:
	GrainChannelComponent m_grainChannel1;
	std::unique_ptr<Slider> bpmSlider;
    std::unique_ptr<Label> bpmLabel;
    std::unique_ptr<Slider> bpmDivSlider;
    std::unique_ptr<Label> bpmDivLabel;
    std::unique_ptr<ToggleButton> convToggle;
    std::unique_ptr<ToggleButton> bpmToggle;
    std::unique_ptr<Slider> inputSlider;
    std::unique_ptr<Label> inputLabel;
    std::unique_ptr<Slider> outputSlider;
    std::unique_ptr<Label> outputLabel;
    std::unique_ptr<Slider> noiseGateSlider;
    std::unique_ptr<Label> noiseGateLabel;

	std::unique_ptr<SliderAttachment> m_masterTempoAttachment;
	std::unique_ptr<SliderAttachment> m_tempoDivisionAttachment;
	std::unique_ptr<ButtonAttachment> m_midiTrigAttach;
	std::unique_ptr<SliderAttachment> m_gateAttach;
    std::unique_ptr<SliderAttachment> m_inputAttach;
    std::unique_ptr<SliderAttachment> m_outputAttach;
	std::unique_ptr<ButtonAttachment> m_convTrigAttach;

	AudioProcessorValueTreeState& m_valueTreeState;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HourglassGranularAudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HourglassGranularAudioProcessorEditor)
};
