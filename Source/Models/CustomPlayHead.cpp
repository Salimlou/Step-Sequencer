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
AudioProcessorCallback (audioProcessor)
{
}

CustomPlayHead::~CustomPlayHead()
{
}

// AudioPlayHead methods
bool CustomPlayHead::getCurrentPosition (CurrentPositionInfo& pos)
{
	pos.bpm = 128;
	
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



