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
	mOutputVolumeSlider.setLookAndFeel(nullptr);
	mSelectorBox.setLookAndFeel(nullptr);
    mInputVolumeSlider.setLookAndFeel(nullptr);
    
}

//==============================================================================
void DistortionAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}
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
	selectorBox.items.addArray({
								makeLabel(mSelectorLabel),
								makeLabel(mSelectorBox)
								});
    
	// MASTER ================================
	FlexBox masterBox;
	masterBox.alignContent = FlexBox::AlignContent::center;
	masterBox.justifyContent = FlexBox::JustifyContent::spaceAround;
	masterBox.flexDirection = FlexBox::Direction::row;
	masterBox.items.addArray({
							   FlexItem(gainBox).withFlex(1),
							   FlexItem(selectorBox).withFlex(1),
							   FlexItem(volumeBox).withFlex(1)
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
	// INPUT VOLUME =================================
	// Label
	mInputVolumeLabel.setText("Gain", dontSendNotification);
	mInputVolumeLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mInputVolumeLabel);

	// Slider
	mInputVolumeSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mInputVolumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, mTextBoxWidth, mTextBoxHeight);
    mInputVolumeSlider.setLookAndFeel(&knobLookAndFeel);
	mInputVolumeSlider.setTextValueSuffix(" dB");
	mInputVolumeAttachment.reset(new SliderAttachment(mParameter, IDs::inputVolume, mInputVolumeSlider));
	addAndMakeVisible(mInputVolumeSlider);

	//	COSAS DEL SELECTOR	==========================
	//	label
	mSelectorLabel.setText("Tipo", dontSendNotification);
	mSelectorLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mSelectorLabel);

	//	ComboBox
	mSelectorBox.setText("Tipo", dontSendNotification);
	mSelectorBox.setJustificationType(Justification::centred);
	mSelectorBox.addItem("gScreamer", 1);
	mSelectorBox.addItem("trebleBrigther", 2);
	mSelectorBox.addItem("bSquasher", 3);
	mSelectorBox.setSelectedId(1);

	//	aqui se me lia jaja ==========================
	// 
	//	bueno, "ComboBoxParameterAttachment" me pide un parametro "RangedAudioParameter".
	//	a diferencia de los otros attachments que piden "AudioProcessorValueTreeState".
	// 
	//		lo que hacemos es sacar el parametro declarado en la clase pluginProcessor y-
	//		castearlo para que se convierta en "AudioParameterChoice", la cual es una- 
	//		clase hija de"RangedAudioParameter" y puede ser usada por el comboBoxParameter.
	//
	auto* selectorParam = dynamic_cast<juce::AudioParameterChoice*>(mParameter.getParameter("selector"));
	
	mSelectorAttachment.reset(new juce::ComboBoxParameterAttachment(*selectorParam, mSelectorBox));
	addAndMakeVisible(mSelectorBox);
	
	// OUTPUT VOLUME ==================================
	// Label
    mOutputVolumeLabel.setText("Level", dontSendNotification);
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
