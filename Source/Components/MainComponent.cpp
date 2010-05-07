/*
 *  MainComponent.cpp
 *  audio_playhead2
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
		<< "Framerate: " << String (pos.frameRate) << "\n" // Shows '99' in Live 8
		<< "Timecode String: " << timeToTimecodeString (pos.timeInSeconds) << "\n"
		<< "Bars, Beats, & Ticks: " << ppqToBarsBeatsString (pos.ppqPosition, pos.timeSigNumerator,
													 pos.timeSigDenominator) << "\n";
		
		positionLabel->setText (displayText, false);
	}
}

// Time conversion methods
const String MainComponent::timeToTimecodeString (const double seconds)
{
	const double absSecs = fabs (seconds);
	
	const int hours = (int) (absSecs / (60.0 * 60.0));
	const int mins = ((int) (absSecs / 60.0)) % 60;
	const int secs = ((int) absSecs) % 60;
						  
	String s;
	if (seconds < 0) {
		s = "-";
	}
	
	s 
	<< String (hours).paddedLeft ('0', 2) << ":"
	<< String (mins).paddedLeft ('0', 2) << ":"
	<< String (secs).paddedLeft ('0', 2) << ":"
	<< String (roundToInt (absSecs * 1000) % 1000).paddedLeft ('0', 3);
	
	return s;
}

const String MainComponent::ppqToBarsBeatsString (double ppq, int numerator, 
												  int denominator)
{
	if (numerator == 0 || denominator == 0) {
		return "1|1|0";
	}
	
	const int ppqPerBar = (numerator * 4 / denominator); // e.g. 4 if 4/4
	const double beats = (fmod (ppq, ppqPerBar) / ppqPerBar) * numerator;
	
	const int bar = ((int) ppq) / ppqPerBar + 1;
	const int beat = ((int) beats) + 1;
	const int ticks = ((int) (fmod (beats, 1.0) * 960.0));
	
	String s;
	s << bar << '|' << beat << '|' << ticks;

	return s;
}






