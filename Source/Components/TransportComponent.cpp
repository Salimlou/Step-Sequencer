/*
 *  TransportComponent.cpp
 *  audio_playhead3
 *
 *  Created by Matt Sonic on 5/7/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#include "CustomPlayHead.h"

#include "TransportComponent.h"

TransportComponent::TransportComponent (AudioProcessor* audioProcessor_) :
Component ("TransportComponent"),
audioProcessor (audioProcessor_),
bpmSlider (0),
playButton (0)
{
	addAndMakeVisible (bpmSlider = new Slider ("bpmSlider"));
	bpmSlider->setSliderStyle (Slider::RotaryVerticalDrag);
	bpmSlider->setValue (128.0, true, false);
	bpmSlider->setTextBoxStyle (Slider::TextBoxRight, false, 100, 20);
	bpmSlider->addListener (this);
	
	addAndMakeVisible (playButton = new TextButton ("Play"));
	playButton->addButtonListener (this);
}

TransportComponent::~TransportComponent()
{
	deleteAllChildren();
}

// Component methods
void TransportComponent::paint (Graphics& g)
{
	g.fillAll (Colour::fromRGB (230, 230, 250));
}

void TransportComponent::resized()
{
	bpmSlider->setBounds (110, 10, 200, 30);
	playButton->setBounds (10, 10, 100, 30);
}

// ButtonListener methods
void TransportComponent::buttonClicked (Button* button)
{
	if (button == playButton) {
		CustomPlayHead* customPlayHead = dynamic_cast<CustomPlayHead*> (audioProcessor->getPlayHead());
		if (customPlayHead != 0) {
			customPlayHead->play();
		}
	}
}

// SliderListener methods
void TransportComponent::sliderValueChanged (Slider* slider)
{
	if (slider == bpmSlider) {
	}
}

