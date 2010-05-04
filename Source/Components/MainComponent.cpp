/*
 *  MainComponent.cpp
 *  plugin_template1
 *
 *  Created by Matt Sonic on 5/4/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#include "PluginAudioProcessor.h"

#include "MainComponent.h"

MainComponent::MainComponent (PluginAudioProcessor* pluginAudioProcessor_) :
Component ("MainComponent"),
pluginAudioProcessor (pluginAudioProcessor_),
gainSlider (0)
{
	addAndMakeVisible (gainSlider = new Slider ("gain"));
	gainSlider->setSliderStyle (Slider::LinearVertical);
	gainSlider->addListener (this);
	gainSlider->setRange (0.0, 1.0, 0.01);
	Label* l = new Label ("", "Gain level:");
	l->attachToComponent (gainSlider, false);
	l->setFont (Font (11.0f));

	startTimer (50);
}

MainComponent::~MainComponent()
{
	deleteAllChildren();
}

// Component methods
void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!",
                      0, 0, getWidth(), getHeight(),
                      Justification::centred, 1);	
}

void MainComponent::resized()
{
	gainSlider->setBounds (getWidth() - 160, 20, 150, getHeight() - 40);
	
}

// Timer methods
void MainComponent::timerCallback()
{
	gainSlider->setValue (pluginAudioProcessor->gain, false);
}

// SliderListener methods
void MainComponent::sliderValueChanged (Slider* slider)
{
	if (slider == gainSlider) {
		pluginAudioProcessor->setParameterNotifyingHost (PluginAudioProcessor::gainParam, 
														 (float) gainSlider->getValue());
	}
}



