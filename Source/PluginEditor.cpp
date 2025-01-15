/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionAudioProcessorEditor::DistortionAudioProcessorEditor (DistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), mParameter(p.getState())
{
    setSize (350, 150);
	initialiseGUI();
}

//==============================================================================
DistortionAudioProcessorEditor::~DistortionAudioProcessorEditor()
{
	// Set the LOF of all sliders to nullptr
    mInputVolumeSlider.setLookAndFeel(nullptr);
	mSelector.setLookAndFeel(nullptr);
    mOutputVolumeSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void DistortionAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

//==============================================================================
// Components are added in the resized-method with FlexBox.
// Input parameters:
//		LEVEL: output volume of the effect chain
//		LOW	 : frequency of a lowpass filter after the waveshaper
//		HIGH : frequency of a highpass filter before the waveshaper
//		DIS	 : input volume of the effects chain
//
//==============================================================================
void DistortionAudioProcessorEditor::resized()
{
	// LEVEL==================================
    FlexBox volumeBox;
    volumeBox.alignContent = FlexBox::AlignContent::center;
    volumeBox.justifyContent = FlexBox::JustifyContent::center;
    volumeBox.flexDirection = FlexBox::Direction::column;
    volumeBox.items.addArray({
							  makeLabel(mOutputVolumeLabel),
                              makeRotarySlider(mOutputVolumeSlider)
							  });

	// DIST ==================================
	FlexBox gainBox;
	gainBox.alignContent = FlexBox::AlignContent::center;
	gainBox.justifyContent = FlexBox::JustifyContent::center;
	gainBox.flexDirection = FlexBox::Direction::column;
	gainBox.items.addArray({ 
							 makeLabel(mInputVolumeLabel),
							 makeRotarySlider(mInputVolumeSlider)
							});

	// selector ==================================
	FlexBox selectorBox;
	selectorBox.alignContent = FlexBox::AlignContent::center;
	selectorBox.justifyContent = FlexBox::JustifyContent::center;
	selectorBox.flexDirection = FlexBox::Direction::column;
    
	// MASTER ================================
	FlexBox masterBox;
	masterBox.alignContent = FlexBox::AlignContent::center;
	masterBox.justifyContent = FlexBox::JustifyContent::spaceAround;
	masterBox.flexDirection = FlexBox::Direction::row;
	masterBox.items.addArray({
							   FlexItem(volumeBox).withFlex(1),
							   FlexItem(selectorBox).withFlex(1),
							   FlexItem(gainBox).withFlex(1)
                             });

	masterBox.performLayout(getLocalBounds().reduced(20, 20).toFloat());
}

//==============================================================================
FlexItem DistortionAudioProcessorEditor::makeRotarySlider(Component & c)
{
	return FlexItem(c).withMinWidth(static_cast<float>(mSliderSize)).withMinHeight(static_cast<float>(mSliderSize));
}

//==============================================================================
FlexItem DistortionAudioProcessorEditor::makeLabel(Component & c)
{
	return FlexItem(c).withMinWidth(static_cast<float>(c.getWidth())).withMinHeight(20);
}

//==============================================================================
void DistortionAudioProcessorEditor::initialiseGUI()
{
	// INPUT VOLUME ================================
	// Label
	mInputVolumeLabel.setText("MI MOTORA", dontSendNotification);
	mInputVolumeLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mInputVolumeLabel);

	// Slider
	mInputVolumeSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mInputVolumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, mTextBoxWidth, mTextBoxHeight);
    mInputVolumeSlider.setLookAndFeel(&knobLookAndFeel);
	mInputVolumeSlider.setTextValueSuffix(" dB");
	mInputVolumeAttachment.reset(new SliderAttachment(mParameter, IDs::inputVolume, mInputVolumeSlider));
	addAndMakeVisible(mInputVolumeSlider);

	//	ComboBox
	mSelector.setText("selector", dontSendNotification);
	mSelector.setJustificationType(Justification::centred);
	mSelector.addItem("gScreamer", 1);
	mSelector.addItem("trebleBrigther", 2);
	mSelector.addItem("bSquasher", 3);
	addAndMakeVisible(mSelector);


	/** LOWPASS FILTER =================================
	// Label
	mLowPassLabel.setText("LOW", dontSendNotification);
	mLowPassLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mLowPassLabel);
	// Slider
	mLowPassSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mLowPassSlider.setTextBoxStyle(Slider::TextBoxBelow, false, mTextBoxWidth, mTextBoxHeight);
	mLowPassSlider.setTextValueSuffix(" Hz");
	mLowPassSlider.setLookAndFeel(&knobLookAndFeel);
	mLowPassAttachment.reset(new SliderAttachment(mParameter, IDs::LPFreq, mLowPassSlider));
	addAndMakeVisible(mLowPassSlider);

	// HIGHPASS FILTER =================================
	// Label
	mHighPassLabel.setText("HIGH", dontSendNotification);
	mHighPassLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mHighPassLabel);

	// Slider
	mHighPassSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mHighPassSlider.setTextBoxStyle(Slider::TextBoxBelow, false, mTextBoxWidth, mTextBoxHeight);
	mHighPassSlider.setTextValueSuffix(" Hz");
	mHighPassSlider.setLookAndFeel(&knobLookAndFeel);
	mHighPassAttachment.reset(new SliderAttachment(mParameter, IDs::HPFreq, mHighPassSlider));
	addAndMakeVisible(mHighPassSlider); **/
	
	// OUTPUT VOLUME ==================================
	// Label
    mOutputVolumeLabel.setText("ganancia", dontSendNotification);
    mOutputVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(mOutputVolumeLabel);
   // Slider 
    mOutputVolumeSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    mOutputVolumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, mTextBoxWidth, mTextBoxHeight);
    mOutputVolumeSlider.setLookAndFeel(&knobLookAndFeel);
	mOutputVolumeSlider.setTextValueSuffix(" dB");
    mOutputVolumeAttachment.reset(new SliderAttachment(mParameter, IDs::outputVolume, mOutputVolumeSlider));
    addAndMakeVisible(mOutputVolumeSlider);
}
