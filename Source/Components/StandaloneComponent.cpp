/*
 *  StandaloneComponent.cpp
 *  audio_playhead3
 *
 *  Created by Matt Sonic on 5/7/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#include "TransportComponent.h"

#include "StandaloneComponent.h"

StandaloneComponent::StandaloneComponent (AudioProcessorEditor* audioProcessorEditor_) :
Component ("StandaloneComponent"),
audioProcessorEditor (audioProcessorEditor_),
transportComponent (0)
{
	addAndMakeVisible (transportComponent = new TransportComponent (audioProcessorEditor->getAudioProcessor()));
	addAndMakeVisible (audioProcessorEditor);
	
	setSize (600, 400);
}

StandaloneComponent::~StandaloneComponent()
{
	deleteAndZero (transportComponent);
}

AudioProcessorEditor* StandaloneComponent::getAudioProcessorEditor()
{
	return audioProcessorEditor;
}

// Component methods
void StandaloneComponent::paint (Graphics& g)
{
}

void StandaloneComponent::resized()
{
	transportComponent->setBounds (0, 0, getWidth(), 50);
	audioProcessorEditor->setBounds (0, 50, getWidth(), getHeight() - 50);
}

