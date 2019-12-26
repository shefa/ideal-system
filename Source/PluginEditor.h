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
#include "GrainContentComponent.h"
#include "SpectrogramContentComponent.h"
#include "Conv/ConvolutionDemo.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MmcwAudioProcessorEditor  : public AudioProcessorEditor,
                                  public Timer,
                                  public Slider::Listener,
                                  public Button::Listener
{
public:
    //==============================================================================
    MmcwAudioProcessorEditor (MmcwAudioProcessor& ownerFilter, AudioProcessorValueTreeState& vts);
    ~MmcwAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void timerCallback() override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	//GrainContentComponent m_grainComponent;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_inputSliderAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_outputSliderAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_noiseGateAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_bpmAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> m_bpmDivAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> m_bpmToggleAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> m_convToggleAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> m_fftToggleAttachment;

	AudioProcessorValueTreeState& m_valueTreeState;
	MmcwAudioProcessor& processor;
	SpectrogramContentComponent m_spectComponent;

	//ConvolutionDemo convolutionComponent;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> inputSlider;
    std::unique_ptr<Label> inputLabel;
    std::unique_ptr<Slider> outputSlider;
    std::unique_ptr<Label> outputLabel;
    std::unique_ptr<Slider> noiseGateSlider;
    std::unique_ptr<Label> noiseGateLabel;
    std::unique_ptr<TabbedComponent> tabbedComponent;
    std::unique_ptr<Slider> bpmSlider;
    std::unique_ptr<Label> bpmLabel;
    std::unique_ptr<ToggleButton> bpmToggle;
    std::unique_ptr<Slider> bpmDivSlider;
    std::unique_ptr<Label> bpmDivLabel;
    std::unique_ptr<ToggleButton> ConvToggle;
    std::unique_ptr<ToggleButton> fftToggle;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MmcwAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

