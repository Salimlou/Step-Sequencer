/*
 *  MainComponent.cpp
 *  audio_playhead1
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
positionLabel (0)
{
	addAndMakeVisible (positionLabel = new Label ("positionLabel", "Position"));
	positionLabel->setColour (Label::textColourId, Colours::blue);
	
	startTimer (50);
}

MainComponent::~MainComponent()
{
	deleteAllChildren();
}

// Component methods
void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey);
}

void MainComponent::resized()
{
	positionLabel->setBoundsInset (BorderSize (10));
}

// Timer methods
void MainComponent::timerCallback()
{
	AudioPlayHead::CurrentPositionInfo pos (pluginAudioProcessor->lastPosInfo);
	
	if (lastDisplayedPosition != pos) {
		lastDisplayedPosition = pos;
		String displayText;
		displayText.preallocateStorage (64);
		
		displayText 
		<< "BPM: " << String (pos.bpm, 2) << "\n"
		<< "Time Sig: " << pos.timeSigNumerator << "/" << pos.timeSigDenominator << "\n"
		<< "Recording: " << String (pos.isRecording) << "\n" // Doesn't work in Live 8
		<< "Playing: " << String (pos.isPlaying) << "\n" 
		<< "Time In Seconds: " << String (pos.timeInSeconds) << "\n"
		<< "PPQ Position: " << String (pos.ppqPosition) << "\n"
		<< "PPQ Position of Last Bar Start: " << String (pos.ppqPositionOfLastBarStart) << "\n"
		<< "Edit Origin Time: " << String (pos.editOriginTime) << "\n" // Doesn't work in Live 8
		<< "Framerate: " << String (pos.frameRate) << "\n"; // Shows '99' in Live 8
	
		positionLabel->setText (displayText, false);
	}
}






