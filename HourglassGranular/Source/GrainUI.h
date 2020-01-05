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



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GrainUI  : public Component,
                 public ChangeListener,
                 public Timer,
                 public ValueTree::Listener,
                 public Button::Listener,
                 public Slider::Listener
{
public:
    //==============================================================================
    GrainUI (HourglassGranularAudioProcessor& proc, JuicyClouds* x, AudioProcessorValueTreeState& vts);
    ~GrainUI() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

	void loadSample(File file);
	void timerCallback() override;
	//void assignGrainProcessor(JuicyClouds * processor);
	/*
	void assignGrainProcessor(JuicyClouds* processor)
	{
		m_grainProcessor = processor;
	}
	*/
	void browseSample();
	void changeListenerCallback(ChangeBroadcaster * source) override;
	void valueTreePropertyChanged(ValueTree & treeWhosePropertyHasChanged, const Identifier & property) override;
	void valueTreeChildRemoved(ValueTree & parentTree, ValueTree & childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;
	void valueTreeChildOrderChanged(ValueTree & parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;
	void valueTreeParentChanged(ValueTree & treeWhoseParentHasChanged) override;
	void valueTreeChildAdded(ValueTree & parentTree, ValueTree & childWhichHasBeenAdded) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void filesDropped (const StringArray& filenames, int mouseX, int mouseY) override;
    void mouseUp (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    HourglassGranularAudioProcessor& m_processor;
    JuicyClouds* m_grainProcessor;
    AudioFormatManager m_formatManager;
	AudioThumbnailCache m_thumbnailCache;
	AudioThumbnail m_sampleThumbnail;

	AudioProcessorValueTreeState& m_valueTreeState;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> loadButton;
    std::unique_ptr<TextButton> playButton;
    std::unique_ptr<TextButton> stopButton;
    std::unique_ptr<Slider> sliderGrainSize;
    std::unique_ptr<Slider> silderGrainStart;
    std::unique_ptr<Slider> sliderGrainPitch;
    std::unique_ptr<Label> labelGrainSize;
    std::unique_ptr<Label> labelGrainStart;
    std::unique_ptr<Label> labelGrainPitch;
    std::unique_ptr<Slider> sliderGrainSize2;
    std::unique_ptr<Slider> silderGrainStart2;
    std::unique_ptr<Slider> sliderGrainPitch2;
    std::unique_ptr<Label> labelGrainSize2;
    std::unique_ptr<Label> labelGrainStart2;
    std::unique_ptr<Label> labelGrainPitch2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GrainUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

