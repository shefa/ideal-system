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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]

#include ""


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UI  : public AudioProcessorEditor,
            public Timer,
            public Slider::Listener,
            public Button::Listener
{
public:
    //==============================================================================
    UI (HourglassGranularAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~UI() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
	void timerCallback() override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::unique_ptr<SliderAttachment> m_masterTempoAttachment;
	std::unique_ptr<SliderAttachment> m_tempoDivisionAttachment;
	std::unique_ptr<ButtonAttachment> m_midiTrigAttach;
	std::unique_ptr<ButtonAttachment> m_convTrigAttach;
	AudioProcessorValueTreeState& m_valueTreeState;
	HourglassGranularAudioProcessor& processor;
    //[/UserVariables]

    //==============================================================================
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
    std::unique_ptr<Component> component;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

