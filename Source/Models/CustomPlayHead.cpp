/*
 *  CustomPlayHead.cpp
 *  audio_playhead4
 *
 *  Created by Matt Sonic on 5/7/10.
 *  Copyright 2010 SonicTransfer. All rights reserved.
 *
 */

#include "CustomPlayHead.h"


CustomPlayHead::CustomPlayHead (AudioProcessor* audioProcessor) :
AudioProcessorCallback (audioProcessor),
sampleRate (0),
bpm (120),
timeSigNumerator (4),
timeSigDenominator (4),
timeInSeconds (0),
ppqPosition (0),
ppqPositionOfLastBarStart (0),
playing (false),
recording (false)
{
	setBPM (bpm);
}

CustomPlayHead::~CustomPlayHead()
{
}

void CustomPlayHead::play()
{
	reset();
	playing = true;
}

void CustomPlayHead::stop()
{
	reset();
	playing = false;
}

void CustomPlayHead::reset()
{
	timeInSeconds = 0;
	ppqPosition = 0;
	ppqPositionOfLastBarStart = 0;
}

bool CustomPlayHead::isPlaying()
{
	return playing;
}

double CustomPlayHead::getBPM()
{
	return bpm;
}

void CustomPlayHead::setBPM (double bpm_)
{
	bpm = bpm_;
	
	double beatsPerSec = bpm / 60.0;
	secPerBeat = 1.0 / beatsPerSec;
	
	ppqPerBar = (timeSigNumerator * 4 / timeSigDenominator);
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
	pos.isPlaying = playing;
	pos.isRecording = recording;
 
	pos.editOriginTime = 0;
	pos.frameRate = AudioPlayHead::fpsUnknown;
	
	return true;	
}

// AudioProcessorCallback methods
void CustomPlayHead::prepareToPlay (double sampleRate_, int samplesPerBlock)
{
	sampleRate = sampleRate_;
}

void CustomPlayHead::releaseResources()
{
}

void CustomPlayHead::processBlock (AudioSampleBuffer& buffer,
								   MidiBuffer& midiMessages)
{
	if (! playing) {
		return;
	}
	
	timeInSeconds += buffer.getNumSamples() / sampleRate;
	ppqPosition = timeInSeconds / secPerBeat;
	ppqPositionOfLastBarStart = (((int) ppqPosition) / ppqPerBar) * ppqPerBar;	
}



