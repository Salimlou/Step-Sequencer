/*
 *  CustomPlayHead.cpp
 *  audio_playhead3
 *
 *  Created by Matt Sonic on 5/7/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#include "CustomPlayHead.h"


CustomPlayHead::CustomPlayHead (AudioProcessor* audioProcessor) :
AudioProcessorCallback (audioProcessor),
bpm (128),
timeSigNumerator (4),
timeSigDenominator (4),
timeInSeconds (0),
ppqPosition (0),
ppqPositionOfLastBarStart (0),
isPlaying (false),
isRecording (false)
{
}

CustomPlayHead::~CustomPlayHead()
{
}

void CustomPlayHead::play()
{
	isPlaying = true;
}

// AudioPlayHead methods
bool CustomPlayHead::getCurrentPosition (CurrentPositionInfo& pos)
{
	pos.bpm = bpm;
	pos.timeSigNumerator = timeSigNumerator;
	pos.timeSigDenominator = timeSigDenominator;
	pos.timeInSeconds = timeInSeconds;
	pos.ppqPosition = ppqPosition;
	pos.ppqPositionOfLastBarStart = ppqPositionOfLastBarStart;
	pos.isPlaying = isPlaying;
	pos.isRecording = isRecording;
 
	pos.editOriginTime = 0;
	pos.frameRate = AudioPlayHead::fpsUnknown;
	
	return true;	
}

// AudioProcessorCallback methods
void CustomPlayHead::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void CustomPlayHead::releaseResources()
{
}

void CustomPlayHead::processBlock (AudioSampleBuffer& buffer,
								   MidiBuffer& midiMessages)
{
}



